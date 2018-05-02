/*-------------------------------------
updateScreen.h
-------------------------------------*/

#ifndef UPDATE_SCREEN_H_   /* Include guard */
#define UPDATE_SCREEN_H_

#include <nds.h>

void scheduleOamMainUpdate();
void scheduleOamSubUpdate();
void scheduleOamUpdate(OamState *oam); // &oamMain or &oamSub

void IntVBlank();

#endif // UPDATE_SCREEN_H_
