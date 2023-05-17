/*
* Lanzador.c
*
* Created: 19.04.2023 17:29:57
* Author : thano
*/

#include "IncFile1.h"
#include "Bolera.h"
#include "Lanzador.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

Position position = LEFT;
volatile uint32_t ms_elapsed = 0;
uint16_t button_check_delay_ms = 50;
uint16_t debounce_buffer_ms = 50;
uint32_t buffer =0;

void setupLanzador(){
	cli();
	enableInterrupt(SW2EIFR);  // set EIMSK
	EICRA |= (1<<ISC01); // interrupcion solo en flanco de bajada, no modificando otros valores del registro
	sei();
}

// lanzador home: se mueve a la izquierda y se guarda el flag position
void lanzadorHome(){
	girarVertical(0);
	position = LEFT;
}

// interrupcion del fin de carrera derecho,
void rightInterrupt(){
	if(state==LANZAMIENTO  || state == PARPADEO){  // si estamos en lanzamiento, cambiamos direccion
		girarVertical(0);
	}
	else{
		frenoVertical();  // si no, frenamos
	}
}

// interrupcion del pulsador medio
void middleInterrupt(){
	if(position==LEFT)	{
		position = RIGHT;  // cambiar position flag, que ahora estamos a la derecha
	}
	else{
		position = LEFT;
	}
	if(state==LANZAMIENTO  || state == PARPADEO){  // cambiar de direccion en estado de lanzamiento
		girarVertical(0);
	}
	else{
		frenoVertical();
	}
}

void leftInterrupt(){
	if(state==LANZAMIENTO  || state == PARPADEO){
		girarVertical(1);  // cambiar de direccion en lanzamiento
	}
	else{
		frenoVertical();
	}
}

// funciones usadas para el timer de main
inline void updateTime(){
	ms_elapsed += 10;
}
inline void setTime(int time){
	ms_elapsed = time;
}
inline uint32_t getTime(){
	return ms_elapsed;
}

// interrupcon del SW2 que sirva para distinguir que pulsador se ha pulsado
ISR(PCINT0_vect)
{
	// debounce protection:
	// si hay dos interupciones entre menos que 50 ms
	if(last_interruption_time > ms_elapsed+50){
		switch (lanzadorFlag){
			case 1:  // moviemiento hacia derecha
			// si estoy RIGHT
			if (position==RIGHT){
				rightInterrupt();
			}
			else if (position==LEFT){  // si estoy LEFT
				middleInterrupt();
			}
			case 0:
			// si estoy moviendo hacia la izquierda y estoy LEFT
			if (position==LEFT){
				leftInterrupt();
			}
			// movimiento hacia la izqrda, estoy RIGHT
			else if (position==RIGHT){
				middleInterrupt();
			}
			case 2:  // parado
			if(position == LEFT){
				leftInterrupt();
			}
			else{
				rightInterrupt();
			}
		}
	}
}

// Explicacion de los estados:
// BOLA_LANZADOR: la bola esta colocada en el lanzador
// LANZAMIENTO: el sistema se encuentra el el proceso de lanzar la bola
// TIRAR_BOLA: la bola fue lanzada para tirar los bolos

States state = SIN_BOLA;

// bucle con estados que debe ser integrado con los otros componentes
int LanzadorLoop(void)
{
	lanzadorHome();  // comprobar si se puede hacer el home de manera segura (ELEVADOR)
	setupLanzador();  // home del lanzador
	while (1)
	{
		switch(state){
			case SIN_BOLA:
			subirElevadorCargas();
			_delay_ms(1000);
			girarVertical(1);
			
			// Aqui: verficiar que bola esta cargada:
			// state = BOLA_LANZADOR
			
			case BOLA_LANZADOR:
			// proceso para enganchar la bola en el lanzador

			// liberamos el carrito
			do {
				liberarCarrito();
				_delay_ms(button_check_delay_ms);}
			while(getSensor4()!=0);
			pararCarrito();
			
			// movemos el vastago adelante
			do {
				moverVastagoAdelante();
				_delay_ms(button_check_delay_ms);}
			while(getSensor3()!=0);
			pararVastago();
			
			// enganchamos el carrito
			do {
				engancharCarrito();
				_delay_ms(button_check_delay_ms);}
			while(getSensor4()!=0);
			pararCarrito();
			
			//movemos el vastago atras (enganchar gomas)
			do {
				moverVastagoAtras();
				_delay_ms(button_check_delay_ms);}
			while(getSensor3()!=0);
			pararVastago();
			
			_delay_ms(button_check_delay_ms);
			
			state = LANZAMIENTO; // empezar lanzamiento
			buffer = ms_elapsed;  // timer de 30 segundos
			
			case LANZAMIENTO:
			
			// encender LED
			encenderLED();

			if(buffer>ms_elapsed+30000){
				state = PARPADEO;
			}
			// esperar interupciones
			loop_until_bit_is_set(SW6PIN,SW6X);  //esperar hasta se pulsa el disparo
			// cuando se interumpe, marcar state=TIRAR_BOLA
			state = TIRAR_BOLA;

			
			case PARPADEO:
			// lanzamiento con parpadeo
			buffer = ms_elapsed;
			
			while(ms_elapsed - buffer < 900){
				encenderLED();
			}
			while(ms_elapsed - buffer < 1000){
				apagarLED();
			}
			// TODO: Cuando se pulsa el interruptor, cambiar a TIRAR_BOLA
			// cuando se interumpe, marcar state=TIRAR_BOLA
			state = TIRAR_BOLA;
			
			case TIRAR_BOLA:
			// El interruptor de disparo se ha pulsado
			apagarLED();
			frenoVertical();
			_delay_ms(button_check_delay_ms);
			liberarCarrito();
			_delay_ms(2000);
			pararCarrito();
		}
	}
}