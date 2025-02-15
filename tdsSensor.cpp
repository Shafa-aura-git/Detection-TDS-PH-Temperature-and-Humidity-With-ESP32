#include "tdsSensor.h"

// Fungsi Median Filtering
int getMedianNum(int bArray[], int iFilterLen) {
    int bTab[iFilterLen];
    for (byte i = 0; i < iFilterLen; i++) {
        bTab[i] = bArray[i];
    }
    int i, j, bTemp;
    for (j = 0; j < iFilterLen - 1; j++) {
        for (i = 0; i < iFilterLen - j - 1; i++) {
            if (bTab[i] > bTab[i + 1]) {
                bTemp = bTab[i];
                bTab[i] = bTab[i + 1];
                bTab[i + 1] = bTemp;
            }
        }
    }
    if ((iFilterLen & 1) > 0) {
        bTemp = bTab[(iFilterLen - 1) / 2];
    } else {
        bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
    }
    return bTemp;
}

// Fungsi untuk Membaca dan Memproses Data Sensor
float readTDSValue(int analogBuffer[], float temperature) {
    // Hitung tegangan rata-rata dengan median filtering
    float averageVoltage = getMedianNum(analogBuffer, SCOUNT) * (float)VREF / 4096.0;

    // Kompensasi suhu
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
    float compensationVoltage = averageVoltage / compensationCoefficient;

    // Konversi tegangan ke nilai TDS
    float tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage
                     - 255.86 * compensationVoltage * compensationVoltage
                     + 857.39 * compensationVoltage) * 0.5;

    return tdsValue;
}
