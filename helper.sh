#!/bin/bash
set -e

## Download Freematic UART Libraries
## Designed to run on MacOS. YMMV if you try it on another OS.
mkdir -p /Users/$USER/Documents/Arduino/libraries/OBD2UART || true
wget -O /Users/$USER/Documents/Arduino/libraries/OBD2UART/OBD2UART.cpp https://raw.githubusercontent.com/stanleyhuangyc/ArduinoOBD/master/libraries/OBD2UART/OBD2UART.cpp
wget -O /Users/$USER/Documents/Arduino/libraries/OBD2UART/OBD2UART.h https://raw.githubusercontent.com/stanleyhuangyc/ArduinoOBD/master/libraries/OBD2UART/OBD2UART.h



