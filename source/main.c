/*---------------------------------------------------
Este codigo se ha implementado basandose en el ejemplo "Simple sprite demo" de 
dovoto y otro de Jaeden Amero
---------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>	    // srand, rand,...
#include <unistd.h>
#include <time.h>       // time 
#include <stdbool.h>

#include "fondos.h"
#include "sprites.h"
#include "defines.h"
#include "rutservs.h"
#include "teclado.h"
#include "temporizadores.h"
#include "screenText.h"

#include "spriteManager.h"
// #include "player.h"

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

//PrintConsole topScreen, bottomScreen;

int estado;
int tecla;
int score;

//---------------------------------------------------
// main
//---------------------------------------------------

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

	/* Inicializar la consola superior e inferior

	Parametros de 'consoleInit'

	consoleInit(
		&theScreen,			//La consola a inicializar
		3, 					// Capa del fondo en la que se imprimirá
		BgType_Text4bpp, 	// Tipo de fondo.
		BgSize_T_256x256, 	// Tamaño del fondo.
		31, 				// Base del mapa.
		0, 					// Base del tile gráfico.
		true, 				// Sistema gráfico a usar (main system).
		true 				// No cargar gráficos para la fuente.
	);

	*/

	// WIP
	// consoleInit(&topScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 22, 3, false, true);
	// consoleInit(&bottomScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 191, 0, true, true);

	/* Para inicializar el generador de numeros aleatorios en funcion de una semilla,
		en este caso time(NULL). srand() solo se suele activar una vez por ejecucion y
		no devuelve ningun valor. 
		La funcion para generar valores aleatorios en el resto del programa es rand() */
	srand(time(NULL));	
	
	//consoleSelect(&topScreen);
	/* Incluimos la siguiente cabecera para que cada grupo la modifique con
	su numero de grupo "xx" en "Gxx". */
	printHeader(2, 0);
	
//---------------------------------------------------

	interrupciones();
	// MostrarBillete(1, 20, 20);
	// MostrarBillete(0, 20, 20);
	// MostrarSobre(100, 120);
	// SpriteEntry billeteEntry = oamMain.oamMemory[0];
	// iprintf("\x1b[05;01H\x1b[0m Sprite x: %d y:%d", billeteEntry.x, billeteEntry.y);
	// iprintf("\x1b[06;01H\x1b[0m Sprite x: %d y:%d", oamMain.oamMemory[1].x, oamMain.oamMemory[1].y);
	// iprintf("\x1b[07;01H\x1b[0m Sprite x: %d y:%d", oamMain.oamMemory[127].x, oamMain.oamMemory[127].y);	
	// iprintf("\x1b[08;01H\x1b[0m Numero Sprites: %d", oamCountFragments(&oamMain));
	estado = INICIO;
	tecla = TeclaPulsada();
	bool exit = false;
	while(!exit) {
		// Temp ////
		switch(tecla) {
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
				estadoInicio();
				break;
			case PARTIDA:
				estadoPartida();
				break;
			case FIN_PARTIDA:
				estadoFinPartida();
				break;
			case FIN:
				estadoFin();
				exit = true;
				break;
		}

		swiWaitForVBlank(); // Halt a thread until the next vertical blank occurs.
		tecla = TeclaPulsada();
		//consumePlayerInput();

    } // while

    return 0;

} //main

void estadoInicio() {
	if(TactilTocada()) {
		if(isStartTextVisible()) {
			hideStartText();
		}
		iprintf("\x1b[05;01H Pantalla tocada");
		ticks = 0;
		estado = PARTIDA;
		score = 0;
		MostrarSobre(120, 172); // Spawn player
	}
}

void estadoPartida() {
	if(!isGameOver()) {
		printTime(21, 2, timer);
		//consumePlayerInput();
		//redrawSprites();
		spriteSpawns();
		movePlayerSprite();
		moveSprites();
		checkPlayerTouch();
		//TODO: Incrementar dificultad (num billetes, velocidad)
		updateDifficulty();
		printScore(15, 2, getScore());
	} else {
		estado = FIN_PARTIDA;	
	}
}

void estadoFinPartida() {
	switch(tecla) {
		case START:
			debugPressedKey("A", "encuesta");
			estado = PARTIDA;
			break;
	}
}

void estadoFin() {
	if(isStartTextVisible()) {
		hideStartText();
	}

    iprintf("\x1b[18;01H\x1b[39m Fin de programa");

}

void consumePlayerInput() {
	switch(TeclaPulsada()) {
		case DERECHA:
			tecla = DERECHA;
			break;
/*
		// case IZQUIERDA:
		// 	break;			
		// case ARRIBA:
		// 	break;
		// case ABAJO:
		// 	break;
		default:
			tecla = -1;
			break;
*/
	}
}

void updateDifficulty() {
	
}

void setScore(int num) {
	score = num;
}

void increaseScore() {
	score++;
}

void decreaseScore() {
	score--;
}

int getScore() {
	return score;
}

int getRandValue(int min, int max) {
	return (rand() % (max-min)) + min;
}

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
