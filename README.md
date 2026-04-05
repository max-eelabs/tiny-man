# TinyMan DevKit 
Git repository that contains user guidelines and code samples for TinyMan ATtiny85 Development Board

## Board Description

The TinyMan DevKit is a powerful and compact development board centered around the ATtiny85 microcontroller (MCU), offering an ideal platform for embedded systems projects, IoT applications, and microcontroller programming education. This ATtiny-based development kit simplifies the process of working with the popular ATtiny85 chip, providing all the essential features for rapid prototyping and deployment.

Designed for both beginners and experienced developers, the TinyMan DevKit features seamless USB programming capabilities through the Micronucleus bootloader, eliminating the need for external programmers in most use cases. The board's robust design ensures reliability and ease of use, making it perfect for hobbyists, students, and professionals working with AVR microcontrollers.

TinyMan DevKit, if ordered with MCU has micronuclious bootkloader and blink sketch pre-loaded; 

## Code upload with micronuclious (USB)
- Using Arduino IDE - [ATTinyCore](https://github.com/SpenceKonde/ATTinyCore/blob/1.5.2/Installation.md)
- Using [Platfiorm IO](https://platformio.org/) - Please see below

### Platform IO Configuration
```ini
[env:attiny85]
platform = atmelavr
board = digispark-tiny
framework = arduino
```


## Burning micronuclious bootloader with USBAasp

[Micronucleus](https://github.com/micronucleus/micronucleus) is a bootloader designed for AVR ATtiny microcontrollers with a minimal usb interface, cross platform libusb-based program upload tool, and a strong emphasis on bootloader compactness. To the authors knowledge this is, by far, the smallest USB bootloader for AVR ATtiny

Bootlader - A microcontroller (MCU) bootloader is a small, specialized program stored in non-volatile memory that runs immediately upon power-up, initiating the system, enabling secure firmware updates, and managing the main application execution.

[USBasp](https://www.fischl.de/usbasp/) - is a USB in-circuit programmer for Atmel AVR controllers.

### Preparation
#### Software
- Windows users need to install USBasp driver using [Zadig](https://zadig.akeo.ie/)
- Install [AVRDUDE](https://github.com/avrdudes/avrdude/tree/v7.2) 
- Grab ATtinyCore [avrdude.conf](https://github.com/SpenceKonde/ATTinyCore/blob/1.5.2/avr/avrdude.conf)
- Download latest micronuclious booloader [hexfile](https://github.com/micronucleus/micronucleus/blob/v2.6/firmware/releases/t85_default.hex)
#### Hardware
- Match GND pin on USBasp 6ping header with TinyMan GND pin (8pin header) and connect USBasp to TinyMan
- Supply external power to TinyMan (USB-C or screw terminal)
- Connect USBasp to your computer. You are ready to burn bootloader

### Burning Bootloader

avrdude.conf and t85_default.hex files are prepared in the `conf` folder of 

```
avrdude -Cavrdude_attinycore_1_5_2.conf -v -pattiny85 -cusbasp -e -Uefuse:w:0xFE:m -Uhfuse:w:0b11011111:m -Ulfuse:w:0xF1:m -Uflash:w:micronuclious_2_6_t85_default.hex:i
```

#### Fuse configuration
- `-Uefuse:w:0xFE:m`: Writes the extended fuse to 0xFE. This enables self-programming (SELFPRGEN=0), allowing the microcontroller to reprogram its own flash memory.
- `-Uhfuse:w:0b11011111:m` (0xDF): Writes the high fuse to 0xDF. This keeps the reset pin enabled (RSTDISBL=1), preserving the reset function. The micronucleus bootloader uses the reset pin for USB communication. Other settings: DWEN=1 (debug wire enabled), SPIEN=0 (serial programming enabled), WDTON=1 (watchdog disabled), EESAVE=1 (EEPROM preserved during chip erase), BODLEVEL=7 (brown-out detection disabled).
- `-Ulfuse:w:0xF1:m`: Writes the low fuse to 0xF1. This sets the clock source to the internal 8MHz RC oscillator with PLL enabled for 16MHz CPU clock (CKSEL=0001), start-up time to 6 CK/14 CK + 64 ms (SUT=00), clock output  disabled (CKOUT=0), and clock divided by 8 initially (CKDIV8=1, but PLL overrides for 16MHz operation in bootloader).

More about fuses [fusecalc](https://www.engbedded.com/fusecalc/)
