// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo3 - Input Capture:
// Este programa prende el led cada vez que se produce un flanco de bajada en ICP1.

// Pseudocódigo:
// - Configuro el Timer en modo Input Capture.
// - Cada vez que ocurre un flanco de bajada prende el LED.

.INCLUDE "M16DEF.INC"		//Incluye definicion archivos ATmega16

	.ORG $00
	JMP PROGRAMA		//Interrupcion Reset
	.ORG $0A
	JMP IN_CAP_1		//Input Capture 1

PROGRAMA:
	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16
		
	LDI R16,$01
	OUT DDRB,R16		//PB0 como salida
	LDI R16,0B00000000
	OUT TCCR1A,R16
	LDI R16,0B10000000
	OUT TCCR1B,R16		//Captura de entrada - Normal - Flanco de bajada
	LDI R16,0B00100000
	OUT TIMSK,R16

	SEI

BUCLE:	RJMP BUCLE

//......INTERRUPCIONES

IN_CAP_1:
	CALL RETARDO
	LDI R16,$01
	EOR R17,R16
	OUT PORTB,R17
	RETI

//......PROCEDIMIENTOS

RETARDO:			//Configurado Evitar Rebote
	LDI R25,31
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