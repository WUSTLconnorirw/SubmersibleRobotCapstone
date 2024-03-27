#include "i2c.c"

#define SLA 0x68
#define SLA_W (SLA << 1)
#define SLA_R (SLA << 1 | 0x01)
#define SLA_DATA_REG 0x16

#define SCALING_FACTOR_2G 16384

uint16_t process(uint8_t LSB, uint8_t MSB){
  return (((uint16_t)MSB << 8) | LSB);
}

void setup() {
  Serial.begin(9600);

  i2c_init();

  i2c_start_condition();
  i2c_write(SLA_W);
  i2c_write(SLA_DATA_REG);
  i2c_stop_condition();

  i2c_start_condition();
  i2c_write(SLA_R);

  //Read two bytes for Z accel
  uint8_t lsb = i2c_read(false);
  uint8_t msb = i2c_read(true);
  i2c_stop_condition();

  uint16_t accZ = process(lsb, msb) / SCALING_FACTOR_2G;
  Serial.println(accZ); // Z accel in gs
}

void loop() {
}
