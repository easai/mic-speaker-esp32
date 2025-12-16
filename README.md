# ESP32-C3 SuperMini I2S Loopback Project

This project showcases an I2S audio loopback, where sound is captured from the MS3625 microphone and immediately played back through the MAX98357A speaker amplifier powered by the ESP32-C3 SuperMini board.

## Environment

PlatformIO configuration:

[env:esp32-c3-supermini]  
platform = espressif32  
board = esp32-c3-supermini  
framework = arduino  

## Features

- Configures ESP32-C3 I2S peripheral in master mode
- Reads audio samples from MS3625 microphone (I2S input)
- Streams audio directly to MAX98357A DAC amplifier (I2S output)
- Simple loopback for testing audio path

## Hardware Connections

### ESP32-C3 SuperMini Pin Assignments

| Signal        | ESP32-C3 GPIO | Connected Device Pin |
|---------------|---------------|----------------------|
| I2S_BCLK      | GPIO2         | MS3625 BCLK, MAX98357A BCLK |
| I2S_LRCLK     | GPIO3         | MS3625 LRCLK, MAX98357A LRCLK |
| I2S_DIN       | GPIO0         | MS3625 SD (data out from mic) |
| I2S_DOUT      | GPIO4         | MAX98357A DIN (data in to amp) |
| 3.3V          | 3V3 pin       | VCC for MS3625 and MAX98357A |
| GND           | GND pin       | Common ground for all devices |

### Notes

- Both microphone and amplifier share the same BCLK and LRCLK lines.  
- MS3625 provides audio data on GPIO0 (I2S_DIN).  
- MAX98357A receives audio data on GPIO4 (I2S_DOUT).  
- Ensure proper power supply: both devices require 3.3V.  
- Use decoupling capacitors near sensor and amplifier for stable operation.

## Usage

1. Connect the MS3625 microphone and MAX98357A amplifier to the ESP32-C3 SuperMini according to the table above.  
2. Flash the firmware using PlatformIO or Arduino IDE.  
3. Open the serial monitor at 115200 baud to confirm loopback start.  
4. Speak into the microphone and listen through the speaker.

## License

This project is released under the MIT License.
