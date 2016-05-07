/*
 * IntExt.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo:
El programa cambia el estado del LED correspondiente cada vez que se active el pulsador.

Pseudocódigo:
- Configuramos Interrupciones
- Al producirse una interrupción el LED cambia de estado.
 */ 

#include <avr/io.h>
//Incluyo las definiciones del ATmega16
#include <avr/interrupt.h>
//Incluyo las definiciones de las Interrupciones
#include "mdelay.h"
//Incluyo las definiciones de retardo


//__INTERRUPCIONES
ISR(INT0_vect)
	{
	_delay_ms(300);
	//Delay para evitar efecto rebote
	PORTA=PINA^0x01;
	}

ISR(INT1_vect)
	{
	_delay_ms(300);
	PORTA=PINA^0x02;
	}

//__PROGRAMA PRINCIPAL
int main(void)
{
	DDRA |= (1<<PA0) | (1<<PA1);
	//Puerto A como salida
	MCUCR |= (1<<ISC11) | (1<<ISC01);
	//INT0 e INT1 Flanco de Bajada
	GICR |= (1<<INT1) | (1<<INT0);
	//INT0 e INT1 Habilitada
	sei();
	//Interrupciones habilitadas
	while (1)
	{
	}					
	//Bucle Infinito
}