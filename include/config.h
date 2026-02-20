include/config.h
#pragma once

// ================= WiFi Access Point =================
#define WIFI_SSID "MyWiFiCar"
#define WIFI_PASS "12345678"

// ================= Motor Driver Pins =================
// Right Motor
#define RIGHT_EN   2
#define RIGHT_IN1 12
#define RIGHT_IN2 13

// Left Motor
#define LEFT_EN    2
#define LEFT_IN1   1
#define LEFT_IN2   3

// ================= Servo Pins =================
#define PAN_PIN  14
#define TILT_PIN 15

// ================= Sensor Pins =================
#define GAS_SENSOR_PIN    34   // Analog MQ sensor
#define METAL_SENSOR_PIN  35   // Digital metal detect
#define TEMP_SENSOR_PIN   32   // Analog temp (or DHT later)

// ================= Light =================
#define LIGHT_PIN 4

// ================= PWM Settings =================
#define PWM_FREQ       1000
#define PWM_RESOLUTION 8
#define MOTOR_PWM_CH   2
#define LIGHT_PWM_CH   3

// ================= Detection Thresholds =================
#define GAS_THRESHOLD     2000
#define TEMP_THRESHOLD    50.0
