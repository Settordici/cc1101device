//All utility functions are defined here

#pragma once

int correctShift (int item_selected, int shift) {
  // set correct values for the previous and next items
  int out = item_selected + shift;
  if (out < 0) {out = NUM_ITEMS - 1;} // previous item would be below first = make it the last
  if (out >= NUM_ITEMS) {out = 0;} // next item would be after last = make it the first
  return out;
}