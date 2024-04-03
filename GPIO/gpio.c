#include "gpio.h"

void gpio_pinMode(uint8_t pinNumber, uint8_t DDR, uint8_t dataDirection){
    uint8_t pinMask = 1 << pinNumber;
    dataDirection = 0 ? (DDR &= ~pinMask) : (DDR |= pinMask); // In = 0, out = 1
}

uint8_t gpio_digital_read(uint8_t pinNumber, uint8_t port){
    uint8_t pinMask = 1 << pinNumber;
    return (port & pinMask);
}

void gpio_digital_write(uint8_t pinNumber, uint8_t port, uint8_t data){
    uint8_t pinMask = 1 << pinNumber;
    data = 0 ? (port &= ~pinMask) : (port |= pinMask);
}

