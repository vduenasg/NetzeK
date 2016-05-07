/*
 * UARTuC.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo: UART uC
Este programa realiza el envío de un par de mensajes desde el microcontrolador y 
luego hace un eco, es decir, que todo dato que se le envía lo reenvía.

La librería de inicialización del UART configura el frame con 
8 bits, sin bit de paridad y un bit de parada.
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"

#define UART_BAUD_RATE 9600
//UART a 9600 baudios    

int main(void)
{
	unsigned int c;
    	char buffer[7];
    	int  num=0x0100;

    	UART_begin( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
	//Inicia el UART con UART_BAUD_SELECT() (normal speed mode )
	//Inicia el UART con doble velocidad UART_BAUD_SELECT_DOUBLE_SPEED() ( double speed mode)
    
    	sei();
	//Activamos las interrupciones ya que esta libreria esta controlada por estas.
	
    	UART_puts("String almacenada en la SRAM\r\n");
	//Transmite la string desde la SRAM
    
    	UART_puts_P("String almacenada en la FLASH\r\n");
    	//Transmite el string desde la memoria de programa
        
    	itoa( num, buffer, 10);
	//Convierte el numero en string para ser transmitido.       
    	UART_puts(buffer);
	//Transmite el numero

    	UART_putc('.');
	//Transmite un solo caracter
    
    while(1)
    {
        c = UART_getc();
        if ( c & UART_NO_DATA )
        {
            //No hay dato disponible
        }
        else
        {
            if ( c & UART_FRAME_ERROR )
            {
                UART_puts_P("UART Frame Error: ");
		//Error de Frame como por ejemplo no bit de parada detectado
            }
            if ( c & UART_OVERRUN_ERROR )
            {
            	UART_puts_P("UART Overrun Error: ");
            	//Error de sobre-escritura
            }
            if ( c & UART_BUFFER_OVERFLOW )
            {
            	UART_puts_P("Buffer overflow error: ");
		//No se lee el dato recibido lo suficientemente rapido
            }
			
	UART_putc( (unsigned char)c );
	//Reenvia el caracter recibido
        }
    }
    
}
