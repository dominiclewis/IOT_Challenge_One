/**
 * File: main.cpp
 * Author: Dominic Lewis
 * Date: 30-01-2018
 * Desc: IOT Assignment 01
 * Notes: For events to be handled I must yield control to the scheduler
 */

#include "MicroBit.h"
#include "Player.h"

//class Player;//Prototype
MicroBit uBit;//Instance of the MicroBit class
MicroBitImage screen(5,5); //Create an instance of 5x5 Led Matrix
Player player_1(true); //instantiate player
Player player_2(false);



/*
*Purpose: Event handler for a button
*Returns: N/A
*/

void on_button_a(MicroBitEvent e)
{
  //screen.setPixelValue(1,1,1);
}

/*
*Purpose: Event handler for b button
*Returns: N/A
*/
void on_button_b(MicroBitEvent e)
{
    //screen.setPixelValue(1,1,0);
}
/*
*Purpose: Controls the flow of the game
*Returns: Void
*Accepts: N/A
*/
void pong()
{

  uBit.display.scroll(player_1.get_score());
  player_1.adjust_score(1);

}
int main()
{
release_fiber();
  uBit.init();
  //uBit.display.scroll("Hello");
  //uBit.display.print("Button B"); I prefer printing to scrolling for readability

/*  for(int y=0; y<=5; y++)
  {
    for( int x=0; x<=5; x++)
    {
      screen.setPixelValue(x,y,1);
      uBit.sleep(500);
      uBit.display.image.paste(screen); //update the screen
      screen.setPixelValue(x,y,0);
      uBit.sleep(500);
      uBit.display.image.paste(screen); //update the screen
    }
  }
  */
  //Below is regisering the event handlers
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, on_button_a);
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, on_button_b);
  while(1){
  //  uBit.sleep(500);//Yield
    pong();
    uBit.display.image.paste(screen); //update the screen
//  release_fiber(); //Release the fiber in main to return control to scheduler
}
}
