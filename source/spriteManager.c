
/*-------------------------------------
 spriteManager.c
-------------------------------------*/

#include "spriteManager.h"

#include <nds.h>
#include <stdio.h>

#include "defines.h"
#include "sprites.h"
#include "teclado.h"
#include "updateScreen.h"
#include "screenText.h"

bool moveScheduled = false;
bool spawnScheduled = false;

bool gameOver = false;

int numberSprites = 0;
int maxSpriteSpawns = 1;

// PlayerInput playerInput = {
// 	0, // x
// 	0 // y
// };

void createSprite(int index, int x, int y) {
	MostrarBillete(index, x, y);
	numberSprites++;
	scheduleOamMainUpdate();
}

void deleteSprite(int index, int x, int y) {
	BorrarBillete(index, x, y);
	numberSprites--;
	scheduleOamMainUpdate();
}

void setMaxSpriteSpawns(int max) {
	if(max > 127) {
		maxSpriteSpawns = 127;
	} else if(max < 0) {
		maxSpriteSpawns = 0;
	} else {
		maxSpriteSpawns = max;
	}
}

int getMaxSpriteSpawns() {
	return maxSpriteSpawns;
}

bool canSpawnSprite() {
	return (numberSprites < maxSpriteSpawns);
}

void printInfo() {
	int i;
	for (i = 0; i < MAX_SPRITES; i++) {
		//Sprite* sprite = spriteArray[i];
		//iprintf("Sprite[%d] = (x:%d, y:%d)\x1b[0m\n", i, sprite->x, sprite->y);
	}
}

void scheduleSpriteMove() {
	moveScheduled = true;
}

void moveSprites() {

	if(moveScheduled) {
		int i;
		//SpriteEntry*  playerSprite = &oamMain.oamMemory[PLAYER_SPRITE];
		for (i = 0; i < numberSprites; i++) {
			if(i != PLAYER_SPRITE) {
				SpriteEntry* spriteEntry = &oamMain.oamMemory[i]; //Sprite with id = i	
				if(!spriteEntry->isHidden) {	
					
					int x = spriteEntry->x;

					// Move random to the left or right, to give more 'leaf' sensation
					switch(getRandValue(0, 2)) {
						case 0:
							//sprite->x = sprite->x+4;
							spriteEntry->x += 4; 
							break;

						case 1:
							//sprite->x = sprite->x-4;
							spriteEntry->x -= 4;
							break;
					}
					spriteEntry->y += 8;

					if(!canSpriteMoveX(spriteEntry->x)) {
						spriteEntry->x = x;
					}

					if(!canSpriteMoveY(spriteEntry->y)) {
						deleteSprite(i, spriteEntry->x, spriteEntry->y);
						//decreasePoints();
						setGameOver(true);
					}
					
					scheduleOamMainUpdate();

					//MostrarBillete(i, spriteEntry->x, spriteEntry->y);
				}
			}
		}
		moveScheduled = false;
	}

}

void scheduleSpriteSpawn() {
	spawnScheduled = true;
}

bool isSpriteSpawnScheduled() {
	return spawnScheduled;
}

void spriteSpawns(){

	iprintf("\x1b[08;01H\x1b[39m Sprites: %d spawn: %5s", numberSprites, spawnScheduled ? "\x1b[42mtrue\x1b[39m" : "\x1b[41mfalse\x1b[39m");

	int i;
	for (i = 0; i < maxSpriteSpawns && spawnScheduled; i++) {				
		SpriteEntry* spriteEntry = &oamMain.oamMemory[i];
		if(spriteEntry->isHidden) {
			spawnScheduled = false;
			createSprite(i, getRandValue(8, 240), 0);
		}
	}

}

void movePlayerSprite() {
	//if(playerInput.x != 0 || playerInput.y != 0) {
	if(tecla != -1) {
		SpriteEntry* spriteEntry = &oamMain.oamMemory[PLAYER_SPRITE];

		int x = spriteEntry->x;
		int y = spriteEntry->y;

		if(tecla == DERECHA) {
			spriteEntry->x++;
		} else if(tecla == IZQUIERDA) {
			spriteEntry->x--;
		}

		if(tecla == ABAJO) {
			spriteEntry->y++;
		} else if(tecla == ARRIBA) {
			spriteEntry->y--;
		}

		bool collision = false; // TODO: Temporal, remove
		if(canSpriteMove(spriteEntry->x, spriteEntry->y)) {
			scheduleOamMainUpdate();
		} else {
			collision = true; // TODO: Temporal, remove
			spriteEntry->x = x;
			spriteEntry->y = y;
		}

		iprintf("\x1b[05;01H x:%3d y:%3d collision: %5s\x1b[0K", x, y, collision ? "\x1b[42mtrue\x1b[39m" : "\x1b[41mfalse\x1b[39m");


	}
}


bool canSpriteMove(int x, int y) {
	return canSpriteMoveX(x) && canSpriteMoveY(y);
}

bool canSpriteMoveX(int x) {
	return !(x < 0 || x > 240);
}

bool canSpriteMoveY(int y) {
	return !(y < 0 || y > 176);
}

void checkPlayerTouch() {
	
	SpriteEntry*  playerSprite = &oamMain.oamMemory[PLAYER_SPRITE];

	int i;
	for (i = 0; i < numberSprites; i++) {

		if(i != PLAYER_SPRITE) {

			SpriteEntry* moneySprite = &oamMain.oamMemory[i]; //Sprite with id = i

			printPickUpText(6, 2, checkSpriteOverlap(playerSprite, moneySprite));
			if(!moneySprite->isHidden && checkSpriteOverlap(playerSprite, moneySprite)) {
				deleteSprite(i, moneySprite->x, moneySprite->y);
				increaseScore();
			}


		}

	}

}


// Source: https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects
bool checkSpriteOverlap(SpriteEntry* sprite1, SpriteEntry* sprite2) {

	float d1x = sprite2->x - (sprite1->x+15);	// d1x = b->min.x - a->max.x;
	float d1y = sprite2->y - (sprite1->y+15);	// d1y = b->min.y - a->max.y;
	float d2x = sprite1->x - (sprite2->x+15);	// d2x = a->min.x - b->max.x;
	float d2y = sprite1->y - (sprite2->y+15);	// d2y = a->min.y - b->max.y;

	if (d1x > 0.0f || d1y > 0.0f) {
		return false;
	} 

	if (d2x > 0.0f || d2y > 0.0f) {
		return false;
	}

	return true;
}

void redrawSprites() {
	int i;
	for (i = 0; i < numberSprites; i++) {
		SpriteEntry spriteEntry = oamMain.oamMemory[i]; //Sprite with id = i
		if(!spriteEntry.isHidden) {	
			//Update x/y
			createSprite(i, spriteEntry.y, spriteEntry.x);
		}
	}
}

bool isGameOver() {
	return gameOver;
}

void setGameOver(bool b) {
	gameOver = b;
}
