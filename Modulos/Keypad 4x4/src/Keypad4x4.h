//*****************************************************************************
//
// File Name	: 'Keypad4x4.h'
// Title		: Keypad 4x4 interface
// Author		: www.netzek.com - Copyright (C) 2014
// Created		: 2014-08-03
// Revised		: 2014-08-03
// Version		: 1.0
// Target MCU	: Atmel AVR series
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************
#ifndef KEYPAD4x4_LIB
#define KEYPAD4x4_LIB

#include <stdlib.h>
#include <avr/io.h>

#define KB_OUT	PORTB
#define KB_IN	PINB
#define KB_DDR	DDRB

void KEYPADinit(void);
//Set up a port for keypad
char AnyKey(void);
char SameKey(void);
void ScanKey(void);
void FindKey(void);
void ClearKey(void);
char KeyNewAvalible(void);
//Return True if a key was pressed
void ClearKeyNew(void);
//Set program to scan a new key
char Scan_Keyboard(void);
//Scan the keypad for pressed keys

#endif