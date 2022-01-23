/*
 * SPIuC.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo:
Este programa se comunica con el RTC DS3234, coloca los segundos 
iniciales a 50 y empieza a leer en adelante.

Al trabajar con esta librería debemos modificar las definiciones de los pines 
que se usen para la comunicación SPI en el archivo "SPI.h", en el caso del 
ATmega16 los pines del SPI se encuentran en el puerto B.

#define SPI_SS   PB4
#define SPI_MOSI PB5
#define SPI_MISO PB6
#define SPI_SCK  PB7
#define SPI_DDR  DDRB
#define SPI_PORT PORTB
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "SPI.h"
#include "UART.h"
#include "mdelay.h"

#define UART_BAUD_RATE 9600
char buffer[7];

unsigned char val, out;

int main(void)
{
	UART_begin(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
	//Inicia UART
	
	SPI_begin();
	//Inicia SPI
	SPI_setBitOrder(MSBFIRST);
	//Envia el bit mas significativo
	SPI_setClockDivider(SPI_CLOCK_1X_DIV4,SPEED_1X);
	//SPI CLK a 2MHz
	SPI_setDataMode(SPI_MODE3);
	//Modo de CPOL y CPHA
	
	sei();
		
	SPI_PORT &= ~(1<<SPI_SS);
	//SS en nivel bajo para activar la comunicación
	
	SPI_transfer(0x80);
	//Coloca la dirección a la cual se escribirá el valor
	SPI_transfer(0x49);
	//Se envia el valor
	
	_delay_us(1);
	SPI_PORT |= (1<<SPI_SS);
	//SS nivel alto para desactivar la comunicación
	
    while(1)
    {
		        
		_delay_ms(1000);
		//Espera 1 segundo
		
		SPI_PORT &= ~(1<<SPI_SS);
		//Activa la comunicacion
		
		SPI_transfer(0x00);
		//Dirección desde donde se leerá el valor
		
		_delay_us(5);
		
		out = SPI_transfer(0);
		//Lectura de la dirección se guarda en la variable "out"
		
		_delay_us(1);
		SPI_PORT |= (1<<SPI_SS);
		//Desactiva la comunicación
		
		itoa(out, buffer, 16);
		//Convierte el valor hexadecimal en string
		UART_puts(buffer);
		//Envia el valor mediante UART
		UART_puts(" segundos\r\n");
    }
}
