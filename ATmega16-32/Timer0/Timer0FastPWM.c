/*
 * Timer0FastPWM.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com

@Ejemplo3 - Timer en Fast PWM:
Este programa genera en OC0 una señal periódica, cada vez que se presiona un pulsador aumenta 
el ciclo de trabajo y al presionar el otro pulsador disminuye el ciclo de trabajo.

Pseudocódigo:
- Configuro al timer en modo Fast PWM.
- Cada vez que se inicia una interrupción externa se aumenta o disminuye el valor de OCR.
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
	if(OCR0 == 0)
	OCR0;
	else
	OCR0--;
	}

ISR(INT1_vect)
	{
	_delay_ms(300);
	//Delay para evitar efecto rebote
	if(OCR0 == 255)
	OCR0;
	else
	OCR0++;
	}

//__PROGRAMA PRINCIPAL
int main(void)
{
	DDRB |= (1<<PB3);
	//PB3 como salida
	MCUCR |= (1<<ISC11) | (1<<ISC01);
	//INT0 e INT1 Flanco de Bajada
	GICR |= (1<<INT1) | (1<<INT0);
	//INT0 e INT1 Habilitada
	TCCR0 |= (1<<WGM00) | (1<<COM01) | (1<<WGM01) | (1<<CS02) | (1<<CS00);
	//No invertido OC0 - Fast PWM - CLK/1024
	OCR0 = 128;
	//50% de ciclo de trabajo
    	sei();
	//Interrupciones habilitadas
    	while (1)
    	{
    	}
}