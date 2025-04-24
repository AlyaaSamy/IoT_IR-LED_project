# ESP32 IR Sensor & LED MQTT Control Project

## 📡 Description

This project allows you to control an LED and detect objects using an IR sensor via MQTT over WiFi using an ESP32. It leverages the `WiFi.h` and `PubSubClient.h` libraries for network and MQTT communication. The system publishes sensor data and listens for control commands to manage an LED, making it suitable for IoT-based object detection and remote control applications.

---

## 🛠 Hardware Setup

### Components:
- ESP32 microcontroller
- IR sensor
- LED
- Breadboard and jumper wires

### Circuit:
1. **IR Sensor**:
   - OUT → GPIO 4 on ESP32
   - VCC → 3.3V on ESP32
   - GND → GND

2. **LED**:
   - Anode (long leg) → GPIO 15 through a resistor
   - Cathode (short leg) → GND

---

## 🔌 Functionality Overview

1. **WiFi Connection**  
   The ESP32 connects to a WiFi network to establish a WSN (Wireless Sensor Network) for communication.

2. **Serial Debugging**  
   Serial Monitor shows WiFi status, IP address, and MQTT events for debugging.

3. **MQTT Broker Connection**  
   The device connects to a public MQTT broker (`broker.emqx.io`) and subscribes to `/sector/alaa/led` for LED control.

4. **Object Detection with IR**  
   - Publishes `OBJECT_DETECTED` to `/sector/alaa/ir` if IR sensor detects something.
   - Publishes `NO_OBJECT_DETECTED` otherwise.

5. **LED Control**  
   - Subscribes to messages:
     - `LED_ON` → Turns LED on
     - `LED_OFF` → Turns LED off

6. **IoT MQTT Panel App**  
   - Add a **switch** that sends `LED_ON` or `LED_OFF` to `/sector/alaa/led`.
   - Add a **LED widget** that listens to `/sector/alaa/ir` and lights up if `OBJECT_DETECTED` is received.

---

## 📚 Libraries Required

- WiFi.h
- PubSubClient.h

Install via the Arduino Library Manager.

---

## 🚀 How to Run

1. Connect your hardware as described.
2. Upload the code using the Arduino IDE.
3. Open Serial Monitor at 9600 baud rate.
4. Use IoT MQTT Panel or any MQTT app to interact.

---

## 🔐 Notes

- The broker used is public, so messages are not secure. For production, use secure connections and authentication.
- Modify `ssid` and `pass` in the code for your WiFi credentials.

---

## 👩‍💻 Developed by

Alyaa Samy
