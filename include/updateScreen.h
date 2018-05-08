/*-------------------------------------
updateScreen.h
-------------------------------------*/

#ifndef UPDATE_SCREEN_H_   /* Include guard */
#define UPDATE_SCREEN_H_

void scheduleOamMainUpdate();
void scheduleOamSubUpdate();
void scheduleOamUpdate();

void IntVBlank();

#endif // UPDATE_SCREEN_H_
