/*
 * TWIuC.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo: Maestro Transmisor - Receptor

Comunicación con una memoria EEPROM y un Sensor de Temperatura.

Para saber como aplicar el protocolo de comunicación TWI con los 
distintos dispositivos que lo requieran hay que entender claramente 
como funcionan estos. En el caso de las memorias EEPROM lo que tenemos 
que saber es la dirección del dispositivo y la ubicación del dato, 
para el sensor es necesario tener conocimiento de su dirección y la 
orden que indica la lectura del mismo.

Pseudocodigo:
- Leemos la temperatura del Sensor.
- Guardamos el dato en la memoria EEPROM en la dirección 0x30 y 0x31.
- Recuperamos los datos de la memoria EEPROM.
- Mostramos los datos.
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include "mdelay.h"
#include "I2Cmaster.h"

#define UART_BAUD_RATE 9600
char buffer[7];


#define EEPROM 0xA0  		
// Dirección de la memoria
#define SENSOR 0x9A			
// Dirección del sensor

uint8_t dato,dato1;

void setup()
{
	I2C_begin();
	// Iniciando TWI
	UART_begin(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));

	sei();
}

int main(void)
{
	setup();
	_delay_ms(200);
	
	while(1)
	{
		I2C_start_wait(SENSOR+I2C_WRITE);
		// Enviamos la condición de inicio y escribir
		I2C_write(0x00);
		// Escribimos la orden (0x00) para realizar la medida
		I2C_stop();
		// Liberamos el bus
		
		I2C_start_wait(SENSOR+I2C_READ);
		// Enviamos la condicion de inicio y leer
		dato = I2C_readNak();
		// Leemos la temperatura y almacenamos
		I2C_stop();
		// Liberamos el bus
		
		I2C_start_wait(EEPROM+I2C_WRITE);
		// Enviamos la condicion de inicio y escribir
		I2C_write(0x30);
		// Ordenamos escribir en la dirección 0x30
		I2C_write(dato);
		// Escribimos el dato (en la direccion 0x30)
		I2C_write(dato);
		// Escribimos el dato (en la dirección 0x31)
		I2C_stop();
		// Liberamos el bus
		
		I2C_start_wait(EEPROM+I2C_WRITE);
		// Enviamos la condicion de inicio y escribir
		I2C_write(0x30);
		// Ordenamos leer la direccion 0x30
		I2C_rep_start(EEPROM+I2C_READ);
		// Enviamos la condicion de inicio y leer
		dato = I2C_readAck();
		// Leemos el dato de la dirección 0x30 y ordenamos leer un nuevo dato
		dato1 = I2C_readNak();
		// Leemos el dato de la dirección 0x31 y avisamos que es el ultimo dato
		I2C_stop();
		// Liberamos el bus
		
		//Mostramos ambos datos
		
		UART_puts(" ");
		itoa(dato, buffer, 10);
		UART_puts(buffer);
		UART_puts(" ");
		itoa(dato1, buffer, 10);
		UART_puts(buffer);
		
		_delay_ms(1000);
		
	}
}