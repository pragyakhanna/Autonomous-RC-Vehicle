# Autonomous RC Vehicle

An autonomous RC car system built with PX4 and embedded C++ to enable autonomous navigation, obstacle detection, and real-time coordination between flight controller and onboard computer.

## 🚗 Overview

This project combines embedded development and computer vision to allow an RC vehicle to drive autonomously, avoid obstacles, and communicate sensor data in real time.

## 🧠 Key Features

- Autonomous navigation using PX4 and uORB
- Real-time motor, servo, and sensor control in C++
- Obstacle detection offloaded to Raspberry Pi (Python + OpenCV)
- MAVLink integration for FMU–companion computer sync

## 🔧 Tech Stack

- **Firmware:** PX4, uORB, C++
- **Vision & Control:** Python, OpenCV, Ultrasonic sensors
- **Communication:** MAVLink
- **Tools:** Keil, pySerial, Open3D
- **Hardware:** STM32, Raspberry Pi, RC chassis, custom sensor housing
