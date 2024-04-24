#include "/Users/connor/Documents/ESE498 - Capstone/SubmersibleRobotCapstone/ADC/adc.c"
#include <math.h>

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

float voltage_to_turbidity(float voltage){
  return (-1120.4 * pow(voltage, 2) + 5742.3 * voltage - 4352.9);
}

float ADCReadings[6] = {0, 0, 0, 0, 0, 0};
const char ADCSampleRateHz = 1; //Hz 
char ADCSampleInterval = (1 / ADCSampleRateHz) * 1000; // millis 

unsigned char ADCIndex = 0;


int main(){
  Serial.begin(9600);
  adc_init();

  Serial.print("Voltage"); Serial.print(", "); Serial.println("Turbidity");

  while(1){
    ADCReadings[ADCIndex % 6] = analogRead(0);
    float voltage = (MovingAverage(ADCReadings, 5, 3, true) / 1024) * 5;
    float turbidity = voltage_to_turbidity(voltage);
    Serial.print(voltage); Serial.print(", "); Serial.println(turbidity);
    ADCIndex++;
  }

  return 0;
}