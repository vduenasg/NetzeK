/*
 * Timer1_FastPWM.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com

@Ejemplo2 - PWM Fast:
Este programa genera dos señales periódicas con la misma frecuencia pero con 
ciclo de trabajo diferente.

Pseudocódigo:
- Configuro el Timer en modo PWM Fast
- Los valores de OCR se multiplican por 0.35 y 0.75 respectivamente para obtener 
  ciclos de trabajo del 75% y 35% respectivamente.
 */ 

#include <avr/io.h>
//Incluyo las definiciones del ATmega16

int main(void)
{
	DDRD |= (1<<PD5) | (1<<PD4);
	//Puerto D como salida
	TCCR1A |= (1<<COM1A0) | (1<<COM1B0) | (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	//Modo 14 - No invertido - PWM Fast - Clk/64
	OCR1A = 4166*0.75;
	//75% de ciclo de trabajo
	OCR1B = 4166*0.35;
	//35% de ciclo de trabajo
	ICR1 = 4166;
    	while (1)
    	{
    	}
}