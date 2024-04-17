#include "spi.c"
#include "/Users/connor/Documents/ESE498 - Capstone/SubmersibleRobotCapstone/GPIO/gpio.h"

void setup() {
  // put your setup code here, to run once:
  spi_init();
  Serial.begin(9600);

  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(10, LOW);
  // put your main code here, to run repeatedly:
  spi_write(0x00);

  uint8_t receivedData = spi_read();

  digitalWrite(10, HIGH);
  delay(1000);
}
