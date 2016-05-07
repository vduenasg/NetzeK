/*
 * FSMTraffic.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
 Implementacion de una maquina de estado finita, mas info:
 http://www.netzek.com/2014/09/maquina-de-estado-finita-fsm.html
 */ 
 
#include <avr/io.h>
#include "mdelay.h"

#define goN   0
#define waitN 1
#define goE   2
#define waitE 3

unsigned long S;
unsigned long Input;

struct State {
	unsigned long Out;
	unsigned long Time;
	unsigned long Next[4];
	};
	
typedef const struct State STyp;

STyp FSM[4]={
	{0x21, 3000, {goN,	waitN,	goN,	waitN	}},
	{0x22,  500, {goE,	goE,	goE,	goE	}},
	{0x0C, 3000, {goE,	goE,	waitE,	waitE	}},
	{0x14,  500, {goN,	goN,	goN,	goN	}}
	};

int main(void)
{
	DDRC = 0xFF;
	S = goN;
	
    while(1)
    {
        PORTC = FSM[S].Out;		//Colocamos las luces
        _delay_ms(FSM[S].Time);
        Input = PINB;			//Leemos los sensores
        S = FSM[S].Next[Input];
    }
}