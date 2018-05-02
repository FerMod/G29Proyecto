/*-------------------------------------
 teclado.c
-------------------------------------*/

// Anadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"
#include "spriteManager.h"
#include "screenText.h"

//bool keyPressed = false;
// int pressedKey = -1;

// Esta funcion tiene que devolver el valor de la tecla pulsada
int TeclaPulsada() {
   // Devuelve el valor asociado a la tecla pulsada: 
   // A=0; B=1; Select=2; Start=3; Der=4; Izq=5;
   // Arriba=6; Abajo=7; R=8; L=9;
   // -1 en otros casos
	if ((TECLAS_DAT & 0x1) == 0) return A;
	if ((TECLAS_DAT & 0x2) == 0) return B; // Por interrupcion
	if ((TECLAS_DAT & 0x4) == 0) return SELECT; // Por interrupcion
	if ((TECLAS_DAT & 0x8) == 0) return START;
	if ((TECLAS_DAT & 0x10) == 0) return DERECHA;
	if ((TECLAS_DAT & 0x20) == 0) return IZQUIERDA; // Por interrupcion
	if ((TECLAS_DAT & 0x40) == 0) return ARRIBA;
	if ((TECLAS_DAT & 0x80) == 0) return ABAJO;
	if ((TECLAS_DAT & 0x100) == 0) return R;
	if ((TECLAS_DAT & 0x200) == 0) return L;

	//keyPressed = key == 0 ?  false : true;
		
	return -1;

}

void debugPressedKey(char *key, char *type) {
	// consoleSelect(&topScreen);
	iprintf("\x1b[17;0H %s(%s)\x1b[0K", key, type);
}


// Rutina de atencion a la interrupcion del teclado
void IntTec() {
	if(estado == PARTIDA) {
		switch(TeclaPulsada()) {
			case B:
				showFinalScoreText();				
				estado = FIN_PARTIDA;
				debugPressedKey("B", "interrupcion");
				break;
			case IZQUIERDA:
				tecla = IZQUIERDA;
				debugPressedKey("IZQUIERDA", "interrupcion");
				break;
		}
	}
	if(TeclaPulsada() == SELECT) {
		estado = FIN;
		debugPressedKey("SELECT", "interrupcion");
	}
}
