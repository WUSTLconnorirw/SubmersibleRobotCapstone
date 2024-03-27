#include <avr/io.h>
#include <stdint.h>

#define i2c_action_await_complete while(!(TWCR & (1 << TWINT)));

#define f_CPU 16000000
#define SCLfreq 100000

void i2c_init();
void i2c_start_condition();
void i2c_sendbyte(uint8_t b);