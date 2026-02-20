#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "config.h"
#include "motor_control.h"
#include "sensors.h"

// ======================================================
// =============== FreeRTOS Objects =====================
// ======================================================

QueueHandle_t sensorQueue;
QueueHandle_t motorQueue;

// ======================================================
// ================= Web Server =========================
// ======================================================

AsyncWebServer server(80);

// ======================================================
// ================= Data Structures ====================
// ======================================================

typedef struct
{
    MotorDirection direction;
    uint8_t speed;
} MotorCommand;

// ======================================================
// ================= Sensor Task ========================
// ======================================================

void sensorTask(void *pv)
{
    SensorData sensorData;

    while (true)
    {
        sensorData = readAllSensors();

        // overwrite keeps latest data (best for sensors)
        xQueueOverwrite(sensorQueue, &sensorData);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

// ======================================================
// ================= Decision Task ======================
// ======================================================

void decisionTask(void *pv)
{
    SensorData sensorData;
    MotorCommand cmd;

    while (true)
    {
        if (xQueueReceive(sensorQueue, &sensorData, portMAX_DELAY))
        {
            if (sensorData.bombDetected)
            {
                Serial.println("⚠️ BOMB DETECTED — STOPPING");

                cmd.direction = MOTOR_STOP;
                cmd.speed = 0;
            }
            else
            {
                cmd.direction = MOTOR_FORWARD;
                cmd.speed = 150;
            }

            xQueueOverwrite(motorQueue, &cmd);
        }
    }
}

// ======================================================
// ================= Motor Task =========================
// ======================================================

void motorTask(void *pv)
{
    MotorCommand cmd;

    while (true)
    {
        if (xQueueReceive(motorQueue, &cmd, portMAX_DELAY))
        {
            setMotorSpeed(cmd.speed);
            driveMotor(cmd.direction);
        }
    }
}

// ======================================================
// ================= Telemetry Task =====================
// ======================================================

void telemetryTask(void *pv)
{
    while (true)
    {
        Serial.printf("\n===== SYSTEM HEALTH =====\n");
        Serial.printf("Free Heap: %u\n", ESP.getFreeHeap());
        Serial.printf("Free PSRAM: %u\n", ESP.getFreePsram());
        Serial.printf("=========================\n");

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// ======================================================
// ================= WiFi Setup =========================
// ======================================================

void setupWiFi()
{
    WiFi.softAP(WIFI_SSID, WIFI_PASS);
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
}

// ======================================================
// ================= Setup ==============================
// ======================================================

void setup()
{
    Serial.begin(115200);

    // ---------- Hardware Init ----------
    motorInit();
    sensorsInit();

    // ---------- Create Queues ----------
    sensorQueue = xQueueCreate(1, sizeof(SensorData));
    motorQueue  = xQueueCreate(1, sizeof(MotorCommand));

    if (!sensorQueue || !motorQueue)
    {
        Serial.println("❌ Queue creation failed!");
        while (true);
    }

    // ---------- WiFi ----------
    setupWiFi();

    // ---------- Basic HTTP endpoint ----------
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *req)
    {
        req->send(200, "text/plain",
                  "ESP32 FreeRTOS Surveillance Rover Running");
    });

    server.begin();

    // ==================================================
    // =============== Create Tasks =====================
    // ==================================================

    xTaskCreatePinnedToCore(sensorTask, "Sensor Task",
                            4096, NULL, 3, NULL, 1);

    xTaskCreatePinnedToCore(decisionTask, "Decision Task",
                            4096, NULL, 4, NULL, 1);

    xTaskCreatePinnedToCore(motorTask, "Motor Task",
                            4096, NULL, 3, NULL, 1);

    xTaskCreatePinnedToCore(telemetryTask, "Telemetry Task",
                            2048, NULL, 1, NULL, 0);

    Serial.println("✅ FreeRTOS system started");
}

// ======================================================
// ================= Loop ===============================
// ======================================================

void loop()
{
    // Empty — RTOS handles scheduling
}
