#include "/Users/connor/Documents/ESE498 - Capstone/SubmersibleRobotCapstone/ADC/adc.c"

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

float resistance_to_temperature(float resistance) {
    // Using Beta Parameter Equation
    return 1.0 / ((1.0 / 298.15) + (1.0 / 3950.0) * log(resistance / 10000.0)) - 273.15;
}

float adc_to_r(float adcReading){
  return 10000 / ((1023 / adcReading) - 1);
}

float ADCReadings[6] = {0, 0, 0, 0, 0, 0};
const char ADCSampleRateHz = 1; //Hz 
char ADCSampleInterval = (1 / ADCSampleRateHz) * 1000; // millis 

unsigned char ADCIndex = 0;

unsigned long currentTime;
unsigned long previousTime = 0;

int main(){
  Serial.begin(9600);
  adc_init();

  Serial.print("Time Since Start(Millis)"); Serial.print(", "); Serial.print("Sensor Resistance"); Serial.print(", "); Serial.println("Temperature (C)");

  while(1){
    currentTime = millis();
    // if (currentTime - previousTime >= ADCSampleInterval) {
          ADCReadings[ADCIndex % 6] = analogRead(0);
          float reading = adc_to_r(MovingAverage(ADCReadings, 5, 3, true));
          Serial.print(currentTime); Serial.print(", "); Serial.print(reading); Serial.print(", "); Serial.println(resistance_to_temperature(reading));
          ADCIndex++;
          previousTime = currentTime;
    // }
  }

  return 0;
}