// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo2:
// Colocar el valor $EE en los primeros 400 bytes de la memoria RAM.

// Pseudocódigo:
// - Cargo el valor que deseo colocar en los bytes correspondientes.
// - Inicio el procedimiento de "llenado" dos veces ya que cada "llenado" esta colocando el valor en 200 bytes.

.INCLUDE "M16DEF.INC"	//Incluye definicion archivos ATmega16

	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16		//Coloco la Pila al final de la RAM

	LDI R20,$EE		//Cargo el valor $EE en R20
	LDI ZH,$00
	LDI ZL,$60		//Ubico inicio de RAM en el puntero Z
	CALL LLENADO
	CALL LLENADO		//Cada procedimiento solo puede llenar hasta 200 bytes

BUCLE:	RJMP BUCLE		//Bucle infinito

//......PROCEDIMIENTOS

LLENADO:
	PUSH R21		//Coloco en la Pila R21
	PUSH R16		//Coloco en la Pila R16
	IN R16,SREG
	PUSH R16		//Coloco en la Pila SREG

	LDI R21,200		//Cargo el numero de bytes
	Colocar:
	ST Z+,R20		//Coloco $EE en la RAM y post_incremento Z
	DEC R21			//Decremento el numero de bytes
	BRNE Colocar

	POP R16			//Recupero SREG de la Pila
	OUT SREG,R16
	POP R16			//Recupero R16 de la Pila
	POP R21			//Recupero R21 de la Pila
	RET			//Retorno del procedimiento