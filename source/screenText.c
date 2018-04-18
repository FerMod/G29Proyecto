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
	// consoleSelect(&bottomScreen);
	iprintf("\x1b[12;05H\x1b[41m %s \x1b[0m", "Para comenzar, toque");
	iprintf("\x1b[13;06H\x1b[41m %s \x1b[0m",  "la pantalla tactil");
	startTextVisible = true;
}

void hideStartText() {
	// consoleSelect(&bottomScreen);
	iprintf("\x1b[12;00H\x1b[0K\x1b[0m");
	iprintf("\x1b[13;00H\x1b[0K\x1b[0m");
	startTextVisible = false;
}

void toggleStartText() {
	if(!startTextVisible) {
		showStartText();
	} else {
		hideStartText();
	}
}

