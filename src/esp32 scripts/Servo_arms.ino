#include <ESP32Servo.h>

Servo rightThumbServo;
Servo rightFingersServo;
Servo leftThumbServo;
Servo leftFingersServo;

// Servo control pins
int rightThumbServoPin = 33;
int rightFingersServoPin = 32;
int leftThumbServoPin = 25;
int leftFingersServoPin = 26;

// Servo positions
int startPos = 90;
int rightThumbServoEndPos = 190;
int rightFingersServoEndPos = 210;
int leftThumbServoEndPos = -10;
int leftFingersServoEndPos = -30;

// Servo control parameters
int stepDelay = 15;
int minPulseWidth = 500;
int maxPulseWidth = 2500;

// Servo state tracking
struct ServoState {
    int currentPos;
    int targetPos;
    unsigned long lastStepTime;
};

ServoState rightThumbState = {startPos, startPos, 0};
ServoState rightFingersState = {startPos, startPos, 0};
ServoState leftThumbState = {startPos, startPos, 0};
ServoState leftFingersState = {startPos, startPos, 0};

// Idle mode variables
bool idleMode = false;

enum HandIdleState { 
    IDLE_OFF, 
    IDLE_WAITING, 
    IDLE_MOVING_TO_CLOSE, 
    IDLE_HOLDING_CLOSED, 
    IDLE_MOVING_TO_OPEN 
};

struct HandState {
    HandIdleState state;
    unsigned long timer;
    bool isRightHand; // true for right, false for left
};

HandState rightHandState = {IDLE_OFF, 0, true};
HandState leftHandState = {IDLE_OFF, 0, false};

void updateServoPosition(Servo &servo, int pos) {
    pos = constrain(pos, 0, 270);
    int pulseWidth = map(pos, 0, 270, minPulseWidth, maxPulseWidth);
    servo.writeMicroseconds(pulseWidth);
}

void updateServo(Servo &servo, ServoState &state) {
    if (state.currentPos == state.targetPos) return;
    
    unsigned long currentTime = millis();
    if (currentTime - state.lastStepTime >= stepDelay) {
        int step = (state.currentPos < state.targetPos) ? 1 : -1;
        state.currentPos += step;
        updateServoPosition(servo, state.currentPos);
        state.lastStepTime = currentTime;
    }
}

void resetAllServosToStart() {
    rightThumbState.targetPos = startPos;
    rightFingersState.targetPos = startPos;
    leftThumbState.targetPos = startPos;
    leftFingersState.targetPos = startPos;
}

void processCommand(String command) {
    command.trim();
    
    if (command.startsWith("right_thumb_")) {
        int percentage = command.substring(12).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (rightThumbServoEndPos - startPos) * percentage / 100;
        rightThumbState.targetPos = constrain(target, 0, 270);
    }
    else if (command.startsWith("right_fingers_")) {
        int percentage = command.substring(14).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (rightFingersServoEndPos - startPos) * percentage / 100;
        rightFingersState.targetPos = constrain(target, 0, 270);
    }
    else if (command.startsWith("left_thumb_")) {
        int percentage = command.substring(11).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (leftThumbServoEndPos - startPos) * percentage / 100;
        leftThumbState.targetPos = constrain(target, 0, 270);
    }
    else if (command.startsWith("left_fingers_")) {
        int percentage = command.substring(13).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (leftFingersServoEndPos - startPos) * percentage / 100;
        leftFingersState.targetPos = constrain(target, 0, 270);
    }
    else if (command == "hands_idle_on") {
        idleMode = true;
        rightHandState.state = IDLE_WAITING;
        rightHandState.timer = millis() + random(4000, 7001);
        leftHandState.state = IDLE_WAITING;
        leftHandState.timer = millis() + random(4000, 7001);
    }
    else if (command == "hands_idle_off") {
        idleMode = false;
        rightHandState.state = IDLE_OFF;
        leftHandState.state = IDLE_OFF;
        resetAllServosToStart();  // Reset all servos to start position
    }
}

void handleHandIdle(HandState &handState, ServoState &thumbState, ServoState &fingersState, int thumbEndPos, int fingersEndPos) {
    if (!idleMode || handState.state == IDLE_OFF) return;

    switch (handState.state) {
        case IDLE_WAITING:
            if (millis() >= handState.timer) {
                thumbState.targetPos = constrain(thumbEndPos, 0, 270);
                fingersState.targetPos = constrain(fingersEndPos, 0, 270);
                handState.state = IDLE_MOVING_TO_CLOSE;
            }
            break;

        case IDLE_MOVING_TO_CLOSE:
            if (thumbState.currentPos == thumbState.targetPos &&
                fingersState.currentPos == fingersState.targetPos) {
                handState.timer = millis() + 5000;
                handState.state = IDLE_HOLDING_CLOSED;
            }
            break;

        case IDLE_HOLDING_CLOSED:
            if (millis() >= handState.timer) {
                thumbState.targetPos = startPos;
                fingersState.targetPos = startPos;
                handState.state = IDLE_MOVING_TO_OPEN;
            }
            break;

        case IDLE_MOVING_TO_OPEN:
            if (thumbState.currentPos == startPos &&
                fingersState.currentPos == startPos) {
                handState.timer = millis() + random(4000, 7001);
                handState.state = IDLE_WAITING;
            }
            break;
    }
}

void setup() {
    Serial.begin(115200);
    
    rightThumbServo.attach(rightThumbServoPin, minPulseWidth, maxPulseWidth);
    rightFingersServo.attach(rightFingersServoPin, minPulseWidth, maxPulseWidth);
    leftThumbServo.attach(leftThumbServoPin, minPulseWidth, maxPulseWidth);
    leftFingersServo.attach(leftFingersServoPin, minPulseWidth, maxPulseWidth);

    // Initialize servos to start position
    resetAllServosToStart();
    updateServoPosition(rightThumbServo, startPos);
    updateServoPosition(rightFingersServo, startPos);
    updateServoPosition(leftThumbServo, startPos);
    updateServoPosition(leftFingersServo, startPos);
}

void loop() {
    // Update servo positions
    updateServo(rightThumbServo, rightThumbState);
    updateServo(rightFingersServo, rightFingersState);
    updateServo(leftThumbServo, leftThumbState);
    updateServo(leftFingersServo, leftFingersState);

    // Handle incoming commands
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        processCommand(command);
    }

    // Handle idle mode for each hand separately
    handleHandIdle(rightHandState, rightThumbState, rightFingersState, rightThumbServoEndPos, rightFingersServoEndPos);
    handleHandIdle(leftHandState, leftThumbState, leftFingersState, leftThumbServoEndPos, leftFingersServoEndPos);
}
