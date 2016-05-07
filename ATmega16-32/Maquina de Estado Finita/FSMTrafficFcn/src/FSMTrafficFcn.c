/*
 * FSMTrafficFcn.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
 Implementacion de una maquina de estado finita usando funciones, mas info:
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
	void (*CmdPt)(void);
	unsigned long Time;
	unsigned long Next[4];
	};
	
typedef const struct State STyp;

void state_goN(void)
{
	PORTC |= (1<<PC0) | (1<<PC5);
	PORTC &= ~(1<<PC1) & ~(1<<PC2) & ~(1<<PC3) & ~(1<<PC4);
}

void state_waitN(void)
{
	PORTC |= (1<<PC1);
	PORTC &= ~(1<<PC0) & ~(1<<PC2);
}

void state_goE(void)
{
	PORTC |= (1<<PC2) |(1<<PC3);
	PORTC &= ~(1<<PC0) & ~(1<<PC1) & ~(1<<PC4) & ~(1<<PC5);
}

void state_waitE(void)
{
	PORTC |= (1<<PC4);
	PORTC &= ~(1<<PC3) & ~(1<<PC5);
}

STyp FSM[4]={
	{&state_goN,	3000,	{goN,	waitN,	goN,	waitN	}},
	{&state_waitN,  500,	{goE,	goE,	goE,	goE	}},
	{&state_goE,	3000,	{goE,	goE,	waitE,	waitE	}},
	{&state_waitE,  500,	{goN,	goN,	goN,	goN	}}
	};

int main(void)
{
	DDRC = 0xFF;
	S = goN;
	
    while(1)
    {
        (FSM[S].CmdPt)();		//Colocamos las luces mediante funciones
        _delay_ms(FSM[S].Time);
        Input = PINB;			//Leemos los sensores
        S = FSM[S].Next[Input];
    }
}