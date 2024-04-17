#include "usart.h"

/*
 * Using USART 0 
*/

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR (FOSC / 16 / BAUD - 1)

void usart_init(uint8_t baud){
    uint16_t ubrr_tmp = (16000000 / (baud * 16UL)) - 1;
    UBRR0H = (uint8_t)(MYUBRR >> 8);
    UBRR0L = (uint8_t)(MYUBRR);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); //Enable the reciever and transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (1 << USBS0); //1 byte data frame, 1 stop bit
    // Set USART in async mode
    UCSR0C &= ~(1 << UMSEL01);
    UCSR0C &= ~(1 << UMSEL00);
    // NO parity bits
    UCSR0C &= ~(1 << UPM01);
    UCSR0C &= ~(1 << UPM00);
    
}

void usart_write(uint8_t b){
    while(!(UCSR0A & (1 << UDRE0))); //Wait until transmit buffer is empty
    UDR0 = b; //Put data into buffer to be sent
}

uint8_t usart_read(){
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}