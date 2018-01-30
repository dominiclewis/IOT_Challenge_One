/**
 * File: main.cpp
 * Author: Dominic Lewis
 * Date: 30-01-2018
 * Desc: IOT Assignment 01
 */

#include "MicroBit.h"

MicroBit uBit;

int main(){

  uBit.init();
  uBit.display.scroll("Test");
  release_fiber(); //Release the fiber in main to return control to scheduler
}
