#include "pwm.c"

void setup() {
  // put your setup code here, to run once:
  // pwm_init(&DDRH, 3);
  // pwm_begin(99);
  pinMode(3, OUTPUT);
  analogWrite(3, 10);
}

void loop() {
  // put your main code here, to run repeatedly:

}
