#include <avr/io.h>
#include <stdint.h>

#define i2c_action_await_complete while(!(TWCR & (1 << TWINT)));

#define f_CPU 16000000
#define SCLfreq 100000

/**
 * @brief Initialize the I2C peripheral
*/
void i2c_init();

/**
 * @brief Send I2C start condition before transmission
*/
void i2c_start_condition();

/**
 * @brief Write a byte on the I2C bus
 * @param b byte to write
*/
void i2c_write(uint8_t b);

/**
 * @brief Reads a byte off of I2C bus
 * @param finalByte true/false whether reading final desired byte from transmission. Necessary for proper acknowledgement.
 * @return byte read off I2C bus
*/
uint8_t i2c_read(char finalByte);

/**
 * @brief Send I2C stop condition after transmission
*/
void i2c_stop_condition();