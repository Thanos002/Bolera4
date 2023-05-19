#include <avr/io.h>

#ifndef ELEVADORES_H_
#define	ELEVADORES_H_

//Prototipo de funciones

int setuptimer();

int setupEC(); 

int setupER();

int bajaEC();

int subeEC();

int waitforEC(int estado);//La variable estado correspode a la posici�n en la que debe acabar el elevador . El programa esperar� hasta que llegue a ella;

int bajaER();

int subeER();

int estadoER();//Devuelve la posici�n del ER

void setupulsador();

int recarga(int td,int ultimo_disparo);//Le pasamos el tiempo de delay y la condici�n del ultimo disparo y procede a recargar la bola
#endif