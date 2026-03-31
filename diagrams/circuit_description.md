# Circuit Wiring Reference

## HC-SR04 Ultrasonic Sensor

```
HC-SR04           Arduino Uno
-------           -----------
VCC       ──────► 5V
GND       ──────► GND
TRIG      ──────► Pin 9
ECHO      ──────► Pin 10
```

## OLED Display (0.96" I2C SSD1306)

```
OLED              Arduino Uno
------            -----------
VCC       ──────► 5V
GND       ──────► GND
SDA       ──────► A4
SCL       ──────► A5
```

> **Note:** The I2C address is `0x3C` by default. If your display stays blank, try `0x3D` in the sketch.

## SG90 Servo Motor

```
Servo Wire         Arduino Uno
----------         -----------
Red   (VCC)  ────► 5V
Brown (GND)  ────► GND
Orange (SIG) ────► Pin 6
```

> **Tip:** If the servo causes the Arduino to reset or behave erratically, power it from an **external 5V supply** (share GND with Arduino).

---

## Power

- Use a USB cable connected to a PC/laptop for basic testing.
- For standalone use, power the Arduino with a **7–12V DC adapter** via the barrel jack.
- The servo can draw up to 250 mA; use an external supply for heavy loads.
