// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo:
// Al presionar un pulsador se enciende el LED correspondiente.

// Pseudocódigo: 
// - Compruebo la activación del pulsador comprobando los pines de entrada.
// - Si se activa un pulsador inicio un retardo sino sigo comprobando.
// - Espero desactivacion del pulsador.
// - Envío el valor correspondiente por el puerto de salida.

.INCLUDE "M16DEF.INC	//Incluye definición archivos ATmega16

.ORG 0
JMP PROGRAM		//Interrupción Reset

PROGRAMA:
	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R1			//Coloco la Pila al final de la RAM
  
	LDI R16,$00
	OUT DDRB,R16			//Puerto B entrada
	LDI R16,$0F
	OUT DDRD,R16			//Puerto D salida
  
	BUCLE: RCALL WAIT_ACTIVATION	//Espero la activación del pulsador
	OUT PORTD,R18			//Activo el LED correspondiente
	RJMP BUCLE

//......PROCEDIMIENTOS

WAIT_ACTIVATION:
	IN R18,PINB
	CPI R18,0B10101010
	BREQ WAIT_ACTIVATION

	CPI R18,0B10101000		//Compruebo Pulsador 1
	BRNE Noes0
	LDI R18,0B00000001
	RJMP Seguir
	Noes0:
	CPI R18,0B10100010		//Compruebo Pulsador 2
	BRNE Noes1
	LDI R18,0B00000010
	RJMP Seguir
	Noes1:
	CPI R18,0B10001010		//Compruebo Pulsador 3
	BRNE Noes2
	LDI R18,0B00000100
	RJMP Seguir
	Noes2:
	CPI R18,0B00101010		//Compruebo Pulsador 4
	BRNE WAIT_ACTIVATION
	LDI R18,0B00001000
	Seguir:
	RCALL RETARDO

WAIT_DEACTIVATION:
	IN R19,PINB
	CPI R19,0B10101010		//Compruebo desactivación de pulsador
	BRNE WAIT_DEACTIVATION
	RCALL RETARDO
	RET

RETARDO:				//Configurado Evitar Rebote
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