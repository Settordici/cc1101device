
#include <Arduino.h>
#include <U8g2lib.h>

#include "bitmaps.h"
#include "animations.h"
#include "functions.h"
#include "definitions.h"

/* 
Pins needed
2 for I2C screen
3/5 for the joystick
4 for the SPI antenna
2 for the antenna

3 gnd
2 3.3 v

*/

void setup() {
  u8g2.setColorIndex(1);  // set the color to white
  u8g2.begin();
  u8g2.setBitmapMode(1);

  // define pins for buttons
  // INPUT_PULLUP means the button is HIGH when not pressed, and LOW when pressed
  // since it´s connected between some pin and GND
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP); // left button
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP); // select button
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP); // right button

}


void loop() {

    if (current_screen == -1) {
      // left and right buttons only work for the menu screen
      if ((digitalRead(BUTTON_LEFT_PIN) == LOW) && (button_left_clicked == 0)) { // left button clicked - jump to previous menu item
        shiftLeft(20, item_selected);
        item_selected = item_selected - 1; // select previous item
        button_left_clicked = 1; // set button to clicked to only perform the action once
        if (item_selected < 0) { // if first item was selected, jump to last item
          item_selected = NUM_ITEMS-1;
        }
      }
      else if ((digitalRead(BUTTON_RIGHT_PIN) == LOW) && (button_right_clicked == 0)) { // right button clicked - jump to next menu item
        shiftRight(20, item_selected);
        item_selected = item_selected + 1; // select next item
        button_right_clicked = 1; // set button to clicked to only perform the action once
        if (item_selected >= NUM_ITEMS) { // last item was selected, jump to first menu item
          item_selected = 0;
          }
      } 

      if ((digitalRead(BUTTON_LEFT_PIN) == HIGH) && (button_left_clicked == 1)) { // unclick 
        button_left_clicked = 0;
      }
      if ((digitalRead(BUTTON_RIGHT_PIN) == HIGH) && (button_right_clicked == 1)) { // unclick
        button_right_clicked = 0;
      }
    
    }

    if ((digitalRead(BUTTON_SELECT_PIN) == LOW) && (button_select_clicked == 0)) { // select button clicked, jump between screens
     button_select_clicked = 1; // set button to clicked to only perform the action once
     current_screen = item_selected; // qr codes screen --> menu items screen
  }
  if ((digitalRead(BUTTON_SELECT_PIN) == HIGH) && (button_select_clicked == 1)) { // unclick 
    button_select_clicked = 0;
  }

  u8g2.clearBuffer();
    if(!animation && current_screen == -1) {
    //Slider
    u8g2.drawXBMP(0, 0, 128, 8, Slider_bits);
    u8g2.drawXBMP((120/(NUM_ITEMS-1))*item_selected, 0, 8, 3, SliderThing_bits);

    //Main menu
    u8g2.drawXBMP(45, 7, 38, 38, MenuMain_bits);
    u8g2.drawXBMP(48, 10, 32, 32, bitmap_icons[item_selected]);
    animateMain(item_selected);

    //Side menu
    u8g2.drawXBMP(105, 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(108, 10, 32, 32, bitmap_icons[correctShift(item_selected, 1)]);

    u8g2.drawXBMP(-15, 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(-12, 10, 32, 32, bitmap_icons[correctShift(item_selected, -1)]);

    //Text
    u8g2.setFont(u8g_font_7x14B);
    u8g2.drawStr(((126-u8g2.getStrWidth(menu_items[item_selected]))/2)+1, 60, menu_items[item_selected]);
    }
    if (current_screen == 1) {
      u8g2.clearBuffer();
      u8g2.setFont(u8g_font_7x14B);
      u8g2.drawStr(0, 10, "Value detected:");
              
        u8g2.sendBuffer();
      
    }

  u8g2.sendBuffer();

}