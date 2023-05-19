/*
 * Elevadores.c
 *
 * Created: 09/05/2023 13:24:24
 * Author : iagol
 */ 



#include <avr/io.h>
#include <avr/interrupt.h>

#include "IncFile1.h"



int ERpos;
int ECPos;
int rutina=0;
int current_time=0;
int bandera=0;
int disparador=0;

//MOTORES 
// EC: M1 di: PK6  en: PL0
// ER: M5 di: PD5  en: PD7
//SW
// EC: SW1: PD6
// ER: SW5: PD3 /INT3

//PULSADOR DIRSPARO
// SW6: PD2 INT2 


//SET UP//

void setuptimer(){	
	
	
		TCCR0A= 0b00000010;
		TCCR0B=0b00000011;
		TIMSK0=0b00000010;
		OCR0A=124;
		TIFR0=0b00000010;
	
	
	}
	
void setupEC(){

		setBit(DDRK,6);			//M1_diDDR=0x01
		setBit(DDRL,0);			//M1_enDDR=0x01;
		clearBit(DDRD,6);		//SW1DDR=0x01;
		clearBit(PORTL,0);		//M1_enPORT=0;
		
	
}

void setupER(){
	
		setBit(DDRD,5);			//M5_diDDR=0x01;
		setBit(DDRD,7);			//M5_enDDR=0x01;
		clearBit(DDRD,3);
		EICRA|=0x80;			//flanco de bajada
		EIMSK|=0x08;			//INT3
		EIFR|=0x08;
		clearBit(PORTD,7);		//M5_enPORT=0;
		
	
}

void setupulsador() {
	clearBit(DDRD,2);		//PD4 Pulsador de disparo
	EICRA|=0x20;			//flanco de bajada
	EIMSK|=0x04;			//INT3
	EIFR|=0x04;
	
}

void setup(){
	cli();
	setuptimer();
	setupEC();
	setupER();
	setupulsador();
	sei();}



//Rutina de espera 

void wait(int t){
	volatile int t0=current_time;
	while( current_time-t0<t){}
}


//void delay(int ms){
	//for(int i=0;i<ms;i++){
		//for(volatile int j=0;j<400;j++){}
	//}
//}




//FUNCIONES EC//



void bajaEC(){
	if(ECPos==1){
		clearBit(PORTK,6);			//M1_diPORT=0x00;
		setBit(PORTL,0);			//M1_enPORT=0x01;
		wait(1000);
		while((PIND & 0x40)!=0){}	//Espera a que vuelva a saltar SW
		clearBit(PORTL,0);			//M1_enPORT=0
		ECPos=0;
	}
}

void subeEC(){
	if(ECPos==0){
		setBit(PORTK,6);			//M1_diPORT=0;
		setBit(PORTL,0);			//M1_enPORT=1;
		wait(1000);	//Espera a que el SW1 se haya dejado de pulsar.
		while((PIND & 0x40)==1){}	//Espera a que vuelva a saltar SW
		clearBit(PORTL,0);			//M1_enPORT=0
		ECPos=1;
	}	
}

//FUNCIONES HOME

void homeEC(){
	
		setBit(PORTK,6);			//M1_diPORT=0x00; sube
		setBit(PORTL,0);			//M1_enPORT=0x01;
		wait(2000);					//Espera 2 segundos para asegurarse de que baja
		clearBit(PORTL,0);			//M1_enPORT=0
		ECPos=1;
	
}

void homeER(){
								//Coloca el motor en su posición inicial
		clearBit(PORTD,5);		//M5 di=1
		setBit(PORTD,7);		//M5 en=1
		wait(3000);				//Espera 4 segundos para asegurarse de que sube
		clearBit(PORTD,7);
		ERpos=0;
		bandera=0;
	
}

//FUNCIONES ER//


void bajaER(){
	if(ERpos==1){
		clearBit(PORTD,5);	//M5_diPORT=0x01;
		setBit(PORTD,7);	//M5_enPORT=0x01;
	}	
}


void subeER(){
	if(ERpos==0){
		setBit(PORTD,5);	//M5_diPORT=0x00;
		setBit(PORTD,7);	//M5_enPORT=0x01;
	}
}
//Devuelve la posición de ER

int estadoER(){return ERpos;}

////Parada ER sin interrupciones (por si acaso)
//
//int bajaERsin(){
	//
	//setBit(PORTD,5);//M5_diPORT=0x01;
	//setBit(PORTD,7);//M5_enPORT=0x01;
	//while(PIND3==0){}//Espera a que el SW se haya dejado de pulsar.
	//while(PIND3==1){}//Espera a que vuelva a saltar SW
	//clearBit(PORTD,7);//M1_enPORT=0
	//return 0;
//}
//int subeERsin(){
	//
	//clearBit(PORTD,5);//M5_diPORT=0x00;
	//setBit(PORTD,7);//M5_enPORT=0x01;
	//while(PIND3==0){}//Espera a que el SW se haya dejado de pulsar.
	//while(PIND3==1){}//Espera a que vuelva a saltar SW
	//clearBit(PORTD,7);//M1_enPORT=0
	//return 0;
//}



//int disparador(){return}

//INTERRUPCIONES//


//Cuando ER toca el tope nos dice donde está
ISR(INT3_vect) {
	/*if(bandera==1){*/
	if((PIND & 0x10)==0){	//M5 di= 1
		ERpos=0;
		clearBit(PORTD,7);
		bandera=0;
	}
	if((PIND & 0x10)==1){	//M5 di= 0
		ERpos=1;
		clearBit(PORTD,7);
		bandera=0;
	}
	//if (rutina==1){			//Rutina de reacomodo
		//if(ERpos==1){
			//bajaER();
			//rutina=0;
			//bandera=0;
		//}
	
		
	//}

// 	}
// 		else{bandera=1;}
}

ISR(TIMER0_COMPA_vect)
{
	current_time++;
}	

ISR(INT2_vect)
{
	disparador=1;
}



//FUNCION DISPARADOR

int disparo(){
	if(disparador==1){
		disparador=0;
		return 1;
	}
	else{
		return 0;
	}
}

//FUNCIONES COMPLEJAS//


int recarga(int td,int ultimo_disparo){//td es el tiempo de delay y ultimo disparo indica si se ha realizado el disparo posterior a 30s
	wait(td);
	rutina=1;
	subeER();
	if(ultimo_disparo==1){
		while((PIND & 0x10)!=1){} //PD4 Pulsador de disparo
	}
return 0;
}


//MAIN
int main(void)
{
	setup();
	
	homeER();
	//homeEC();
	
	subeER();
	wait(2000);
	bajaER();

	
     while (1) 
	
    {
	
    }
}

