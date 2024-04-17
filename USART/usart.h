#include <avr/io.h>
#include <stdint.h>

void usart_init(uint8_t baud);
void usart_write(uint8_t b);
uint8_t usart_read();