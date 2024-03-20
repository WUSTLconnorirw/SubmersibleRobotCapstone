#include <DFRobot_BMX160.h>

float MovingAverage(float data[], int pos, int numVals, bool wrap){
  float sumVals = 0;
  int count = 0;
  int dataArraySize = 6;
  for(int i = 0; i < numVals; i++){
    if(pos - i >= 0 & pos - 1 < dataArraySize){
      sumVals = sumVals + data[(pos - i)];
      count++;
    }
    else if(pos - i < 0 & wrap == true){
      sumVals = sumVals + data[(pos - i)];
      count++;
    }
    else if(pos - i > dataArraySize & wrap == true){
      sumVals = sumVals + data[(pos - i) % dataArraySize];
      count++;
    }
  }
  return sumVals / count;
}

DFRobot_BMX160 bmx160;
// IMU buffers
float IMUMagnX[6] = {0, 0, 0, 0, 0, 0};
float IMUMagnY[6] = {0, 0, 0, 0, 0, 0};
float IMUMagnZ[6] = {0, 0, 0, 0, 0, 0};
float IMUGyroX[6] = {0, 0, 0, 0, 0, 0};
float IMUGyroY[6] = {0, 0, 0, 0, 0, 0};
float IMUGyroZ[6] = {0, 0, 0, 0, 0, 0};
float IMUAccelX[6] = {0, 0, 0, 0, 0, 0};
float IMUAccelY[6] = {0, 0, 0, 0, 0, 0};
float IMUAccelZ[6] = {0, 0, 0, 0, 0, 0};
// pH buffer
float pH[6] = {0, 0, 0, 0, 0, 0};
// Turbidity buffer
float turbidity[6] = {0, 0, 0, 0, 0, 0};
// Pressure buffer
float pressure[6] = {0, 0, 0, 0, 0, 0};
// Temperature buffer
float temperature[6] = {0, 0, 0, 0, 0, 0};

// Sample rates in Hz
const char IMUSampleRateHz = 10; //Hz 
const char pHSampleRateHz = 10; //Hz 
const char turbiditySampleRateHz = 10; //Hz 
const char pressureSampleRateHz = 10; //Hz 
const char waterDetectionSampleRateHz = 10; //Hz 
const char temperatureSampleRateHz = 10; //Hz

// Sample intervals in millis
char IMUSampleInterval = (1 / IMUSampleRateHz) * 1000; // millis 
char pHSampleInterval = (1 / pHSampleRateHz) * 1000; // millis 
char turbiditySampleInterval = (1 / turbiditySampleRateHz) * 1000; // millis 
char pressureSampleInterval = (1 / pressureSampleRateHz) * 1000; // millis  
char waterDetectionSampleInterval = (1 / waterDetectionSampleRateHz) * 1000; // millis 
char temperatureSampleInterval = (1 / temperatureSampleRateHz) * 1000; // millis  

// Buffer indices for moving average support
unsigned char IMUIndex = 0;
unsigned char pHIndex = 0;
unsigned char turbidityIndex = 0;
unsigned char pressureIndex = 0;
unsigned char waterDetectionIndex = 0;
unsigned char temperatureIndex = 0;

//Pins
const char pHPin = A0;
const char turbidityPin = A1;
const char pressurePin = A2;
const char waterDetectionPin = 57;
const char temperaturePin = A4;


void setup(){
  Serial.begin(9600);
  delay(100);
  //init the hardware bmx160  
  if (bmx160.begin() != true){
    Serial.println("init false");
    while(1);
  }
  Serial.print("Millis");  Serial.print(",");  Serial.print("Magnetometer X Raw");  Serial.print(",");  Serial.print("Magnetometer Y Raw");  Serial.print(",");  Serial.print("Magnetometer Y Raw");  Serial.print(",");  Serial.print("Gyroscope X Raw");  Serial.print(",");  Serial.print("Gyroscope Y Raw");  Serial.print(",");  Serial.print("Gyroscope Z Raw");  Serial.print(",");  Serial.print("Accelerometer X Raw");  Serial.print(",");  Serial.print("Accelerometer Y Raw");  Serial.print(",");  Serial.print("Accelerometer Z Raw");  Serial.print(",");  Serial.print("Magnetometer X Average");  Serial.print(",");  Serial.print("Magnetometer Y Average");  Serial.print(",");  Serial.print("Magnetometer Y Average");  Serial.print(",");  Serial.print("Gyroscope X Average");  Serial.print(",");  Serial.print("Gyroscope Y Average");  Serial.print(",");  Serial.print("Gyroscope Z Average");  Serial.print(",");  Serial.print("Accelerometer X Average");  Serial.print(",");  Serial.print("Accelerometer Y Average");  Serial.print(",");  Serial.println("Accelerometer Z Average");
  delay(100);
}

sBmx160SensorData_t Omagn, Ogyro, Oaccel;
unsigned long previousTime = 0;
unsigned long currentTime;

int i = 0;
int index = 0;
void loop(){
  currentTime = millis();
  if (currentTime - previousTime >= IMUSampleInterval) {
    bmx160.getAllData(&Omagn, &Ogyro, &Oaccel);
    IMUMagnX[IMUIndex % 6] = Omagn.x;
    IMUMagnY[IMUIndex % 6] = Omagn.y;
    IMUMagnZ[IMUIndex % 6] = Omagn.z;
    IMUGyroX[IMUIndex % 6] = Ogyro.x;
    IMUGyroY[IMUIndex % 6] = Ogyro.y;
    IMUGyroZ[IMUIndex % 6] = Ogyro.z;
    IMUAccelX[IMUIndex % 6] = Oaccel.x;
    IMUAccelY[IMUIndex % 6] = Oaccel.y;
    IMUAccelZ[IMUIndex % 6] = Oaccel.z;
    // /* Display the magnetometer results (magn is magnetometer in uTesla) */
    // /* Display the gyroscope results (gyroscope data is in g) */
    // /* Display the accelerometer results (accelerometer data is in m/s^2) */
    Serial.print(millis());  Serial.print(",");  Serial.print(Omagn.x);  Serial.print(",");  Serial.print(Omagn.y);  Serial.print(",");  Serial.print(Omagn.z);  Serial.print(",");  Serial.print(Ogyro.x);  Serial.print(",");  Serial.print(Ogyro.y);  Serial.print(",");  Serial.print(Ogyro.z);  Serial.print(",");  Serial.print(Oaccel.x);  Serial.print(",");  Serial.print(Oaccel.y);  Serial.print(",");  Serial.print(Oaccel.z);  Serial.print(",");  Serial.print(MovingAverage(IMUMagnX, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUMagnY, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUMagnZ, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUGyroX, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUGyroY, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUGyroZ, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUAccelX, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUAccelY, 5, 3, true));  Serial.print(",");  Serial.println(MovingAverage(IMUAccelZ, 5, 3, true));
    IMUIndex++;
    previousTime = currentTime;
  }

  if (currentTime - previousTime >= pHSampleInterval) {
    pH[pHIndex % 6] = analogRead(pHPin);
    Serial.println(MovingAverage(pH, 5, 3, true));
    pHIndex++;
    previousTime = currentTime;
  }

  if (currentTime - previousTime >= turbiditySampleInterval) {
    turbidity[turbidityIndex % 6] = analogRead(turbidityPin);
    Serial.println(MovingAverage(turbidity, 5, 3, true));
    turbidityIndex++;
    previousTime = currentTime;
  }

  if (currentTime - previousTime >= pressureSampleInterval) {
    pressure[pressureIndex % 6] = analogRead(pressurePin);
    Serial.println(MovingAverage(pressure, 5, 3, true));
    pressureIndex++;
    previousTime = currentTime;
  }

  if (currentTime - previousTime >= waterDetectionSampleInterval) {
    Serial.println(digitalRead(waterDetectionPin));
    previousTime = currentTime;
  }

  if (currentTime - previousTime >= temperatureSampleInterval) {
    temperature[temperatureIndex % 6] = analogRead(temperaturePin);
    Serial.println(MovingAverage(temperature, 5, 3, true));
    temperatureIndex++;
    previousTime = currentTime;
  }
}