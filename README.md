# ESP32 Autonomous Surveillance & Bomb Detection Rover

An RTOS-based autonomous surveillance rover built on ESP32-CAM capable of real-time video streaming, multi-sensor bomb detection, and remote navigation.

---

## 🚀 Key Features

- 📡 Live video streaming over WiFi
- 🤖 FreeRTOS-based real-time architecture
- 🧠 Multi-sensor bomb detection (Gas + Metal + Temperature)
- 🎮 Web-based remote control interface
- ⚡ PWM-based motor speed control
- 🔍 Pan-tilt camera mechanism
- 📊 Real-time telemetry monitoring
- 🧩 Modular embedded firmware design

---

## 🧱 System Architecture

- Sensor Task → periodic environmental sensing  
- Decision Task → threat detection logic  
- Motor Task → real-time motion control  
- Telemetry Task → system health monitoring  

Inter-task communication implemented using FreeRTOS queues.

---

## 🛠️ Hardware Used

- ESP32-CAM
- L298N Motor Driver
- MQ Gas Sensor
- Metal Detector Module
- Temperature Sensor
- Pan-Tilt Servo Mechanism
- 4WD Robot Chassis
- Li-ion Battery Pack

---

## 💻 Software Stack

- Embedded C / Arduino Framework
- ESP32 FreeRTOS
- Async Web Server
- WebSocket Streaming
- PWM Motor Control

---

## 📸 Project Demonstration

> Add your robot photos and demo video in the `/docs` folder.

---

## 🔧 Future Improvements

- SLAM-based navigation  
- Edge AI object detection  
- OTA firmware updates  
- Low-power optimization  

---

## 👨‍💻 Author

**Molli Vamsi Krishna**  
Embedded Systems & Robotics Engineer  

---

⭐ If you find this project useful, consider starring the repo.
