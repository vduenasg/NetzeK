/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for avr.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#define SPI_SS   PB4
#define SPI_MOSI PB5
#define SPI_MISO PB6
#define SPI_SCK  PB7
#define SPI_DDR  DDRB
#define SPI_PORT PORTB

#define MSBFIRST 0
#define LSBFIRST 1

#define SPEED_2X 1
#define SPEED_1X 0

#define SPI_CLOCK_1X_DIV4 0x00
#define SPI_CLOCK_1X_DIV16 0x01
#define SPI_CLOCK_1X_DIV64 0x02
#define SPI_CLOCK_1X_DIV128 0x03
#define SPI_CLOCK_2X_DIV2 0x00
#define SPI_CLOCK_2X_DIV8 0x01
#define SPI_CLOCK_2X_DIV32 0x02
#define SPI_CLOCK_2X_DIV64 0x03

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR

void SPI_begin();
/**
* Set direction register for SCK and MOSI pin.
* MISO pin automatically overrides to INPUT.
* When the SS pin is set as OUTPUT, it can be used as
* a general purpose output port (it doesn't influence
* SPI operations).
*/
void SPI_end();
/**
* Disable SPI interface
*/
void SPI_setBitOrder(uint8_t bitOrder);
/**
* MSBFIRST
* LSBFIRST
*
* MSB first or LSB first
*/
void SPI_setDataMode(uint8_t mode);
/**
* SPI_MODE0
* SPI_MODE1
* SPI_MODE2
* SPI_MODE3
*
* Leading Edge		| Trailing Edge		| SPI Mode
*--------------------------------------------------
* Sample (Rising)	| Setup (Falling)	| 0
* Setup (Rising)	| Sample (Falling)	| 1
* Sample (Falling)	| Setup (Rising)	| 2
* Setup (Falling)	| Sample (Rising)	| 3
*/
void SPI_setClockDivider(uint8_t rate, uint8_t speed);
/**
* SPI_CLOCK_1X_DIV4
* SPI_CLOCK_1X_DIV16
* SPI_CLOCK_1X_DIV64
* SPI_CLOCK_1X_DIV128
* SPI_CLOCK_2X_DIV2
* SPI_CLOCK_2X_DIV8
* SPI_CLOCK_2X_DIV32
* SPI_CLOCK_2X_DIV64
*/
uint8_t SPI_transfer(uint8_t data);
/**
* Send data through SPI interface
*/
void SPI_attachInterrupt();
void SPI_detachInterrupt();

#endif