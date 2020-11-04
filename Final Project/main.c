/*
 * Final Project.c
 *
 * Description:	The objective of this lab is to use what was learned in this course
 * and integrate it together to move a crane to pick up objects. Using PWM, interrupts,
 * ADC, delays, USART, and EEPOM.
 *
 * Hardware: Crane
 * Potentiometer: PIN A2, A3, and A7.
 * PWM of crane motors: OCR3A, OCR3B, and OCR3C
 * 
 * Creator: Jason Lin, Matheus Abrao, Stepano Rust, Joe
 *
 *
 *
 */ 

//pre processor directives:
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "my_delay.h"
#include "dc_motor.h"
#include "USART.h"
#include "eeprom.h"
#include "main.h"

uint8_t input, Hook, Horizontal, Vertical = 0; //variables for operation of crane

uint8_t *data_ptr;

uint8_t i = 0;

//uint8_t test[6] = {55, 24, 18, 99, 12, 77};

int main(void)	
{
	//initialize functions:
	init_PWM();
	init_ms_timer0();
	init_ADC_8();
	init_UART();
	init_UART_3();
	init_INT();
	sei(); //enable interrupts
		
	location_address = 0x0000; //set address to 0
	uint8_t jason = 0;
	uint8_t Hread[6]; //used to print eeprom values
	
	//initialize ports:
	DDRA = 0x00;
	PORTA = 0x07;

	DDRE = (1 << PE5) | (1 << PE4) | (1 << PE3);
	PORTE = (1 << PE5) | (1 << PE4) | (1 << PE3);
	
	DDRH = (1 << PH3);
	PORTH = (1 << PH3);
	
	DDRF = 0x00;
	PORTF = 0x00;
	
	DDRD = 0x00;
	PORTD = 0x01;
	
	DDRJ = 0x00;
	PORTJ = 0xFF;
	
	
    while (1) 
    {	
		////start manual control	//
		//OCR3A = ADC_read_8(0);	// vertical - 5
		//OCR3B = ADC_read_8(7);	// horizontal - 2
		//OCR3C = ADC_read_8(2);	// hook - 3
		//Vertical = OCR3A;		//assign PWM value to vertical variable
		//Horizontal = OCR3B;		//assign PWM value to Horizontal variable
		//Hook = OCR3C;			//assign PWM value to Hook variable
		//printf("%u %u %u\n", Hook, Horizontal, Vertical); //print PWM values to serial monitor
		////end manual control
		//procedure 3:
		location_address = 0x0000;
		if (jason == 0) //if push button pressed (PORTA bit 2)
		{
			home(); //bring to initial position
			OCR3B = EEPROM_read(location_address, Hread);
			pickUp(); //pick up
			printf("\n%d", OCR3B);
			printf("\n%d", Hread[location_address]);
			location_address++;
			OCR3B = EEPROM_read(location_address, Hread);
			putDown(); //put down
			printf("\n%d", OCR3B);
			pickUp(); //pick up
			location_address++;
			OCR3B = EEPROM_read(location_address, Hread);
			putDown(); //put down
			printf("\n%d", OCR3B);
			jason = 1;	
		}	
		
		
		// procedure 4 and 5:	
		char com[] = "calibrate"; //used for compare string
		
		uint8_t calibrate; //used to start calibration
		
		calibrate = compare_strings(rx_buffer, com); //if rx buffer(value sent through cool term) and com are the same calibration return 0
		printf("%u\n", calibrate); //print 1 before calibration starts
		location_address = 0x0000; //set address to 0
		i = 0;
		//*data_ptr = &Hread[0];
		if(calibrate == 0) //start calibration
		{
			printf("\n calibration in progress");
			//run this loop while end pushbutton is not pressed:
			while ((PINA & 0x01) == 0x00) //stop pushbutton
			{
				while((PINA & 0x04) != 0x04) //read potentiometers position recorded button is not pressed
				{
					OCR3A = ADC_read_8(0);	// vertical - 5
					OCR3B = ADC_read_8(7);	// horizontal - 2
					OCR3C = ADC_read_8(2);	// hook - 3
					Vertical = OCR3A;		
					Horizontal = OCR3B;	
					Hook = OCR3C;
					if (PINA & 0x01)
					break;					
				}
				
				
				printf("\n position recorded");
				printf("\n Horizontal value: %u", Horizontal); //print PWM values to serial monitor
				Hread[i] = Horizontal;
				ms_delay(750); //Delay for 1 second
				printf("\n %d", Hread[i]);
				i++; //update array variable
				EEPROM_write_one_char(location_address, Hread);
				location_address++;
			}
			printf("\n calibration complete");
			calibrate = 1;
			break;
		}
		
		//eeprom_write_byte(location_address, Hread);
		//location_address++;
		
		//for(uint8_t k = 0; k < 3; k++) //for loop to write
		//{
			//EEPROM_write_one_char(location_address, Hread[k]);
			//location_address++;
		//}
		
		
		
		//start hard path
		

		
		//end hard path
		
		//start calibration
		//if(PINA == 0x01){
			//calibrateHorizontal();
			//EEPROM_write_calibration(0x0000, *location_data);
		//}
		//
		//for(uint8_t i = 0; i < 6; i++){
			//printf("%u ", EEPROM_location[i]);
		//}
		//printf("\n");
		////end calibration
		
		
		
		
 		
// 		for (i = 0; i < 6; i++){	
// 			location_data[i] = k;
// 			k++;
// 		}
// 		
// 		for(i = 0; i < 6; i++){
// 		EEPROM_write_one_char(location_address, location_data);
// 		location_address++;
// 		}
// 
// 		EEPROM_read(0x0000, EEPROM_location);
// 		
// 		
// 		for (uint8_t i = 0; i < 6; i++){
// 			printf("%u ", EEPROM_location[i]);
// 		}
// 		printf("\n");
	}
}
