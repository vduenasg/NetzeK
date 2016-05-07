// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo:
// - Colocar el valor $AA en los 100 primeros bytes de la memoria.
// - Realizar el copiado de los 100 primeros bytes de la memoria hacia la posición $0200 de la memoria.

// Pseudo-código:
// - Defino el número de bytes que serán copiados.
// - Defino la posición inicial donde serán colocados los "n" primeros bytes.
// - Defino la posición donde serán movidos los "n" bytes.
// - Coloco los "n" bytes usando modo de direccionamiento con post-incremento.

.INCLUDE "M16DEF.INC"	//Incluye definición archivos ATmega16

LDI R16,10		//Cargo el numero de bytes a colocar
LDI XH,$00
LDI XL,$6		//Cargo el inicio de la RAM en el puntero X
LDI ZH,$02
LDI ZL,$0		//Cargo la posición $0200 en el puntero Z

LDI R18,$A		//Cargo el valor $AA para colocar en los 100 primeros bytes de la RAM
Colocar:
ST X+,R1		//Coloco el valor $AA y post-incremento la dirección
DEC R16			//Decremento en uno el numero de bytes
BRNE Colocar		//Salto a colocar hasta que no hayan más bytes para copiar

			//Copio los 100 bytes a las posición $0200
LDI R16,10		//Cargo el numero de bytes a copiar
LDI XH,$00
LDI XL,$6		//Cargo el inicio de la RAM en el puntero X

Copiar:
LD R17,X		//Cargo el valor de la posición de la RAM
ST Z+,R1		//Coloco el valor cargado en la posición $0200
DEC R16
BRNE Copiar

BUCLE: RJMP BUCLE	//Bucle infinito