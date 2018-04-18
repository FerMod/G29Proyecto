/*-------------------------------------
teclado.h
-------------------------------------*/

//Esta función tiene que devolver el valor de la tecla pulsada
extern int TeclaPulsada();

//Rutina de atencion a la interrupcion del teclado
extern void IntTec();


// Funcion temporal, para debugear la tecla pulsada 
extern void debugPressedKey(char *key, char *type);
