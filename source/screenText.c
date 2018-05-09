/*-------------------------------------
 screenText.c

// https://github.com/devkitPro/libnds/blob/master/source/arm9/console.c
// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors

-------------------------------------*/

// Anadir los includes que sean necesarios
#include <nds.h>

#include <stdio.h>
#include <stdbool.h>

#include "defines.h"
#include "sprites.h"
#include "temporizadores.h"

#include<stdarg.h>

bool startTextVisible = false;

void setStartTextVisible(bool visible) {
	startTextVisible = visible;
}

bool isStartTextVisible() {
	return startTextVisible;
}

void showStartText() {
	// consoleSelect(&bottomScreen);
	iprintf("\x1b[12;05H\x1b[41m %s \x1b[39m", "Para comenzar, toque");
	iprintf("\x1b[13;06H\x1b[41m %s \x1b[39m",  "la pantalla tactil");
	startTextVisible = true;
}

void hideStartText() {
	// consoleSelect(&bottomScreen);
	iprintf("\x1b[12;00H\x1b[2K\x1b[39m");
	iprintf("\x1b[13;00H\x1b[2K\x1b[39m");
	startTextVisible = false;
}

void toggleStartText() {
	if(!startTextVisible) {
		showStartText();
	} else {
		hideStartText();
	}
}

void printHeader() {
	iprintf("\x1b[02;00H  +--------------------------+  ");
	iprintf("\x1b[03;00H  | EC 17/18            G29  |  ");
	iprintf("\x1b[04;00H  +--------------------------+  ");
}

void printFinalScore() {
	consoleClear();
	iprintf("\x1b[05;00H  +--------------------------+  ");
	iprintf("\x1b[06;00H  |     \x1b[41mFin de Partida\x1b[39m       |  ");
	iprintf("\x1b[07;00H  +--------------------------+  ");
	
	iprintf("\x1b[10;02H\x1b[43mPuntuacion Final:\x1b[39m");
	iprintf("\x1b[11;02H\x1b[43m%04d\x1b[39m", getScore());

	iprintf("\x1b[14;02H\x1b[43mTiempo:\x1b[39m");
	iprintf("\x1b[15;02H\x1b[43m%d s\x1b[39m", getTime());
}

void printTime(int x, int y, int time) {
	iprintf("\x1b[%d;%dH\x1b[39mTime:  %d s\x1b[0K", x, y, time);
}

void printStats(int x, int y, int pickedUp) {
	iprintf("\x1b[%d;%dH\x1b[43mBilletes recogidos:  %05d\x1b[0K", x, y, pickedUp);
}

void printScore(int x, int y, int score) {
	iprintf("\x1b[%d;%dH\x1b[43mPuntuacion: %05d\x1b[0K", x, y, score);
}

void printPickUpText(int x, int y, bool b) {
	iprintf("\x1b[%d;%dH\x1b[39mpickup:%5s\x1b[39m\x1b[0K", x, y, b ? "\x1b[42mtrue" : "\x1b[41mfalse");
}

