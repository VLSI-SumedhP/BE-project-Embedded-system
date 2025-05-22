# Voice Controlled Elevator System

This project demonstrates a voice-controlled elevator system using the **Elechouse Voice Recognition Module V3**, **ATmega2560**, and a **stepper motor**. The system interprets spoken floor commands and drives a motor to simulate an elevator reaching designated floors.

## 📷 System Overview

### Block Diagram

![Block Diagram](FINAL%20BLOCK%20DIGRAM%20BE%20MAJOR%20PROJECT%20SEM%202%20-%20Copy.png)

---

### Serial Monitor Output Samples

#### Recognized Voice Commands and Motor Actions

- ![Output 1](output%20img%201.png)
- ![Output 2](output%20img%202.png)
- ![Output 3](output%20img%203.png)
- ![Output 4](output%20img%204.png)
- ![Output 5](output%20img.png)

---

## ⚙️ Hardware Components

- ATmega2560 Pro Microcontroller
- Elechouse Voice Recognition Module V3
- Microphone
- Stepper Motor + Stepper Motor Driver (e.g., ULN2003/A4988)
- Limit Switches
- I2C Serial Interface Modules
- 5V and 9V Power Supply

---

## 🧠 Software Requirements

- Arduino IDE
- Elechouse Voice Recognition V3 Library
- Serial Monitor (baud rate: `115200`)

---

## 📂 Project Files

- `voice_controlled_elevator.ino` — Main Arduino sketch for the elevator control logic.

---

## 🔌 How It Works

1. **Voice Recognition Initialization**:
   - Loads predefined voice commands (e.g., "floor one", "floor two", etc.).

2. **Command Detection**:
   - Recognizes the floor number spoken by the user.
   - Prints the recognized command to the Serial Monitor.

3. **Motor Movement**:
   - The system calculates required steps and drives the stepper motor to move the elevator to the commanded floor.
   - Direction (clockwise/anticlockwise) depends on the current and target floor.
   - Limit switches are used to ensure safety and accurate floor detection.

---

## 🗣 Sample Voice Commands

| Command       | Record Number | Floor  |
|---------------|----------------|--------|
| `floor one`   | 1              | 1st    |
| `floor two`   | 2              | 2nd    |
| `floor three` | 3              | 3rd    |

---

## 🛠 Setup Instructions

1. Connect all hardware as shown in the block diagram.
2. Load and upload `voice_controlled_elevator.ino` to the ATmega2560 board.
3. Train the voice recognition module using the Elechouse tool or sketch.
4. Open the Serial Monitor (baud rate `115200`) to monitor recognized commands and movement.
5. Speak floor commands to test elevator operation.

---

## 📸 Screenshots

### Arduino Serial Monitor Example

```text
-> Elechouse Voice Recognition V3 Module
-> Recognizer cleared.
-> floor1 loaded
-> floor2 loaded
-> floor3 loaded
-> VR Index 2   | RecordNum 2 | Signature: floor two
-> anticlockwise
