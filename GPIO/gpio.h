#include <avr/io.h>
#include <stdint.h>

void gpio_pinMode(uint8_t pinNumber, uint8_t portNumber, uint8_t dataDirection);
uint8_t gpio_digital_read(uint8_t pinNumber, uint8_t port);
void gpio_digital_write(uint8_t pinNumber, uint8_t port, uint8_t data);