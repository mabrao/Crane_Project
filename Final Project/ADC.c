/*
 * ADC.c
 *
 * Created: 3/4/2019 2:06:54 PM
 *  Author: rust0
 */ 

#include <avr/io.h>
#include "ADC.h"

void init_ADC_8(void)
{
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1<<ADPS1) | (1 << ADPS0);
	ADMUX = (1 << REFS0) | (1 << ADLAR);
	ADCSRB = 0x00;
}

void init_ADC_10(void)
{
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1<<ADPS1) | (1 << ADPS0);
	ADMUX = (1 << REFS0) /*| (1 << ADLAR)*/;
	ADCSRB = 0x00;
}

uint8_t ADC_read_8(uint8_t channel)
{
	uint8_t adc = 0;
	
	ADMUX = (ADMUX & 0xE0) | channel;
	ADMUX |= (1 << ADLAR);
	ADCSRA = ADCSRA | (1 << ADSC);
	while ((ADCSRA & (1 << ADIF)) == 0);	//wait until ADIF turns to 1
	adc = ADCH;
	return adc;
}

uint16_t ADC_read_10(uint8_t channel)
{
	uint16_t adc = 0;
	
	ADMUX = (ADMUX & 0xE0) | channel;
	ADMUX &= ~(1 << ADLAR);
	ADCSRA = ADCSRA | (1 << ADSC);
	while ((ADCSRA & (1 << ADIF)) == 0);	//wait until ADIF turns to 1
	adc = ADCL;
	adc = adc | (ADCH << 8);
	ADCSRA = ADCSRA | (1 << ADIF);	//reset ADIF flag
	return adc;
}
////
//ISR (ADC_vect)
//{
	//adc_read = ADCH;
//}