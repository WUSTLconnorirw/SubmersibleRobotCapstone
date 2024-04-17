#include "pwm.h"


void pwm_init(uint8_t* port, uint8_t pin){
    
    TCCR0A |= (1 << COM0A0); //Non inverting mode
    //Normal PWM mode
    TCCR0A &= ~(1 << WGM02);
    TCCR0A &= ~(1 << WGM01);
    TCCR0A &= ~(1 << WGM00);
    TCCR0B |= (1 << CS02); // Set prescaler to 256 (f_pwm = ((16000000 / prescaler) / 256)
    TCCR0B &= ~(1 << CS01);
    TCCR0B &= ~(1 << CS00);
    *port = (1 << pin);
}

void pwm_begin(uint8_t dutyCycle){
    uint8_t dc = 255 * dutyCycle;
    OCR0A = dc;
}