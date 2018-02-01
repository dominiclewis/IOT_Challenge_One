/**
 * File: main.cpp
 * Author: Dominic Lewis
 * Date: 30-01-2018
 * Desc: IOT Assignment 01
 * Notes: For events to be handled I must yield control to the scheduler
 */

#include "MicroBit.h"
#include "Player.h"

#define USER_X 4

MicroBit uBit;//Instance of the MicroBit class
MicroBitImage screen(5,5); //Create an instance of 5x5 Led Matrix
Player player_1(true); //instantiate player
bool new_round = true;



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
*Purpose: Draws the users paddle on the grid
*Returns: Void
*Accepts: N/A
*/
void draw_user_paddle()
{
  if (new_round)
  {
    //Draw the paddle in the bottom left
    screen.setPixelValue(0,USER_X,1);
    screen.setPixelValue(1,USER_X,1);
    //Update the player calss with the co-ordinates
    uBit.display.image.paste(screen); //refresh the screen
    uBit.sleep(200);
    new_round = false;
  }

}
/*
*Purpose: Controls the flow of the game
*Returns: Void
*Accepts: N/A
*/
void pong()
{
  draw_user_paddle();

}
int main()
{
  uBit.init(); //initialise the scheduler memory allocator and bluetooth stack
  //Below is regisering the event handlers
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, on_button_a);
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, on_button_b);
  uBit.display.scroll("Pong!!!");
  while(1){
    pong();
}
  release_fiber();//Release the main fiber
}
