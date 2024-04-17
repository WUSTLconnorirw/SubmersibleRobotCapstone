#include "gpio.c"
#include <avr/io.h>

// Port B Pin 7 is the built in LED on the Arduino MEGA

void setup() {
  // put your setup code here, to run once:
  gpio_pinMode(7, &DDRB, 1);
}

void loop() {
  // put your main code here, to run repeatedly:

  gpio_digital_write(7, &PORTB, 1);
  delay(120);
  gpio_digital_write(7, &PORTB, 0);
  delay(120);

}
