#ifndef TDSSENSOR_H
#define TDSSENSOR_H

#include <Arduino.h>

#define TdsSensorPin 35
#define VREF 3.3             
#define SCOUNT 30             

void initializeSensor();
int getMedianNum(int bArray[], int iFilterLen);
float readTDSValue(int analogBuffer[], float temperature);

#endif 
