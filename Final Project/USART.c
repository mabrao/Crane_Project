/*
 * USART.c
 *
 * Created: 3/25/2019 2:19:52 PM
 *  Author: rust0
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART.h"
#include "main.h"

void init_UART_3(void)
{
	uint16_t myubr;
	
	UCSR3A = 0x00;
	UCSR3B = (1 << RXCIE3) | (1 << RXEN3) |(1 << TXEN3);
	UCSR3C = (1 << UCSZ31) | (1 << UCSZ30);
	
	myubr = (F_CPU / (16UL * (uint16_t)baud)) - 1;
	
	UBRR3L = myubr;
	UBRR3H = 0x00;
}

void UART_out (uint8_t ch)
{
	while ((UCSR3A & (1 << UDRE3)) == 0);
	UDR3 = ch; 
}

void send_string (char *str_ptr)
{
	char temp;
	while(*str_ptr != '\0')
	{
		temp = *str_ptr;		//save to temp char
		*str_ptr++;
		UART_out(temp);		//call uart out each time
	}
}

// uint8_t UART_in (void)
// {
// 	while ((UCSR3A & (1 << RXC3)) == 0);
// 	return (UDR3);
// }

ISR (USART3_RX_vect)	//interrupt for rx
{
	rx_char = UDR3;	//save recieved char
	
	if (rx_char == 0x0D){	//save all recieved chars to array unless "ENTER" is sent
		rx_buffer[array_index] = '\0';
// 		array_index ++;
// 		rx_buffer[array_index] = '0';
		LCD_update = 1;	//set flag to true
		array_index = 0;	//reset index for next run
	} else {
		rx_buffer[array_index] = rx_char;	//save char to array
		array_index++;	//increment index
	}

} 
