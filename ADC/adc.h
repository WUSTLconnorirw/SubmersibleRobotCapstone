#include <avr/io.h>
#include <stdint.h>

void adc_init();
uint8_t adc_read(uint8_t adcChannel);