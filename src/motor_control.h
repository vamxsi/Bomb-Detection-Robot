#pragma once
#include <Arduino.h>

typedef enum
{
    MOTOR_STOP = 0,
    MOTOR_FORWARD,
    MOTOR_BACKWARD,
    MOTOR_LEFT,
    MOTOR_RIGHT
} MotorDirection;

void motorInit();
void setMotorSpeed(uint8_t speed);
void driveMotor(MotorDirection dir);
void stopMotors();
