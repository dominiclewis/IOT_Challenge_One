/**
 * File: main.cpp
 * Author: Dominic Lewis
 * Date: 30-01-2018
 * Desc: IOT Assignment 01
 */

#include "MicroBit.h"

MicroBit uBit;

void onButtonA(MicroBitEvent e){

  uBit.display.print("World");
}

void onButtonB(MicroBitEvent e){
  uBit.display.print("Button B");
}

int main(){

  uBit.init();
  uBit.display.scroll("Hello");

  uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
  while(1){
    uBit.sleep(500);

  }
  release_fiber(); //Release the fiber in main to return control to scheduler
}
