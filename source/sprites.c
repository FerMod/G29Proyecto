/*---------------------------------------------------------------------------------
Este codigo se ha implementado basandose en el ejemplo "Simple sprite demo" de 
dovoto y otro de Jaeden Amero
---------------------------------------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sprites.h"
#include "defines.h"
#include "updateScreen.h"

u16* gfxBillete;
u16* gfxSobre;


/* Inicializar la memoria de Sprites. */
void initSpriteMem() {

	//int i;
	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

	gfxBillete = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxSobre   = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);

}



/* Dentro de esta funcion hay que definir el color con el que se mostrara cada uno de los 256 
 * colores posibles en la pantalla principal. El 0 es transparente y los no definidos son negros.
 */
void establecerPaletaPrincipal() {
                                         // 0: TRANSPARENTE
   SPRITE_PALETTE[1]  = RGB15(31,0,0);   // ROJO:           RGB24={FF,00,00}
   SPRITE_PALETTE[2]  = RGB15(31,31,0);  // AMARILLO:       RGB24={FF,FF,00}
   SPRITE_PALETTE[3]  = RGB15(31,31,31); // BLANCO:         RGB24={FF,FF,FF}
   SPRITE_PALETTE[4]  = RGB15(0,31,0);   // VERDE:          RGB24={00,FF,00}
   SPRITE_PALETTE[5]  = RGB15(0,0,31);   // AZUL:           RGB24={00,00,FF}
   SPRITE_PALETTE[6]  = RGB15(0,0,0);    // NEGRO:          RGB24={00,00,00}
   SPRITE_PALETTE[7]  = RGB15(0,31,31);  // CYAN:           RGB24={00,FF,FF}
   SPRITE_PALETTE[8]  = RGB15(31,0,31);  // MAGENTA:        RGB24={FF,00,FF}
   SPRITE_PALETTE[9]  = RGB15(16,16,16); // GRIS:           RGB24={80,80,80}
   SPRITE_PALETTE[10] = RGB15(25,25,25); // GRIS CLARO:     RGB24={D0,D0,D0}
   SPRITE_PALETTE[11] = RGB15(8,8,8);    // GRIS OSCURO:    RGB24={40,40,40}
   SPRITE_PALETTE[12] = RGB15(31,19,0);  // NARANJA:        RGB24={FF,99,00}
   SPRITE_PALETTE[13] = RGB15(19,0,4);   // GRANATE:        RGB24={99,00,21}
   SPRITE_PALETTE[14] = RGB15(25,0,0);   // MARRON:         RGB24={66,00,00}
   SPRITE_PALETTE[15] = RGB15(16,0,16);  // MORADO:         RGB24={80,00,80}
   SPRITE_PALETTE[16] = RGB15(25,19,31); // LILA:           RGB24={CC,99,FF}
   SPRITE_PALETTE[17] = RGB15(31,19,25); // ROSA:           RGB24={FF,99,CC}
   SPRITE_PALETTE[18] = RGB15(23,21,21); // AZUL CLARO:     RGB24={BB,FF,FF}
   SPRITE_PALETTE[19] = RGB15(0,0,16);   // AZUL MARINO:    RGB24={00,00,80}
   SPRITE_PALETTE[20] = RGB15(0,16,16);  // VERDE AZULADO:  RGB24={00,80,80}
   SPRITE_PALETTE[21] = RGB15(0,12,0);   // VERDE OSCURO:   RGB24={00,66,00}
   SPRITE_PALETTE[22] = RGB15(16,16,0);  // VERDE OLIVA:    RGB24={80,80,00}
   SPRITE_PALETTE[23] = RGB15(19,31,19); // VERDE CLARO:    RGB24={99,FF,99}
   SPRITE_PALETTE[24] = RGB15(31,31,19); // AMARILLO CLARO: RGB24={FF,FF,99}
}

/* Dentro de esta funcion hay que definir el color con el que se mostrara cada uno de los 256 
 * colores posibles en la pantalla secundaria. El 0 es transparente y los no definidos son negros.
 */
void establecerPaletaSecundaria() {
	SPRITE_PALETTE_SUB[1] = RGB15(0,31,0);   // los pixels a 1 se mostraran verdes
	SPRITE_PALETTE_SUB[2] = RGB15(31,31,31); // los pixels a 1 se mostraran blancos
	SPRITE_PALETTE_SUB[3] = RGB15(31,31,0);  // los pixels a 1 se mostraran amarillos
}


/* Dibujado de un Sprite de 16x16 pixels */

/* Debido al funcionamiento de los bancos de memoria, las primeras cuatro filas 
 * forman el cuadrante superior izquiero, las siguientes, el cuadrante superior 
 * derecho, las siguientes el cuadrante inferior izquierdo y las ultimas cuatro
 * filas, el cuadrante inferior derecho, como se muestra al lado.
 */


u8 Sobre[256] = 
{
	0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,3,        // 0000000660000000
	0,0,0,0,0,6,3,3,0,0,0,0,6,3,3,3,        // 0000006336000000
	0,0,0,6,3,3,3,3,0,0,6,3,3,3,3,3,        // 0000063333600000
	0,6,3,3,3,3,3,3,6,3,6,24,24,24,24,24,   // 0000633333360000

	6,0,0,0,0,0,0,0,3,6,0,0,0,0,0,0,        // 0006333333336000
	3,3,6,0,0,0,0,0,3,3,3,6,0,0,0,0,        // 0063333333333600
	3,3,3,3,6,0,0,0,3,3,3,3,3,6,0,0,        // 0633333333333360
	3,3,3,3,3,3,6,0,24,24,24,24,24,6,3,6,   // 63624242424242424242424636

	6,3,3,6,24,24,24,24,6,3,3,3,6,24,24,24, // 633624242424242424246336
	6,3,3,3,3,6,24,24,6,3,3,3,3,3,6,24,     // 6333624242424242463336
	6,3,3,3,3,3,3,6,6,3,3,3,3,3,3,3,        // 63333624242424633336
	6,3,3,3,3,3,3,3,6,6,6,6,6,6,6,6,        // 633333624246333336

	24,24,24,24,6,3,3,6,24,24,24,6,3,3,3,6, // 6333333663333336
	24,24,6,3,3,3,3,6,24,6,3,3,3,3,3,6,     // 6333333333333336
	6,3,3,3,3,3,3,6,3,3,3,3,3,3,3,6,        // 6333333333333336
	3,3,3,3,3,3,3,6,6,6,6,6,6,6,6,6,        // 6666666666666666
};


u8 Billete[256] = 
{
	0,0,0,0,21,21,21,21,0,0,0,0,21,21,23,23, // 000021212121212121210000
	0,0,0,0,21,23,23,23,0,0,0,0,21,23,23,21, // 000021212323232321210000
	0,0,0,0,21,23,23,23,0,0,0,0,21,23,23,23, // 000021232323232323210000
	0,0,0,0,21,23,23,21,0,0,0,0,21,23,21,23, // 000021232321212323210000

	21,21,21,21,0,0,0,0,23,23,21,21,0,0,0,0, // 000021232323232323210000
	23,23,23,21,0,0,0,0,21,23,23,21,0,0,0,0, // 000021232323232323210000
	23,23,23,21,0,0,0,0,23,23,23,21,0,0,0,0, // 000021232321212323210000
	21,23,23,21,0,0,0,0,23,21,23,21,0,0,0,0, // 000021232123232123210000

	0,0,0,0,21,23,21,23,0,0,0,0,21,23,23,21, // 000021232123232123210000
	0,0,0,0,21,23,23,23,0,0,0,0,21,23,23,23, // 000021232321212323210000
	0,0,0,0,21,23,23,21,0,0,0,0,21,23,23,23, // 000021232323232323210000
	0,0,0,0,21,21,23,23,0,0,0,0,21,21,21,21, // 000021232323232323210000

	23,21,23,21,0,0,0,0,21,23,23,21,0,0,0,0, // 000021232321212323210000
	23,23,23,21,0,0,0,0,23,23,23,21,0,0,0,0, // 000021232323232323210000
	21,23,23,21,0,0,0,0,23,23,23,21,0,0,0,0, // 000021212323232321210000
	23,23,21,21,0,0,0,0,21,21,21,21,0,0,0,0, // 000021212121212121210000
};

/* Para cada Sprite que se quiera llevar a pantalla hay que hacer una de estas funciones. */

void BorrarBillete(int indice, int x, int y) {
	oamSet(&oamMain, //main graphics engine context
		indice,  //oam index (0 to 127)  
		x, y,    //x and y pixle location of the sprite
		0,       //priority, lower renders last (on top)
		0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxBillete,//+16*16/2, 	//pointer to the loaded graphics
		-1,                  	//sprite rotation data  
		false,               	//double the size when rotating?
		true,			//hide the sprite?
		false, false, 		//vflip, hflip
		false			//apply mosaic
		); 
	// oamUpdate(&oamMain);
	scheduleOamMainUpdate(); // In the next VBlank it will update the OAM
}

void MostrarBillete (int indice, int x, int y){ 
	oamSet(&oamMain, //main graphics engine context
		indice,  //oam index (0 to 127)  
		x, y,    //x and y pixle location of the sprite
		0,       //priority, lower renders last (on top)
		0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxBillete,//+16*16/2, 	//pointer to the loaded graphics
		-1,                  	//sprite rotation data  
		false,               	//double the size when rotating?
		false,			//hide the sprite?
		false, false, 		//vflip, hflip
		false			//apply mosaic
		); 
	// oamUpdate(&oamMain);
	scheduleOamMainUpdate(); // In the next VBlank it will update the OAM
}

void BorrarSobre(int x, int y){
	oamSet(&oamMain, //main graphics engine context
		127,     //oam index (0 to 127)  
		x, y,    //x and y pixle location of the sprite
		0,       //priority, lower renders last (on top)
		0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxSobre,//+16*16/2,	//pointer to the loaded graphics
		-1,                  	//sprite rotation data  
		false,               	//double the size when rotating?
		true,			//hide the sprite?
		false, false, 		//vflip, hflip
		false			//apply mosaic
		); 
	// oamUpdate(&oamMain);
	scheduleOamMainUpdate(); // In the next VBlank it will update the OAM
}

void MostrarSobre (int x, int y){
	oamSet(&oamMain, //main graphics engine context
		127,     //oam index (0 to 127)  
		x, y,    //x and y pixle location of the sprite
		0,       //priority, lower renders last (on top)
		0,       //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,
		SpriteColorFormat_256Color, 
		gfxSobre,//+16*16/2,	//pointer to the loaded graphics
		-1,                  	//sprite rotation data  
		false,               	//double the size when rotating?
		false,			//hide the sprite?
		false, false, 		//vflip, hflip
		true			//apply mosaic
		); 
	// oamUpdate(&oamMain);
	scheduleOamMainUpdate(); // In the next VBlank it will update the OAM
}



void guardarSpritesEnMemoria(){ 
	int i;
	for(i = 0; i < 16 * 16 / 2; i++){ //muestra un cuadrado en la memoria de la pantalla principal		
		gfxBillete[i] = Billete[i*2] | (Billete[(i*2)+1]<<8);
		gfxSobre[i]   = Sobre[i*2]   | (Sobre[(i*2)+1]<<8);
	}
}




