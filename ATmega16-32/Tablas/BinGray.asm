// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo1:
// Ingresar un valor en Binario Natural y obtener su equivalente en Código Gray.

// Pseudocódigo:
// - Cargo el valor en binario.
// - Cargo la dirección de la tabla.
// - Calculo la posición del código correspondiente en gray.

.INCLUDE "M16DEF.INC"	//Incluye definicion archivos ATmega16

	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16			//Coloco la Pila al final de la RAM
		
	LDI R16,0B00001100		//Coloco en R16 la cifra binario (12)

	LDI ZL,LOW(TablaGRAY<<1)
	LDI ZH,HIGH(TablaGRAY<<1)	//Cargo en el puntero Z la dirección de la tabla TablaGRAY
	ADD ZL,R16
	LDI R16,0
	ADC ZL,R16
	LPM R16,Z			//Cargo el R16 el código correspondiente
		
BUCLE:	RJMP BUCLE			//Bucle infinito

//......TABLAS

.CSEG
.ORG 0x100
TablaGRAY:
.DB 0B0000,0B0001,0B0011,0B0010		//0,1,2,3
.DB 0B0110,0B0111,0B0101,0B0100		//4,5,6,7
.DB 0B1100,0B1101,0B1111,0B1110		//8,9,10,11
.DB 0B1010,0B1011,0B1001,0B1000		//12,13,14,15