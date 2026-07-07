# Week 1: Dynamic LED Blink & Speed Controller

## Project Description
An integrated Arduino system that dynamically controls the blinking frequency of a hardware LED using an analog potentiometer. The system tracks system cycles, computing and broadcasting telemetry data (blink counts and latency delays) in real-time over a serial connection.

---

## Hardware Required
To replicate this circuit, the following hardware components are required:
* **1x** Arduino Uno (or compatible microcontroller board)
* **1x** 5mm LED
* **1x** $220\Omega$ Current Limiting Resistor
* **1x** $10k\Omega$ Rotary Potentiometer
* **1x** Breadboard
* **Solid-core** Jumper Wires

---

## Circuit Diagram Description
Since this is a text-based layout, follow these hardware pin mapping connections:

1. **LED Configuration:**
   * Connect the **Anode** (longer leg) of the LED to Digital Pin `13` of the Arduino.
   * Connect the **Cathode** (shorter leg) of the LED to one end of a $220\Omega$ resistor.
   * Connect the other terminal of the resistor to the Arduino's **GND** pin.

2. **Potentiometer Configuration:**
   * Connect **Pin 1** (Left Terminal) to the Arduino **GND** rail.
   * Connect **Pin 2** (Middle Wiper Terminal) to Analog Input Pin **`A0`**.
   * Connect **Pin 3** (Right Terminal) to the Arduino **5V** power rail.

---

## How to Upload Code

1. **Install IDE:** Ensure you have the latest [Arduino IDE](https://www.arduino.cc/en/software) installed on your local system.
2. **Connect Hardware:** Connect your Arduino board to your computer using a compatible USB data cable.
3. **Open Project:** Copy the source code found within `led_blink.ino` into a new project window inside your Arduino IDE.
4. **Configure Board Target:**
   * Navigate to **Tools > Board** and select your board type (e.g., *Arduino Uno*).
   * Navigate to **Tools > Port** and select the active COM port assigned to your board.
5. **Compile & Push:** Click the **Verify** button (Checkmark icon) to build the program. Once successful, click the **Upload** button (Right arrow icon) to push the binary to the microcontroller.

---

## Expected Output
* **Hardware Interface:** The LED on pin 13 will begin to blink regularly. Rotating the potentiometer clockwise will increase the cycle delay (slowing down the flash rate); rotating it counter-clockwise will decrease the delay (speeding up the flash rate).
* **Serial Monitor Telemetry:** Open the Serial Monitor (**Tools > Serial Monitor**) and configure the baud rate to **9600**. You should observe live logs streaming down in the following structural format:
  ```text
  Blink count: 1 | Delay: 120
  Blink count: 2 | Delay: 435
  Blink count: 3 | Delay: 980
