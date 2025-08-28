# DC Motor Control System Design with Integrated Safety Feature

## 📌 Overview
This project implements a **DC motor control system** on the STM32F4 microcontroller platform.  
It integrates **PWM-based motor speed control**, a **safety shutoff mechanism** triggered by overcurrent detection, and a simple **user interface with button and LED indicators**.

The system is designed with a focus on **embedded safety**, **real-time monitoring**, and **robust firmware structure**.

---

## ⚡ Features
- PWM motor control (50% duty cycle start/stop)
- Overcurrent detection via ADC
- Automatic motor shutdown when threshold exceeded
- Button-controlled motor toggle (with debounce logic)
- Fault indicator LED
- Modular and portable C firmware structure

---

## 🛠️ Hardware Requirements
- STM32F411 (or compatible STM32F4 MCU)
- DC motor driver circuit
- Current sensing circuit (shunt resistor + amplifier)
- Push button (motor control)
- LED (fault indicator)

---

## 💻 Software & Tools
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
- [VS Code + CMake](https://code.visualstudio.com/) (for build/run outside CubeIDE)  
- STM32 HAL & CMSIS libraries  
- OpenOCD / ST-Link utility for flashing 
