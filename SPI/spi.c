#include "spi.h"


void spi_init(){
    // gpio_pinMode(0x01, &DDRB, 0x01); //Set SCK as output
    // gpio_pinMode(0x02, &DDRB, 0x01); // Set MOSI as output
    DDRB |= (1 << 1); //SCK Output
    DDRB |= (1 << 2); //MOSI Output
    DDRB |= (1 << 0); //SS Output

    
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable, Master, Clock rate scalar
}

void spi_write(uint8_t b){
    SPDR = b; // Pass byte into data register
    while(!(SPSR & (1 << SPIF))); //Check interrup flag for if byte sent
}

uint8_t spi_read(){
    while(!(SPSR & (1 << SPIF))); //Check interrup flag for if byte recieved
    return SPDR;
}