#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <OBD2UART.h>

COBD obd;

// Display setup
#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8
#define BACKGROUND_COLOR ST77XX_BLACK
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST); // For 1.14", 1.3", 1.54", and 2.0" TFT with ST7789:

void setup() {
  tft.init(240, 240);           // Init ST7789 240x240
  tft.fillScreen(BACKGROUND_COLOR);
  tft.setTextSize(5);
  drawtextByLine("FORD\nRANGER", ST77XX_BLUE, 0);

  // Wait for connection to adapter
  for (;;) {
    delay(1000);
    byte version = obd.begin();
    drawtextByLine("OBDbegin", ST77XX_WHITE, 0);
    drawtextByLine("Connect?", ST77XX_WHITE, 40);
    if (version > 0) {
      drawtextByLine("Detected", ST77XX_GREEN, 80);
      break;
    } else {
      drawtextByLine("Not\ndetected", ST77XX_RED, 80);
    }
  }

  tft.fillScreen(BACKGROUND_COLOR);
  drawtextByLine("OBD Init?", ST77XX_WHITE, 0);
  drawtextByLine("Waiting..", ST77XX_WHITE, 60);
  while (!obd.init()); // Initiate OBD-II connection until success
  drawtextByLine("OBD2 OK!", ST77XX_GREEN, 80);

  // Reset display
  delay(1000);
  tft.fillScreen(BACKGROUND_COLOR);
  randomSeed(analogRead(0)); // for when testing/generating dummy values

  // Draw titles on startup to reduce the time it takes to redraw the display (improves fps)
  drawtextByLine("RPM:", ST77XX_BLUE, 0);
  drawtextByLine("BOOST:", ST77XX_BLUE, 80);
  drawtextByLine("WATTEMP:", ST77XX_BLUE, 160);

  // Check for error codes on startup? Flash display if true
  //  tft.invertDisplay(true);
  //  delay(500);
  //  tft.invertDisplay(false);
  //  delay(500);

}

void loop() {
// Tests:
//  float BOOST = random(-500, 200) / 100;
//  float OIL_TEMP = random(150, 275);
//  float RPM = random(600, 9000);

  // Get values from OBD
  int RPMvalue;
  if (obd.readPID(PID_RPM, RPMvalue)) {
    if (RPMvalue < 1000) {
      drawtextByLine("    ", ST77XX_WHITE, 40);
    }
    drawtextByLine(String(RPMvalue), ST77XX_WHITE, 40);
  }

  int WATERvalue;
  if (obd.readPID(PID_COOLANT_TEMP, WATERvalue)) {
    if (WATERvalue > 98) {
      drawtextByLine(String(WATERvalue), ST77XX_RED, 200);
    } else {
        drawtextByLine(String(WATERvalue), ST77XX_WHITE, 200);
    }
  }

  int MAPvalue;
  int BAROvalue;
  
  if (obd.readPID(PID_INTAKE_MAP, MAPvalue)) {
    if (obd.readPID(PID_BAROMETRIC, BAROvalue)) {
      int BOOSTvalue = MAPvalue - BAROvalue; //calculate boost pressure
      BOOSTvalue = map(BOOSTvalue, 0, 255, 0, 37); //convert to PSI (https://mechanics.stackexchange.com/questions/45239/calculate-boost-from-map-sensor-via-obd-ii)
      drawtextByLine(String(MAPvalue), ST77XX_WHITE, 120);
    }
  }

  // Tests
  //  drawtextByLine(String(RPM), ST77XX_WHITE, 40);
  //  drawtextByLine(String(BOOST), ST77XX_WHITE, 120);
  //  drawtextByLine(String(OIL_TEMP), ST77XX_WHITE, 200);


  // Example for reading multiple PIDs at once -- https://github.com/stanleyhuangyc/ArduinoOBD/blob/master/libraries/OBD2UART/examples/obd_uart_test/obd_uart_test.ino#L69
}


void drawtext(String text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color, BACKGROUND_COLOR);
  tft.setTextWrap(true);
  tft.print(text);
}

void drawtextByLine(String text, uint16_t color, uint16_t line) {
  tft.setCursor(0, line);
  tft.setTextColor(color, BACKGROUND_COLOR);
  tft.setTextWrap(false);
  tft.print(text);
}
