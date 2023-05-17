/* 
* Lanzador_Pruebas.c
* Realizar primeras pruebas de la maqueta 
*
*/

#include "IncFile1.h"
#include "Lanzador.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t display_number;
int s1state;
int s2state;
int s3state;

void setup(){
	enableInterrupt(SW2EIFR);
	EICRA |= (1<<ISC01); // interrupcion solo en flanco de bajada, no modificando otros valores del registro
	// Sensores:
	setInput(SW2DDR, SW2X);
	setInput(SW3DDR, SW3X);
	setInput(SW4DDR, SW4X);
	setInput(SW5DDR, SW5X);
	// Motores:
	setOutput(M1_diDDR, M1_di_X);
	setOutput(M2_diDDR, M2_di_X);
	setOutput(M3_diDDR, M3_di_X);
	setOutput(M4_diDDR, M4_di_X);
	setOutput(M5_diDDR, M5_di_X);
	setOutput(M1_enDDR, M1_en_X);
	setOutput(M2_enDDR, M2_en_X);
	setOutput(M3_enDDR, M3_en_X);
	setOutput(M4_enDDR, M4_en_X);
	setOutput(M5_enDDR, M5_en_X);
	setOutput(M2_bkDDR, M2_bk_X);
}

void timerSetup(){
	TCCR1A = 0x00;
	TCCR1B = (1 << WGM12) | (1 << CS12);  // CTC mode, prescaler 256
	OCR1A = 625;  // timer con frecuencia 100Hz
	TIMSK1 = (1 << OCIE1A);
}

int main(void)
{
	cli();
	setup();
	timerSetup();
	sei();
	setTime(0);
	/* TODO: Pruebas de las funciones:
	* M2: girarVertical 
	* M3: moverVastago
	* M4: parar Vastago 
	 */
	while (0)
	{
		setTime(0);
		apagarLED();
		_delay_ms(500);
		liberarCarrito();
		_delay_ms(500);
		engancharCarrito();
		_delay_ms(500);
		girarVertical(1);
		_delay_ms(500);
		girarVertical(0);
		_delay_ms(500);
		frenoVertical();
		_delay_ms(500);
		moverVastagoAdelante();
		_delay_ms(500);
		moverVastagoAtras();
		_delay_ms(500);
		moverVastagoAdelante();
		getSensor1();
	}
}

ISR(TIMER1_COMPA_vect){
	updateTime();
	if (getTime() % 100 <40){
		encenderLED();
		s1state = getSensor1();
		s2state = getSensor2();
		s3state = getSensor3();
	}
	else{
	apagarLED();
	}
}
