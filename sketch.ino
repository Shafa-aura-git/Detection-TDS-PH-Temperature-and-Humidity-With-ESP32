#include "dhtConfig.h"
#include "tdsSensor.h"
#include "phSensor.h"

unsigned long previousMillis = 0;
const unsigned long interval = 2000;
const unsigned long intervalph = 000;

int analogBuffer[SCOUNT];
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;

float temperature = 25;
float tdsValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(TdsSensorPin, INPUT);
  initializeDHT();
  initPHSensor();
}

void loop() {
  delay(10); 

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

  float temperature = getTemperature();
  float humidity = getHumidity();

  if(isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C");
    Serial.print(" Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    }
  
  float phValue = readPHValue();
  Serial.print("pH Value: ");
  Serial.println(phValue);
  }

    static unsigned long analogSampleTimepoint = millis();
    static unsigned long printTimepoint = millis();

    if (millis() - analogSampleTimepoint > 40U) {
        analogSampleTimepoint = millis();
        analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);
        analogBufferIndex++;
        if (analogBufferIndex == SCOUNT) {
            analogBufferIndex = 0;
        }
    }

    if (millis() - printTimepoint > 800U) {
        printTimepoint = millis();
        memcpy(analogBufferTemp, analogBuffer, SCOUNT * sizeof(int));
        float tdsValue = readTDSValue(analogBufferTemp, temperature);

        Serial.print("TDS Value: ");
        Serial.print(tdsValue, 0);
        Serial.println(" ppm");
    }
}