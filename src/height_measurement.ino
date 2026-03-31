/*
 * ============================================================
 *  Object Height Measurement System
 * ============================================================
 *  Hardware:
 *    - Arduino Uno
 *    - HC-SR04 Ultrasonic Sensor  (TRIG → Pin 9, ECHO → Pin 10)
 *    - SG90 Servo Motor           (Signal → Pin 6)
 *    - 0.96" OLED Display I2C     (SDA → A4, SCL → A5)
 *
 *  Libraries Required:
 *    - Adafruit SSD1306
 *    - Adafruit GFX
 *    - Servo (built-in)
 *
 *  How it works:
 *    The ultrasonic sensor is mounted at a fixed height
 *    (SENSOR_HEIGHT cm above the ground). It measures the
 *    distance to the top of an object. The object height is:
 *        height = SENSOR_HEIGHT - measured_distance
 *    The result is shown on the OLED and the servo rotates
 *    to an angle proportional to the measured height.
 * ============================================================
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

// ── OLED Configuration ────────────────────────────────────────
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64
#define OLED_RESET     -1          // Not connected to any Arduino pin
#define OLED_I2C_ADDR  0x3C       // Common address; try 0x3D if display is blank

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ── Pin Definitions ───────────────────────────────────────────
const int TRIG_PIN  = 9;
const int ECHO_PIN  = 10;
const int SERVO_PIN = 6;

// ── Sensor Configuration ──────────────────────────────────────
const int SENSOR_HEIGHT = 30;     // Height of sensor above ground (cm)
                                   // Adjust this to your actual setup

// ── Servo State ───────────────────────────────────────────────
Servo myServo;
int   currentServoAngle = 0;

// ── Helpers ───────────────────────────────────────────────────

/**
 * Trigger the HC-SR04 and return the distance in centimetres.
 * Returns -1 if no echo is received within the sensor's range.
 */
float measureDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 25000UL); // 25 ms timeout (~4 m)
    if (duration == 0) return -1;

    return duration * 0.0343 / 2.0;   // µs → cm
}

/**
 * Move the servo smoothly in 5-degree steps.
 */
void moveServoSmoothly(int targetAngle) {
    targetAngle = constrain(targetAngle, 0, 180);

    int step = (targetAngle > currentServoAngle) ? 5 : -5;
    for (int a = currentServoAngle; a != targetAngle; a += step) {
        myServo.write(a);
        delay(20);
    }
    myServo.write(targetAngle);        // Ensure we land exactly on target
    currentServoAngle = targetAngle;
}

/**
 * Map a measured height (cm) to the corresponding servo angle.
 */
int heightToServoAngle(float height) {
    if (height < 10)              return 0;
    if (height >= 10 && height < 14) return 45;
    if (height >= 14 && height < 18) return 90;
    if (height >= 18 && height < 24) return 135;
    return 180;                        // height >= 24 cm
}

/**
 * Update the OLED with the current height reading.
 */
void updateDisplay(float height) {
    display.clearDisplay();

    // Title
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Height Meter"));

    // Divider line
    display.drawLine(0, 10, SCREEN_WIDTH - 1, 10, SSD1306_WHITE);

    // Height value (large)
    display.setTextSize(2);
    display.setCursor(0, 18);
    if (height < 0) {
        display.println(F("No Object"));
    } else {
        display.print(height, 1);   // 1 decimal place
        display.println(F(" cm"));
    }

    // Servo angle hint
    display.setTextSize(1);
    display.setCursor(0, 50);
    display.print(F("Servo: "));
    display.print(currentServoAngle);
    display.print((char)247);       // degree symbol
    
    display.display();
}

// ── Setup ─────────────────────────────────────────────────────
void setup() {
    Serial.begin(9600);
    Serial.println(F("Object Height Measurement System"));
    Serial.println(F("----------------------------------"));

    // Ultrasonic sensor pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // OLED initialisation
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDR)) {
        Serial.println(F("ERROR: SSD1306 not found. Check wiring / I2C address."));
        while (true);              // Halt; check your wiring
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    display.println(F("Height"));
    display.setCursor(20, 42);
    display.println(F("Meter"));
    display.display();

    // Servo initialisation
    myServo.attach(SERVO_PIN);
    myServo.write(0);
    currentServoAngle = 0;

    delay(2000);                   // Splash screen pause
}

// ── Main Loop ─────────────────────────────────────────────────
void loop() {
    float distance = measureDistance();
    float height   = (distance < 0) ? -1 : SENSOR_HEIGHT - distance;

    // Clamp negative heights (object taller than sensor, or measurement error)
    if (height < 0 && distance >= 0) height = 0;

    // Serial output
    if (height < 0) {
        Serial.println(F("No object detected."));
    } else {
        Serial.print(F("Distance: "));
        Serial.print(distance, 1);
        Serial.print(F(" cm  |  Height: "));
        Serial.print(height, 1);
        Serial.println(F(" cm"));
    }

    // Update display
    updateDisplay(height);

    // Move servo
    int targetAngle = (height < 0) ? 0 : heightToServoAngle(height);
    moveServoSmoothly(targetAngle);

    delay(500);                    // Measurement interval
}
