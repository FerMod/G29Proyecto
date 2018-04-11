/*-------------------------------------
 teclado.c
-------------------------------------*/

// Anadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include "defines.h"
#include "sprites.h"

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
		
	return -1;

	}


// Rutina de atencion a la interrupcion del teclado
void IntTec() {
	switch(TeclaPulsada()) {
		case B:
			iprintf("B\n");
			break;
		case SELECT:
			estado = FIN;
			iprintf("SELECT\n");
			break;
		case IZQUIERDA:
			iprintf("IZQUIERDA\n");
			break;
	}
} 


