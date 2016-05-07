// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo2 - Timer en modo CTC:
// Este programa genera en OC0 una señal periódica de 5ms de nivel alto y 2ms de nivel bajo al presionar el pulsador.

// Pseudocódigo:
// - Al activar la interrupción externa configuro el timer en modo CTC.
// - Cada vez que se produce interrupción en el timer se cambia el valor de OCR.

.INCLUDE "M16DEF.INC"		//Incluye definición archivos ATmega16

.EQU OCR_2ms=15
.EQU OCR_5ms=38

	.ORG $00
	JMP PROGRAMA		//Interrupción Reset
	.ORG $02
	JMP INTER0		//Interrupcion 0
	.ORG $26
	JMP TIMER0		//Interrupcion Timer 0

PROGRAMA:
	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16
	
	LDI R16,0B00000010
	OUT MCUCR,R16		//INT0 Flanco de Bajada
	LDI R16,0B01000000
	OUT GICR,R16		//INT0 Habilitada

	LDI R17,$01

	SEI

BUCLE:	RJMP BUCLE

;.......INTERRUPCIONES

INTER0:	
	CALL RETARDO
	LDI R16,0B00001000
	OUT DDRB,R16		//Habilito salida OC0
	LDI R16,0B00011101
	OUT TCCR0,R16		//Toggle OC0 - CTC - CLK/1024
	LDI R16,0B00000010
	OUT TIMSK,R16		//Habilito OC0 por Igualdad en Comparacion
	RETI

TIMER0:
	EOR R0,R17		//Con cada EOR cambia el valor OCR
	BREQ Escero
	LDI R16,OCR_5ms
	OUT OCR0,R16
	RJMP Salida
	Escero:
	LDI R16,OCR_2ms
	OUT OCR0,R16
	Salida:
	RETI

//......PROCEDIMIENTOS

RETARDO:
	LDI R25,31		//Configurado Evitar Rebote
	Bucle_Externo:
	LDI R24,255
	Bucle_Interno:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	DEC R24
	BRNE Bucle_Interno
	DEC R25
	BRNE Bucle_Externo
	RET