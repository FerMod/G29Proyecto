/*---------------------------------------------------
Este codigo se ha implementado basandose en el ejemplo "Simple sprite demo" de 
dovoto y otro de Jaeden Amero
---------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>	    // srand, rand,...
#include <unistd.h>
#include <time.h>       // time 

#include "fondos.h"
#include "sprites.h"
#include "defines.h"
#include "rutservs.h"
#include "teclado.h"
#include "temporizadores.h"
#include "screenText.h"

//---------------------------------------------------
// Funciones
//---------------------------------------------------

// Esta funcion consulta si se ha tocado la pantalla tactil
int TactilTocada() {
	touchPosition pos_pantalla;
	touchRead(&pos_pantalla);
	return !(pos_pantalla.px==0 && pos_pantalla.py==0);
}

//---------------------------------------------------
// Variables globales
//---------------------------------------------------

int estado;
int timer;

//---------------------------------------------------
// main
//---------------------------------------------------

void inicio() {
	if(TactilTocada()) {
		if(isStartTextVisible()) {
			hideStartText();
		}
		iprintf("Pantalla tocada\n");
		estado = PARTIDA;
	}
}

void partida() {
	
}

void finPartida() {
	
}

void estadoFin() {
	
}

int main() {

	/* Definir variables */	
	touchPosition pos_pantalla;

	/* Poner en marcha el motor grafico 2D. */
	powerOn(POWER_ALL_2D);

	/* Establecer la pantalla inferior como principal, inicializar el sistema grafico
	y configurar el sistema de fondos. */
	lcdMainOnBottom();
	initVideo();
	initFondos();

	/* Mostrar fondos en pantalla. */
	SetFondo();
	//mostrarFondoSub();

	/* Inicializar memoria de sprites y guardar en ella los sprites */
	initSpriteMem();
	guardarSpritesEnMemoria();

	/* Establecer las paletas para los sprites */
	establecerPaletaPrincipal();
	establecerPaletaSecundaria();

	/* Inicializa la consola (superior) de texto. 
	   Nota.- Para borrar la pantalla existe la funcion consoleClear() */
	consoleDemoInit();

	/* Para inicializar el generador de numeros aleatorios en funcion de una semilla,
	   en este caso time(NULL). srand() solo se suele activar una vez por ejecucion y
	   no devuelve ningun valor. 
	   La funcion para generar valores aleatorios en el resto del programa es rand() */
	srand (time(NULL));	
	
	/* Incluimos la siguiente cabecera para que cada grupo la modifique con
	su numero de grupo "xx" en "Gxx". */
	iprintf("\x1b[02;00H  +--------------------------+  ");
	iprintf("\x1b[03;00H  | EC 17/18            G29  |  ");
	iprintf("\x1b[04;00H  +--------------------------+  ");

//---------------------------------------------------

	interrupciones();

	estado = INICIO;
	while(estado != FIN) {
		// Temp ////
		switch(TeclaPulsada()) {
			case A:
				debugPressedKey("A", "encuesta");
				break;
			case START:
				debugPressedKey("START", "encuesta");
				break;
			case DERECHA:
				debugPressedKey("DERECHA", "encuesta");
				break;		
			case ARRIBA:
				debugPressedKey("ARRIBA", "encuesta");
				break;
			case ABAJO:
				debugPressedKey("ABAJO", "encuesta");
				break;
			case R:
				debugPressedKey("R", "encuesta");
				break;
			case L:
				debugPressedKey("L", "encuesta");
				break;
		}
		//////////

		switch(estado) {
			case INICIO:
				inicio();
				break;
			case PARTIDA:
				break;
			case FIN_PARTIDA:
				break;
			case FIN:
				break;
		}

    } // while

    iprintf("Fin de programa");

} //main

/*
switch(TeclaPulsada()) {
	case A:
		break;
	case B:
		break;
	case SELECT:
		break;
	case START:
		break;
	case DERECHA:
		break;
	case IZQUIERDA:
		break;			
	case ARRIBA:
		break;
	case ABAJO:
		break;
	case R:
		break;
	case L:
		break;
	default:
		break;
}
*/
