/*
* Lanzador.h
*/

#ifndef LANZADOR_H_
#define LANZADOR_H_

#include "IncFile1.h"
#include "Bolera.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Function prototypes
void setup();
void lanzadorHome();
void rightInterrupt();
void middleInterrupt();
void leftInterrupt();

void updateTime();
void setTime(int time);
uint32_t getTime();

typedef enum {SIN_BOLA, BOLA_LANZADOR, LANZAMIENTO, TIRAR_BOLA, PARPADEO} States;
extern States state;

typedef enum {LEFT, RIGHT} Position;
extern Position position;

#endif /* LANZADOR_H_ */
