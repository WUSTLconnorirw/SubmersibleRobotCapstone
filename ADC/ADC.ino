#include "adc.c"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  adc_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(adc_read(0));
}
