/*
 * Servos.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo:
Controlar 8 servomotores mediante PC.

Pseudocódigo:
- Configuramos al timer 0 para que produzca una interrupción cada 2.5ms.
- Durante la interrupción ponemos en nivel alto un pin I/O, esperamos un 
  tiempo y luego ponemos el pin I/O a nivel bajo.
- Mediante UART recibimos letras (A-P) del PC que harán que se modifique 
  el delay que se tiene que esperar en la interrupción del timer. Con cada 
  letra se incrementa o decrementa el Delay.
 */ 
 
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "mdelay.h"
#include "uart.h"

#define UART_BAUD_RATE 9600

float top_lag,bottom_lag,inc_lag;
float lag0,lag1,lag2,lag3,lag4,lag5,lag6,lag7;
volatile int contador;
volatile char flag_contador, data;

ISR(TIMER0_COMP_vect)
{
	flag_contador = 1;
}

void setup()
{
	UART_begin( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	
	DDRB = 0xFF;
	//Puerto B como salida

	TCCR0 |= (1<<WGM01) | (1<<CS02);
	//CTC - Clk/256
	OCR0 = 77;
	//400 Hz
	TIMSK |= (1<<OCIE0);
	//Habilito Interrupción en la Comparación
	
	top_lag = 1.7;
	bottom_lag = 0.04;
	inc_lag = 0.1;
	lag0=lag1=lag2=lag3=lag4=lag5=lag6=lag7= 0.82;

	sei();
}

void ControlServo(char letter)
{
	switch(letter)
	{
		case 'A':
				if (lag0 <= top_lag)
					lag0 = lag0 + inc_lag;
				else
					lag0 = top_lag;
				break;
		case 'B':
				if (lag0 >= bottom_lag)
					lag0 = lag0 - inc_lag;
				else
					lag0 = bottom_lag;
				break;
		case 'C':
				if (lag1 <= top_lag)
					lag1 = lag1 + inc_lag;
				else
					lag1 = top_lag;
				break;
		case 'D':
				if (lag1 >= bottom_lag)
					lag1 = lag1 - inc_lag;
				else
					lag1 = bottom_lag;
				break;
		case 'E':
				if (lag2 <= top_lag)
					lag2 = lag2 + inc_lag;
				else
					lag2 = top_lag;
				break;
		case 'F':
				if (lag2 >= bottom_lag)
					lag2 = lag2 - inc_lag;
				else
					lag2 = bottom_lag;
				break;
		case 'G':
				if (lag3 <= top_lag)
					lag3 = lag3 + inc_lag;
				else
					lag3 = top_lag;
				break;
		case 'H':
				if (lag3 >= bottom_lag)
					lag3 = lag3 - inc_lag;
				else
					lag3 = bottom_lag;
				break;
		case 'I':
				if (lag4 <= top_lag)
					lag4 = lag4 + inc_lag;
				else
					lag4 = top_lag;
				break;
		case 'J':
				if (lag4 >= bottom_lag)
					lag4 = lag4 - inc_lag;
				else
					lag4 = bottom_lag;
				break;
		case 'K':
				if (lag5 <= top_lag)
					lag5 = lag5 + inc_lag;
				else
					lag5 = top_lag;
				break;
		case 'L':
				if (lag5 >= bottom_lag)
					lag5 = lag5 - inc_lag;
				else
					lag5 = bottom_lag;
				break;
		case 'M':
				if (lag6 <= top_lag)
					lag6 = lag6 + inc_lag;
				else
					lag6 = top_lag;
				break;
		case 'N':
				if (lag6 >= bottom_lag)
					lag6 = lag6 - inc_lag;
				else
					lag6 = bottom_lag;
				break;
		case 'O':
				if (lag7 <= top_lag)
					lag7 = lag7 + inc_lag;
				else
					lag7 = top_lag;
				break;
		case 'P':
				if (lag7 >= bottom_lag)
					lag7 = lag7 - inc_lag;
				else
					lag7 = bottom_lag;
				break;

		default:
				break;
	}
}

void ServoSignal(void)
{
	contador += 1;
	
	switch (contador)
	{
		case (1):
				PORTB |= (1<<PB0);
				_delay_ms(lag0);
				PORTB &= ~(1<<PB0);
				break;
		case (2):
				PORTB |= (1<<PB1);
				_delay_ms(lag1);
				PORTB &= ~(1<<PB1);
				break;
		case (3):
				PORTB |= (1<<PB2);
				_delay_ms(lag2);
				PORTB &= ~(1<<PB2);
				break;
		case (4):
				PORTB |= (1<<PB3);
				_delay_ms(lag3);
				PORTB &= ~(1<<PB3);
				break;
		case (5):
				PORTB |= (1<<PB4);
				_delay_ms(lag4);
				PORTB &= ~(1<<PB4);
				break;
		case (6):
				PORTB |= (1<<PB5);
				_delay_ms(lag5);
				PORTB &= ~(1<<PB5);
				break;
		case (7):
				PORTB |= (1<<PB6);
				_delay_ms(lag6);
				PORTB &= ~(1<<PB6);
				break;
		case (8):
				PORTB |= (1<<PB7);
				_delay_ms(lag7);
				PORTB &= ~(1<<PB7);
				contador=0;
				break;
		default:
				break;
	}
}

int main(void)
{
	setup();
	
	while(1)
	{
		data = UART_getc();
		
		if ( data & UART_NO_DATA )
		{
			//No hay dato disponible
		}
		else
		{
			ControlServo(data);
		}
		
		if (flag_contador == 1)
		{
			ServoSignal();
			flag_contador = 0;
		}
	}
}