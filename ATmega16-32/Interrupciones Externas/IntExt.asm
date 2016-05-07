// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo:
// El programa cambia el estado del LED correspondiente cada vez que se active el pulsador.

// Pseudocódigo:
// - Configuramos Interrupciones
// - Al producirse una interrupción el LED cambia de estado.

.INCLUDE "M16DEF.INC			//Incluye definición archivos ATmega16

.ORG $00
JMP PROGRAMA				//Interrupción Reset
.ORG $02
JMP INTER0				//Interrupción 0
.ORG $04
JMP INTER1				//Interrupción 1

PROGRAMA:
	LDI R16,HIGH(RAMEND)		//Coloco la Pila al final de la RAM
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16
 
	LDI R16,0B00000011
	OUT DDRA,R16			//Puerto A Salida
	  
	LDI R16,0B00001010
	OUT MCUCR,R16			//INT0 e INT1 Flanco de Bajada
	LDI R16,0B11000000
	OUT GICR,R16			//INT0 e INT1 Habilitada
	SEI

BUCLE: RJMP BUCLE

//......INTERRUPCIONES

INTER0:
	CALL RETARDO
	LDI R17,0B00000001
	CALL CAMBIAR
	RETI

INTER1:
	CALL RETARDO
	LDI R17,0B00000010
	CALL CAMBIAR
	RETI

//......PROCEDIMIENTOS

CAMBIAR:
	IN R16,PINA
	EOR R16,R17			//Cambio el estado del LED
	OUT PORTA,R16
	RET

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