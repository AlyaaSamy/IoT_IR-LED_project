# ESP32 IR Sensor & LED MQTT Control Project

## 📡 Description

This project allows you to control a led and detect objects using an IR sensor via MQTT over WiFi using an ESP32. It leverages the `WiFi.h` and `PubSubClient.h` libraries for network and MQTT communication. The system publishes sensor data and listens for control commands to manage the led, making it suitable demo for IoT-based object detection and remote control applications.

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
   The device connects to a public MQTT broker (`broker.emqx.io`) and subscribes to `/aliaa/led` topic for LED control.

4. **Object Detection with IR**  
   - Publishes `OBJECT_DETECTED` to `/aliaa/ir` topic if IR sensor detects something.
   - Publishes `NO_OBJECT_DETECTED` otherwise.

5. **LED Control**  
   - Subscribes to messages on `/aliaa/led` so you can you control the led based on what the esp received:
     - `LED_ON` → Turns LED on
     - `LED_OFF` → Turns LED off

6. **IoT MQTT Panel App**  
   - Add a **switch** that sends/publishes `LED_ON` when turned on or `LED_OFF` when turned off to `/aliaa/led`.
   - Add a **LED widget** that listens/subscribes to `/aliaa/ir` and lights up if `OBJECT_DETECTED` is received and turnes back off if `NO_OBJECT_DETECTED` is received from the esp over mqtt.

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
- I used `WiFi.mode(WIFI_STA);` in the setup() in my code because when I ran the code it kept stuck at `connecting to wifi..` and the wifi.status() result was the number 6 after searching I found this command and it helped establishh the connection successfully. You don't need it if your wifi.status() code didn't return 6. for more info about this here: https://forum.arduino.cc/t/serial-println-wifi-status-codes-meaning/486265
- if you're using NodeMCU (ESP8266) the code still works but use `ESP8266WiFi.h` library instead of `WiFi.h`

---

## 👩‍💻 Developed by

Alyaa Samy
