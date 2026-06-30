#include <Arduino.h>
#include <Wire.h>

// ESP32-C3 pin mapping from PCB footprint
static const int PIN_GPIO04 = 4;
static const int PIN_GPIO05 = 5;
static const int PIN_GPIO06 = 6;
static const int PIN_GPIO07 = 7;
static const int PIN_GPIO08 = 8;
static const int PIN_GPIO09 = 9;
static const int PIN_GPIO10 = 10;
static const int PIN_GPIO18 = 18;
static const int PIN_GPIO19 = 19;
static const int PIN_IO3 = 3;
static const int PIN_IO2 = 2;
static const int PIN_IO1 = 1;
static const int PIN_IO0 = 0;

// I2C pins used by INA219, MPU-6050, VL53L0X
// On the ESP32-C3 WROOM-02 footprint these are labeled IO20/RXD and IO21/TXD
static const int PIN_I2C_SDA = 20;
static const int PIN_I2C_SCL = 21;

// TB6612FNG control pins on ESP32
static const int MOTOR_A_PWM = PIN_GPIO06;   // PWMA
static const int MOTOR_A_IN1 = PIN_GPIO04;   // AIN1
static const int MOTOR_A_IN2 = PIN_GPIO05;   // AIN2
static const int MOTOR_B_PWM = PIN_GPIO09;   // PWMB
static const int MOTOR_B_IN1 = PIN_GPIO07;   // BIN1
static const int MOTOR_B_IN2 = PIN_GPIO08;   // BIN2

// Note: TB6612FNG STBY is tied to +3.3V on this board, so it is always enabled.

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(MOTOR_A_PWM, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);

  pinMode(PIN_I2C_SDA, INPUT_PULLUP);
  pinMode(PIN_I2C_SCL, INPUT_PULLUP);

  digitalWrite(MOTOR_A_PWM, LOW);
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  digitalWrite(MOTOR_B_PWM, LOW);
  digitalWrite(MOTOR_B_IN1, LOW);
  digitalWrite(MOTOR_B_IN2, LOW);

  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

  Serial.println("EcoBot firmware starting...");
}

void loop() {
  // Simple motor test sequence
  // Motor standby is permanently enabled on this board.

  // Drive motor A forward
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  analogWrite(MOTOR_A_PWM, 128);

  // Drive motor B forward
  digitalWrite(MOTOR_B_IN1, HIGH);
  digitalWrite(MOTOR_B_IN2, LOW);
  analogWrite(MOTOR_B_PWM, 128);

  delay(1000);

  // Stop motors
  analogWrite(MOTOR_A_PWM, 0);
  analogWrite(MOTOR_B_PWM, 0);

  delay(1000);
}
