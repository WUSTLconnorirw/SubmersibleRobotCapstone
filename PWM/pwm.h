#include <avr/io.h>
#include <stdint.h>

/*
PINS THAT ALLOW PWM
PL3
PL4
PL5

PB4
PB5
PB6
PB7

PG5

PE3
PE4
PE5

PH3
PH4
PH5
PH6
*/

/*!
 * @brief Initialize PWM on a specified port
 * @param port Port to initializw PWM on
*/
void pwm_init(uint8_t port, uint8_t pin);

/**
 * @brief Begins PWM signal on previosuly specified pin
*/
void pwm_begin();