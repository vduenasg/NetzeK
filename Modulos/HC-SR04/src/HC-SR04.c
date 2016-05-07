/*
 * HC-SR04.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo:
Configurar un ultrasonido para que mida distancias en centímetros. 

Pseudocódigo:
- Configuramos el ICP1 para capturar con flanco de subida.
- Enviamos un pulso de 10us por el PB1
- Al capturar el flanco de subida iniciamos el contador y configuramos 
  el ICP1 para capturar flancos de bajada.
- Al detectar el flanco de bajada detenemos el contador y configuramos 
  el ICP1 para capturar flancos de subida.
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "mdelay.h"

#define UART_BAUD_RATE 9600

int counter, pulseW;
float distance;
char run;

char buffer[7];

ISR(TIMER1_CAPT_vect)
{
	if (run == 0)
	{
		TCCR1B |= (1<<CS11) | (1<<CS10);
		//clk/64
		TCCR1B &= ~(1<<ICES1);
		//Flanco de bajada
		
		run = 1;
	}
	else
	{
		TCCR1B &= ~(1<<CS11) & ~(1<<CS10);
		//stop clk
		TCCR1B |= (1<<ICES1);
		//Flanco de subida
		
		counter = TCNT1;
		TCNT1 = 0x00;
		//Resetear Contador
		run = 0;
	}
}

void setup()
{
	UART_begin( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	
	DDRB |= (1<<PB1);
	
	TCCR1B |= (1<<ICNC1) | (1<<ICES1);
	//Flanco de subida
	TIMSK |= (1<<TICIE1);
	//interrupción por captura de entrada

	sei();
}

int ReadUltra(void)
{
	PORTB |= (1<<PB1);
	_delay_us(10);
	PORTB &= ~(1<<PB1);
	//Iniciando HC-SR04
	
	_delay_ms(50);
	//Esperamos al sensor
	
	return (counter*8);
}

int main(void)
{
	setup();
	
	while(1)
	{
		pulseW = ReadUltra();
		
		distance = pulseW / 58;
		//Calculando la distancia
		
		itoa(distance, buffer, 10);
		UART_puts(buffer);
		
		UART_putc('.');
		
		if (pulseW / 58 < 10)
		{
			UART_putc('0');		
		}
		
		distance = pulseW % 58;
		
		itoa(distance, buffer, 10);
		UART_puts(buffer);
		
		UART_puts(" centimetros");
		UART_puts("\n\r");
		
		_delay_ms(1000);
	}
	
}