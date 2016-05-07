// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo - Modo Asíncrono:
// Este programa enciende un LED un segundo y se apaga otro segundo.

// Pseudocódigo:
// - Configuro al Timer en modo asíncrono.
// - Genero una frecuencia de 0.5Hz.

.INCLUDE "M16DEF.INC"		//Incluye definición archivos ATmega16

.EQU VALOR_OCR=127

	.ORG $00
	JMP PROGRAMA		//Interrupción Reset

PROGRAMA:
	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16
	 
	LDI R16,$80
	OUT DDRD,R16		//OC2 como salida
	
	LDI R16,0B00011110
	OUT TCCR2,R16		//Toggle - CTC - Xtal/256
	LDI R16,VALOR_OCR
	OUT OCR2,R16
	LDI R16,0B00001000
	OUT ASSR,R16		//Modo asíncrono

BUCLE: RJMP BUCLE