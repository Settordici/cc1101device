#include <U8g2lib.h>
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include "RCSwitch.h"

#include "definitions.h"

#include <stdlib.h>



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