# Ranger Things
An OBDII gauge.

## Hardware
 - [Arduino Nano](https://www.amazon.com/Arduino-A000005-ARDUINO-Nano/dp/B0097AU5OU/)
 - [1.3" TFT Display](https://www.adafruit.com/product/4313)
 - [Freematics OBD-II UART Adapter](https://freematics.com/store/index.php?route=product/product&product_id=83)

Building this is pretty straightforward! Just follow the docs for the display and OBD adapter on how to wire it up. I'm using the default pins.

&nbsp;

## Requirements
You'll want to install these via the Arduino library manager:

```
Adafruit_GFX
Adafruit ST7735 and ST7789
```

You will also need the `OBD2UART` library. If you're on a Mac you can grab this by running the `helper.sh` script.

&nbsp;


## Customizing
The general idea is to have it grab the PIDs you want to display. You can see the [available PIDs here](https://github.com/stanleyhuangyc/ArduinoOBD/blob/master/libraries/OBD2UART/OBD2UART.h#L25). There's also a wiki article that [lists them](https://en.wikipedia.org/wiki/OBD-II_PIDs), in case any are missing. 

&nbsp;


## Flashing the image
Use the Arduino IDE as normal. The only caveat is you may need to disconnect the UART RX pin before uploading the image, else you'll get errors. You can just unplug the 4 pin connector that goes into the OBDII adapter to work around this. 


