// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo1 - Modo CTC:
// Este programa genera dos señales periódicas con la misma frecuencia y desfasadas 180º

// Pseudocódigo:
// - Configuro el Timer en modo CTC.
// - Los valores de OCR están desfasados el uno al otro en 180º, esto se logra
//   multiplicando a uno de los OCR por 0.01.

.INCLUDE "M16DEF.INC"			//Incluye definicion archivos ATmega16
.EQU TOP=(8000000/(2*64*1))-1
.EQU VALOR_OCR1A=TOP*0.01
.EQU VALOR_OCR1B=TOP

	.ORG $00
	JMP PROGRAMA			//Interrupcion Reset

PROGRAMA:
	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16
		
	LDI R16,0B00110000
	OUT DDRD,R16			//OC1A y OC1B Salida
		
	LDI R16,HIGH(VALOR_OCR1A)
	OUT OCR1AH,R16
	LDI R16,LOW(VALOR_OCR1A)
	OUT OCR1AL,R16

	LDI R16,HIGH(VALOR_OCR1B)
	OUT OCR1BH,R16
	LDI R16,LOW(VALOR_OCR1B)
	OUT OCR1BL,R16

	LDI R16,0B00011011
	OUT TCCR1B,R16
	LDI R16,0B01010000
	OUT TCCR1A,R16			//Modo 12 - Toggle - CTC - Clk/64

	LDI R16,HIGH(TOP)
	OUT ICR1H,R16
	LDI R16,LOW(TOP)
	OUT ICR1L,R16
		
BUCLE:	RJMP BUCLE