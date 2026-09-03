# RoverX 

### Event Flow
``` 
1. Introduction 
2. Mechanical and Electrical Analysis
3. Programming
4. Building the bot
```
# RoverX - TechnoVIT

Resources and firmware for the RoverX workshop by IEEE RAS VIT Chennai. This covers the CAD assembly and ESP32 web-server control for a 4WD skid-steer rover.

## Repository Structure

*   **/Cad_Models**
    *   `/Assets` - Individual parts and reference files.
    *   `4WD_Rover.SLDASM` - Native SolidWorks assembly file.
    *   `4WD_Rover_Step.STEP` - Exported STEP file for Onshape/browser viewing.
*   **/esp32_code**
    *   `esp32_code.ino` - Main Arduino IDE sketch for the ESP32 Wi-Fi controller.
    *   `esp32_code.txt` - Text backup of the firmware.
*   `Readme.md` - Documentation.

## Verified Wiring

**Power**
*   **ESP32 Vin** -> Driver 1 **5V**
*   **Battery 12V (+)** -> Driver 1 & 2 **12V**
*   **GND** -> Tie Battery (-), ESP32 GND, and both Driver GNDs together.

**Driver 1 (Left)**
*   **ENA:** D32 (PWM)
*   **IN1:** D33
*   **IN2:** D25
*   **IN3:** D26
*   **IN4:** D27
*   **ENB:** D14 (PWM)

**Driver 2 (Right)**
*   **ENA:** D22 (PWM)
*   **IN1:** RX2 (D16)
*   **IN2:** TX2 (D17)
*   **IN3:** D18
*   **IN4:** D19
*   **ENB:** D23 (PWM)

## Quick Start

1.  **Mechanical:** Open `4WD_Rover.SLDASM` in SolidWorks or import the `.STEP` file to Onshape to view the physical layout.
2.  **Flash:** Open `esp32_code.ino` in the Arduino IDE, select the ESP32 board, and upload.
3.  **Run:** Power the rover with the 12V battery. Connect your phone to the **yourwifiname** Wi-Fi network (password: `yourpwd`).
4.  **Control:** Go to `http://192.168.4.1` in your mobile browser to drive.