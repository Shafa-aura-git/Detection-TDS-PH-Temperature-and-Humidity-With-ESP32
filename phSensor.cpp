#include "phSensor.h"

const float calibration_value = 21.34 - 0.7;
int buffer_arr[10];
int temp = 0;

void initPHSensor(){
  pinMode(PH_SENSOR_PIN, INPUT);
}

float readPHValue() {
  for (int i = 0; i < 10; i++){
    buffer_arr[i] = analogRead(PH_SENSOR_PIN);
    delay(30);
  }

  for (int i = 0; i < 9; i++){
    for (int j = i +1; j < 10; j++){
      if (buffer_arr[i] > buffer_arr[j]){
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr [j];
        buffer_arr[j] = temp;
      }
    }
  }

  unsigned long avgval = 0;
  for (int i = 2; i <8; i++){
    avgval += buffer_arr[i];
  }

  float voltage = (float)avgval*3.3/4095/6;

  float phValue = -5.70*voltage + calibration_value;

  return phValue;
}