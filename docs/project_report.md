# Object Height Measurement System — Project Report

## Abstract

This project focuses on building a smart height-measuring device using an ultrasonic sensor and an Arduino Uno. The sensor measures the distance from a fixed point to the top of an object, and the system calculates the object's height by subtracting that distance from a known reference height.

It is a non-contact, affordable, and accurate way to measure height — suitable for inventory tracking, industrial automation, or robotics. The measured height is displayed in real time on an OLED screen, and a servo motor reacts proportionally to the height reading.

---

## Introduction

Measuring object height is important in packaging, manufacturing, agriculture, and robotics. Doing this manually is slow and error-prone. This project introduces an automated solution using an Arduino, an ultrasonic sensor, and a servo motor to eliminate manual effort and reduce measurement errors.

---

## Objectives

- Build a low-cost, automated height measurement system.
- Use an **HC-SR04** ultrasonic sensor for non-contact measurement.
- Display real-time results on a **0.96" OLED** screen.
- Use an **SG90 servo motor** to respond physically to measured height.

---

## Components

| Component                   | Quantity |
|-----------------------------|----------|
| Arduino Uno                 | 1        |
| Ultrasonic Sensor (HC-SR04) | 1        |
| Servo Motor (SG90)          | 1        |
| OLED Display (0.96" I2C)    | 1        |
| Breadboard                  | 1        |
| Jumper Wires                | As needed |
| USB Cable / Power Supply    | 1        |

---

## Component Descriptions

### 1. HC-SR04 Ultrasonic Sensor

| Parameter       | Value              |
|----------------|--------------------|
| Working Voltage | 5V DC             |
| Current         | 15 mA             |
| Range           | 2 cm – 400 cm     |
| Accuracy        | ±3 mm             |

Emits a 40 kHz ultrasonic pulse via the TRIG pin. The pulse reflects off the object and returns to the ECHO pin. Distance is calculated as:

```
Distance (cm) = (Echo Duration in µs × 0.0343) / 2
```

### 2. OLED Display (SSD1306)

| Parameter       | Value         |
|----------------|---------------|
| Voltage         | 3.3V – 5V DC |
| Interface       | I2C (SDA/SCL)|
| Resolution      | 128 × 64 px  |
| Current         | ~20–30 mA    |

Communicates over I2C (only 2 data pins required), displaying height and servo angle in real time.

### 3. SG90 Servo Motor

| Parameter       | Value          |
|----------------|----------------|
| Voltage         | 4.8V – 6V DC  |
| Angle Range     | 0° – 180°     |
| Torque          | ~1.8 kg·cm    |
| Current (no load) | 100–250 mA  |

Controlled via PWM signals from the Arduino; rotates to an angle based on the measured height.

---

## Working Principle

1. **Ultrasonic measurement** — HC-SR04 measures distance to the object top.
2. **Height calculation** — `Height = Sensor Height − Measured Distance`
3. **Display** — OLED updates with current height value every 500 ms.
4. **Servo response** — Motor rotates to an angle corresponding to height:

| Height Range  | Servo Angle |
|--------------|-------------|
| < 10 cm      | 0°          |
| 10 – 14 cm   | 45°         |
| 14 – 18 cm   | 90°         |
| 18 – 24 cm   | 135°        |
| ≥ 24 cm      | 180°        |

---

## Procedure

### Step 1 — Connect HC-SR04
- VCC → 5V, GND → GND, TRIG → Pin 9, ECHO → Pin 10

### Step 2 — Connect OLED Display
- VCC → 5V, GND → GND, SDA → A4, SCL → A5

### Step 3 — Connect Servo Motor
- Red → 5V, Black/Brown → GND, Signal → Pin 6

### Step 4 — Upload Code
- Open `src/height_measurement.ino` in Arduino IDE.
- Install libraries: **Adafruit SSD1306**, **Adafruit GFX**.
- Select Board: **Arduino Uno**, then upload.

---

## Applications

- **Manufacturing** — Assembly line dimension checking
- **Logistics** — Parcel height measurement for sorting systems
- **Agriculture** — Greenhouse plant growth monitoring
- **Robotics** — Object detection and profiling
- **Education** — Hands-on embedded systems learning

---

## Advantages

- Non-contact measurement — suitable for sterile environments
- Real-time updates — useful for moving conveyor applications
- Low cost — HC-SR04 and SG90 are widely available
- Beginner-friendly — Arduino platform with simple wiring
- Expandable — easy to add wireless modules, buzzers, or LCDs

---

## Limitations

- Soft or angled surfaces may cause inconsistent echo returns
- Fixed sensor height constrains the measurable range
- Temperature and humidity affect ultrasonic wave speed
- Servo provides only basic positioning (0°–180°)

---

## Future Scope

- Wireless transmission via **Bluetooth / Wi-Fi / LoRa**
- **SD card** or **cloud** data logging for trend analysis
- Multi-sensor setup for full 3D object profiling (width + depth)
- **Machine learning** for automatic shape-based calibration
- **Camera module + OpenCV** for intelligent object identification
- Ruggedised industrial enclosure with calibration controls

---

## Conclusion

The Object Height Measurement System demonstrates how ultrasonic sensing, servo actuation, and real-time display can be combined into a compact, affordable, and effective measurement tool. It is well-suited for educational, prototyping, and small-scale industrial use, and provides a strong foundation for more advanced automated measurement systems.

---

## References

1. Curtis D. Johnson, *Process Control Instrumentation Technology*, Prentice Hall India.
2. D.V.S. Murty, *Transducers and Instrumentation*, Prentice Hall India.
3. [Arduino Documentation](https://www.arduino.cc/)
4. [Adafruit SSD1306 OLED Guide](https://learn.adafruit.com/monochrome-oled-breakouts)
5. [HC-SR04 Sensor Guide](https://www.electronicwings.com/)
6. [Servo Motor with Arduino](https://lastminuteengineers.com/servo-motor-arduino-tutorial/)
7. [HC-SR04 Datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
8. [SG90 Servo Datasheet](https://www.towerpro.com.tw/product/sg90-2/)
