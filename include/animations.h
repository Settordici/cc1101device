//All animations functions are defined here

#include <U8g2lib.h>

#include "definitions.h"
#include "functions.h"


void shiftRight(int speed, int menu_item_selected) {

    animation = 1;

    for(int i=0; i<speed; i++) {
    u8g2.clearBuffer();

    //Slider
    u8g2.drawXBMP(0, 0, 128, 8, Slider_bits);
    u8g2.drawXBMP(((120/(NUM_ITEMS-1))*menu_item_selected)+map(i, 0, speed, 0, 120/(NUM_ITEMS-1)), 0, 8, 3, SliderThing_bits);

    //Old Main menu
    u8g2.drawXBMP(45-map(i, 0, speed, 0, 60), 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(48-map(i, 0, speed, 0, 60), 10, 32, 32, bitmap_icons[menu_item_selected]);

    //New right menu
    u8g2.drawXBMP(165-map(i, 0, speed, 0, 60), 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(168-map(i, 0, speed, 0, 60), 10, 32, 32, bitmap_icons[correctShift(menu_item_selected, 2, NUM_ITEMS)]);

    //New Main menu
    u8g2.drawXBMP(105-map(i, 0, speed, 0, 60), 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(108-map(i, 0, speed, 0, 60), 10, 32, 32, bitmap_icons[correctShift(menu_item_selected, 1, NUM_ITEMS)]);

    //Exiting left menu
    u8g2.drawXBMP(-15-map(i, 0, speed, 0, 60), 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(-12-map(i, 0, speed, 0, 60), 10, 32, 32, bitmap_icons[correctShift(menu_item_selected, -1, NUM_ITEMS)]);

    //Text
    u8g2.setFont(u8g_font_7x14);
    u8g2.drawStr(((126-u8g2.getStrWidth(menu_items[menu_item_selected]))/2)+1-map(i, 0, speed, 0, 128), 60, menu_items[menu_item_selected]);
    u8g2.drawStr(((126-u8g2.getStrWidth(menu_items[correctShift(menu_item_selected, 1, NUM_ITEMS)]))/2)+129-map(i, 0, speed, 0, 128), 60, menu_items[correctShift(menu_item_selected, 1, NUM_ITEMS)]);

    //Battery
    drawBattery();

    u8g2.sendBuffer(); // send buffer from RAM to display controller

    //RGB led
    if (menu_item_selected == NUM_ITEMS-1) nled.fill(nled.ColorHSV(map(i, 0, speed, 0, 65536*(correctShift(menu_item_selected, 1, NUM_ITEMS)+1)/NUM_ITEMS), 255, LED_BRIGHTNESS));
    else nled.fill(nled.ColorHSV(map(i, 0, speed, 65536*(menu_item_selected+1)/NUM_ITEMS, 65536*(correctShift(menu_item_selected, 1, NUM_ITEMS)+1)/NUM_ITEMS), 255, LED_BRIGHTNESS));
    nled.show();
    }
    animation = 0;
}

void shiftLeft(int speed, int menu_item_selected) {

    animation = 1;

    for(int i=0; i<speed; i++) {
    u8g2.clearBuffer();

    //Slider
    u8g2.drawXBMP(0, 0, 128, 8, Slider_bits);
    u8g2.drawXBMP(((120/(NUM_ITEMS-1))*menu_item_selected)-map(i, 0, speed, 0, 120/(NUM_ITEMS-1)), 0, 8, 3, SliderThing_bits);

    //Old Main menu
    u8g2.drawXBMP(45+map(i, 0, speed, 0, 60), 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(48+map(i, 0, speed, 0, 60), 10, 32, 32, bitmap_icons[menu_item_selected]);

    //New left menu
    u8g2.drawXBMP(-75+map(i, 0, speed, 0, 60), 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(-72+map(i, 0, speed, 0, 60), 10, 32, 32, bitmap_icons[correctShift(menu_item_selected, -2, NUM_ITEMS)]);

    //New Main menu
    u8g2.drawXBMP(-15+map(i, 0, speed, 0, 60), 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(-12+map(i, 0, speed, 0, 60), 10, 32, 32, bitmap_icons[correctShift(menu_item_selected, -1, NUM_ITEMS)]);

    //Exiting right menu
    u8g2.drawXBMP(105+map(i, 0, speed, 0, 60), 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(108+map(i, 0, speed, 0, 60), 10, 32, 32, bitmap_icons[correctShift(menu_item_selected, 1, NUM_ITEMS)]);

    //Text
    u8g2.setFont(u8g_font_7x14);
    u8g2.drawStr(((126-u8g2.getStrWidth(menu_items[menu_item_selected]))/2)+1+map(i, 0, speed, 0, 128), 60, menu_items[menu_item_selected]);
    u8g2.drawStr(((126-u8g2.getStrWidth(menu_items[correctShift(menu_item_selected, -1, NUM_ITEMS)]))/2)-127+map(i, 0, speed, 0, 128), 60, menu_items[correctShift(menu_item_selected, -1, NUM_ITEMS)]);

    //Battery
    drawBattery();

    u8g2.sendBuffer(); // send buffer from RAM to display controller

    //RGB led
    if (menu_item_selected == 0) nled.fill(nled.ColorHSV(map(i, 0, speed, 65536*(menu_item_selected+1)/NUM_ITEMS, 0), 255, LED_BRIGHTNESS));
    else nled.fill(nled.ColorHSV(map(i, 0, speed, 65536*(menu_item_selected+1)/NUM_ITEMS, 65536*(correctShift(menu_item_selected, -1, NUM_ITEMS)+1)/NUM_ITEMS), 255, LED_BRIGHTNESS));
    nled.show();
    }
    animation = 0;
}

void animateMain(int menu_item_selected) {

      switch(menu_item_selected) {
        case 0:
          u8g2.setDrawColor(0);
          u8g2.drawBox(53, 15, 22, 22);
          u8g2.setDrawColor(1);
          int randomValue[4];
          for(int i=0; i<4; i++) {
            randomValue[i] = random(1024);

          }
          u8g2.drawLine(53, 26, 59, 26+map(randomValue[0], 0, 1023, -10, 10));
          u8g2.drawLine(59, 26+map(randomValue[0], 0, 1023, -10, 10), 64, 26+map(randomValue[1], 0, 1023, -10, 10));
          u8g2.drawLine(64, 26+map(randomValue[1], 0, 1023, -10, 10), 68, 26+map(randomValue[2], 0, 1023, -10, 10));
          u8g2.drawLine(68, 26+map(randomValue[2], 0, 1023, -10, 10), 71, 26+map(randomValue[3], 0, 1023, -10, 10));
          u8g2.drawLine(71, 26+map(randomValue[3], 0, 1023, -10, 10), 74, 26);
          delay(75);
          break;
        
        case 2:
          u8g2.setDrawColor(0);
          switch(counter%75) {
            case 0 ... 14:
              break;
            case 15 ... 29:
              u8g2.drawBox(76, 10, 2, 12);
              u8g2.drawBox(72, 22, 4, 5);
              u8g2.drawBox(50, 10, 2, 12);
              u8g2.drawBox(52, 22, 4, 5);
              break;
            case 30 ... 44:
              u8g2.drawBox(72, 10, 2, 11);
              u8g2.drawBox(70, 21, 2, 2);
              u8g2.drawBox(54, 10, 2, 11);
              u8g2.drawBox(56, 21, 2, 2);
              break;
            case 45 ... 59:
              u8g2.drawBox(69, 10, 2, 9);
              u8g2.drawBox(57, 10, 2, 9);
              break;
            case 60 ... 74:
              u8g2.drawBox(62, 11, 4, 6);
              u8g2.drawBox(61, 12, 6, 4);
              break;
          }
          u8g2.setDrawColor(1);
          counter++;
          break;

        case 6:
          u8g2.setDrawColor(0);
          switch(counter%60) {
            case 45 ... 59:
              break;
            case 30 ... 44:
              u8g2.drawBox(63, 10, 15, 12);
              u8g2.drawBox(64, 22, 14, 5);
              break;
            case 15 ... 29:
              u8g2.drawBox(54, 22, 11, 10);
              u8g2.drawBox(56, 32, 9, 3);
              break;
            case 0 ... 14:
              u8g2.drawBox(48, 32, 9, 10);
              break;
          }
          u8g2.setDrawColor(1);
          u8g2.drawLine(64, 22, 64, 26);
          counter++;
          break;
        default: break;
      }
}

void turnOff() {
  u8g2.setDrawColor(0);
  switch (counter%32) {
    case 1 ... 31:
      u8g2.drawBox(0, 0, 128, counter%32);
      u8g2.drawBox(0, 63-counter%32, 128, counter%32);
      u8g2.setDrawColor(1);
      break;
  
    case 0:
      Serial.println("Going to sleep...");
      ELECHOUSE_cc1101.goSleep();
      disableInternalPower();
      //esp_sleep_enable_timer_wakeup(1000000); // 1 sec
      esp_deep_sleep_start();
      // we never reach here
      break;
  }
        
}