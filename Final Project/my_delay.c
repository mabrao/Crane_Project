/*
 * my_delay.c
 *
 * Created: 2/18/2019 1:48:59 PM
 *  Author: rust0
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "my_delay.h"

void init_ms_timer0 (void)
{
	TCNT0	= 0x00;
	TCCR0A	= 0x00;
	TCCR0B	= 0x00;
	OCR0A	= 250;
}

void init_ms_timer0_tovo (void)
{
	TCNT0 = 241;
	TCCR0A = 0;
	TCCR0B = 0;
}

void ms_delay (uint16_t msec)
{
	for (uint16_t i = 0; i < msec; i++)
	{
		TCCR0B = 0x03;
		while ((TIFR0 & (1 << OCF0A)) == 0);
		TCCR0B = 0;
		TIFR0 = TIFR0 | (1 << OCF0A);
		TCNT0 = 0;
	}
}

void ms_delay_tovo (uint16_t msec)
{
	TCCR0B = 0x05;
	while ((TIFR0 & (1 << TOV0)) == 0);
	TCCR0B = 0;
	TIFR0 = TIFR0 | (1 << TOV0);
	TCNT0 = 241;
}