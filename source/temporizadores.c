/*-------------------------------------
 temporizadores.c
-------------------------------------*/

#include "temporizadores.h"

// Anadir los includes que sean necesarios
#include "defines.h"
#include "sprites.h"

#include <nds.h>
#include <stdio.h>

#include "screenText.h"
#include "spriteManager.h"

int ticks = 0;
int timer = 0;

int spawnCooldown = 1024; // Max ticks that need to pass, before allowing another spawn

int spawnCountdown = 0;
int dropSpeed = 256;

// Rutina de atencion a la interrupcion del temporizador
void IntTemp() {

	if(estado != FIN && estado != FIN_PARTIDA) {
		if(ticks==513) {
			ticks = 0;
		}		
		ticks++;
	}

	switch(estado) {
		case INICIO:
			if(ticks==256 || ticks==512) {
				toggleStartText();
			}
			break;
		case PARTIDA:
			if(ticks==512) {
				timer++;
			}
			updateSprites();	
			break;
		case FIN_PARTIDA:
			break;
		case FIN:
			break;
	}

	// consoleSelect(&topScreen);
	iprintf("\x1b[22;1H\x1b[39m ticks: %3d\x1b[0K", ticks);
	
}

int getTime() {
	return timer;
}

void setTime(int t) {
	timer = t;
}

void updateSprites() {
	
	if(ticks == dropSpeed) {
		scheduleSpriteMove();
	}

	iprintf("\x1b[07;1H spawn billete: %5s (%3d)\x1b[0K", canSpawnSprite() ? "\x1b[42mtrue\x1b[39m" : "\x1b[41mfalse\x1b[39m", spawnCountdown);
	if(canSpawnSprite()) {
		if(spawnCountdown == 0) {
			scheduleSpriteSpawn();
			//createSprite(0, getRandValue(8, 240), 0);
			spawnCountdown = SPAWN_TIME;
		} else {
			spawnCountdown--;
		}
	}

}
