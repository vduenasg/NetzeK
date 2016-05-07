/*
 * CompAnalog.c
 *
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
@Ejemplo
El potenciómetro RV1 sirve para variar el voltaje de referencia 
y el LDR nos sirve para detectar la intensidad luminosa, una vez 
calibrado el voltaje de referencia el LED se encenderá al bajar 
la intensidad luminosa.

Pseudocódigo:
- Configuro al comparador analógico.
- Cuando el voltaje en el LDR sea mayor al voltaje de referencia 
  se enciende el LED en caso contrario se apaga.
 */

#include <avr/io.h>       
#include <avr/interrupt.h>  

ISR(ANA_COMP_vect)
{
	if bit_is_clear(ACSR, ACO)
	PORTD=0x01;
	else
	PORTD=0x00;
}

int main(void)
{
	DDRD |= (1<<PD0);
	
	ACSR |= (1<<ACIE);
	//V Ref ANI0 - Interrupción Habilitada - Interrupcion en toggle
	sei();
	
	PORTD |= (1<<PD0);
	while (1)
	{
	}
}