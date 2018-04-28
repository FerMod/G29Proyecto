/*-------------------------------------
spriteManager.h
-------------------------------------*/

#ifndef SPRITE_MANAGER_H_   /* Include guard */
#define SPRITE_MANAGER_H_

#include <nds.h>

#define MAX_SPRITES 128
#define PLAYER_SPRITE 127

extern int numberSprites;
extern int maxSpriteSpawns;

extern void createSprite(int index, int x, int y);

extern void deleteSprite(int index, int x, int y);

extern void setMaxSpriteSpawns(int max);
extern int getMaxSpriteSpawns();
extern bool canSpawnSprite();

extern void printInfo();

extern void moveSprites();

extern void scheduleMove();

extern void redrawSprites();

extern void movePlayerSprite();

bool canSpriteMove(int x, int y);

bool canSpriteMoveX(int x);

bool canSpriteMoveY(int y);

bool checkSpriteOverlap(SpriteEntry* sprite1, SpriteEntry* sprite2);

//int getRandValue(int min, int max);

#endif // SPRITE_MANAGER_H_
