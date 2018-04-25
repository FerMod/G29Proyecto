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

int spawnCountdown = 0;
int dropSpeed = 256;

// Rutina de atencion a la interrupcion del temporizador
void IntTemp() {

	if(estado != FIN) {
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

void updateSprites() {
	
	if(ticks == dropSpeed) {
		moveSprites();
	}

	if(spawnCountdown == 0) {
		createSprite(numberSprites, rand()%255, 0);
		spawnCountdown = SPAWN_TIME;
	} else {
		spawnCountdown--;			
	}
}