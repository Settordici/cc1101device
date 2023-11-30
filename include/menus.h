#include <U8g2lib.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include "RCSwitch.h"

#include "definitions.h"

#include <stdlib.h>
#include "WiFi.h"

void mainMenu() {

    // left and right buttons only work for the menu screen
    if ((digitalRead(BUTTON_LEFT_PIN) == LOW) && (button_left_clicked == 0)) { // left button clicked - jump to previous menu item
        shiftLeft(20, menu_item_selected);
        menu_item_selected = correctShift(menu_item_selected, -1, NUM_ITEMS);
      }
    else if ((digitalRead(BUTTON_RIGHT_PIN) == LOW) && (button_right_clicked == 0)) { // right button clicked - jump to next menu item
        shiftRight(20, menu_item_selected);
        menu_item_selected = correctShift(menu_item_selected, +1, NUM_ITEMS);
    } 

    if ((digitalRead(BUTTON_LEFT_PIN) == HIGH) && (button_left_clicked == 1)) { // unclick 
        button_left_clicked = 0;
    }
    if ((digitalRead(BUTTON_RIGHT_PIN) == HIGH) && (button_right_clicked == 1)) { // unclick
        button_right_clicked = 0;
    }

    if ((digitalRead(BUTTON_SELECT_PIN) == LOW) && (button_select_clicked == 0)) { // select button clicked, jump between screens
        button_select_clicked = 1; // set button to clicked to only perform the action once
        current_screen = menu_item_selected;
        switch (current_screen) {
            case 1:
                cc1101Init('R');
                break;
            case 2:
                cc1101Init('T');
                //initialized = false; //Something needs to be initialized
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
    u8g2.drawXBMP((120/(NUM_ITEMS-1))*menu_item_selected, 0, 8, 3, SliderThing_bits);

    //Main menu
    u8g2.drawXBMP(45, 7, 38, 38, MenuMain_bits);
    u8g2.drawXBMP(48, 10, 32, 32, bitmap_icons[menu_item_selected]);
    animateMain(menu_item_selected);

    //Side menu
    u8g2.drawXBMP(105, 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(108, 10, 32, 32, bitmap_icons[correctShift(menu_item_selected, 1, NUM_ITEMS)]);

    u8g2.drawXBMP(-15, 7, 38, 38, MenuSide_bits);
    u8g2.drawXBMP(-12, 10, 32, 32, bitmap_icons[correctShift(menu_item_selected, -1, NUM_ITEMS)]);

    //Text
    u8g2.setFont(u8g_font_7x14B);
    u8g2.drawStr(((126-u8g2.getStrWidth(menu_items[menu_item_selected]))/2)+1, 60, menu_items[menu_item_selected]);

    //RGB led
    nled.fill(nled.ColorHSV(65536*(menu_item_selected+1)/NUM_ITEMS, 255, LED_BRIGHTNESS));
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

void transmitCode() {
    //Parse the saved codes
    //TODO: Make this run only once
    CSV_Parser cp(/*format*/ "sfdddd");
    File file = SPIFFS.open("/codes.csv");
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
    while(file.available()){
        cp << (char)file.read();
    }
    file.close();
    cp.parseLeftover(); // needed after reading the whole file when the last line of the file doesn't end with "\n"
    char **displayNames = (char**)cp["DisplayName"];
    float *frequency = (float*)cp["Frequency"];
    int16_t *protocol = (int16_t*)cp["Protocol"];
    int16_t *value = (int16_t*)cp["Value"];
    int16_t *bit = (int16_t*)cp["Bit"];
    int16_t *pulse = (int16_t*)cp["Pulse"];
    
    u8g2.setFont(u8g_font_6x10);
    for(int i=1; i<=(cp.getRowsCount()-(send_item_selected/5)*5); i++) {
        u8g2.drawStr(1, 12*i+1, displayNames[(send_item_selected/5)*5+i-1]);
    }

    //Selection
    u8g2.setDrawColor(2);
    u8g2.drawBox(0, 4+send_item_selected%5*12, 128, 11);
    u8g2.sendBuffer();

    //Button handling
    if ((digitalRead(BUTTON_SELECT_PIN) == LOW) && (button_select_clicked == 0)) { 
        nled.fill(nled.ColorHSV(0, 255, 255));
        nled.show();
        delay(100);
        nled.fill(nled.ColorHSV(0, 0, 0));
        nled.show();

        ELECHOUSE_cc1101.setMHZ(frequency[0]);
        mySwitch.setProtocol(protocol[0]);
        mySwitch.setPulseLength(pulse[0]);
    
        //mySwitch.send(value[0], bit[0]);

        Serial.println(frequency[0]);
        Serial.println(protocol[0]);
        Serial.println(value[0]);
        Serial.println(bit[0]);
        Serial.println(pulse[0]);

        Serial.println("Code sent");

        button_select_clicked = 1; // set button to clicked to only perform the action once
    }
    if ((digitalRead(BUTTON_SELECT_PIN) == HIGH) && (button_select_clicked == 1)) { // unclick 
        button_select_clicked = 0;
    }

    if ((digitalRead(BUTTON_UP_PIN) == LOW) && (button_up_clicked == 0)) { // up button clicked - jump to previous entry
        send_item_selected = correctShift(send_item_selected, -1, cp.getRowsCount());
        delay(75);
      }
    else if ((digitalRead(BUTTON_DOWN_PIN) == LOW) && (button_down_clicked == 0)) { // up button clicked - jump to nexr entry
        send_item_selected = correctShift(send_item_selected, 1, cp.getRowsCount());
        delay(75);
    } 

    if ((digitalRead(BUTTON_UP_PIN) == HIGH) && (button_up_clicked == 1)) { // unclick 
        button_left_clicked = 0;
    }
    if ((digitalRead(BUTTON_DOWN_PIN) == HIGH) && (button_down_clicked == 1)) { // unclick
        button_right_clicked = 0;
    }
}

void wifiScan() {
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