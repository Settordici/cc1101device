//All global variable and constants are defined here

#pragma once

const int NUM_ITEMS = 7; // number of items in the list and also the number of screenshots and screenshots with QR codes (other screens)
const int MAX_ITEM_LENGTH = 20; // maximum characters for the item name

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

int animation = 0;

int button_left_clicked = 0; // only perform action when button is clicked, and wait until another press
int button_select_clicked = 0; // same as above
int button_right_clicked = 0; // same as above

int item_selected = 0; // which item in the menu is selected

int current_screen = -1;