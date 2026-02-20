#include "sensors.h"
#include "config.h"

// ================= Init =================
void sensorsInit()
{
    pinMode(GAS_SENSOR_PIN, INPUT);
    pinMode(METAL_SENSOR_PIN, INPUT);
    pinMode(TEMP_SENSOR_PIN, INPUT);
}

// ================= Read Sensors =================
SensorData readAllSensors()
{
    SensorData data;

    data.gasLevel = analogRead(GAS_SENSOR_PIN);
    data.metalDetected = digitalRead(METAL_SENSOR_PIN);

    // simple analog temperature estimate
    float voltage = analogRead(TEMP_SENSOR_PIN) * (3.3 / 4095.0);
    data.temperature = voltage * 30.0;

    data.bombDetected = evaluateBombThreat(data);

    return data;
}

// ================= Threat Logic =================
bool evaluateBombThreat(const SensorData &data)
{
    if ((data.gasLevel > GAS_THRESHOLD && data.metalDetected) ||
        data.temperature > TEMP_THRESHOLD)
    {
        return true;
    }
    return false;
}
