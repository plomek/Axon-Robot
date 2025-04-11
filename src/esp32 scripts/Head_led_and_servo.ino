#include <Adafruit_NeoPixel.h>
#include <ESP32Servo.h>

#define LED_PIN 5      // Pin connected to the data input of the first LED ring
#define LED_COUNT 14   // Total LEDs (7 from first ring + 7 from second ring)
#define SERVO_PIN 17    // Pin connected to the servo motor
#define SERVO_MIN 0    // Minimum servo angle
#define SERVO_MAX 180  // Maximum servo angle
#define SERVO_STEP 15  // Step size for servo movement

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Servo headServo;
int servoPosition = 90; // Start at center position

void setup() {
    Serial.begin(115200); // Start UART communication
    strip.begin();
    strip.show();  // Initialize all LEDs to 'off'
    setColor(0, 255, 0); // Default to green

    headServo.attach(SERVO_PIN);
    headServo.write(servoPosition); // Initialize servo to center
}

void loop() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        handleCommand(command);
    }
}

void handleCommand(String command) {
    if (command == "led_red") {
        setColor(255, 0, 0);
    } else if (command == "led_blue") {
        setColor(0, 0, 255);
    } else if (command == "led_green") {
        setColor(0, 255, 0);
    } else if (command == "led_yellow") {
        setColor(255, 255, 0);
    } else if (command == "led_purple") {
        setColor(128, 0, 128);
    } else if (command == "led_orange") {
        setColor(255, 165, 0);
    } else if (command == "led_pink") {
        setColor(255, 20, 147);
    } else if (command == "led_rainbow") {
        rainbowMode();
    } else if (command == "led_off") {
        strip.clear();
        strip.show();
    } else if (command == "head_left") {
        moveServo(SERVO_STEP);
    } else if (command == "head_right") {
        moveServo(-SERVO_STEP);
    } else if (command == "head_center") {
        centerServo();
    }
}

void setColor(int r, int g, int b) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
}

void rainbowMode() {
    int j = 0;
    while (Serial.available() == 0) { // Stay in rainbow mode until a new command is received
        uint32_t color = Wheel(j);
        setColor((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
        j = (j + 1) % 256;
        delay(50);
    }
}

uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void moveServo(int step) {
    int newPosition = servoPosition + step;
    if (newPosition > SERVO_MAX) newPosition = SERVO_MAX;
    if (newPosition < SERVO_MIN) newPosition = SERVO_MIN;
    
    while (servoPosition != newPosition) {
        if (servoPosition < newPosition) {
            servoPosition++;
        } else {
            servoPosition--;
        }
        headServo.write(servoPosition);
        delay(20); // Smooth transition
    }
}

void centerServo() {
    int newPosition = 90;
    while (servoPosition != newPosition) {
        if (servoPosition < newPosition) {
            servoPosition++;
        } else {
            servoPosition--;
        }
        headServo.write(servoPosition);
        delay(20); // Smooth transition
    }
}
