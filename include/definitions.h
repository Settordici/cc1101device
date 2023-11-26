//All global variable and constants are defined here

#pragma once

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, SCL, SDA);
RCSwitch mySwitch = RCSwitch();
Adafruit_NeoPixel nled = Adafruit_NeoPixel(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

const int NUM_ITEMS = 7; // number of items in the list and also the number of screenshots and screenshots with QR codes (other screens)
const int MAX_ITEM_LENGTH = 20; // maximum characters for the item name
const int LED_BRIGHTNESS = 255;

char menu_items [NUM_ITEMS] [MAX_ITEM_LENGTH] = {  // array with item names
  { "Frequence Analyzer" },
  { "Receive Code" }, 
  { "Transmit Code" }, 
  { "Bruteforce" }, 
  { "Sub Ghz Jammer" }, 
  { "Wifi Deauther" }, 
  { "Deep Sleep" }
 };

 const unsigned char* bitmap_icons[NUM_ITEMS] = {
  frequency,
  rx,
  tx,
  bruteforce,
  jammer,
  wifi,
  dsleep
};
// note - when changing the order of items above, make sure the other arrays referencing bitmaps
// also have the same order, for example array "bitmap_icons" for icons, and other arrays for screenshots and QR codes

#define BUTTON_LEFT_PIN 13 // pin for LEFT button 
#define BUTTON_SELECT_PIN 27 // pin for SELECT button
#define BUTTON_RIGHT_PIN 12 // pin for RIGHT button
#define BUTTON_UP_PIN 15 // pin for UP button
#define BUTTON_DOWN_PIN 33 // pin for DOWN button

#define RECEIVE_PIN 32
#define SEND_PIN 14

int animation = 0;
unsigned int counter = 1;

int button_left_clicked = 0; // only perform action when button is clicked, and wait until another press
int button_select_clicked = 0; // same as above
int button_right_clicked = 0; // same as above
int button_up_clicked = 0; // same as above
int button_down_clicked = 0; // same as above

int menu_item_selected = 0; // which item in the main menu is selected

int current_screen = -1;

char numbuffer[6];
char pbuffer[1];
char plsbuffer[4];

//bool initialized = false;