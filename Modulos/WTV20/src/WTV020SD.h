/*
 * WTV020_SD.h
 *
 * Created: 03/09/2014 20:44
 * Author: Victor Dueñas Guardia
 * Info: www.netzek.com
 */ 


#ifndef WTV020SD_H_
#define WTV020SD_H_

#define DI  		PB0
#define CLK 		PB1
#define RST 		PB2
#define WTV20_PORT	PORTB
#define WTV20_DDR	DDRB

#define RST_delay_ms		5
#define RST_CLK_delay_ms	300
#define CLK_DATA_delay_ms	2
#define CLK_delay_us		50
#define AFTER_DATA_delay_ms	20

void WTV20_begin(void);
void WTV20_reset(void);
void WTV20_send(int addr);

#endif /* WTV020SD_H_ */