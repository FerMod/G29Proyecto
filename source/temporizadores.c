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

// Rutina de atencion a la interrupcion del temporizador
void IntTemp() {

	ticks++;
	if(ticks==512) {
		ticks = 0;
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
			break;
		case FIN_PARTIDA:
			break;
		case FIN:
			break;
	}

	iprintf("\x1b[22;00H ticks: %3d", ticks);

}
