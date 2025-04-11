#include <Arduino.h>

// Motor control pins
#define LEFT_PITCH_DIR_PIN 25
#define LEFT_PITCH_PWM_PIN 26
#define LEFT_PITCH_LIMIT_PIN 17

#define LEFT_ROLL_DIR_PIN 32
#define LEFT_ROLL_PWM_PIN 33
#define LEFT_ROLL_LIMIT_PIN 16

#define RIGHT_PITCH_DIR_PIN 22
#define RIGHT_PITCH_PWM_PIN 13
#define RIGHT_PITCH_LIMIT_PIN 14

#define RIGHT_ROLL_DIR_PIN 18
#define RIGHT_ROLL_PWM_PIN 19
#define RIGHT_ROLL_LIMIT_PIN 21

// Speed settings (0-255)
#define UART_MOVE_SPEED 80
#define LIMIT_SWITCH_SPEED 100

// Motor direction configuration
const bool MOTOR_DIRECTIONS[4] = {
  LOW,   // LEFT_PITCH
  HIGH,  // LEFT_ROLL
  HIGH,  // RIGHT_PITCH
  LOW    // RIGHT_ROLL
};

struct Motor {
  uint8_t dirPin;
  uint8_t pwmPin;
  uint8_t limitPin;
  bool uartActive;
  bool currentDirection;
  unsigned long uartStartTime;
  uint8_t motorIndex;
};

Motor motors[4] = {
  {LEFT_PITCH_DIR_PIN, LEFT_PITCH_PWM_PIN, LEFT_PITCH_LIMIT_PIN, false, MOTOR_DIRECTIONS[0], 0, 0},
  {LEFT_ROLL_DIR_PIN, LEFT_ROLL_PWM_PIN, LEFT_ROLL_LIMIT_PIN, false, MOTOR_DIRECTIONS[1], 0, 1},
  {RIGHT_PITCH_DIR_PIN, RIGHT_PITCH_PWM_PIN, RIGHT_PITCH_LIMIT_PIN, false, MOTOR_DIRECTIONS[2], 0, 2},
  {RIGHT_ROLL_DIR_PIN, RIGHT_ROLL_PWM_PIN, RIGHT_ROLL_LIMIT_PIN, false, MOTOR_DIRECTIONS[3], 0, 3}
};

void emergencyStop() {
  for (int i = 0; i < 4; i++) {
    motors[i].uartActive = false;
    analogWrite(motors[i].pwmPin, 0);
  }
}

void stopSingleMotor(uint8_t motorIndex) {
  if (motorIndex < 4) {
    motors[motorIndex].uartActive = false;
    analogWrite(motors[motorIndex].pwmPin, 0);
  }
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(motors[i].dirPin, OUTPUT);
    pinMode(motors[i].pwmPin, OUTPUT);
    pinMode(motors[i].limitPin, INPUT_PULLUP);
    digitalWrite(motors[i].pwmPin, LOW);
    digitalWrite(motors[i].dirPin, motors[i].currentDirection);
  }
}

void handleUART() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command.equals("STOP")) {
      emergencyStop();
    }
    else if (command.startsWith("macro")) {
      int macroNumber = command.substring(5).toInt();
      
      if (macroNumber >= 1 && macroNumber <= 8) {
        int motorIndex = (macroNumber - 1) % 4;
        bool isForward = (macroNumber <= 4);
        
        if (!motors[motorIndex].uartActive && (digitalRead(motors[motorIndex].limitPin) == HIGH)) {
          motors[motorIndex].currentDirection = isForward ? MOTOR_DIRECTIONS[motorIndex] : !MOTOR_DIRECTIONS[motorIndex];
          motors[motorIndex].uartStartTime = millis();
          motors[motorIndex].uartActive = true;
        }
      }
    }
  }
}

void loop() {
  handleUART();

  for (int i = 0; i < 4; i++) {
    Motor &m = motors[i];
    
    if (digitalRead(m.limitPin) == LOW) {
      stopSingleMotor(i);
    }
    else if (m.uartActive) {
      unsigned long elapsed = millis() - m.uartStartTime;
      
      if (elapsed < 300) {
        digitalWrite(m.dirPin, m.currentDirection);
        analogWrite(m.pwmPin, UART_MOVE_SPEED);
      } else {
        analogWrite(m.pwmPin, 0);
        m.uartActive = false;
      }
    }
  }
}
