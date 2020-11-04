/*
 * eeprom.c
 *
 * Created: 4/12/2019 1:39:14 PM
 *  Author: rust0
 */ 

#include "eeprom.h"
#include <avr/interrupt.h>

void EEPROM_write_one_char(uint16_t address, uint8_t data)
{
	while (EECR & (1 << EEPE));
	EEAR = address;
	EEDR = data;
	EECR |= (1 << EEMPE);
 	EECR |= (1 << EEPE);
}

void EEPROM_write_string(uint16_t address, char *data)
{
	while (*data != '\0')
	{
		EEPROM_write_one_char(address, *data);
		address++;
		data++;
	}
}

char EEPROM_read_one (uint16_t address)
{
	while (EECR & (1 << EEPE));
	EEAR = address;
	EECR |= (1 << EERE);
	return EEDR;
}

void EEPROM_read (uint16_t address, char *EEPROM_buf_ptr) //read from EEPROM
{
	char EEPROM_data;
	do{
		EEPROM_data = EEPROM_read_one(address);		
		*EEPROM_buf_ptr = EEPROM_data;
		address++;		//increments
		EEPROM_buf_ptr++;
	}while (EEPROM_data != 0xFF);
	EEPROM_buf_ptr--;
	*EEPROM_buf_ptr = '\0';	//re-write last char in array 
}

void EEPROM_write_calibration(uint16_t address, char *data)
{
	for(uint8_t i = 0; i < 6; i++)
	{
		EEPROM_write_one_char(address, *data);
		address++;
		data++;
	}
}

void EEPROM_read_calibration (uint16_t address, char *EEPROM_buf_ptr) //read from EEPROM
{
	
	uint8_t EEPROM_data;
	for(uint8_t i = 0; i < 6; i++){
		EEPROM_data = EEPROM_read_one(address);
		*EEPROM_buf_ptr = EEPROM_data;
		address++;		//increments
		EEPROM_buf_ptr++;
	}
}

uint8_t compare_strings(char w1[], char w2[])
{
	uint8_t i = 0;
	
	while (w1[i] == w2[i]) 
	{
		if (w1[i] == '\0' || w2[i] == '\0')
		break;
		i++;
	}
	
	if (w1[i] == '\0' && w2[i] == '\0')
	return 0;
	else
	return 1;
}


//  ISR (INT1_vect)		//pushbutton to save rotational location
//  {
//  	EEPROM_write_one_char(location_address, location_data);
//  	location_address++;
//  }