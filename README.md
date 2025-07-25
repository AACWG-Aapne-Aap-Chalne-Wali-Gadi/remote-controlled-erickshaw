# Remote Controlled E-Rickshaw

This project focuses on transforming a second-hand electric rickshaw into a semi-autonomous vehicle. The current phase of development implements **remote control of the e-rickshaw’s forward and reverse motion** as well as **acceleration control** using an **ESP32 microcontroller** and **Bluetooth communication**.

---

## Table of Contents

- [Overview](#overview)  
- [Project Objectives](#project-objectives)  
- [System Architecture](#system-architecture)  
- [Getting Started](#getting-started)  
- [Installation](#installation)  
- [Usage](#usage)  
- [Visuals](#visuals)  
- [Project Structure](#project-structure)  
- [Roadmap](#roadmap)  
- [Contributing](#contributing)  
- [Authors and Acknowledgements](#authors-and-acknowledgements)  
- [License](#license)  
- [Project Status](#project-status)  

---

## Overview

This repository contains source code and documentation for the basic control system of an electric rickshaw. The system allows the user to control direction (forward or reverse) and throttle wirelessly through Bluetooth. The control logic is implemented on an **ESP32**, and uses the DAC pin for voltage-based throttle control along with a relay for direction switching.

---

## Project Objectives

- Enable **wireless forward and reverse movement** using relay switching  
- Provide **analog throttle control** using DAC output (0V for stop, 3.3V for full speed)  
- Build a scalable platform for future integration of steering, braking, and autonomous driving capabilities  

---

## System Architecture

```
[Mobile App]
     ↓ Bluetooth
[ESP32 Microcontroller]
     ↓
[Relay Module (IN1, K1)] — Controls direction (F/R)
     ↓
[Motor Controller Wire]
     ↓
[Electric Motor System]
```

- The **ESP32** receives Bluetooth commands and controls the relay (direction) and DAC (acceleration).
- Bluetooth commands: `'F'` for forward, `'B'` for reverse.
- A slider input on the mobile app sets DAC output between 0 and 255, corresponding to 0V–3.3V.

---

## Getting Started

### Clone the repository

```bash
git clone https://gitlab.com/aacwg/remote_controlled_e-rickshaw.git
cd remote_controlled_e-rickshaw
```

### If you already have an existing local repository

```bash
cd existing_repo
git remote add origin https://gitlab.com/aacwg/remote_controlled_e-rickshaw.git
git branch -M main
git push -uf origin main
```

---

## Installation

### Requirements

- ESP32 Development Board  
- Arduino IDE or PlatformIO  
- BluetoothSerial Library  
- 2-Channel Relay Module  
- Compatible Motor Controller  
- Mobile App for Bluetooth input  
- Power Supply (e.g., 48V battery for motor, 5V for ESP32)

### Setup Steps

1. Open `remote_throttle_direction.ino` in Arduino IDE.
2. Select the ESP32 board (e.g., "ESP32 Dev Module") in Tools.
3. Connect your ESP32 to your PC and upload the code.
4. Connect the relay and motor controller as per the wiring diagram.
5. Pair your mobile with the ESP32 Bluetooth module (named "EV_Throttle").
6. Use a mobile app with buttons and a slider:
   - `'F'` to move forward
   - `'B'` to reverse
   - Slider to control speed (0–255)

---

## Usage

- **Direction Control**:  
  The relay is triggered by sending either `'F'` or `'B'` via Bluetooth. Relay pins IN1 and K1 are used to switch the connection of the motor controller's input wire.

- **Throttle Control**:  
  The ESP32’s DAC pin (GPIO 25) outputs a voltage between 0V (value 0) and 3.3V (value 255) based on slider input. This analog signal simulates the throttle voltage input to the motor controller.

---

## Visuals

Place your project images in the `images/` folder and reference them here.

| Description                  | File Path                   |
|-----------------------------|-----------------------------|
| E-Rickshaw Control Wiring   | images/wiring_diagram.jpg   |
| Mobile App Control Layout   | images/mobile_control.jpg   |
| ESP32 Circuit View          | images/esp32_setup.jpg      |

---

## Project Structure

```
remote_controlled_e-rickshaw/
├── images/
│   ├── wiring_diagram.jpg
│   ├── mobile_control.jpg
│   └── esp32_setup.jpg
├── remote_throttle_direction.ino
├── README.md
└── wiring_diagram.pdf
```

---

## Roadmap

| Phase      | Description                                 | Status   |
|------------|---------------------------------------------|----------|
| Phase 1    | Remote control of forward/reverse and speed | Completed |
| Phase 2    | Steering control using stepper motor        | Upcoming  |
| Phase 3    | Integration of braking system               | Upcoming  |
| Phase 4    | Obstacle detection and basic autonomy       | Upcoming  |
| Phase 5    | Full SLAM-based autonomous navigation       | Planned   |

---

## Contributing

We welcome contributions, ideas, and suggestions from developers, students, and researchers.

### How to Contribute

1. Fork the repository  
2. Create a feature branch (`git checkout -b feature-name`)  
3. Make your changes  
4. Push your branch (`git push origin feature-name`)  
5. Open a Merge Request on GitLab

Please ensure that your code is well-documented and tested where applicable.

---

## License

This project is licensed under the MIT License. You are free to use, modify, and distribute the code with proper attribution.

---

## Project Status

The project is currently in **active development**.  
Phase 1 is complete, and preparations are ongoing for steering and braking integration. Updates will be pushed regularly.
