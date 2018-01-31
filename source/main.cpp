/**
 * File: main.cpp
 * Author: Dominic Lewis
 * Date: 30-01-2018
 * Desc: IOT Assignment 01
 * Notes: For events to be handled I must yield control to the scheduler
 */

#include "MicroBit.h"
#define PLAYERONEID 1
#define PLAYERTWOID 2

MicroBit uBit;//Instance of the MicroBit class
//MicroBitDisplay display; //Create an instance of 5x5 Led Matrix
MicroBitImage screen(5,5);

/*
*Purpose: Contains information on the players in the game
*/
class Player
{
  public:   //Access specifier
    Player(int score, bool user) : player_score(score), player_is_user(user) //Constructor
    {}
    //Apparantly the above initialises the player classes without assignments

    /*
    * Purpose: This method will return the players score
    * Accepts: N/A
    * Returns: Integer containing players score
    */
    int get_score()
    {
        return player_score;
    }

    /*
    *Purpose: Returns whether or not a player is a user or computer controlled
    *Accepts: N/A
    *Returns: Boolean. True if user controlled player, false if otherwise.
    */
    bool get_player_is_user()
    {
      return player_is_user;
    }
    /*
    *Purpose: Adjusts the score by either incrementing or decrementing by 1.
    *Accepts: An integer of either 1 or -1
    *Returns: Boolean - True if an adjustment is carried out, false if otherwise
    */
    bool adjust_score(int adjustment)
    {
      if ((adjustment == 1) || (adjustment == -1))
      {
        player_score += adjustment;
        return true;
      }
      else
      {
        return false;
      }

    }

  private: //Private variables
    int player_score;
    bool player_is_user;
    struct paddle {
      unsigned int top = 0;
      unsigned int bottom = 0;
    };
};

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

}
int main()
{

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
    //uBit.sleep(500);//Yield
    pong();
    uBit.display.image.paste(screen); //update the screen
  release_fiber(); //Release the fiber in main to return control to scheduler
}
}
