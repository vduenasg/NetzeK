// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo1:
// Contar cuantos bits tienen valor uno en los 100 primeros bytes de la memoria RAM.

// Pseudocódigo:
// - Coloco la Pila al final de la RAM.
// - Defino el número de bytes a contar.
// - Cargo el contenido de primer byte.
// - Llamo al procedimiento para que cuente los unos en este byte.
// - Retorno del procedimiento.
// - Sumo los unos contados.
// - Cargo el siguiente byte y continuo hasta que los "n" bytes sean leídos y sus unos hayan sido contados.

.INCLUDE "M16DEF.INC"		//Incluye definición archivos ATmega16

	LDI R16,HIGH(RAMEND)	//Coloco la Pila al final de la RAM
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16

	LDI R17,100		//Cargo en R17 el numero de bytes a contar
	LDI ZH,$00
	LDI ZL,$00		//Inicio el puntero Z en $0000
	LDI R16,0		//Limpio el valor de R16

	Otrobyte:
	LD R16,Z+		//Cargo en R16 el contenido del Puntero Z
	CALL CONTAR_UNOS	//Inicio el procedimiento de contar unos
	ADD YL,R16
	LDI R16,0
	ADC YH,R16		//Sumo el numero de unos al puntero Y
	DEC R17			//Decremento el numero de bytes
	BRNE Otrobyte

BUCLE:	RJMP BUCLE		//Bucle infinito

//......PROCEDIMIENTOS

CONTAR_UNOS:
	PUSH R17		//Coloco en la Pila R17
	LDI R17,8		//Numero de bits
	LDI R18,0		//Numero de unos al inicio
	Otrobit:
	ROL R16			//Roto a la izquierda con acarreo
				//Cada vez que haya un uno, se ira al acarreo
	BRCC Escero		//Salto si no existe acarreo
				//Si no hay nada en el acarreo, es un cero
	INC R18			//Incremento el numero de unos
	Escero:
	DEC R17			//Decremento el numero de bits
	BRNE Otrobit		//Salto si NO es cero
	MOV R16,R18		//Muevo el valor contado a R16
	POP R17			//Recupero el valor de R17 de la Pila
	RET			//Regreso del Procedimiento