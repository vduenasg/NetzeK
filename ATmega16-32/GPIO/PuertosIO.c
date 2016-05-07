/*
 * PuertosIO.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo:
Al presionar un pulsador se enciende el LED correspondiente.

Pseudocódigo: 
- Compruebo la activación del pulsador comprobando los pines de entrada.
- Si se activa un pulsador inicio un retardo sino sigo comprobando.
- Espero desactivacion del pulsador.
- Envío el valor correspondiente por el puerto de salida.
 */ 
 
#include <avr/io.h>	//Incluyo las definiciones del ATmega16
#include "mdelay.h"	//Incluyo las definiciones de retardo

int main(void)
{
	DDRB &= ~(1<<PB1) | ~(1<<PB3) | ~(1<<PB5) | (1<<PB7);
	//PB1, PB3, PB5, PB7 como entrada
	DDRD |= (1<<PD0) | (1<<PD1) | (1<<PD2) | (1<<PD3);
	//PD0, PD1, PD2, PD3 como salida
	PORTD=0x00;
	//Apago todos los LED's inicialmente
	
	while(1)
	{
		_delay_ms(300);
		//Delay para evitar efecto rebote
		switch(PINB)
		{
			case 0b10101000:
			PORTD = 0b00000001;
			break;
			case 0b10100010:
			PORTD = 0b00000010;
			break;
			case 0b10001010:
			PORTD = 0b00000100;
			break;
			case 0b00101010:
			PORTD = 0b00001000;
			break;
			default:
			break;
		}
	}
}
	