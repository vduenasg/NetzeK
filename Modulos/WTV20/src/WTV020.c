/*
 * WTV020.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 */ 


#include <avr/io.h>
#include "mdelay.h"
#include "WTV020SD.h"

void setup()
{
	WTV20_begin();
	WTV20_reset();
}

int main(void)
{
	setup();
		
	while(1)
	{
		WTV20_send(0x0000);
		_delay_ms(6000);
		//Reproduce el archivo 0x0000 6 segundos
		WTV20_send(0xFFF7);
		//Coloca el volumen maximo
		WTV20_send(0x0002);
		_delay_ms(6000);
		//Reproduce el archivo 0x0001 6 segundos
		WTV20_send(0xFFFE);
		_delay_ms(6000);
		//Pausea la reproduccion 6 segundos
		WTV20_send(0xFFFE);
		//Reanuda la reproduccion
		_delay_ms(6000);
		WTV20_send(0xFFFF);
		//Para la reproduccion
		_delay_ms(6000);
	}
}