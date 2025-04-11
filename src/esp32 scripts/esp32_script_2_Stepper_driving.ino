#include <ESP32Servo.h>

Servo rightThumbServo;
Servo rightFingersServo;
Servo leftThumbServo;
Servo leftFingersServo;
Servo rightElbowServo;
Servo rightWristServo;
Servo leftElbowServo;
Servo leftWristServo;

// Servo control pins (elbows and wrists swapped)
int rightThumbServoPin = 33;
int rightFingersServoPin = 32;
int leftThumbServoPin = 25;
int leftFingersServoPin = 26;
int rightElbowServoPin = 5;    // Previously left elbow
int rightWristServoPin = 18;   // Previously left wrist
int leftElbowServoPin = 16;    // Previously right elbow
int leftWristServoPin = 17;    // Previously right wrist

// Servo positions
const int startPos = 90;
int rightThumbEndPos = 190;
int rightFingersEndPos = 210;
int leftThumbEndPos = -10;
int leftFingersEndPos = -30;
int rightElbowEndPos = 170;
int rightWristEndPos = 180;
int leftElbowEndPos = 10;
int leftWristEndPos = 0;

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
ServoState rightElbowState = {startPos, startPos, 0};
ServoState rightWristState = {startPos, startPos, 0};
ServoState leftElbowState = {startPos, startPos, 0};
ServoState leftWristState = {startPos, startPos, 0};

// Idle mode variables
bool idleMode = false;

enum ArmComponent {
    COMPONENT_PALM,
    COMPONENT_ELBOW,
    COMPONENT_WRIST
};

enum IdleState { 
    IDLE_OFF, 
    IDLE_WAITING, 
    IDLE_MOVING_TO_CLOSE, 
    IDLE_HOLDING_CLOSED, 
    IDLE_MOVING_TO_OPEN 
};

struct ArmState {
    IdleState palmState;
    IdleState elbowState;
    IdleState wristState;
    unsigned long palmTimer;
    unsigned long elbowTimer;
    unsigned long wristTimer;
    bool isRightArm;
};

ArmState rightArmState = {IDLE_OFF, IDLE_OFF, IDLE_OFF, 0, 0, 0, true};
ArmState leftArmState = {IDLE_OFF, IDLE_OFF, IDLE_OFF, 0, 0, 0, false};

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
    rightElbowState.targetPos = startPos;
    rightWristState.targetPos = startPos;
    leftElbowState.targetPos = startPos;
    leftWristState.targetPos = startPos;
}

void processCommand(String command) {
    command.trim();
    
    if (command.startsWith("right_thumb_")) {
        int percentage = command.substring(12).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (rightThumbEndPos - startPos) * percentage / 100;
        rightThumbState.targetPos = constrain(target, 0, 270);
    }
    else if (command.startsWith("right_fingers_")) {
        int percentage = command.substring(14).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (rightFingersEndPos - startPos) * percentage / 100;
        rightFingersState.targetPos = constrain(target, 0, 270);
    }
    else if (command.startsWith("left_thumb_")) {
        int percentage = command.substring(11).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (leftThumbEndPos - startPos) * percentage / 100;
        leftThumbState.targetPos = constrain(target, 0, 270);
    }
    else if (command.startsWith("left_fingers_")) {
        int percentage = command.substring(13).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (leftFingersEndPos - startPos) * percentage / 100;
        leftFingersState.targetPos = constrain(target, 0, 270);
    }
    else if (command.startsWith("right_elbow_")) {
        int percentage = command.substring(12).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (rightElbowEndPos - startPos) * percentage / 100;
        rightElbowState.targetPos = constrain(target, 0, 270);
    }
    else if (command.startsWith("right_wrist_")) {
        int percentage = command.substring(12).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (rightWristEndPos - startPos) * percentage / 100;
        rightWristState.targetPos = constrain(target, 0, 270);
    }
    else if (command.startsWith("left_elbow_")) {
        int percentage = command.substring(11).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (leftElbowEndPos - startPos) * percentage / 100;
        leftElbowState.targetPos = constrain(target, 0, 270);
    }
    else if (command.startsWith("left_wrist_")) {
        int percentage = command.substring(11).toInt();
        percentage = constrain(percentage, 0, 100);
        int target = startPos + (leftWristEndPos - startPos) * percentage / 100;
        leftWristState.targetPos = constrain(target, 0, 270);
    }
    else if (command == "hands_idle_on") {
        idleMode = true;
        rightArmState.palmTimer = millis() + random(4000, 7001);
        rightArmState.elbowTimer = millis() + random(4000, 7001);
        rightArmState.wristTimer = millis() + random(4000, 7001);
        rightArmState.palmState = IDLE_WAITING;
        rightArmState.elbowState = IDLE_WAITING;
        rightArmState.wristState = IDLE_WAITING;
        
        leftArmState.palmTimer = millis() + random(4000, 7001);
        leftArmState.elbowTimer = millis() + random(4000, 7001);
        leftArmState.wristTimer = millis() + random(4000, 7001);
        leftArmState.palmState = IDLE_WAITING;
        leftArmState.elbowState = IDLE_WAITING;
        leftArmState.wristState = IDLE_WAITING;
    }
    else if (command == "hands_idle_off") {
        idleMode = false;
        resetAllServosToStart();
        rightArmState.palmState = IDLE_OFF;
        rightArmState.elbowState = IDLE_OFF;
        rightArmState.wristState = IDLE_OFF;
        leftArmState.palmState = IDLE_OFF;
        leftArmState.elbowState = IDLE_OFF;
        leftArmState.wristState = IDLE_OFF;
    }
}

void handleArmComponent(ArmState &arm, ServoState &servo1, ServoState &servo2, 
                       int endPos1, int endPos2, IdleState &state, unsigned long &timer, 
                       ArmComponent component) {
    if (!idleMode || state == IDLE_OFF) return;

    switch (state) {
        case IDLE_WAITING:
            if (millis() >= timer) {
                servo1.targetPos = endPos1;
                if (component == COMPONENT_PALM) {
                    servo2.targetPos = endPos2;
                }
                state = IDLE_MOVING_TO_CLOSE;
            }
            break;

        case IDLE_MOVING_TO_CLOSE:
            if (servo1.currentPos == servo1.targetPos && 
                (component != COMPONENT_PALM || servo2.currentPos == servo2.targetPos)) {
                timer = millis() + 5000;
                state = IDLE_HOLDING_CLOSED;
            }
            break;

        case IDLE_HOLDING_CLOSED:
            if (millis() >= timer) {
                servo1.targetPos = startPos;
                if (component == COMPONENT_PALM) {
                    servo2.targetPos = startPos;
                }
                state = IDLE_MOVING_TO_OPEN;
            }
            break;

        case IDLE_MOVING_TO_OPEN:
            if (servo1.currentPos == startPos && 
                (component != COMPONENT_PALM || servo2.currentPos == startPos)) {
                timer = millis() + random(4000, 7001);
                state = IDLE_WAITING;
            }
            break;
    }
}

void setup() {
    Serial.begin(115200);
    
    // Attach all servos (with swapped elbows/wrists)
    rightThumbServo.attach(rightThumbServoPin, minPulseWidth, maxPulseWidth);
    rightFingersServo.attach(rightFingersServoPin, minPulseWidth, maxPulseWidth);
    leftThumbServo.attach(leftThumbServoPin, minPulseWidth, maxPulseWidth);
    leftFingersServo.attach(leftFingersServoPin, minPulseWidth, maxPulseWidth);
    rightElbowServo.attach(rightElbowServoPin, minPulseWidth, maxPulseWidth);  // Now pin 5
    rightWristServo.attach(rightWristServoPin, minPulseWidth, maxPulseWidth);  // Now pin 18
    leftElbowServo.attach(leftElbowServoPin, minPulseWidth, maxPulseWidth);    // Now pin 16
    leftWristServo.attach(leftWristServoPin, minPulseWidth, maxPulseWidth);    // Now pin 17

    // Initialize all servos to start position
    resetAllServosToStart();
    updateServoPosition(rightThumbServo, startPos);
    updateServoPosition(rightFingersServo, startPos);
    updateServoPosition(leftThumbServo, startPos);
    updateServoPosition(leftFingersServo, startPos);
    updateServoPosition(rightElbowServo, startPos);
    updateServoPosition(rightWristServo, startPos);
    updateServoPosition(leftElbowServo, startPos);
    updateServoPosition(leftWristServo, startPos);
}

void loop() {
    // Update all servo positions
    updateServo(rightThumbServo, rightThumbState);
    updateServo(rightFingersServo, rightFingersState);
    updateServo(leftThumbServo, leftThumbState);
    updateServo(leftFingersServo, leftFingersState);
    updateServo(rightElbowServo, rightElbowState);
    updateServo(rightWristServo, rightWristState);
    updateServo(leftElbowServo, leftElbowState);
    updateServo(leftWristServo, leftWristState);

    // Handle incoming commands
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        processCommand(command);
    }

    // Handle idle modes for each component group
    handleArmComponent(rightArmState, rightThumbState, rightFingersState,
                      rightThumbEndPos, rightFingersEndPos,
                      rightArmState.palmState, rightArmState.palmTimer, COMPONENT_PALM);
    handleArmComponent(rightArmState, rightElbowState, rightElbowState,
                      rightElbowEndPos, rightElbowEndPos,
                      rightArmState.elbowState, rightArmState.elbowTimer, COMPONENT_ELBOW);
    handleArmComponent(rightArmState, rightWristState, rightWristState,
                      rightWristEndPos, rightWristEndPos,
                      rightArmState.wristState, rightArmState.wristTimer, COMPONENT_WRIST);

    handleArmComponent(leftArmState, leftThumbState, leftFingersState,
                      leftThumbEndPos, leftFingersEndPos,
                      leftArmState.palmState, leftArmState.palmTimer, COMPONENT_PALM);
    handleArmComponent(leftArmState, leftElbowState, leftElbowState,
                      leftElbowEndPos, leftElbowEndPos,
                      leftArmState.elbowState, leftArmState.elbowTimer, COMPONENT_ELBOW);
    handleArmComponent(leftArmState, leftWristState, leftWristState,
                      leftWristEndPos, leftWristEndPos,
                      leftArmState.wristState, leftArmState.wristTimer, COMPONENT_WRIST);
}
