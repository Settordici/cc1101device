//All utility functions are defined here

#pragma once

int correctShift (int item_selected, int shift, int max) {
  // set correct values for the previous and next items
  int out = item_selected + shift;
  if (out < 0) {out = max + shift + item_selected;} // previous item would be below first = make it the last
  if (out > max) {out = 0 + (shift - 1);}
  if (out == max) {out = 0;} // next item would be after last = make it the first
  return out;
}

void disableInternalPower() {
  #if defined(NEOPIXEL_POWER)
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, LOW);
  #endif
  #if defined(NEOPIXEL_I2C_POWER)
  pinMode(NEOPIXEL_I2C_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_I2C_POWER, LOW);
  #endif
}

void cc1101Init(char mode) { //TODO: Handle both recepting and transmitting
  ELECHOUSE_cc1101.setSpiPin(SCK, 21, 19, 4);
  ELECHOUSE_cc1101.Init();            // must be set to initialize the cc1101!
  //ELECHOUSE_cc1101.setRxBW(812.50);  // Set the Receive Bandwidth in kHz. Value from 58.03 to 812.50. Default is 812.50 kHz.
  //ELECHOUSE_cc1101.setPA(10);       // set TxPower. The following settings are possible depending on the frequency band.  (-30  -20  -15  -10  -6    0    5    7    10   11   12)   Default is max!
  ELECHOUSE_cc1101.setMHZ(433.92); // Here you can set your basic frequency. The lib calculates the frequency automatically (default = 433.92).The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
  if (mode == 'R') {
    mySwitch.enableReceive(RECEIVE_PIN);  // Receiver on
    ELECHOUSE_cc1101.SetRx();  // set Receive on
  }
  else if (mode == 'T') {
    mySwitch.enableTransmit(SEND_PIN);
    ELECHOUSE_cc1101.SetTx();
  }
  
  if (ELECHOUSE_cc1101.getCC1101()){       // Check the CC1101 Spi connection.
  Serial.println("Connection OK");
  }else{
  Serial.println("Connection Error");
  }
}

void listAllFiles(){
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
 
  while(file){
      Serial.print("FILE: ");
      Serial.println(file.name());
      file = root.openNextFile();
  }

  Serial.print("Used: ");
  Serial.print(SPIFFS.usedBytes());
  Serial.print(" of: ");
  Serial.println(SPIFFS.totalBytes());
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("- message appended");
    } else {
        Serial.println("- append failed");
    }
    file.close();
}