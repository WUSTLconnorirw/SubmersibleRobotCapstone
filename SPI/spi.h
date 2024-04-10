#include <avr/io.h>
#include <stdint.h>
#include "/Users/connor/Documents/ESE498 - Capstone/SubmersibleRobotCapstone/GPIO/gpio.h"

/*
    MOSI - PB2
    MISO - PB3
    SCK - PB1
    SS - Up to the user to define through GPIO (PB0 pin)
*/

/**
 * @brief Initialize the SPI peripheral
*/
void spi_init(); 

/**
 * @brief Write a byte onto the SPI bus
 * @param b byte to write onto the bus
*/
void spi_write(uint8_t b);

/**
 * @brief Read a byte off of SPI bus
 * @return byte read
*/
uint8_t spi_read();