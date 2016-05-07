/*
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 
Debido a que este timer maneja registros de 16 bits (TCNT1, OCR1A, OCR1B, ICR1) 
hay que tener en cuenta la forma de acceso a estos:
Para leer estos registros hay que seguir el siguiente procedimiento:
 */ 

unsigned int TIM16_LeerTCNT1(void)
{
	unsigned char sreg;
	unsigned int i;
	sreg = SREG;
	//Guardo la bandera de Interrupción Global
	_CLI();
	//Deshabilito Interrupciones
	i = TCNT1;
	//Coloco el valor de TCNT1 en i
	SREG = sreg;
	//Restauro la bandera de Interrupción Global
	return i;
}

void TIM16_EscribirTCNT1 (unsigned int i)
{
	unsigned char sreg;
	unsigned int i;
	sreg = SREG;
	//Guardo la bandera de Interrupción Global
	_CLI();
	//Deshabilito Interrupciones
	TCNT1 = i;
	//Coloco el valor de i en TCNT1
	SREG = sreg;
	//Restauro la bandera de Interrupción Global
}