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

void createSprite(int index, int x, int y);

void deleteSprite(int index, int x, int y);

void setMaxSpriteSpawns(int max);
int getMaxSpriteSpawns();
bool canSpawnSprite();

void printInfo();

void scheduleSpriteMove();
void moveSprites();

void scheduleSpriteSpawn();
void spriteSpawns();
bool isSpriteSpawnScheduled();

void redrawSprites();

void movePlayerSprite();

bool canSpriteMove(int x, int y);

bool canSpriteMoveX(int x);

bool canSpriteMoveY(int y);

bool checkSpriteOverlap(SpriteEntry* sprite1, SpriteEntry* sprite2);

void checkPlayerTouch();

bool isGameOver();
void setGameOver(bool b);

#endif // SPRITE_MANAGER_H_
