// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo2 - PWM Fast:
// Este programa genera dos señales periódicas con la misma frecuencia pero con 
// ciclo de trabajo diferente.

// Pseudocódigo:
// - Configuro el Timer en modo PWM Fast
// - Los valores de OCR se multiplican por 0.35 y 0.75 respectivamente para obtener 
//   ciclos de trabajo del 75% y 35% respectivamente.

.INCLUDE "M16DEF.INC"			//Incluye definicion archivos ATmega16
.EQU TOP=(8000000/(64*30))-1
.EQU VALOR_OCR1A=TOP*0.75		//Ciclo de trabajo al 75%
.EQU VALOR_OCR1B=TOP*0.35		//Ciclo de trabajo al 35%

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
	LDI R16,0B10100010
	OUT TCCR1A,R16			//Modo 14 - No invertido - PWM Fast - Clk/64

	LDI R16,HIGH(TOP)
	OUT ICR1H,R16
	LDI R16,LOW(TOP)
	OUT ICR1L,R16
		
BUCLE:	RJMP BUCLE