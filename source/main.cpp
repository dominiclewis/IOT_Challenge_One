/**
 * File: main.cpp
 * Author: Dominic Lewis
 * Date: 30-01-2018
 * Desc: IOT Assignment 01
 */

#include "MicroBit.h"
#define PLAYERONEID 1
#define PLAYERTWOID 2

MicroBit uBit;

/*
* Purpose: Will score player information
*/
class Player
{
  public:   //Access specifier
    Player(int score, bool user) : player_score(score), player_is_user(user)
    //Apparantly the above initialises the player classes

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
    *Accepts: An integer of eithe 1 or -1
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
}

void on_button_A(MicroBitEvent e)
{

  uBit.display.print("World");
}

void on_button_b(MicroBitEvent e)
{
  uBit.display.print("Button B");
}

int main(){

  uBit.init();
  uBit.display.scroll("Hello");

  uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, on_button_A);
  uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, on_button_B);
  while(1){
    uBit.sleep(500);

  }
  release_fiber(); //Release the fiber in main to return control to scheduler
}
