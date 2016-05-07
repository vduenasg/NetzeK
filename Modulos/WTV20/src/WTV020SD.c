//**********************************************************************//
//FILE: WTV20.h
//AUTHOR: Victor Dueñas
//DATE:	05-02-2012
//DESCRIPTION: Library for module WTv20-SD-20S
//INFO: www.netzek.com
//**********************************************************************//

#include <avr/io.h>
#include "WTV020SD.h"
#include "mdelay.h"

void WTV20_begin(void)
{
	WTV20_DDR |= (1<<RST) | (1<<CLK) | (1<<DI);
	WTV20_PORT |= (1<<RST) | (1<<CLK) | (1<<DI);
}

void WTV20_reset(void)
{
	WTV20_PORT &= ~(1<<RST);
	
	_delay_ms(RST_delay_ms);
	
	WTV20_PORT |= (1<<RST);
	
	_delay_ms(RST_CLK_delay_ms);
}

void WTV20_send(int addr)
{
	WTV20_PORT &= ~(1<<CLK);
	
	_delay_ms(CLK_DATA_delay_ms);

	for (int i=15; i>=0; i--)
	{
		_delay_us(CLK_delay_us);
		
		if( ((addr>>i) & 0x0001) > 0)
		{
			WTV20_PORT |= (1<<DI);
		}
		else
		{
			WTV20_PORT &= ~(1<<DI);
		}
		
		_delay_us(CLK_delay_us);
		
		WTV20_PORT |= (1<<CLK);
		
		_delay_us(CLK_delay_us);
		
		if(i>0)
		{
			WTV20_PORT &= ~(1<<DI);
		}
		else
		{
			WTV20_PORT |= (1<<DI);
		}
				
		_delay_us(CLK_delay_us);
		
		if(i>0)
		{
			WTV20_PORT &= ~(1<<CLK);
		}
		else
		{
			WTV20_PORT |= (1<<CLK);
		}
	}
	
	_delay_ms(AFTER_DATA_delay_ms);
}