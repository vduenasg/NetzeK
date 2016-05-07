/*
 * Timer1_IC.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo3 - Input Capture:
Este programa prende el led cada vez que se produce un flanco de bajada en ICP1.

Pseudocódigo:
- Configuro el Timer en modo Input Capture.
- Cada vez que ocurre un flanco de bajada prende el LED.
 */ 

#include <avr/io.h>
//Incluyo las definiciones del ATmega16
#include <avr/interrupt.h>
//Incluyo las definiciones de las Interrupciones
#include "mdelay.h"
//Incluyo las definiciones de retardo

//__INTERRUPCIONES
ISR(TIMER1_CAPT_vect)
	{
	_delay_ms(300);
	//Delay para evitar efecto rebote
	PORTB =~ PINB;
	}

//__PROGRAMA PRINCIPAL
int main(void)
{
	DDRB |= (1<<PB0);
	//Puerto B como salida
	TCCR1B |= (1<<ICNC1);
	//Captura de entrada - Normal - Flanco de bajada
	TIMSK |= (1<<TICIE1);
	//Habilito interrupción por captura de entrada
	sei();
	//Interrupciones habilitadas
    	while (1)
    	{
    	}
}