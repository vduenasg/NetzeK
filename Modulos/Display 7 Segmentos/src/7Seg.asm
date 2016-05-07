// * Author: Victor Dueñas Guardia
// * Info: www.netzek.com

// @Ejemplo Barrido Display:
// Este programa realiza el conteo de 0 a 9999, al llegar a este valor regresa a cero. 
// Aplicamos el uso del barrido de display de cátodo común mediante timers, también usa 
// blanqueo del cero.

// Pseudocódigo:
// - Configuro el Timer 0 para producir una interrupcion a 400Hz, esto servira para 
//   activar cada display.
// - Configuro el Timer 2 para que me sirva como contador.

// Colocando un par de instrucciones COM en lenguaje ensamblador podemos cambiar el 
// display de cátodo común a ánodo común.

.INCLUDE "M16DEF.INC"
.EQU OCR0_TOP=155
.EQU OCR2_TOP=127
.EQU LIMITE=100

.DEF TEMPO=R16				//Registro Temporal
.DEF NUM_0=R18				//Numero
.DEF NUM_1=R19				//Numero
.DEF NUMERO=R20				//Numero
.DEF SIETE_SEG_1=R21			//Numero de 7 Segmentos (4)
.DEF SIETE_SEG_2=R22			//Rastreo de 7 Segmentos
.DEF SIETE_SEG_3=R23			//Codigo de 7 Segmentos
.DEF SIETE_SEG=R17			//Registro Mostrado

//......VECTORES INTERRUPCION

	.ORG $00
	JMP RESET
	.ORG $06
	JMP TIMER_2_COMP
	.ORG $26
	JMP TIMER_0_COMP

RESET:

//......PILA

	LDI TEMPO,HIGH(RAMEND)
	OUT SPH,TEMPO
	LDI TEMPO,LOW(RAMEND)
	OUT SPL,TEMPO

//......PUERTOS

//______Puerto A

//______Puerto B
//Configurado 7 Segmentos

	LDI TEMPO,$0F
	OUT DDRB,TEMPO

//______Puerto C

//______Puerto D
 //Configurado 7 Segmentos

	LDI TEMPO,$7F
	OUT DDRD,TEMPO

//......TIMERS

//______Timer 0
//Configurado 7 Segmentos

	LDI TEMPO,0B00001100
	OUT TCCR0,TEMPO			//CTC - Normal - Xtal/256

	LDI TEMPO,OCR0_TOP
	OUT OCR0,TEMPO			//Genera 200Hz

//______Timer 2
//Configurado Contador
 
	LDI TEMPO,0B00001110
	OUT TCCR2,TEMPO  		//CTC - Normal - Xtal/256

	LDI TEMPO,OCR2_TOP
	OUT OCR2,TEMPO
	LDI TEMPO,0B00001000
	OUT ASSR,TEMPO 			//Modo asincrono

	LDI TEMPO,0B10000010
	OUT TIMSK,TEMPO			//OCIE0 y OCIE2 Habilitado
 
//......CONFIGURACIONES EXTRA

	LDI SIETE_SEG_2,0B11101111
	 
	CLR NUM_0
	CLR NUM_1
	    
	SEI
  
BUCLE: RJMP BUCLE

//......INTERRUPCIONES

TIMER_0_COMP:
	CPI SIETE_SEG_1,4
	BREQ Cambiar_Nible
	
	Cont_Tim_0_Comp:
	ROR SIETE_SEG_2
		 
	JMP ESCOGER_DIGITO
		
	Salir_Escoger_Dig:
	INC SIETE_SEG_1
	MOV SIETE_SEG_3,SIETE_SEG_2	
	// COM SIETE_SEG_3		//Colocando esta instrucción cambiamos a Anodo Común
	ANDI SIETE_SEG_3,$0F
	  
	OUT PORTB,SIETE_SEG_3
	// COM SIETE_SEG		//Colocando esta instrucción cambiamos a Anodo Común
	OUT PORTD,SIETE_SEG

	RETI

	Cambiar_Nible:
	SWAP SIETE_SEG_2
	CLR SIETE_SEG_1
	RJMP Cont_Tim_0_Comp

TIMER_2_COMP:
	INC NUM_0
	CPI NUM_0,LIMITE
	BREQ Usar_NUM_1
	
	Seguir_Timer2:
	MOV YL,NUM_0
	MOV YH,NUM_1
	
	CALL CONFIRMAR_LIMITE
	RETI

 	Usar_NUM_1:
	CLR NUM_0
	INC NUM_1
	RJMP Seguir_Timer2  
  
//......PROCEDIMIENTOS

CONFIRMAR_LIMITE:
	CPI NUM_1,LIMITE
	BREQ Confirmar_NUM_0
 
	Salir_Confirmar:
	RET

	Confirmar_NUM_0:
	CPI NUM_0,LIMITE
	BREQ Resetear
	RJMP Salir_Confirmar
  
	Resetear:
	CLR NUM_0
	CLR NUM_1
	RJMP Salir_Confirmar

ESCOGER_DIGITO:
//Configurado Escoger Digito

	LDI ZL,LOW(Tabla_Bifur_Digito)
	LDI ZH,HIGH(Tabla_Bifur_Digito)
	MOV TEMPO,SIETE_SEG_1
	ADD TEMPO,TEMPO
	ADD ZL,TEMPO
	LDI TEMPO,$00
	ADC ZH,TEMPO
	IJMP

PRIMER_DIG:
	CPI YH,$00
	BREQ Confirma_Blanqueo_1
	Seguir_Primer_Dig:
	MOV NUMERO,YL
	CALL HEX_A_BCD
	
	MOV TEMPO,XL
	ANDI TEMPO,$0F

	CALL HEX_7_SEG
	
	JMP Salir_Escoger_Dig
	  
	Confirma_Blanqueo_1:
	CPI YL,$00
	BREQ BLANQUEAR
	RJMP Seguir_Primer_Dig

SEGUNDO_DIG:
	CPI YH,$00
	BREQ Confirma_Blanqueo_2
	Seguir_Segundo_Dig:
	MOV NUMERO,YL
	CALL HEX_A_BCD
	
	MOV TEMPO,XL
	ANDI TEMPO,$F0
	SWAP TEMPO
	
	CALL HEX_7_SEG

	JMP Salir_Escoger_Dig
  
	Confirma_Blanqueo_2:
	CPI YL,10
	BRLO BLANQUEAR
	RJMP Seguir_Segundo_Dig

TERCER_DIG:
	CPI YH,$00
	BREQ BLANQUEAR
	MOV NUMERO,YH
	CALL HEX_A_BCD
	
	MOV TEMPO,XL
	ANDI TEMPO,$0F
	
	CALL HEX_7_SEG
	
	JMP Salir_Escoger_Dig

CUARTO_DIG:
	CPI YH,10
	BRLO BLANQUEAR
	MOV NUMERO,YH
	CALL HEX_A_BCD
	
	MOV TEMPO,XL
	ANDI TEMPO,$F0
	SWAP TEMPO

	CALL HEX_7_SEG
	
	JMP Salir_Escoger_Dig

BLANQUEAR:
	LDI SIETE_SEG,$00
	JMP Salir_Escoger_Dig

HEX_A_BCD:
	Hexa_BCD:
	CPI NUMERO,100
	BRSH Centenas
	Loop:
	MOV R0,NUMERO
	SUBI NUMERO,10
	BRMI Final
	INC R1
	RJMP Loop
	Final:
	SWAP R1
	ADD R1,R0
	MOV XL,R1
	CLR R1
	CLR R2
	RET

	Centenas:
	SUBI NUMERO,100
	INC R2
	MOV XH,R2
	RJMP HEX_A_BCD

HEX_7_SEG:
//Configurado Hexadecimal a 7 Segmentos

	LDI ZL,LOW(TablaHex7Seg<<1)
	LDI ZH,HIGH(TablaHex7Seg<<1)
	ADD ZL,TEMPO
	LDI TEMPO,$00
	ADC ZL,TEMPO
	LPM SIETE_SEG,Z
	RET

//......TABLAS

.CSEG
.ORG 0x100
TablaHex7Seg:
.DB 0B1111110,0B0110000 //0,1
.DB 0B1101101,0B1111001 //2,3
.DB 0B0110011,0B1011011 //4,5
.DB 0B1011111,0B1110000 //6,7
.DB 0B1111111,0B1111011 //8,9
.DB 0B1110111,0B0011111 //A,b
.DB 0B1001110,0B0111101 //C,d
.DB 0B1001111,0B1000111 //E,F

.CSEG
.ORG 0x200
Tabla_Bifur_Digito:
JMP PRIMER_DIG
JMP SEGUNDO_DIG
JMP TERCER_DIG
JMP CUARTO_DIG