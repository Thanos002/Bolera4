
#include <avr/io.h>

#ifndef BOLERA
#define BOLERA

// dir -> 1 derecha, 0 izquierda

// *******
// MOTORES
// *******

//MACROS
{
	#define M1_diPORT	PK6
	#define M1_diDDR	DDK6
	#define M1_diPIN	PINK6

	#define M1_enPORT	PL0
	#define M1_enDDR	DDL0
	#define M1_enPIN	PINL0

	#define M2_diPORT	PK7
	#define M2_diDDR	DDK7
	#define M2_diPIN	PINK7

	#define M2_enPORT	PL1
	#define M2_enDDR	DDL1
	#define M2_enPIN	PINL1

	#define M2_bkPORT	PL3
	#define M2_bkDDR	DDL3
	#define M2_bkPIN	PINL3

	#define M3_diPORT	PL2
	#define M3_diDDR	DDL2
	#define M3_diPIN	PINL2

	#define M3_enPORT	PL4
	#define M3_enDDR	DDL4
	#define M3_enPIN	PINL4

	#define M4_diPORT	PL5
	#define M4_diDDR	DDL5
	#define M4_diPIN	PINL5

	#define M4_enPORT	PL7
	#define M4_enDDR	DDL7
	#define M4_enPIN	PINL7

	#define M5_diPORT	PD5
	#define M5_diDDR	DDD5
	#define M5_diPIN	PIND5

	#define M5_enPORT	PD7
	#define M5_enDDR	DDD7
	#define M5_enPIN	PIND7

}


void girarSistemaLanzador(int dir);
void pararSistemaLanzador();

// M1: Elevador de Cargas
void subirElevadorCargas();

void bajarElevadorCargas();

void pararElevadorCargas();

// M2: Giro vertical

void girarVertical(int dir);

void frenoVertical();

// M3: Vastago

void 

// M4: Carrito

void engancharCarrito();
void liberarCarrito();

// M5: Elevador de retorno de bolas

void elevarBola();
void bajarBola();

// *******
// SENSORES SW
// *******

//MACROS
{
	#define SW1PORT PD6
	#define SW1DDR	DDD6
	#define SW1PIN	PIND6
	
	#define SW6PORT PD4
	#define SW6DDR	DDD4
	#define SW6PIN	PIND4
	
	
	
	#define SWEICR 	EICRA//configurar en función de las necesidades
	#define SWEIMSK EIMSK//0b00001111
	
	#define SW2EIFR INTF0
	#define SW3EIFR INTF1
	#define SW4EIFR INTF2
	#define SW5EIFR INTF3
}


// Sensor SW1:

int getSensor1();
bool reachedFin1(){
	return getSensor1()==0;
}

// Sensor SW2:
// ojo: aqui fin de carrera tambien en la mitad del trayecto!

void getSensor2();
bool reachedFin2(){
	return getSensor2()==0;
}

// Sensor SW3:

void getSensor3();
bool reachedFin3(){
	return getSensor3()==0;
}

// Sensor SW4:

void getSensor4();
bool reachedFin4(){
	return getSensor4()==0;
}

// Sensor SW5:

void getSensor5();
bool reachedFin5(){
	return getSensor5()==0;
}

// Sensor SW6:

void getSensor6();
bool reachedFin6(){
	return getSensor6()==0;
}

// *******
// SENSORES OPTICOS
// *******

//MACROS
{
	#define SOPCICR		PCICR //0b00000100
	#define SOPCMSK		PCMSK2//0b00111111
	#define SOPCIFR		PCIFR	
	
	#define SO1PIN		PINK0
	#define SO2PIN		PINK1
	#define SO3PIN		PINK2
	#define SO4PIN		PINK3
	#define SO5PIN		PINK4
	#define SO6PIN		PINK5
	

	
	
}
}

int getOptico(int num){
	readBit(PORTK, num)
}

bool pinIsFallen(int num){
	return getOptico(num)==1;
}

// *******
// LED Y DISPLAYS
// *******

//MACROS
{
	#define L1PORT		PL6
	#define L1DDR		DDL6
	#define L1PIN		PINL6

	#define DaPORT		PB0
	#define DaDDR		DDB0
	#define DaPIN		PINB0
	
	#define DbPORT		PB1
	#define DbDDR		DDB1
	#define DbPIN		PINB1	
	
	#define DcPORT		PB2
	#define DcDDR		DDB2
	#define DcPIN		PINB2	
	
	#define DdPORT		PB3
	#define DdDDR		DDB3
	#define DdPIN		PINB3
	
	#define DePORT		PB4
	#define DeDDR		DDB4
	#define DePIN		PINB4
	
	#define DfPORT		PB5
	#define DfDDR		DDB5
	#define DfPIN		PINB5
	
	#define DgPORT		PB6
	#define DgDDR		DDB6
	#define DgPIN		PINB6
	
	#define DSPORT		PB7
	#define DSDDR		DDB7
	#define DSPIN		PINB7					
}
}
#endif