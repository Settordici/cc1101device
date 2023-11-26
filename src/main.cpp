
#include <Arduino.h>
#include <U8g2lib.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <Adafruit_NeoPixel.h>
#include "RCSwitch.h"
#include <Arduino.h>
#include <SPIFFS.h>
#include <FS.h>

#define CSV_PARSER_DONT_IMPORT_SD
#include <CSV_Parser.h>

#include "bitmaps.h"
#include "animations.h"
#include "functions.h"
#include "definitions.h"
#include "menus.h"

/* 
Pins needed
2 for I2C screen
3/5 for the joystick
4 for the SPI antenna
2 for the antenna

3 gnd
2 3.3 v

*/

// ! Insulate better

void setup() {
  Serial.begin(115200);
  u8g2.setColorIndex(1);  // set the color to white
  u8g2.begin();
  u8g2.setBitmapMode(1);

  // define pins for buttons
  // INPUT_PULLUP means the button is HIGH when not pressed, and LOW when pressed
  // since it´s connected between some pin and GND
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP); // left button
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP); // select button
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP); // right button
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP); // up button
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP); // down button

  nled.begin();
  nled.show(); // Initialize the pixel to 'off'

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  if(!SPIFFS.exists("/codes.csv")) {
    File file = SPIFFS.open("/codes.csv", FILE_WRITE);
    if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
    }
    if (file.print("DisplayName,Frequency,Protocol,Value,Bit,Pulse\n")) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }
    file.close();
  }
  
  listAllFiles();
}


void loop() {
  u8g2.clearBuffer();

  if(!animation && current_screen == -1) {
    mainMenu();
  }

  switch(current_screen) { 
    case 1:
      receiveCode();
      break;
    case 2:
      transmitCode();
      break;
    case 5:
      wifiScan();
      break;
    case 6:
      deepSleep();
      break;
  }

  u8g2.sendBuffer();

}