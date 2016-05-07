// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo2:
// Ingresar un valor en Código Gray y obtener su equivalente en Binario Natural.

// Pseudocódigo:
// - Cargo el valor en código gray.
// - Inicio un puntero para la tabla en binario.
// - Calculo la primera posición.
// - Comparo si el valor en la posición es igual al puntero.
// - Si es igual se muestra el número.
// - Sino es igual calculo la siguiente posición y sigo comparando hasta encontrar la comparación correcta.

.INCLUDE "M16DEF.INC"	//Incluye definición archivos ATmega16

	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16			//Coloco la Pila al final de la RAM
	
	LDI R16,0B00000111		//Coloco en R16 la cifra GRAY (5)

	LDI R18,0			//R18 es mi indice
	Seguir:
	MOV R17,R18
	LDI ZL,LOW(TablaGRAY<<1)
	LDI ZH,HIGH(TablaGRAY<<1)	//Cargo en el puntero Z la dirección de la tabla TablaGRAY
	ADD ZL,R17
	LDI R17,0
	ADC ZL,R17
	LPM R17,Z			//Cargo el R17 el código correspondiente
	CP R17,R16			//Comparo con mi cifra GRAY
	BRNE Incrementar
	MOV R16,R17			//Obtengo mi cifra GRAY en R16
		
BUCLE:	RJMP BUCLE			//Bucle infinito

	Incrementar:
	INC R18
	RJMP Seguir

;.......TABLAS

.CSEG
.ORG 0x100
TablaGRAY:
.DB 0B0000,0B0001,0B0011,0B0010		//0,1,2,3
.DB 0B0110,0B0111,0B0101,0B0100		//4,5,6,7
.DB 0B1100,0B1101,0B1111,0B1110		//8,9,10,11
.DB 0B1010,0B1011,0B1001,0B1000		//12,13,14,15