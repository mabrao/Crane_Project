/*
 * dc_motor.c
 *
 * Created: 2/25/2019 11:38:59 AM
 *  Author: rust0
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "my_delay.h"
#include "main.h"
#include "eeprom.h"
#include "dc_motor.h"
#include "ADC.h"
#include "dc_motor.h"


	void init_io (void)	//initialize io
	{
		DDRE = (1<<PE3);	//PE3 = out
		PORTE = 0xFF;		
		DDRL = 0x00;		//PORTL = in
	}
	
	void PWM_Fast (uint8_t dc)	//set pwm to fast mode and output duty cycle passed in
	{
		TCCR3A = (1 << COM3A1) | (1 << WGM31) | (1 << WGM30);	//set values
		TCCR3B = (1 << CS32) | (1 << WGM32);	//set values
		OCR3A = (1024UL * dc) / 100;	//calculation to convert duty cycle to 10bit input
	}
	
	
	void init_PWM (void)	//set up pwm for later use
	{
		TCCR3A = (1 << COM3A1) | (1 << COM3B1) | (1 << COM3C1) | (1 << WGM31) | (1 << WGM30);
		TCCR3B = (1 << CS32) | (1 << WGM32);
		OCR3A = 0x00;
		OCR3B = 0x00;
		OCR3C = 0x00;
	}
	
// 	void init_PWM_4 (void)	//set up pwm for later use
// 	{
// 		TCCR4B = (1 << COM4A1) | (1 << WGM41) | (1 << WGM40);
// 		TCCR4B = (1 << CS42) | (1 << WGM42);
// 		OCR4A = 0x00;
// 		OCR4B = 0x00;
// 		OCR4B = 0x00;
// 	}
	
	//void rampUp (uint8_t start, uint8_t stop, uint16_t ms, uint8_t steps) //pass in start duty cycle, stop duty cycle, time interval in ms, and number of steps desired
	//{
		//if (steps > 5 && steps < 20){	//check that steps used are reasonable. if not, does not run
			//uint8_t dif = 0, flag = 0;
			//uint16_t dc = 0;
			//
			//if (start > stop){	//check if start is higher or lower, then determine abs value of the desired change
				//dif = start - stop;
				//flag = 1;				//if flag = 1, ramp is up else ramp down
			//} else {
				//dif = stop - start;
			//}
			//
			//if (flag == 1){	//change duty cycle to high point if the ramp is down
				//dc = start;
			//}
			//
			//for(uint8_t i = 0; i < steps; i++)	//loop for ramp itself
			//{ 
				//if (flag == 0){		//if negative slope, start high then work to low
					//dc = dc + (dif / steps);
					//OCR3A = (1024UL * dc) / 100;
				//} else {		//if positive:
					//dc = dc - (dif / steps);
					//OCR3A = (1024UL * dc) / 100;
				//}
				//ms_delay(ms / steps); //wait for proper time to pass
			//}
		//}
	//}


//start for crane.c

void init_INT(void)
{
	EICRA = (1<<ISC00) | (1<<ISC01);
	EIMSK = (1<<INT0);
}
	
void home (void)
{
	OCR3B = A;
	OCR3A = UP;
	OCR3C = RELEASE;
}
	
void changeVertical (uint8_t destination) //pass in start duty cycle, stop duty cycle, time interval in ms, and number of steps desired
{
	OCR3A = destination;
	ms_delay(1000);
}	

void changeHorizontal (uint8_t destination) //pass in start duty cycle, stop duty cycle, time interval in ms, and number of steps desired
{
	OCR3B = destination;
	ms_delay(1000);
}

void changeHook (uint8_t destination) //pass in start duty cycle, stop duty cycle, time interval in ms, and number of steps desired
{
	OCR3C = destination;
	ms_delay(1000);
}

void pickUp (void)
{
	changeVertical(DOWN);
	ms_delay(500);
	changeHook(GRAB);
	ms_delay(500);
	changeVertical(UP);
	ms_delay(500);
}

void putDown (void)
{
	changeVertical(DOWN);
	ms_delay(500);
	changeHook(RELEASE);
	ms_delay(500);
	changeVertical(UP);
	ms_delay(500);
}

//void calibrateHorizontal (void)
//{
	//for(uint8_t i = 0; i < 6; i++){
		//while (PINA != 0x01)
		//{
			//OCR3A = ADC_read_8(0);	// vertical - 5
			//OCR3B = ADC_read_8(7);	// horizontal - 2
			//OCR3C = ADC_read_8(2);	// hook - 3
		//}
		//location_data[i] = OCR3B;
		//i++;
		//while (PINA == 0x01);
	//}
//}
//
//ISR (INT0_vect)
//{
	//home();
	//changeHorizontal(A);
	//pickUp();
	//changeHorizontal(B);
	//putDown();
	//pickUp();
	//changeHorizontal(A);
	//putDown();
//}

