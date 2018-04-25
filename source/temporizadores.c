/*-------------------------------------
 temporizadores.c
-------------------------------------*/
// Anadir los includes que sean necesarios
#include "defines.h"
#include "sprites.h"
#include <nds.h>
#include <stdio.h>

#include "screenText.h"

int ticks = 0;
int timer = 0;

int numBillete;
int nextSpawnTime = 0;

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
						
			//
			int i;
			for(i = 0; i <= numBillete - 1;i++) {
				// MostrarBillete(numBillete, rand()%255, );
			}
			//
							
			//TODO define in another file
			if(nextSpawnTime==0) {
				MostrarBillete(numBillete, rand()%255, 0);
				numBillete++;
				nextSpawnTime = 768;
			} else {
				nextSpawnTime--;			
			}
			////
			break;
		case FIN_PARTIDA:
			break;
		case FIN:
			break;
	}

	// consoleSelect(&topScreen);
	iprintf("\x1b[22;1H\x1b[39m ticks: %3d\x1b[0K", ticks);
	
}

// https://github.com/devkitPro/libnds/blob/master/source/arm9/console.c
// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
