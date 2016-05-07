/*
 * Timer0CTC.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com

@Ejemplo2 - Timer en modo CTC:
Este programa genera en OC0 una señal periódica de 5ms de nivel alto y 2ms de nivel bajo al presionar el pulsador.

Pseudocódigo:
- Al activar la interrupción externa configuro el timer en modo CTC.
- Cada vez que se produce interrupción en el timer se cambia el valor de OCR.
 */ 

#include <avr/io.h>
//Incluyo las definiciones del ATmega16
#include <avr/interrupt.h>
//Incluyo las definiciones de las Interrupciones
#include "mdelay.h"
//Incluyo las definiciones de retardo

unsigned char temporal;

//__INTERRUPCIONES
ISR(INT0_vect)
	{
	_delay_ms(300);
	//Delay para evitar efecto rebote
	TCCR0 |= (1<<COM00) | (1<<WGM01) | (1<<CS02) | (1<<CS00);
	//Toggle OC0 - CTC - CLK/1024
	TIMSK |= (1<<OCIE0)
	//Habilito Interrupción Compare Match
	}

ISR(TIMER0_COMP_vect)
	{
	temporal =~ temporal;
	if (temporal == 0)
	OCR0 = 38;
	else
	OCR0 = 15;
	}

//__PROGRAMA PRINCIPAL
int main(void)
{
	DDRB |= (1<<PB3)
	//PB3 como salida
	MCUCR |= (1<<ISC01);
	//INT0 Flanco de Bajada
	GICR |= (1<<INT0);
	//INT0 Habilitada
    	sei();
	//Interrupciones habilitadas
    	while (1)
    	{
    	}
}