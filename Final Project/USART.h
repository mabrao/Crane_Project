/*
 * USART.h
 *
 * Created: 3/25/2019 2:20:03 PM
 *  Author: rust0
 */ 

#define F_CPU 16000000UL
#define baud 9600
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



#ifndef USART_H_
#define USART_H_

volatile uint8_t rx_char;
volatile uint8_t tx_char;

volatile uint8_t LCD_update;
volatile uint8_t array_index;
volatile char rx_buffer[32], rx_buffer_2[16];
void send_string (char *str_ptr);
void init_UART_3(void);
void UART_out (uint8_t ch);
uint8_t UART_in (void);

#endif /* USART_H_ */