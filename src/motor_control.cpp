#include "motor_control.h"
#include "config.h"

// ================= Internal Helpers =================
static void setRightMotor(bool in1, bool in2)
{
    digitalWrite(RIGHT_IN1, in1);
    digitalWrite(RIGHT_IN2, in2);
}

static void setLeftMotor(bool in1, bool in2)
{
    digitalWrite(LEFT_IN1, in1);
    digitalWrite(LEFT_IN2, in2);
}

// ================= Public Functions =================
void motorInit()
{
    pinMode(RIGHT_IN1, OUTPUT);
    pinMode(RIGHT_IN2, OUTPUT);
    pinMode(LEFT_IN1, OUTPUT);
    pinMode(LEFT_IN2, OUTPUT);

    ledcSetup(MOTOR_PWM_CH, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(RIGHT_EN, MOTOR_PWM_CH);
    ledcAttachPin(LEFT_EN, MOTOR_PWM_CH);

    stopMotors();
}

void setMotorSpeed(uint8_t speed)
{
    ledcWrite(MOTOR_PWM_CH, speed);
}

void driveMotor(MotorDirection dir)
{
    switch (dir)
    {
        case MOTOR_FORWARD:
            setRightMotor(HIGH, LOW);
            setLeftMotor(HIGH, LOW);
            break;

        case MOTOR_BACKWARD:
            setRightMotor(LOW, HIGH);
            setLeftMotor(LOW, HIGH);
            break;

        case MOTOR_LEFT:
            setRightMotor(HIGH, LOW);
            setLeftMotor(LOW, HIGH);
            break;

        case MOTOR_RIGHT:
            setRightMotor(LOW, HIGH);
            setLeftMotor(HIGH, LOW);
            break;

        default:
            stopMotors();
            break;
    }
}

void stopMotors()
{
    setRightMotor(LOW, LOW);
    setLeftMotor(LOW, LOW);
}
