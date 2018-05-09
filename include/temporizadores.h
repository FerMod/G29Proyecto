/*-------------------------------------
temporizadores.h
-------------------------------------*/

#ifndef TEMPORIZADORES_H_   /* Include guard */
#define TEMPORIZADORES_H_

void IntTemp();

int getTime();
void setTime(int t);

void updateSprites();


void setDropSpeed(int speed);
int getDropSpeed();

void setSpawnCooldown(int cooldown);
int getSpawnCooldown();

#endif // TEMPORIZADORES_H_
