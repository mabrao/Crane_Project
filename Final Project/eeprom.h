/*
 * eeprom.h
 *
 * Created: 4/12/2019 1:39:03 PM
 *  Author: rust0
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

#ifndef EEPROM_H_
#define EEPROM_H_

volatile uint8_t location_data[6];
volatile uint16_t location_address;
volatile uint8_t data_index;

char EEPROM_read_buff[50];
uint16_t EEPROM_location[6];

void EEPROM_write_one_char(uint16_t address, uint8_t data);
void EEPROM_write_string(uint16_t address, char *data);
char EEPROM_read_one (uint16_t address);
void EEPROM_read (uint16_t address, char *EEPROM_buf_ptr);
void EEPROM_write_calibration(uint16_t address, char *data);
void EEPROM_read_calibration (uint16_t address, char *EEPROM_buf_ptr);

#endif /* EEPROM_H_ */