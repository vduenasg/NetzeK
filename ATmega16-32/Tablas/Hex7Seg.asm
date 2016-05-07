// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo3:
// Ingresar un número hexadecimal y devolver su equivalente en código de 7 Segmentos.

// Pseudocódigo:
// - Cargo el valor en hexadecimal.
// - Calculo la posición del valor de la posición.
// - Cargo el valor de la posición calculada.

.INCLUDE "M16DEF.INC"	//Incluye definición archivos ATmega16

	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16			//Coloco la Pila al final de la RAM
		
	LDI R16,$0B			//Coloco en R16 la cifra hexadecimal

	LDI R30,LOW(TablaHex7Seg<<1)
	LDI R31,HIGH(TablaHex7Seg<<1)	//Cargo en el puntero Z la dirección de la tabla TablaHex7Seg
	ADD R30,R16
	LDI R16,0
	ADC R30,R16
	LPM R16,Z			//Cargo el R16 el código correspondiente
		
BUCLE:	RJMP BUCLE			//Bucle infinito

//......TABLAS

.CSEG
.ORG 0x100
TablaHex7Seg:
.DB 0B1111110,0B0110000		//0,1
.DB 0B1101101,0B1111001		//2,3
.DB 0B0110011,0B1011011		//4,5
.DB 0B1011111,0B1110000		//6,7
.DB 0B1111111,0B1111011		//8,9
.DB 0B1110111,0B0011111		//A,b
.DB 0B1001110,0B0111101		//C,d
.DB 0B1001111,0B1000111		//E,F