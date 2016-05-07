/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for avr.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "SPI.h"

void SPI_begin() {
  // Set direction register for SCK and MOSI pin.
  // MISO pin automatically overrides to INPUT.
  // When the SS pin is set as OUTPUT, it can be used as
  // a general purpose output port (it doesn't influence
  // SPI operations).
  
  SPI_DDR |= (1<<SPI_MOSI) | (1<<SPI_SCK) | (1<<SPI_SS);
  SPI_PORT |= (1<<SPI_SS);

  // Warning: if the SS pin ever becomes a LOW INPUT then SPI 
  // automatically switches to Slave, so the data direction of 
  // the SS pin MUST be kept as OUTPUT.
  SPCR |= (1<<SPE) | (1<<MSTR);
}

void SPI_end() {
  SPCR &= ~(1<<SPE);
}

void SPI_setBitOrder(uint8_t bitOrder)
{
  if(bitOrder == 1) {
    SPCR |= (1<<DORD);
  } else {
    SPCR &= ~(1<<DORD);
  }
}

void SPI_setDataMode(uint8_t mode)
{
  SPCR = (SPCR & ~SPI_MODE_MASK) | mode;
}

void SPI_setClockDivider(uint8_t rate, uint8_t speed)
{
	SPCR = (SPCR & ~SPI_CLOCK_MASK) | (rate & SPI_CLOCK_MASK);
	if (speed == 1){	
		SPSR |= (1<<SPI2X);
	} 
	else{
		SPSR &= ~(1<<SPI2X);
	}	
}

uint8_t SPI_transfer(uint8_t data) {
	SPDR = data;
	while (!(SPSR & (1<<SPIF)))
	;
	return SPDR;
}

void SPI_attachInterrupt() {
	SPCR |= (1<<SPIE);
}

void SPI_detachInterrupt() {
	SPCR &= ~(1<<SPIE);
}