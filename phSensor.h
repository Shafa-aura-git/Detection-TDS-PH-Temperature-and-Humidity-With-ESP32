#ifndef PH_SENSOR_H
#define PH_SENSOR_H

#include <Arduino.h>
#define PH_SENSOR_PIN 33

void initPHSensor();
float readPHValue();

#endif