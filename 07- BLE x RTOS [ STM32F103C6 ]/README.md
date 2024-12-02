# STM32 RTOS-Based GPIO and USART Control

## Video Demonstration
[Watch the video demonstration here](https://drive.google.com/file/d/1ikAQXqwTphfN4xack9VWojjD1Xys_g71/view?usp=sharing)  

---

## Table of Contents
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Code Overview](#code-overview)
- [USART Command Details](#usart-command-details)
- [How to Run](#how-to-run)
- [License](#license)

---

## Features
- **Custom RTOS Integration**: Tasks are managed using `teraRTOS`.
- **USART Command Handling**: Reacts to specific USART commands to toggle LEDs.
- **GPIO Pin Control**: Controls GPIO pins `PB8` and `PB9`.
- **Two Independent Tasks**:
  - Task 1: Toggles `PB9` when activated.
  - Task 2: Toggles `PB8` when activated.

---

## Hardware Requirements
- **Microcontroller**: STM32F103x8
- **Development Board**: STM32-based board (e.g., STM32 Blue Pill).
- **Peripherals**:
  - LEDs connected to GPIO pins `PB8` and `PB9`.
  - USART1 for serial communication.

---

## Software Requirements
- **IDE**: STM32CubeIDE
- **Toolchain**: GCC for ARM
- **Dependencies**:
  - `teraRTOS`: Custom RTOS library.
  - Peripheral drivers:
    - GPIO
    - USART
  - STM32 HAL drivers (as needed).

---

## Code Overview
1. **Initialization**:
   - Hardware components (GPIO, USART) are initialized in `main()`.
   - Pins `PB8` and `PB9` are configured as output pins for LED control.
   - USART1 is initialized for serial communication.

2. **USART Callback**:
   - Processes incoming data and sets task flags based on the command received.

3. **RTOS Tasks**:
   - **Task 1**: Toggles `PB9` based on `task1_flag`.
   - **Task 2**: Toggles `PB8` based on `task2_flag`.

4. **Main Loop**:
   - Activates tasks and starts the RTOS.

---

## USART Command Details
The application responds to the following commands via USART:

| Command (Hex) | Action                            |
| ------------- | --------------------------------- |
| `0x10`        | Activate Task 1 (toggle PB9).     |
| `0x20`        | Activate Task 2 (toggle PB8).     |
| `0x11`        | Deactivate Task 1 (turn off PB9). |
| `0x22`        | Deactivate Task 2 (turn off PB8). |

---

## How to Run
1. **Setup Hardware**:
   - Connect LEDs to GPIO pins `PB8` and `PB9` with appropriate resistors.
   - Ensure USART1 is connected to a serial terminal on your PC.

2. **Compile and Flash**:
   - Use STM32CubeIDE to build the project.
   - Flash the binary onto the STM32 microcontroller.

3. **Run the Program**:
   - Open a serial terminal (e.g., Tera Term or PuTTY).
   - Set the baud rate to `9600` and match other USART settings.

4. **Send Commands**:
   - Use the serial terminal to send hex commands (`0x10`, `0x20`, etc.) and observe LED behavior.

---

## License
This project is licensed under the BSD 3-Clause License. See [LICENSE](https://opensource.org/licenses/BSD-3-Clause) for details.

---

## Acknowledgments
- **STMicroelectronics**: For the STM32 hardware and STM32CubeIDE.
- **teraRTOS**: The custom RTOS library used in this project.
