#include "adc.h"

void adc_init(){
    ADMUX |= ((1 << REFS0)); // Set ADC ref voltage to Analog Vcc
    ADMUX &= ~(1 << ADLAR); // 10 bit accuracy
    ADCSRA |= ((1 << ADEN) | (1 << ADPS2)); // Setting prescaler to 16 (Middleground for speed and accuracy)

}

uint16_t adc_read(uint8_t adcChannel){
    if (adcChannel < 8){
        uint8_t channelMask = (adcChannel & 0x0F);
        ADMUX |= channelMask;
    } else if (adcChannel > 8 && adcChannel <= 15){
        uint8_t lsb = (0x0F & (9 % adcChannel));
        ADMUX |= lsb;
        ADCSRB |= (1 << MUX5);
    }
    ADCSRA |= (1 << ADSC); // Start an ADC conversion
    return (uint16_t)((ADCH << 8) | ADC); // Grab ADC High byte and combine with low
}