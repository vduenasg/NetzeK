/*
 * ADC.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com

@Ejemplo:
Este programa nos muestra el voltaje introducido por el canal ADC0.

Pseudocódigo:
- Configuró el ADC con autodisparo.
- Al producirse la interrupción de fin de conversión ADC leo el valor del registro.
- En el programa principal calculo el valor en decimal del registro del ADC.
- Muestro el valor calculado cada 500ms.
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "mdelay.h"
#include "UART.h"

#define UART_BAUD_RATE 9600
// UART a 9600 baudios
char buffer[7];

volatile uint8_t v_adc;

void setup()
{
	UART_begin(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
	//Inicio UART
	
	ADMUX |= (1<<REFS1) | (1<<REFS0) | (1<<ADLAR);
	//V Ref 2.56V - Ajuste a la Izquierda - Entrada Unica ADC0
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1);
	//ADC Habilitado - Iniciar Conversion - Auto Disparo Habilitado
	//Flag Interrupcion Cero - Interrupcion Habilitada - Preescalador 64
	
	sei();
}

//__INTERRUPCIONES
ISR(ADC_vect)
{
	v_adc = ADCH;
}

//__PROGRAMA PRINCIPAL
int main(void)
{
	setup();
	while (1)
	{
		itoa(v_adc/100, buffer, 10);
		UART_puts(buffer);
		//Envio el valor entero
		UART_puts(".");
		if (v_adc%100<10)
		{
			UART_puts("0");
		}
		itoa(v_adc%100, buffer, 10);
		UART_puts(buffer);
		//Envio el valor decimal
		UART_puts(" voltios");
		UART_puts("\n\r");
		
		_delay_ms(500);
		//Espero 0.5 segundos
	}
}