#pragma once
#include <Arduino.h>

typedef struct
{
    uint16_t gasLevel;
    bool metalDetected;
    float temperature;
    bool bombDetected;
} SensorData;

void sensorsInit();
SensorData readAllSensors();
bool evaluateBombThreat(const SensorData &data);
