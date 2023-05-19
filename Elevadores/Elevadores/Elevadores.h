#include <avr/io.h>

#ifndef ELEVADORES_H_
#define	ELEVADORES_H_

//Prototipo de funciones

int setuptimer();

int setupEC(); 

int setupER();

int bajaEC();

int subeEC();

int waitforEC(int estado);//La variable estado correspode a la posición en la que debe acabar el elevador . El programa esperará hasta que llegue a ella;

int bajaER();

int subeER();

int estadoER();//Devuelve la posición del ER

void setupulsador();

int recarga(int td,int ultimo_disparo);//Le pasamos el tiempo de delay y la condición del ultimo disparo y procede a recargar la bola
#endif