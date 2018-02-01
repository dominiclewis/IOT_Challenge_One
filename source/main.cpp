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
#define MAX_LEFT_CORD 0
#define MAX_RIGHT_CORD 4
#define LEFT_DIR 0x01
#define RIGHT_DIR 0x02

//Prototypes
void draw_user_paddle();
MicroBit uBit;//Instance of the MicroBit class
MicroBitImage screen(5,5); //Create an instance of 5x5 Led Matrix
Player player_1(true); //instantiate player
bool new_round = true;

struct movement //Stores related user movement data
{
bool trying_to_move; //Is the user trying to move
int direction; //Which direction
};

movement user_movement;

/*
*Purpose: Event handler for a button
*Returns: N/A
*/
void on_button_a(MicroBitEvent e) //Move left
{
  user_movement.trying_to_move = true;
  user_movement.direction = LEFT_DIR;
  draw_user_paddle();
}

/*
*Purpose: Event handler for b button, moves the player right
*Returns: N/A
*/
void on_button_b(MicroBitEvent e)
{
  user_movement.trying_to_move = true;
  user_movement.direction = RIGHT_DIR;
  draw_user_paddle();
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
    player_1.set_paddle_left(0);
    player_1.set_paddle_right(1);
    new_round = false;
  }
  //The user has moved
  else if ( (new_round == false) && (user_movement.trying_to_move == true))
  {

    if (user_movement.direction == LEFT_DIR )
    {


      if (player_1.get_paddle_left() != MAX_LEFT_CORD ) //Check if we're at max left
      {
        //set the right px to turn off
        screen.setPixelValue(player_1.get_paddle_right(),USER_X,0);
        //set the px on the left of the player left to on
        screen.setPixelValue((player_1.get_paddle_left() -1 ),USER_X,1);
        //Set the right value in the player class
        player_1.set_paddle_right(player_1.get_paddle_left());
        //Set the left paddle_right
        player_1.set_paddle_left(player_1.get_paddle_left() -1);


      }
    }
    else
    {
      if(player_1.get_paddle_right() != MAX_RIGHT_CORD)
        {
        //Turn off the left pixel
        screen.setPixelValue(player_1.get_paddle_left(),USER_X,0);
        //Set the px on the right of the player right to be on
        screen.setPixelValue((player_1.get_paddle_right() +1),USER_X,1);
        //Set the left value in the player class
        player_1.set_paddle_left(player_1.get_paddle_right());
        //Set the right padle right one more
        player_1.set_paddle_right(player_1.get_paddle_right() +1);
      }
    }
        user_movement.trying_to_move = false; //reset flag
  }

}
/*
*Purpose: Controls the flow of the game
*Returns: Void
*Accepts: N/A
*/
void pong()
{
  //Create individual fibers to handle actor movement
  create_fiber(draw_user_paddle);
  while(player_1.get_score() != 3) //Quit Condition
  {
    uBit.sleep(100);//Yield main fiber (let the user play the game and )
    uBit.display.image.paste(screen); //refresh the screen
  }
}
int main()
{
  uBit.init(); //initialise the scheduler memory allocator and bluetooth stack
  //Below is regisering the event handlers
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, on_button_a);
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, on_button_b);
  while(1){
    uBit.display.scroll("Pong!!!");
    pong();
}
  release_fiber();//Release the main fiber
}
