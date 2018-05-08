/*-------------------------------------
updateScreen.c
---------------------------------------

Used to update the OAM

### OAM(Object Attribute Memory) ###

The OAM manages all the sprites. 
Used to keep track of and control the sprites.
The OAM works with a SpriteEntry and a SpriteRotation struct to manage the attributes of the sprites.

-------------------------------------*/

#include "updateScreen.h"

#include <nds.h>

bool oamMainUpdateScheduled = false;
bool oamSubUpdateScheduled = false;

void scheduleOamMainUpdate() {
	oamMainUpdateScheduled = true;
}

void scheduleOamSubUpdate() {
	oamSubUpdateScheduled = true;
}

void scheduleOamUpdate() {
	scheduleOamMainUpdate();
	scheduleOamSubUpdate();
}

void IntVBlank() {
	if(oamMainUpdateScheduled) {
		oamUpdate(&oamMain);
		oamMainUpdateScheduled = false;
	}
	if(oamSubUpdateScheduled) {
		oamUpdate(&oamSub);
		oamSubUpdateScheduled = false;
	}
}
