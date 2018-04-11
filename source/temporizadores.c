/*-------------------------------------
 temporizadores.c
-------------------------------------*/
// Anadir los includes que sean necesarios
#include "defines.h"
#include "sprites.h"
#include <nds.h>
#include <stdio.h>

int ticks = 0;
int coreTimer = 0;

// Rutina de atencion a la interrupcion del temporizador
void IntTemp() {
	if(++ticks>=512) {
		ticks = 0;
		iprintf("\x1b[010;00H  Time: %ds", ++coreTimer);
	}
}
