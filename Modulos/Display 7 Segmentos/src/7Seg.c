/*
 * 7Seg.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo Barrido Display:
Este programa realiza el conteo de 0 a 9999, al llegar a este valor regresa a cero. 
Aplicamos el uso del barrido de display de cátodo común mediante timers, también usa 
blanqueo del cero.

Pseudocódigo:
- Configuro el Timer 0 para producir una interrupcion a 400Hz, esto servira para 
  activar cada display.
- Configuro el Timer 2 para que me sirva como contador.
 */ 
 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char contador_1, contador_2, display;
volatile unsigned char flag;
volatile int limite=99;

char seg []={126,48,109,121,51,91,95,112,127,123};
//Código 7-segmentos



ISR(TIMER2_COMP_vect)
{
	if (contador_1<limite)
	{
		contador_1++;
	}
	else
	{
		if(contador_2<limite)
		{
			contador_1 = 0;
			contador_2++;
		}
		else
		{
			contador_2 = 0;
		}
	}
}

ISR(TIMER0_COMP_vect)
{
	display++;
	flag = 1;
}

int main(void)
{
	DDRB |= (1<<PB3) | (1<<PB2) | (1<<PB1) | (1<<PB0);
	DDRD |= (1<<PD6) | (1<<PD5) | (1<<PD4) | (1<<PD3) | (1<<PD2) | (1<<PD1) | (1<<PD0);
	TCCR0 |= (1<<WGM01) | (1<<CS02);
	//CTC - Normal - Xtal/256
	OCR0 = 155;
	//200Hz
	TCCR2 |= (1<<WGM21) | (1<<CS22) | (1<<CS21);
	//CTC - Normal - Xtal/256
	ASSR |= (1<<AS2);
	//Modo Asíncrono
	OCR2 = 127;
	//1HZ
	TIMSK |= (1<<OCIE2) | (1<<OCIE0);
	//OCIE0 y OCIE2 Habilitado
	sei();
	
	flag = 0;
	
	while (1)
	{
		if (flag == 1)
		{
			switch (display)
			{
				case 1:
					PORTB |= (1<<PB3) | (1<<PB2) | (1<<PB1);
					PORTB &= ~(1<<PB0);
					//		PORTB=0B00000001;
					if (contador_2 < 10){
						PORTD=0;
					}
					else{						
						PORTD=seg[contador_2/10];
					}
					break;
				case 2:
					PORTB |= (1<<PB3) | (1<<PB2) | (1<<PB0);
					PORTB &= ~(1<<PB1);
					//		PORTB=0B00000010;
					if (contador_2==0){						
						PORTD=0;
					}
					else{						
						PORTD=seg[contador_2%10];
					}
					break;
				case 3:
					PORTB |= (1<<PB3) | (1<<PB1) | (1<<PB0);
					PORTB &= ~(1<<PB2);
					//		PORTB=0B00000100;
					if (contador_2==0 && contador_1<10){						
						PORTD=0;
					}
					else{						
						PORTD=seg[contador_1/10];
					}
					break;
				case 4:
					PORTB |= (1<<PB2) | (1<<PB1) | (1<<PB0);
					PORTB &= ~(1<<PB3);
					//		PORTB=0B00001000;
					PORTD=seg[contador_1%10];
					display=0;
					break;
				default:
					break;
			}
			
			flag = 0;
		}
		
	}
}
