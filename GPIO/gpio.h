#include <avr/io.h>
#include <stdint.h>

/**
 * @brief Set the pin mode of a desired GPIO pin
 * @param pinNumber pin number
 * @param DDR address of data direction register for desired port
 * @param dataDirection input or output
*/
void gpio_pinMode(uint8_t pinNumber, uint8_t DDR, uint8_t dataDirection);

/**
 * @brief Reads a specified GPIO pin
 * @param pinNumber pin number
 * @param port port the desired GPIO pin lives on
 * @return ADC reading
*/
uint8_t gpio_digital_read(uint8_t pinNumber, uint8_t port);

/**
 * @brief Write high or low to GPIO pin
 * @param pinNumber pin number
 * @param port port the GPIO lives on
 * @param data HIGH or LOW
*/
void gpio_digital_write(uint8_t pinNumber, uint8_t port, uint8_t data);