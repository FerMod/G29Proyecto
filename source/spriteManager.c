
/*-------------------------------------
 spriteManager.c
-------------------------------------*/

#include "spriteManager.h"

#include <nds.h>
#include <stdio.h>

#include "sprites.h"

Sprite* spriteArray[MAX_SPRITES];

int numberSprites = 0;

void createSprite(int index, int x, int y) {
	
	Sprite* sprite = malloc(sizeof(*sprite));
	sprite->x = x;
	sprite->y = y;

	spriteArray[index] = sprite;

	MostrarBillete(index, x, y);

	numberSprites++;
}

void deleteSprite(int index) {
	Sprite* sprite = spriteArray[index];
	BorrarBillete(index, sprite->x, sprite->y);
	spriteArray[index] = NULL;
	numberSprites--;
}

void printInfo() {
	int i;
	for (i = 0; i < MAX_SPRITES; i++) {
		Sprite* sprite = spriteArray[i];
		iprintf("Sprite[%d] = (x:%d, y:%d)\x1b[0m\n", i, sprite->x, sprite->y);
	}
}

void moveSprites() {
	int i;
	for (i = 0; i < 128; i++) {
		SpriteEntry spriteEntry = oamMain.oamMemory[i]; //Sprite with id = i
		if(!spriteEntry.isHidden) {	
			//Update x/y
			Sprite* sprite = spriteArray[i];
			switch(getRandValue(0, 2)) {
				case 0:
					sprite->x = sprite->x+4;
					break;

				case 1:
					sprite->x = sprite->x-4;
					break;
			}
			sprite->y = sprite->y+8;

			createSprite(i, sprite->x, sprite->y);
		}
	}
}

void redrawSprites() {
	int i;
	for (i = 0; i < 128; i++) {
		SpriteEntry spriteEntry = oamMain.oamMemory[i]; //Sprite with id = i
		if(!spriteEntry.isHidden) {	
			//Update x/y
			createSprite(i, spriteEntry.y, spriteEntry.x);
		}
	}
}

int getRandValue(int min, int max) {
	return (rand()%(max-min))+min;
}