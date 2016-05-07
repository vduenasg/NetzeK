/*
 * Timer1_CTC.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo1 - Modo CTC:
Este programa genera dos señales periódicas con la misma frecuencia y desfasadas 180º

Pseudocódigo:
- Configuro el Timer en modo CTC.
- Los valores de OCR están desfasados el uno al otro en 180º, esto se logra
  multiplicando a uno de los OCR por 0.01.
 */ 

#include <avr/io.h>
//Incluyo las definiciones del ATmega16

int main(void)
{
	DDRD |= (1<<PD5) | (1<<PD4);
	//Puerto D como salida
	TCCR1A |= (1<<COM1A0) | (1<<COM1B0);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	//Modo 12 - Toggle - CTC - Clk/64
	OCR1A = 62499*0.01;
	OCR1B = 62499;
	ICR1 = 62499;
    	while (1)
    	{
	}
}