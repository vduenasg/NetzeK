/*
 * Keypad4x4uC.c
 *
 * Created: 21/08/2014 13:34
 *  Author: user
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "UART.h"
#include "mdelay.h"
#include "Keypad4x4.h"

#define UART_BAUD_RATE 9600

char buffer[7];

char val, check;ISR(TIMER1_COMPA_vect){	check = 1;}void setup(void)
{
	UART_begin( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	KEYPADinit();
	TCCR1B |= (1<<WGM12) | (1<<CS11) | (1<<CS10);
	//Modo 4 CTC - CLK/64 - Normal Port
	OCR1A =2499;
	// Interrupt every 20ms
	TIMSK |= (1<<OCIE1A);
	sei();
}

int main(void)
{
	setup();	
	
    while(1)
    {	
		if (check == 1)
		{
			val = Scan_Keyboard();
			check = 0;
		}
		
		if(KeyNewAvalible())
		{
			UART_putc(val);
			UART_puts("\n\r");
			ClearKeyNew();
		}
    }
}