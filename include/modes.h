#include <U8g2lib.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include "RCSwitch.h"

#include "definitions.h"

#include <stdlib.h>
#include "WiFi.h"


void receiveCode() {
    //u8g2.clearBuffer();

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