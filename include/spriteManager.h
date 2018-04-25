/*-------------------------------------
spriteManager.h
-------------------------------------*/

#ifndef SPRITE_MANAGER_H_   /* Include guard */
#define SPRITE_MANAGER_H_

#define MAX_SPRITES 128

typedef struct Sprites {
	int x;
	int y;
} Sprite;

extern Sprite* spriteArray[MAX_SPRITES];

extern int numberSprites;

extern void createSprite(int index, int x, int y);
//extern void deleteSprite(int index);

extern void printInfo();

extern void moveSprites();

// extern void spawnSprites();

extern void redrawSprites();

int getRandValue(int min, int max);

#endif // SPRITE_MANAGER_H_
