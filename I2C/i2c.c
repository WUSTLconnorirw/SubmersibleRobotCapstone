#include "i2c.h"

void i2c_init(){
    TWBR = 0x48;  // ((f_CPU / SCLfreq) - 16) / 2 Equation obtained from data sheet
    TWSR &= 0xFC;    // Set Prescaler value to 1
}

void i2c_start_condition(){
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    i2c_action_await_complete;
}

void i2c_write(uint8_t b){
    TWDR = b;   // Pass byte into I2C data register
    TWCR = (1 << TWINT) | (1 << TWEN);  // Clear interrupt and control registers to begin I2C action
    i2c_action_await_complete;
}

uint8_t i2c_read(char finalByte){
  //Handle ACK & NACK
  if(finalByte){
      TWCR = (1 << TWINT) | (1 << TWEN);
  } else {
      TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  }
  i2c_action_await_complete;
  return TWDR;
}

void i2c_stop_condition(){
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    while (TWCR & (1 << TWSTO)); // Ensure stop condition finishes
}