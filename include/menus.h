#include <U8g2lib.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include "RCSwitch.h"

#include "definitions.h"

#include <stdlib.h>
#include "WiFi.h"

void mainMenu() {

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

    if ((digitalRead(BUTTON_SELECT_PIN) == LOW) && (button_select_clicked == 0)) { // select button clicked, jump between screens
        button_select_clicked = 1; // set button to clicked to only perform the action once
        current_screen = item_selected;
        switch (current_screen) {
            case 1:
                cc1101Init();
                break;
            case NUM_ITEMS-1:
                counter = 1;
                break;
        }
    }
    if ((digitalRead(BUTTON_SELECT_PIN) == HIGH) && (button_select_clicked == 1)) { // unclick 
        button_select_clicked = 0;
    }

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

    //RGB led
    nled.fill(nled.ColorHSV(65536*(item_selected+1)/NUM_ITEMS, 255, LED_BRIGHTNESS));
    nled.show();
}


void receiveCode() {

    u8g2.setFont(u8g_font_7x14B);
    u8g2.drawStr(0, 15, "Protocol: ");
    u8g2.drawStr(70, 15, pbuffer);
    u8g2.drawStr(0, 30, "Value: ");
    u8g2.drawStr(45, 30, numbuffer);
    u8g2.drawStr(0, 45, "Pulse: ");
    u8g2.drawStr(45, 45, plsbuffer);
    u8g2.sendBuffer();
    
    if (mySwitch.available()) {
    

      

      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      ultoa(mySwitch.getReceivedValue(), numbuffer, 10);
      u8g2.drawStr(45, 30, numbuffer);
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
      ultoa(mySwitch.getReceivedProtocol(), pbuffer, 10);
      u8g2.drawStr(70, 15, pbuffer);
      ultoa(mySwitch.getReceivedDelay(), plsbuffer, 10);
      u8g2.drawStr(45, 45, plsbuffer);
      
    }

    mySwitch.resetAvailable();
    
}

void wifiScan() {
  
}

void deepSleep() {
    mainMenu();
    turnOff();
}
/*
WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    Serial.println("Wifi setup done");

    int n = WiFi.scanNetworks();
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.printf("%2d",i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4ld", WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2ld", WiFi.channel(i));
            Serial.print(" | ");
            switch (WiFi.encryptionType(i))
            {
            case WIFI_AUTH_OPEN:
                Serial.print("open");
                break;
            case WIFI_AUTH_WEP:
                Serial.print("WEP");
                break;
            case WIFI_AUTH_WPA_PSK:
                Serial.print("WPA");
                break;
            case WIFI_AUTH_WPA2_PSK:
                Serial.print("WPA2");
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                Serial.print("WPA+WPA2");
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE:
                Serial.print("WPA2-EAP");
                break;
            case WIFI_AUTH_WPA3_PSK:
                Serial.print("WPA3");
                break;
            case WIFI_AUTH_WPA2_WPA3_PSK:
                Serial.print("WPA2+WPA3");
                break;
            case WIFI_AUTH_WAPI_PSK:
                Serial.print("WAPI");
                break;
            default:
                Serial.print("unknown");
            }
            Serial.println();
            delay(10);
        }
    }
    Serial.println("");

    // Delete the scan result to free memory for code below.
    WiFi.scanDelete();
*/