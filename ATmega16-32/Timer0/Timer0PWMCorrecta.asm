// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo4 - Timer en PWM Correcta:
// Este programa genera en OC0 una señal periódica, cada vez que se presiona un pulsador, aumenta el ciclo de trabajo, y al presionar el otro pulsador disminuye el ciclo de trabajo.

// Pseudocódigo:
// - Configuro al timer en modo PWM Correcta.
// - Cada vez que se inicia una interrupción externa se aumenta o disminuye el valor de OCR.

.INCLUDE "M16DEF.INC"		//Incluye definición archivos ATmega16

.EQU OCR_INICIAL=128

	.ORG $00
	JMP PROGRAMA		//Interrupción Reset
	.ORG $02
	JMP INTER0		//Interrupción 0
	.ORG $04
	JMP INTER1		//Interrupción 1

PROGRAMA:
	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16
		
	LDI R16,0B00001000
	OUT DDRB,R16		//Habilito salida OC0
	LDI R17,OCR_INICIAL
	OUT OCR0,R17		//Coloco la señal al 50% ciclo de trabajo
	LDI R16,0B01100101
	OUT TCCR0,R16		//No invertido OC0 - PWM Correcta - CLK/1024
	LDI R16,0B00001010
	OUT MCUCR,R16		//INT0 e INT1 Flanco de Bajada
	LDI R16,0B11000000
	OUT GICR,R16		//INT0 e INT1 Habilitada

	SEI

BUCLE:	RJMP BUCLE

//......INTERRUPCIONES

INTER0:	
	CALL RETARDO
	CPI R17,0
	BREQ Salir0
	DEC R17
	OUT OCR0,R17
	Salir0:
	RETI

INTER1:
	CALL RETARDO
	CPI R17,255
	BREQ Salir1
	INC R17
	OUT OCR0,R17
	Salir1:
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