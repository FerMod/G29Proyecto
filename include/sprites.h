
extern u16* gfxBillete;
extern u16* gfxSobre;
extern u16* gfxFullHeart;
extern u16* gfxEmptyHeart;
extern u16* gfxHeartPickup;
extern u16* gfxClearPickup;

typedef enum {
	HEALTH,
	CLEAR
} PickupType;

typedef struct {
	int index;
	PickupType type;
} Pickup;

/* Inicializar la memoria de Sprites. */
extern void initSpriteMem();

/* Dentro de esta funcion hay que definir el color con el que se mostrara cada uno de los 256 
 * colores posibles en la pantalla principal. El 0 es transparente y los no definidos son negros.
 */
extern void establecerPaletaPrincipal();

/* Dentro de esta funcion hay que definir el color con el que se mostrara cada uno de los 256 
 * colores posibles en la pantalla secundaria. El 0 es transparente y los no definidos son negros.
 */
extern void establecerPaletaSecundaria();

/* Para guardar los sprites en memoria y luego poder usarlos. */

extern void guardarSpritesEnMemoria();

/* Funciones especificas para manejar los sprites. */

extern void MostrarBillete(int indice, int x, int y);
extern void BorrarBillete(int indice, int x, int y);

extern void MostrarSobre(int x, int y);
extern void BorrarSobre(int x, int y);

extern void showHeart(int index, int x, int y, bool isFull);

extern void showPickup(int index, int x, int y, PickupType pickupType);

u16* getPickupSprite(PickupType pickupType);

extern void hideSprite(int index);
