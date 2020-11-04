/*
 * ADC.h
 *
 * Created: 3/4/2019 2:07:13 PM
 *  Author: rust0
 */ 


#ifndef ADC_H_
#define ADC_H_

void init_ADC_8(void);
void init_ADC_10(void);
uint8_t ADC_read_8(uint8_t channel);
uint16_t ADC_read_10(uint8_t channel);

volatile uint8_t adc_read;


#endif /* ADC_H_ */