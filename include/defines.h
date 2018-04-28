/*-------------------------------------
defines.h
-------------------------------------*/

#include <nds.h>
#include <stdio.h>

// Aqui se definen los registros del gestor de interrupciones
#define IME		(*(vuint16*)0x04000208) //Interrupt Master Enable - Habilita o deshabilita todas las interrupciones
#define IE		(*(vuint32*)0x04000210) //Interrupt Enable - Activa o desactiva las interrupciones una a una
#define IF		(*(vuint32*)0x04000214) //Interrupt Flag - Guarda las peticiones de interrupcion

// Aqui se definen algunas funciones para el tratamiento de las interrupciones
#define EnableInts() 	IME=1 //Habilita todas las interrupciones
#define DisableInts() 	IME=0 //Deshabilita todas las interrupciones

// Aqui se definen los registros del teclado 
#define TECLAS_DAT	(*(vuint16*)0x4000130) //Registro de datos del teclado
#define TECLAS_CNT	(*(vuint16*)0x4000132) //Registro de control del teclado

// Aqui se definen los registros del temporizador
#define TIMER0_CNT   	(*(vuint16*)0x04000102) //Registro de control del temporizador
// El temporizador se activa poniendo un 1 en el bit 7.
// El temporizador interrumpira al desbordarse el contador, si hay un 1 en el bit 6.
// Los dos bits de menos peso indican lo siguiente:
//		00 frecuencia 33554432 hz
//		01 frecuencia 33554432/64 hz
//		10 frecuencia 33554432/256 hz
//		11 frecuencia 33554432/1024 hz

#define TIMER0_DAT    (*(vuint16*)0x04000100) //Registro de datos del temporizador
// Se utiliza para indicar a partir de que valor tiene que empezar a contar


// Esta funcion consulta si se ha tocado la pantalla tactil
extern int TactilTocada();

// Para no liarse con los numeros a cada teclas se le ha asignado un nombre

#define A			0 
#define B			1
#define SELECT		2 
#define START		3
#define DERECHA		4 
#define IZQUIERDA	5
#define ARRIBA		6 
#define ABAJO		7
#define R			8 
#define L			9

// Asignar un nombre a cada estado
#define INICIO		0
#define PARTIDA		1
#define FIN_PARTIDA	2
#define FIN			3


// Variables globales

// extern PrintConsole topScreen, bottomScreen;

extern int estado;
extern int ticks;
extern int timer;
extern int numBilletes;
extern int tecla;

void estadoInicio();
void estadoPartida();
void estadoFinPartida();
void estadoFin();

void MostrarBillete(int indice, int x, int y);
void BorrarBillete(int indice, int x, int y);

void MostrarSobre(int x, int y);
void BorrarSobre(int x, int y);

int getRandValue(int min, int max);

void consumePlayerInput();

