/*-------------------------------------
spriteManager.h
-------------------------------------*/

#ifndef SPRITE_MANAGER_H_   /* Include guard */
#define SPRITE_MANAGER_H_

#include <nds.h>

#define PLAYER_SPRITE 127
#define MAX_MONEY_SPRITES 10
#define MAX_LIFES 3

extern int numberSprites;
extern int maxSpriteSpawns;

typedef struct {
	int index;
	bool isFull;
} Heart;

void createPlayerSprite(int x, int y);
void deletePlayerSprite();

void createSprite(int index, int x, int y);
void deleteSprite(int index);

void createHearts();
void deleteHearts();

void createPickup();

void clearMoneySprites();
void clearSprites();

void setMaxSpriteSpawns(int max);
int getMaxSpriteSpawns();
bool canSpawnSprite();

void scheduleSpriteMove();
void moveSprites();
void moveMoney();
void movePickups();

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
void checkPlayerTouchMoney();
void checkPlayerTouchPickup();

void applyPickupEffect(int index);

int getMaxLifes();

int getLives();
void setLives(int num);
void increaseLives();
void decreaseLives();

bool isGameOver();
void setGameOver(bool b);

#endif // SPRITE_MANAGER_H_
