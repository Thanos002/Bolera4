/*
 * SensoresBolos.c
 *
 * Created: 09/05/2023 8:55:28
 * Author : mario
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t puntuacion = 0;
//volatile uint8_t puertoanterior = 0xFF;			//Preguntar Jorge, volatile y el fallo que nos daba de entrar a dos interrupciones

void setup(){
	cli();
	DDRK = 0xC0;    //0b11000000
	//PORTK |= (1 << PK0) | (1 << PK1) | (1 << PK2) | (1 << PK3) | (1 << PK4) | (1 << PK5);
 // Activa las resistencias de pull-up pq normalmente esta en nivel alto
	PCICR = (1<<PCIE2);
	PCMSK2 = 0x3F;   //0b00111111 Hay que habilitarlos cuando llegue la señal de disparo, pq durante las deshabilitamos
	sei();
}


int main(void)
{
	setup();
    /* Replace with your application code */
    while (1) 
    {
    }
}

ISR(PCINT2_vect){ //Cuidado que era por flanco de bajada
	puntuacion++;
	volatile uint8_t puertoactual = ~PINK;
	//volatile uint8_t bitscambiados= 0;
//	bitscambiados = ~(puertoactual ^ puertoanterior); //Lo negamos por el tema de que esta en nivel alto y pasa a nivel bajo
	
	//AND bit a bit para determinar si un bit en particular ha cambiado en el puerto
	if(puertoactual & (0b00000001)){
		PCMSK2 &=~(1<<PCINT16);
		} //Deshabilito esa interrupcion para que no rebote
	if(puertoactual & (0b00000010))
	{PCMSK2 &=~(1<<PCINT17);
	}
	if(puertoactual & (0b00000100))
	{PCMSK2 &=~(1<<PCINT18);
	}
	if(puertoactual & (0b00001000))
	{PCMSK2 &=~(1<<PCINT19);
	}
	if(puertoactual & (0b00010000))
	{PCMSK2 &=~(1<<PCINT20);
	}
	if(puertoactual & (0b00100000))
	{PCMSK2 &=~(1<<PCINT21);
	}
//ese and del if entra siempre que en 1 de los 8 bits salga un 1
	//	puertoanterior=puertoactual;
}