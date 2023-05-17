/*
 * Bolera4.c
 *
 * Created: 19.04.2023 17:29:57
 * Author : thano
 */ 

#include <avr/io.h>
#include "IncFile1.h"
#include "Bolera.h"
#include <avr/interrupt.h>

uint8_t display_number;
volatile uint32_t ms_elapsed = 0;

void setup(){
	// REGISTRO del Port 18 para la LED
	register uint8_t display_number asm("r18");
}

void timerSetup(){
	TCCR1A = 0x00;
	TCCR1B = (1 << WGM12) | (1 << CS12);  // CTC mode, prescaler 256
	OCR1A = 6250;  // timer con frecuencia 100Hz
	TIMSK1 = (1 << OCIE1A);
}

int main(void)
{
	cli();
	setup();
	timerSetup();
	sei();
    pruebas();
}

ISR(TIMER1_COMPA_vect){
	ms_elapsed += 10; 
}
