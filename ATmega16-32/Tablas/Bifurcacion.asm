// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo4:
// Cada vez que se ingrese el valor uno incremente el registro R17

// Pseudocódigo:
// - Cargo el número de la tabla de bifurcación.
// - Cargo la dirección de la tabla de bifurcación.
// - Realiza la operación correspondiente en la tabla.
// - Continúa con el programa.

.INCLUDE "M16DEF.INC"	//Incluye definicion archivos ATmega16

	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16			//Coloco la Pila al final de la RAM
		
	LDI R16,1			//Cargo el numero de la bifurcacion

	LDI ZL,LOW(Bifurcaciones)
	LDI ZH,HIGH(Bifurcaciones)	//Cargo en el puntero Z la direccion de la tabla de bifurcaciones
	ADD R16,R16
	ADD ZL,R16
	LDI R16,0
	ADC ZH,R16
	IJMP
	Seguir:

BUCLE:	RJMP BUCLE			//Bucle infinito

//......PROCEDIMIENTOS

CERO:
	NOP
	JMP Seguir
UNO:
	INC R17
	JMP Seguir
DOS:
	NOP
	JMP Seguir

//......TABLAS

.CSEG
.ORG 0x100
Bifurcaciones:
JMP CERO
JMP UNO
JMP DOS