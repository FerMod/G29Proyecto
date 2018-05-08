
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

Heart heart[MAX_LIFES];
int lives = MAX_LIFES;

// Pickup pickup[MAX_PICKUPS];
// int numberPickups = 0;
Pickup pickup;
bool pickupCreated = false;

void createSprite(int index, int x, int y) {
	MostrarBillete(index, x, y);
	numberSprites++;
	increaseSpawnedMoney();
	scheduleOamMainUpdate();
}

void deleteSprite(int index) {
	hideSprite(index);
	numberSprites--;
	scheduleOamMainUpdate();
}

void createHearts() {
	int spriteIndex = 127 - MAX_LIFES;
	int separation = 0;
	int i;
	for (i = 0; i < MAX_LIFES; i++) {
		heart[i].index = spriteIndex + i;
		heart[i].isFull = true;
		separation += 2;
		showHeart(heart[i].index, (i * 16) + separation, 2, heart[i].isFull);
	}
}

void updateHearts() {
	int separation = 0;
	int i;
	for (i = 0; i < MAX_LIFES; i++) {
		heart[i].isFull = i < lives;
		separation += 2;
		showHeart(heart[i].index, (i * 16) + separation, 2, heart[i].isFull);
	}
}

void deleteHearts() {
	int i;
	for (i = 0; i < MAX_LIFES; i++) {
		hideSprite(heart[i].index);
	}
}

void createPickup() {
	// bool pickupCreated = false;
	// int spriteIndex = MAX_MONEY_SPRITES;
	// int i;
	// for (i = 0; i < MAX_PICKUPS || !pickupCreated; i++) {
	// 	// Let it have a % chance to appear
	// 	if(getRandValue(1, 1000) <= 1) {
	// 		pickupCreated = true;
	// 		pickup[i].index = spriteIndex + i;
	// 		pickup[i].type = HEALTH;
	// 		showPickup(pickup[i].index, getRandValue(8, 240), 0, pickup[i].type);
	// 		numberPickups++;
	// 	}
	// }

	// Blue shell effect
	// Less lives, gives more healing chances
 	if(!pickupCreated && getRandValue(1, 100) <= 5 * (MAX_LIFES - getLives()) ) {
		//pickupCreated = true;
		pickup.index = MAX_MONEY_SPRITES;
		pickup.type = HEALTH;
		showPickup(pickup.index, getRandValue(8, 240), 0, pickup.type);
		pickupCreated = true;
	}
}

void deletePickup(int index) {
	hideSprite(index);
	// numberPickups--;
}

void clearMoneySprites() {
	int i;
	for (i = 0; i < maxSpriteSpawns; i++) {				
		deleteSprite(i);
	}
}

void clearSprites() {
	int i;
	for (i = 0; i < 127; i++) {
		hideSprite(i);
	}
	numberSprites = 0;
}

void setMaxSpriteSpawns(int max) {
	if(max > MAX_MONEY_SPRITES) {
		maxSpriteSpawns = MAX_MONEY_SPRITES;
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
	for (i = 0; i < MAX_MONEY_SPRITES; i++) {
		//Sprite* sprite = spriteArray[i];
		//iprintf("Sprite[%d] = (x:%d, y:%d)\x1b[0m\n", i, sprite->x, sprite->y);
	}
}

void scheduleSpriteMove() {
	moveScheduled = true;
}

void moveSprites() {

	if(moveScheduled) {		
		moveMoney();
		movePickups();
		moveScheduled = false;
	}

}

void moveMoney() {
	int i;
	for (i = 0; i < maxSpriteSpawns; i++) {
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
				deleteSprite(i);
				decreaseLives();
				updateHearts();
			}
			
			scheduleOamMainUpdate();

			//MostrarBillete(i, spriteEntry->x, spriteEntry->y);
		}
	}
}

void movePickups() {

	// if(numberPickups > 0) {
		// int i;
		// for (i = 0; i < MAX_PICKUPS; i++) {

			// SpriteEntry* spriteEntry = &oamMain.oamMemory[pickup[i].index];	
			if(pickupCreated) {
				SpriteEntry* spriteEntry = &oamMain.oamMemory[MAX_MONEY_SPRITES];	

				if(!spriteEntry->isHidden) {	
					
					spriteEntry->y += 8;

					if(!canSpriteMoveY(spriteEntry->y)) {
						// deletePickup(i);
						deletePickup(pickup.index);
					}
					
					scheduleOamMainUpdate();
				}
			}
		// }
	// }

}

void scheduleSpriteSpawn() {
	spawnScheduled = true;
}

bool isSpriteSpawnScheduled() {
	return spawnScheduled;
}

void spriteSpawns(){

	iprintf("\x1b[08;01H\x1b[39m Sprites:%d spawnScheduled:%5s", numberSprites, spawnScheduled ? "\x1b[42mtrue" : "\x1b[41mfalse");

	int i;
	for (i = 0; i < maxSpriteSpawns && spawnScheduled; i++) {				
		SpriteEntry* spriteEntry = &oamMain.oamMemory[i];
		if(spriteEntry->isHidden) {
			spawnScheduled = false;
			createSprite(i, getRandValue(8, 240), 0);
			createPickup();
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
	checkPlayerTouchMoney();
	checkPlayerTouchPickup();
}

void checkPlayerTouchMoney() {

	SpriteEntry*  playerSprite = &oamMain.oamMemory[PLAYER_SPRITE];

	int i;
	for (i = 0; i < maxSpriteSpawns; i++) {

		SpriteEntry* moneySprite = &oamMain.oamMemory[i]; //Sprite with id = i

		printPickUpText(6, 2, checkSpriteOverlap(playerSprite, moneySprite));
		if(!moneySprite->isHidden && checkSpriteOverlap(playerSprite, moneySprite)) {
			deleteSprite(i);
			increaseScore();
			increasePickedUpMoney();
		}

	}

}

void checkPlayerTouchPickup() {
	
	if(pickupCreated) {
		SpriteEntry*  playerSprite = &oamMain.oamMemory[PLAYER_SPRITE];

		// int i;
		// for (i = 0; i < MAX_PICKUPS; i++) {

		// 	SpriteEntry* pickupSprite = &oamMain.oamMemory[pickup[i].index]; //Sprite with id = i

		SpriteEntry* pickupSprite = &oamMain.oamMemory[MAX_MONEY_SPRITES];
		printPickUpText(6, 2, checkSpriteOverlap(playerSprite, pickupSprite));
		if(!pickupSprite->isHidden && checkSpriteOverlap(playerSprite, pickupSprite)) {
			pickupCreated = false;
			applyPickupEffect(MAX_MONEY_SPRITES);
			deleteSprite(MAX_MONEY_SPRITES);
		}

		// 	printPickUpText(10, 2, checkSpriteOverlap(playerSprite, pickupSprite));
		// 	if(!pickupSprite->isHidden && checkSpriteOverlap(playerSprite, pickupSprite)) {
		// 		applyPickupEffect(i);
		// 		deleteSprite(i);
		// 	}

		// }
	}

}

void applyPickupEffect(int index) {

	//switch(pickup[index].type) {
	switch(pickup.type) {
		case HEALTH:
			increaseLives();
			updateHearts();
			break;
		case CLEAR:
			clearMoneySprites();
			break;
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

//TODO: Remove
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

int getLives() {
	return lives;
}

void setLives(int num) {
	lives = num;
}

int getMaxLifes() {
	return MAX_LIFES;
}

void increaseLives() {
	if(lives < MAX_LIFES){
		lives++;
	}
}

void decreaseLives() {
	if(lives > 0){
		lives--;
	}
}

bool isGameOver() {
	return gameOver || lives <= 0;
}

void setGameOver(bool b) {
	gameOver = b;
}
