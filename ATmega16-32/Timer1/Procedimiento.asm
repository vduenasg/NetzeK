// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// Debido a que este timer maneja registros de 16 bits (TCNT1, OCR1A, OCR1B, ICR1) 
// hay que tener en cuenta la forma de acceso a estos:
// Para leer estos registros hay que seguir el siguiente procedimiento:

Leer_TCNT1:
	IN R18,SREG	//Guarda bandera de interrupción global
	CLI		//Inhabilitar Interrupciones
	IN R16,TCNT1L
	IN R17,TCNT1H	//Leer TCNT1 en R17:R16
	OUT SREG,R18	//Restaurar la bandera de interrupción global
	RET

Escribir_TCNT1:
	IN R18,SREG	//Guarda bandera de interrupción global
	CLI		//Inhabilitar Interrupciones
	OUT TCNT1H,R17
	OUT TCNT1L,R16	//Escribir TCNT1 en R17:R16
	OUT SREG,R18	//Restaurar la bandera de interrupción global
	RET