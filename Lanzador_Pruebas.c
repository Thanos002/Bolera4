/* 
* Lanzador_Pruebas.c
* Realizar primeras pruebas de la maqueta 
*
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "IncFile1.h"
#include "Bolera.h"
#include "Lanzador.h"

uint8_t display_number;
uint8_t s1state;
uint8_t s2state;
uint8_t s3state;
volatile uint32_t ms_elapsed = 0;

void setup(){
	enableInterrupt(SW2EIFR);
	EICRA |= (1<<ISC01); // interrupcion solo en flanco de bajada, no modificando otros valores del registro
	// Sensores:
	setInput(SW2X,SW2PIN);
	setInput(SW3X,SW3PIN);
	setInput(SW4X,SW4PIN);
	setInput(SW5X,SW5PIN);
	// Motores:
	setOutput(M1_di_X,M1_diPORT);
	setOutput(M2_di_X,M2_diPORT);
	setOutput(M3_di_X,M3_diPORT);
	setOutput(M4_di_X,M4_diPORT);
	setOutput(M5_di_X,M5_diPORT);
	setOutput(M1_en_X,M1_enPORT);
	setOutput(M2_en_X,M2_enPORT);
	setOutput(M3_en_X,M3_enPORT);
	setOutput(M4_en_X,M4_enPORT);
	setOutput(M5_en_X,M5_enPORT);
	setOutput(M2_bk_X,M2_bkPORT);
	setOutput(L1DDR, L1X);
}

void timerSetup(){
	TCCR1A = 0x00;
	TCCR1B = (1 << WGM12) | (1 << CS12);  // CTC mode, prescaler 256
	OCR1A = 6250;  // timer con frecuencia 100Hz
	TIMSK1 = (1 << OCIE1A);
}

int pruebas(void)
{
	cli();
	setup();
	timerSetup();
	sei();
	/* TODO: Pruebas de las funciones:
	* M2: girarVertical 
	* M3: moverVastago
	* M4: parar Vastago 
	 */
	while (1)
	{
		_delay_ms(1000);
		liberarCarrito();
		_delay_ms(1000);
		engancharCarrito();
		_delay_ms(1000);
		moverVastagoAdelante();
		_delay_ms(1000);
		moverVastagoAtras();
		_delay_ms(1000);
		pararVastago();
		_delay_ms(1000);
		getSensor1();
	}
}

ISR(TIMER1_COMPA_vect){
	ms_elapsed += 10;
	if (ms_elapsed / 1000 == 0){
		toggleBit(L1X,L1PORT);
		s1state = getSensor1();
		s2state = getSensor2();
		s3state = getSensor3();
	}
}
