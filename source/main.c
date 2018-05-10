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
int spawnedMoney;
int pickedUpMoney;

bool pickedUpMoneyChanged = false;

//---------------------------------------------------
// main
//---------------------------------------------------

int main() {

	/* Definir variables */	
	//touchPosition pos_pantalla;

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
	setGameState(INICIO);	
	tecla = TeclaPulsada();
	bool exit = false;
	while(!exit) {

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
		tecla = TeclaPulsada(); //COMENTAR PARA TECLA IZQUIERDA POR ENCUESTA

    } // while

    return 0;

} //main

void estadoInicio() {
	if(TactilTocada()) {
		if(isStartTextVisible()) {
			hideStartText();
		}
		//iprintf("\x1b[05;01H Pantalla tocada");
		setGameState(PARTIDA);
	}
}

void estadoPartida() {
	if(!isGameOver()) {
		printTime(21, 2, timer);
		//consumePlayerInput(); //DESCOMENTAR PARA TECLA IZQUIERDA POR ENCUESTA
		spriteSpawns();
		movePlayerSprite();
		moveSprites();
		checkPlayerTouch();
		updateDifficulty(pickedUpMoney); // Incrementar dificultad (num billetes, velocidad, etc.)
		printScore(15, 2, getScore());
		printStats(17, 2,  getPickedUpMoney());
	} else {
		setGameState(FIN_PARTIDA);
	}
}
void estadoFinPartida() {
	switch(tecla) {
		case START:
			//debugPressedKey("START", "encuesta");
			setGameState(PARTIDA);
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

int getGameState() {
	return estado;
}

void setGameState(int newState) {
	estado = newState;
	switch(newState) {
		case INICIO:
			break;
		case PARTIDA:
			consoleClear();
			printHeader();
			ticks = 0;
			score = 0;
			spawnedMoney = 0;
			pickedUpMoney = 0;
			setLives(MAX_LIFES);
			createHearts();
			resetDifficulty();
			MostrarSobre(120, 172); // Spawn player		
			break;
		case FIN_PARTIDA:
			clearSprites();
			printFinalScore();
			break;
		case FIN:
			break;
	}
}

void resetDifficulty() {
	setMaxSpriteSpawns(1);
	setSpawnCooldown(1024);
	setDropSpeed(256);
	pickedUpMoneyChanged = false;
}

void updateDifficulty(int pickedMoney) {
	if(pickedUpMoneyChanged){

		if(pickedMoney % 3 == 0) {
			setMaxSpriteSpawns(getMaxSpriteSpawns()+1);
		}

		if(pickedMoney % 4 == 0) {
			setDropSpeed(getDropSpeed()-1);
		}

		if(pickedMoney % 7 == 0) {
			setSpawnCooldown(getSpawnCooldown()-1);
		}

		pickedUpMoneyChanged = false;

	}
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

int getSpanwedMoney() {
	return spawnedMoney;
}

void setSpanwedMoney(int num) {
	spawnedMoney = num;
}

void increaseSpawnedMoney() {
	spawnedMoney++;
}

void decreaseSpawnedMoney() {
	spawnedMoney--;
}

int getPickedUpMoney() {
	return pickedUpMoney;
}

void setPickedUpMoney(int num) {
	pickedUpMoney = num;
	pickedUpMoneyChanged = true;
}

void increasePickedUpMoney() {
	pickedUpMoney++;
	pickedUpMoneyChanged = true;
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
