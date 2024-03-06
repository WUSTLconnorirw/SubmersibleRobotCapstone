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
float IMUMagnX[6] = {0, 0, 0, 0, 0, 0};
float IMUMagnY[6] = {0, 0, 0, 0, 0, 0};
float IMUMagnZ[6] = {0, 0, 0, 0, 0, 0};
float IMUGyroX[6] = {0, 0, 0, 0, 0, 0};
float IMUGyroY[6] = {0, 0, 0, 0, 0, 0};
float IMUGyroZ[6] = {0, 0, 0, 0, 0, 0};
float IMUAccelX[6] = {0, 0, 0, 0, 0, 0};
float IMUAccelY[6] = {0, 0, 0, 0, 0, 0};
float IMUAccelZ[6] = {0, 0, 0, 0, 0, 0};

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

int i = 0;
int index = 0;
void loop(){
  sBmx160SensorData_t Omagn, Ogyro, Oaccel;
  index = i % 6;
  /* Get a new sensor event */
  bmx160.getAllData(&Omagn, &Ogyro, &Oaccel);
  IMUMagnX[index] = Omagn.x;
  IMUMagnY[index] = Omagn.y;
  IMUMagnZ[index] = Omagn.z;
  IMUGyroX[index] = Ogyro.x;
  IMUGyroY[index] = Ogyro.y;
  IMUGyroZ[index] = Ogyro.z;
  IMUAccelX[index] = Oaccel.x;
  IMUAccelY[index] = Oaccel.y;
  IMUAccelZ[index] = Oaccel.z;
  // /* Display the magnetometer results (magn is magnetometer in uTesla) */
  // /* Display the gyroscope results (gyroscope data is in g) */
  // /* Display the accelerometer results (accelerometer data is in m/s^2) */
  Serial.print(millis());  Serial.print(",");  Serial.print(Omagn.x);  Serial.print(",");  Serial.print(Omagn.y);  Serial.print(",");  Serial.print(Omagn.z);  Serial.print(",");  Serial.print(Ogyro.x);  Serial.print(",");  Serial.print(Ogyro.y);  Serial.print(",");  Serial.print(Ogyro.z);  Serial.print(",");  Serial.print(Oaccel.x);  Serial.print(",");  Serial.print(Oaccel.y);  Serial.print(",");  Serial.print(Oaccel.z);  Serial.print(",");  Serial.print(MovingAverage(IMUMagnX, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUMagnY, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUMagnZ, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUGyroX, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUGyroY, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUGyroZ, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUAccelX, 5, 3, true));  Serial.print(",");  Serial.print(MovingAverage(IMUAccelY, 5, 3, true));  Serial.print(",");  Serial.println(MovingAverage(IMUAccelZ, 5, 3, true));
  delay(500);
  i++;
}