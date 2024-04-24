#include <avr/io.h>
#include <stdint.h>

/**
 * @brief Initialize the ADC
*/
void adc_init();

/**
 * @brief Reads the specified ADC channel
 * @param ADC channel to read from
 * @return ADC reading
 */
uint16_t adc_read(uint8_t adcChannel);

//FOR TESTING
void pwm_begin_11_12(uint8_t dutyCycle);