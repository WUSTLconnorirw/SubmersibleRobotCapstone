#include "usart.c"

void setup() {
  // put your setup code here, to run once:
  usart_init(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  usart_write(0x15);  
}
