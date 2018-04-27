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
#include <stdio.h>

#include "sprites.h"

bool updateScheduled = false;

void scheduleOamUpdate() {
	updateScheduled = true;
}


void IntVBlank() {
	if(updateScheduled) {
		oamUpdate(&oamMain);
		updateScheduled = false;
	}
}
