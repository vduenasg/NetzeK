/*
 * Timer2.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo - Modo Asíncrono:
Este programa enciende un LED un segundo y se apaga otro segundo.

Pseudocódigo:
- Configuro al Timer en modo asíncrono.
- Genero una frecuencia de 0.5Hz.
 */ 

#include <avr/io.h>
//Incluyo las definiciones del ATmega16

int main(void)
{
	DDRD |= (1<<PD7);
	//PD7 como salida
	TCCR2 |= (1<<COM20) | (1<<WGM21) | (1<<CS22) | (1<<CS21);
	//Toggle - CTC - Xtal/256
	ASSR |= (1<<AS2);
	//Habilito el modo asíncrono
	OCR2 = 127;
    	while (1)
    	{
    	}
}