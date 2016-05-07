// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo3:
// Realizar la suma de una o dos cifras BCD

// Pseudocódigo:
// - Cargo los valores a sumar en un registro.
// - Inicio el procedimiento de la suma.

.INCLUDE "M16DEF.INC"	//Incluye definicion archivos ATmega16
.DEF BCD_A=R16		//BCD 1 cifra
.DEF BCD_B=R17		//BCD 1 cifra
.DEF TMP_0=R18		//Registro temporal 0
.DEF NUM_A=R19		//BCD 2 cifras
.DEF NUM_B=R20		//BCD 2 cifras
.DEF TMP_1=R21		//Registro temporal 1
.DEF TMP_2=R22		//Registro temporal 2

	LDI R16,HIGH(RAMEND)
	OUT SPH,R16
	LDI R16,LOW(RAMEND)
	OUT SPL,R16		//Coloco la Pila al final de la RAM
		
	LDI BCD_A,$09
	LDI BCD_B,$09
	CALL SUMA_BCD_1		//Obtengo el resultado en TMP_0

	LDI NUM_A,$99
	LDI NUM_B,$99
	CALL SUMA_BCD_2		//Obtengo las centenas en TMP_2
				//Obtengo las decenas y unidades en TMP_1
		
BUCLE:	RJMP BUCLE		//Bucle infinito

//......PROCEDIMIENTOS

SUMA_BCD_1:
	ADD BCD_A,BCD_B		//Sumo las cifras
	BRHC Salto_1		//Salto si no hay acarreo
	RJMP Salto_2
	Salto_1:
	CPI BCD_A,10		//Comparo con 10
	BRLT Salir		//Si es menor salgo del procedimiento
	Salto_2:
	LDI BCD_B,6		//Cargo 6 a BCD_B
	ADD BCD_A,BCD_B		//Sumo el resultado con 6
	MOV TMP_0,BCD_A
	Salir:
	RET			//Salgo del procedimiento

SUMA_BCD_2:
	MOV BCD_A,NUM_A
	ANDI BCD_A,$0F
	MOV BCD_B,NUM_B
	ANDI BCD_B,$0F
	CALL SUMA_BCD_1		//Sumando las unidades
	MOV TMP_1,BCD_A
	ANDI NUM_A,$F0
	SWAP NUM_A
	MOV BCD_A,NUM_A
	ANDI NUM_B,$F0
	SWAP NUM_B
	MOV BCD_B,NUM_B
	CALL SUMA_BCD_1		//Sumando las decenas
	MOV TMP_2,BCD_A
	SWAP BCD_A
	ANDI BCD_A,$F0
	SWAP TMP_2
	ANDI TMP_2,$0F
	ADD TMP_1,BCD_A
	RET