// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo1 - Timer en Modo Normal:
// Este programa es usado como contador de eventos externos.
// - Cada vez que se produce desbordamiento se incrementa una variable.
// - Al activar la interrupción 0 se guarda el valor de TCNT0.

// Pseudocódigo:
// - Configuro el Timer 0 en Modo Normal.
// - Al producirse 256 conteos enciendo el LED e incremento una variable.
// - Al producir la interrupción externa INT0 capturo el valor del contador.

.INCLUDE "M16DEF.INC"			//Incluye definicion archivos ATmega16

	.ORG $00
	JMP PROGRAMA			//Interrupcion Reset
	.ORG $02
	JMP INTER0			//Interrupcion 0
	.ORG $12
	JMP TIMER0_COM			//Timer0 Compare Match

PROGRAMA:
	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16
		
	LDI R16,$01
	OUT DDRD,R16			//PD0 como salida
	LDI R16,0B00000110
	OUT TCCR0,R16			//Normal Port - Normal - Flanco de bajada
	LDI R16,0B00000001
	OUT TIMSK,R16

	LDI R16,0B00000010
	OUT MCUCR,R16			//INT0 Flanco de Bajada
	LDI R16,0B01000000
	OUT GICR,R16			//INT0 Habilitada

	SEI

BUCLE:	RJMP BUCLE

//......INTERRUPCIONES

INTER0:
	CALL RETARDO
	IN R17,TCNT0
	RETI

TIMER0_COM:
	INC R19
	IN R16,PORTD
	LDI R18,$01
	EOR R16,R18
	OUT PORTD,R16
	RETI

//......PROCEDIMIENTOS

RETARDO:
	LDI R25,31			//Configurado Evitar Rebote
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