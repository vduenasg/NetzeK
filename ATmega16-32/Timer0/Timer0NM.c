/*
 * Timer0NM.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com

@Ejemplo1 - Timer en Modo Normal:
Este programa es usado como contador de eventos externos.
- Cada vez que se produce desbordamiento se incrementa una variable.
- Al activar la interrupción 0 se guarda el valor de TCNT0.

Pseudocódigo:
- Configuro el Timer 0 en Modo Normal.
- Al producirse 256 conteos enciendo el LED e incremento una variable.
- Al producir la interrupción externa INT0 capturo el valor del contador.
 */ 

#include <avr/io.h>
//Incluyo las definiciones del ATmega16
#include <avr/interrupt.h>
//Incluyo las definiciones de las Interrupciones
#include "mdelay.h"
//Incluyo las definiciones de retardo

volatile unsigned char v_tcnt;
//Variables reservadas para lectura de registros en interrupciones
unsigned char contador;
//Variables temporales

//__INTERRUPCIONES
ISR(INT0_vect)
{
	_delay_ms(300);
	//Delay para evitar efecto rebote
	v_tcnt=TCNT0;
	//Guardo el valor de TCNT0 en la variable "v_tcnt"
}

ISR(TIMER0_OVF_vect)
{
	contador++;
	PORTD=PIND^0x01;
	//Cambio el estado del LED
}

//__PROGRAMA PRINCIPAL
int main(void)
{
	DDRD |= (1<<PD0);
	//PD0 como salida
	TCCR0 |= (1<<CS02) | (1<<CS01);
	//Normal Port - Fuente externa de reloj en TO y en Flanco de Bajada
	TIMSK |= (1<<TOIE0);
	//Habilito Interrupción por desbordamiento
	MCUCR |= (1<<ISC01);
	//INT0 Flanco de Bajada
	GICR |= (1<<INT0)
	//INT0 Habilitada
    	sei();
	//Interrupciones habilitadas
	while (1)
	{
	}
}