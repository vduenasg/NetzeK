/*
 * LCDuC.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo Pantalla LCD HD44780
Este programa muestra las diferentes funciones de la librería 
aplicadas a la pantalla LCD.
 */ 
 
#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "mdelay.h"
#include "HD44780.h"

const uint8_t SMS1[] PROGMEM="String en Flash";
const uint8_t new1[] PROGMEM={0b00000,0b01010,0b01010,0b00000,0b10001,0b01110,0b00110,0b0};

int main(void)
{
	char buffer[7];
	int  num=6;
	
	LCDinit();
	//Inicia LCD
	LCDdefinechar(new1,1);
	//Define un nuevo caracter
	
	LCDclr();
	//Limpia la pantalla
	CopyStringtoLCD(SMS1, 0, 0);
	//Envia String almacenada en la Flash
	LCDstring("String en Programa", 0, 1);
	//String almacenada en SRAM
	_delay_ms(1000);
	LCDshiftRight(4);
	//Mueve toda la pantalla 4 posiciones a la derecha
	_delay_ms(1000);
	LCDshiftLeft(4);
	//Mueve la pantalla cuatro posiciones a la izquierda
	_delay_ms(1000);
	LCDclr();
	//Limpia la pantalla
	LCDGotoXY(4, 1);
	//Coloca el inicio de escritura en la posicion (4,1)
	LCDcursorOn();
	//Activa el cursor
	_delay_ms(2000);
	LCDcursorRight(3);
	//Mueve el cursos tres posiciones a la derecha
	_delay_ms(2000);
	LCDsendChar(1);
	//Envia un nuevo caracter definido
	_delay_ms(2000);
	LCDcursorLeft(5);
	//Mueve el cursos cinco posiciones a la izquierda
	_delay_ms(2000);
	LCDsendChar(1);
	//Envia un nuevo caracter definido
	_delay_ms(2000);
	LCDcursorOnBlink();
	//Activa el blink en el cursor
	_delay_ms(2000);
	LCDsendChar(num + 48);
	//Envia el numero 6 en codigo ascii
	_delay_ms(2000);
	itoa(num, buffer, 10);
	//Convierte el numero en string para ser transmitido.
	LCDstring(buffer, 0, 4);
	//Transmite el numero
	_delay_ms(2000);
	LCDcursorOFF();
	//Desactiva el cursor
	_delay_ms(2000);
	LCDclr();
	//Limpia la pantalla
	LCDinit();
	//Vuleve a iniciar el LCD
	_delay_ms(1000);
	LCDhome();
	//Coloca el inicio de escritura en la posicion (0,0)
	LCDstring("Mensaje", 0, 0);
	//Envia un mensaje
	_delay_ms(1000);
	LCDblank();
	//Oculta la pantalla
	_delay_ms(1000);
	LCDvisible();
	//Hace visible la pantalla
	_delay_ms(1000);
	LCDblank();
	//Oculta la pantalla
	_delay_ms(1000);
	LCDvisible();
	//Hace visible la pantalla
	LCDclr();
	//Limpia el LCD
	for(uint8_t i=0;i<40;i++)
	{
		_delay_ms(10);
		LCDGotoXY(0, 1);
		LCDprogressBar(i,38,16);
	}
	//Envia una animacion (progress bar) propia de la libreria

    while(1)
    { 
    }
}