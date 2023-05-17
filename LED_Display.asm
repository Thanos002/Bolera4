 /*

El codigo muestra el valor del Regsitro especificado (R18) 

*/ 
 
 .include "m640def.inc"  // include para ATmega640

   .def temp    = r16 

   // change to change ports
   .equ SEG7_PORT= PORTB
   .equ SEG7_DDR = DDRB

   .cseg 
   .org 0 

// store values to drive 7-segment display
// DP default on (8), needs to be alternated
segments:
   ; digits 0-9
   .db 0b11000000, 0b11111001, 0b10100100, 0b10110000
   .db 0b10011001, 0b10010010, 0b10000010, 0b11111000
   .db 0b10000000, 0b10011000
   ; letters A-F
   .db 0b10001000, 0b10000010, 0b11000010, 0b10101000
   .db 0b10010000, 0b10000110, 0b11000001

Start:
	out SEG7_PORT, R18;  // mostar valor de registro R18


// TODO:
// falta el codigo para actualizar el valor y alternar DP cada pocos milisegundos