/*
 * prueba3.c
 *
 * Created: 15/05/2023 13:30:02
 * Author : mario
 */ 
/* Activos por nivel alto:							Activos por nivel bajo:		
		  Sgfedcba									  Sgfedcba		
 0:		0b00111111;									0b01000000;		
 1:		0b00000110;									0b01111001
 2:		0b01011011;									0b00100100								
 3:		0b01001111;									0b00110000
 4:		0b01100110;									0b00011001
 5:		0b01101101;									0b00010010
 6:		0b01111101;									0b00100000
 7:		0b00000111;									0b01111000
 8:		0b01111111;									0b00000000
 9:		0b01101111;									0b00011000
 default: 0b00000001;
*/	


#include <avr/io.h>
#include <avr/interrupt.h>
//#include <stdlib.h>			//Se usaba para la funcion rand del tiempo aleatorio.
	

uint8_t tiempoSelector = 0;
uint8_t puntuacion = 0;


void setup_timer0(){
	TCCR0A = 0b00000010;	//Para modo CTC
	TCCR0B = 0b00000011;	//Para modo CTC y prescaler 64
	TIMSK0 = 0b00000010;	//Para habilitar OCR0A
	OCR0A  = 124;			//Para interrumpir cada ms
	
}

void setup(){
	cli();
	setup_timer0();			//Para el setup del timer 0
	DDRK = 0xC0;    //0b11000000
	PCICR = (1<<PCIE2);
	PCMSK2 = 0x3F;   //0b00111111 Hay que habilitarlos cuando llegue la señal de disparo, pq durante las deshabilitamos
	DDRB = 0xFF;				//Puerto B configurado como salidas para controlar display 7 segmentos y selector
	
	//El pin 7 del puerto B controla la selección de displays, los otros 7 pines el numero que aparece
	//Un '0' en la señal enciende el display
	PORTB = 0b00111111;				//Inicialemente a 0 en el display 0
	
	DDRD = 0b00100000;				//Entradas salvo el bit 5 que es salida para motor
	//Ver si esos sensores SW son normalemente activos o bajos...
	
	
	sei();
}

int main(void)
{
	setup();
    /* Replace with your application code */
    while (1) 
    {
		if(~PIND & (0b00010000)){				//En teoría el resto por señales bajas
			PCMSK2 = 0x3F;					//Rehabilitar las interrupciones de los bolos
		}
	}
		
	
}

ISR(TIMER0_COMPA_vect){						//Interrupcion que ocurre cada 1ms
	tiempoSelector++;
if(tiempoSelector == 5){					//Cada 5 ms
		tiempoSelector = 0;					//Para resetar esa variable al cambiar de display
		//Preguntar Jorge pero creo que PORT7B no vale, tiene que ser PORTXi --> PXi para los puertos de E/S. No lo que pone en el datasheet, para este caso.
		PORTB ^= (1<<PB7);					//Máscara en el bit de seleccion para alternarlo cada 5 ms, es decir un refresco de 200 veces/segundo	
		//Posible bandera 'Selector	
		
		if(PINB & (1 << PB7)){				//Si está seleccionado Display 1, decenas
			setDisplay(puntuacion/10);
		}
		else{								//Si esta seleccionado Display 0, unidades
			setDisplay(puntuacion%10);
		}
		
		
}
	
	
}
void setDisplay(int numero){
	
	//Primero hago un lienzo, en el que pongo los displays apagados durante el ciclo de reloj para después poder poner el numero al gusto
	PORTB &= ~(1<<PB6)&~(1<<PB5)&~(1<<PB4)&~(1<<PB3)&~(1<<PB2)&~(1<<PB1)&~(1<<PB0);  //Todos los bits de esos puertos a 1_
	//PORTB = 0bX0000000
	switch(numero)
	{
		case 0:	//0b00111111;
		PORTB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5);
		break;
		case 1:	//0b00000110;
		PORTB |= (1<<PB1)|(1<<PB2);
		break;
		case 2: //0b01011011;
		PORTB |= (1<<PB0)|(1<<PB1)|(1<<PB3)|(1<<PB4)|(1<<PB6);
		break;
		case 3: //0b01001111;
		PORTB |= (1<<PB6)|(1<<PB3)|(1<<PB2)|(1<<PB1)|(1<<PB0);
		break;
		case 4: //0b01100110;
		PORTB |= (1<<PB1)|(1<<PB2)|(1<<PB5)|(1<<PB6);
		break;
		case 5: //0b01101101;
		PORTB |= (1<<PB0)|(1<<PB2)|(1<<PB3)|(1<<PB5)|(1<<PB6);
		break;
		case 6: //0b01111101;
		PORTB |= (1<<PB0)|(1<<PB5)|(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB6);
		break;
		case 7: //0b00000111;
		PORTB |= (1<<PB0)|(1<<PB1)|(1<<PB2);
		break;
		case 8: //0b01111111;
		PORTB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5)|(1<<PB6);
		break;
		case 9: //0b01101111;
		PORTB |= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB5)|(1<<PB6);
		break;
		default:
		PORTB |= (1<<PB6);
	}
}

ISR(PCINT2_vect){ //Cuidado que era por flanco de bajada
	puntuacion++;
	volatile uint8_t puertoactual = ~PINK;  //PINK normalmente estará a 1 !!
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