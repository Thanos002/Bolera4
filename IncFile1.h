#ifndef IncFile1_h__
#define IncFile1_h__

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/************************************************************************/
/*  Instrucciones:                                                                     
*	Los Macros PORT, DDR, PIN solo guardan el numero del pin correspondiente
*	Los Macros SWnX tienen la letra del port/pin (D = PORTD)
*	Esto se puede usar con setInput(SW1X,PORT) = setInput(DDR
*   Usar funciones L2***(L) para obtener la direccion del PORT(L)/PIN(L)...
*/
/************************************************************************/


//PORTS:

//MACROS SW PORTS

	//#define L2DDR(L)	DD##L
	//#define L2PIN(L)	PIN##L
	//#define L2PORT(L)	PORT##L

	#define SW1PORT PORTD
	#define SW1DDR	DDRD
	#define SW1PIN	PIND
	#define SW1X	PD6
	
	#define SW2PORT PORTD
	#define SW2DDR	DDRD
	#define SW2PIN	PIND
	#define SW2X	PD0
	
	#define SW3PORT PORTD
	#define SW3DDR	DDRD
	#define SW3PIN	PIND
	#define SW3X	PD1
	
	#define SW4PORT PORTD
	#define SW4DDR	DDRD
	#define SW4PIN	PIND
	#define SW4X	PD2
	
	#define SW5PORT PORTD
	#define SW5DDR	DDRD
	#define SW5PIN	PIND
	#define SW5X	PD3
	
	#define SW6PORT PORTD
	#define SW6DDR	DDRD
	#define SW6PIN	PIND
	#define SW6X	PD4
	
	#define SWEICR 	EICRA //configurar en función de las necesidades
	#define SWEIMSK EIMSK //0b00001111
	
	#define SW2EIFR INTF0
	#define SW3EIFR INTF1
	#define SW4EIFR INTF2
	#define SW5EIFR INTF3


//MACROS Motores

	#define M1_diPORT	PORTK
	#define M1_diDDR	DDRK
	#define M1_diPIN	PINK
	#define M1_di_X		PK6

	#define M1_enPORT	PORTL
	#define M1_enDDR	DDRL
	#define M1_enPIN	PINL
	#define M1_en_X		PL0

	#define M2_diPORT	PORTK
	#define M2_diDDR	DDRK
	#define M2_diPIN	PINK
	#define M2_di_X		PK7

	#define M2_enPORT	PORTL
	#define M2_enDDR	DDRL
	#define M2_enPIN	PINL
	#define M2_en_X		PL1

	#define M2_bkPORT	PORTL
	#define M2_bkDDR	DDRL
	#define M2_bkPIN	PINL
	#define M2_bk_X		PL3

	#define M3_diPORT	PORTL
	#define M3_diDDR	DDRL
	#define M3_diPIN	PINL
	#define M3_di_X		PL3

	#define M3_enPORT	PORTL
	#define M3_enDDR	DDRL
	#define M3_enPIN	PINL
	#define M3_en_X		PL4

	#define M4_diPORT	PORTL
	#define M4_diDDR	DDRL
	#define M4_diPIN	PINL
	#define M4_di_X		PL5

	#define M4_enPORT	PORTL
	#define M4_enDDR	DDRL
	#define M4_enPIN	PINL
	#define M4_en_X		PL7

	#define M5_diPORT	PORTD
	#define M5_diDDR	DDRD
	#define M5_diPIN	PIND
	#define M5_di_X		PD5

	#define M5_enPORT	PORTD
	#define M5_enDDR	DDRD
	#define M5_enPIN	PIND
	#define M5_en_X		PD7


// MACROS Sensores Opticos

	#define SOPCICR		PCICR //0b00000100
	#define SOPCMSK		PCMSK2//0b00111111
	#define SOPCIFR		PCIFR
	
	#define SO1PIN		PINK0
	#define SO2PIN		PINK1
	#define SO3PIN		PINK2
	#define SO4PIN		PINK3
	#define SO5PIN		PINK4
	#define SO6PIN		PINK5
	#define SOPIN		PINK
	


//MACROS LEDs y Display

	#define L1PORT		PORTL
	#define L1DDR		DDRL
	#define L1PIN		PINL
	#define L1X			PL6

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


//MACROS:
// B bit; P registro (p.e. D), V valor, interrupcion I
#define setBit(P, B) (P |= (1 << B))

#define clearBit(P, B) ((P) &= ~(1 << B))

//invertir bit
#define toggleBit(P, B) ((P)^=(1 << B))

// da el valor del bit
// #define readBit(P, B) ((P >> B) & 0x01)
#define readBit(P, B) (((P) & (1 << B)) >> B)

#define setOutput(P, B) ((P) |= (1 << B))
#define setInput(P, B) ((P) &= ~(1 << B))

#define writePWM(P, V) (OCR##P## = V)

// habilitar interrupciones externas
#define enableInterrupt(I) (EIMSK |= (1 << I))
#define disableInterrupt(I) (EIMSK &= ~(1 << I))
 
// para if/else, comprueba si pin numero B de puerto P es high/low
#define isHigh(P, B) (PIN##P & (1 << B))
#define isLow(P, B) (!(PIN##P & (1 << B)))

#endif // IncFile1_h__