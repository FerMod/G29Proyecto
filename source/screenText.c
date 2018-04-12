/*-------------------------------------
 screenText.c
-------------------------------------*/

// Anadir los includes que sean necesarios
#include <nds.h>
#include <stdio.h>
#include <stdbool.h>
#include "defines.h"
#include "sprites.h"

bool startTextVisible = false;

void setStartTextVisible(bool visible) {
	startTextVisible = visible;
}

bool isStartTextVisible() {
	return startTextVisible;
}

void showStartText() {
	iprintf("\x1b[12;05H %s ", "Para comenzar, toque");
	iprintf("\x1b[13;06H %s ",  "la pantalla tactil");
	startTextVisible = true;
}

void hideStartText() {
	iprintf("\x1b[12;00H%32s", "");
	iprintf("\x1b[13;00H%32s", "");
	startTextVisible = false;
}

void toggleStartText() {
	if(!startTextVisible) {
		showStartText();
	} else {
		hideStartText();
	}
}

