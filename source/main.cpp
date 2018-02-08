/**
 * File: main.cpp
 * Author: Dominic Lewis
 * Date: 30-01-2018
 * Desc: IOT Assignment 01
 * Notes: For events to be handled I must yield control to the scheduler
 */

#include "MicroBit.h"
#include "Player.h"

#define BALL_START_X 2
#define BALL_START_Y 2
#define USER_START_X 0 //Left Paddle
#define USER_Y 4
#define OPPONENT_Y 0
#define OPPONENT_START_X 3 //Left Paddle
#define MAX_LEFT_CORD 0
#define MAX_RIGHT_CORD 4
#define LEFT_DIR 0x01
#define RIGHT_DIR 0x02
#define BALL_MOVE_LEFT 1
#define BALL_MOVE_RIGHT 2
#define BALL_MOVE_STRAIGHT 3
#define BALL_MOVE_UP 4
#define BALL_MOVE_DOWN 5
#define PADDLE_SPEED 80 //This is how long to sleep
#define OPPONENT_PADDLE_SPEED 900
#define BALL_FALL_SPEED 1200
#define USER 0
#define CPU 1



//Prototypes
void detect_paddle();
void draw_user_paddle();
void update_ball();

MicroBit uBit;//Instance of the MicroBit class
MicroBitImage screen(5,5); //Create an instance of 5x5 Led Matrix
Player player_1(true); //instantiate player
Player computer_player(false);//Instantiate computer program
bool new_round = true;
bool restart = false;
bool finish = false;
int rally = 0;
bool reset_y = false;
int speed_increase = 0;
//int speed_increase = 0;
int scorer;

struct movement //Stores related user movement data
{
bool trying_to_move; //Is the user trying to move
int direction; //Which direction
};

struct ball //Stores information regarding the ball
{
  int ball_x;
  int ball_y;
  int direction[2]; // 0 = Up/Down, 1 = Right/Left/Straight

};

ball game_ball;
movement user_movement;
movement computer_movement;

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
*Purpose: Detects whether the ball is going to colide with a wall
*Returns: Void
*Accepts: N/A
*/
void detect_border()
{
  //Check for left wall
  int direction = -9;
 bool found = false;


    if (game_ball.direction[0] == BALL_MOVE_UP)
      {
        if (game_ball.direction[1] == BALL_MOVE_LEFT)
        {
          if(((game_ball.ball_y - 1 ) >= -1) && ((game_ball.ball_y - 1)<= 4)) //Y's which could be out of bounds
          {
            if((game_ball.ball_x - 1) < MAX_LEFT_CORD )
            {
              //Reflect as out of bounds
              //game_ball.direction[1] = BALL_MOVE_RIGHT;
              direction = BALL_MOVE_RIGHT;
              found = true;

            }
          }
          //if next light is +1 on middle three x
        }
        else if(game_ball.direction[1] == BALL_MOVE_RIGHT)
        {
          if(((game_ball.ball_y - 1 ) >= -1) && ((game_ball.ball_y - 1)<= 4)) //Y's which could be out of bounds
          {
              if((game_ball.ball_x + 1) > MAX_RIGHT_CORD )
              {

                //game_ball.direction[1] = BALL_MOVE_LEFT;
                direction = BALL_MOVE_LEFT;
                found = true;
              }
          }
        }
      }
      else if (game_ball.direction[0] == BALL_MOVE_DOWN)//Going down
      {

        if (game_ball.direction[1] == BALL_MOVE_LEFT)
        {
            if(((game_ball.ball_y + 1 ) >= 0) && ((game_ball.ball_y + 1)<= 5)) //Y's which could be out of bounds
          {
            if((game_ball.ball_x - 1) < MAX_LEFT_CORD )
            {
              //Reflect as out of bounds
              //game_ball.direction[1] = BALL_MOVE_RIGHT;
              direction = BALL_MOVE_RIGHT;

              found = true;
            }
          }
          //if next light is +1 on middle three x
        }
        else if(game_ball.direction[1] == BALL_MOVE_RIGHT)
        {
              if(((game_ball.ball_y + 1 ) >= 0) && ((game_ball.ball_y + 1)<= 5)) //Y's which could be out of bounds
          {
              if((game_ball.ball_x + 1) > MAX_RIGHT_CORD)
              {
                direction = BALL_MOVE_LEFT;
                found = true;

              }
          }
        }
      }
      if (found)
      {
        game_ball.direction[1] = direction;
      }
      else
      {
        //Check for score
        if (game_ball.direction[0] == BALL_MOVE_UP)
        {
          if ((game_ball.ball_y) < OPPONENT_Y )
          {
            //player scored
            scorer = USER;
            restart = true;
          }

        }
        else if (game_ball.direction[0] == BALL_MOVE_DOWN)
        {
          //CPU Scored
          if((game_ball.ball_y) > USER_Y)
          {
           scorer = CPU;
           restart = true;
           }
        }
      }

    }



/*
*Purpose: Detects whether the ball is going to colide with a paddle
*Returns: Void
*Accepts: N/A
*/
void detect_paddle()
{
  //If the next LED is a paddle then the direction needs to change
  switch(game_ball.direction[0])
  {
    case (BALL_MOVE_DOWN):
    //Check if moving in a certain direction
      if(game_ball.direction[1] != BALL_MOVE_STRAIGHT)
      {
        if (game_ball.direction[1] == BALL_MOVE_LEFT)
        {
          //CHECK LEFT DOWNtrying_to_move
          if (((game_ball.ball_y + 1) == USER_Y ) &&
          (game_ball.ball_x - 1 ) == player_1.get_paddle_left())
          {
            //Reflect Left
            game_ball.direction[0] = BALL_MOVE_UP;
            game_ball.direction[1] = BALL_MOVE_LEFT;

          }
          else if (((game_ball.ball_y + 1) == USER_Y ) &&
              (game_ball.ball_x - 1 ) == player_1.get_paddle_right())
              {
                //Reflect right
                game_ball.direction[0] = BALL_MOVE_UP;
                game_ball.direction[1] = BALL_MOVE_RIGHT;

              }

        }
        else
        {
          // It's going right
          //CHECK right DOWN
          if (((game_ball.ball_y + 1) == USER_Y ) &&
          (game_ball.ball_x + 1 ) == player_1.get_paddle_left())
          {
            //Reflect Left
            game_ball.direction[0] = BALL_MOVE_UP;
            game_ball.direction[1] = BALL_MOVE_LEFT;

          }
          else if (((game_ball.ball_y + 1) == USER_Y ) &&
              (game_ball.ball_x + 1 ) == player_1.get_paddle_right())
              {
                //Reflect right
                game_ball.direction[0] = BALL_MOVE_UP;
                game_ball.direction[1] = BALL_MOVE_RIGHT;

              }
        }
      }
      else
      {
        // just check with the [0]
        if (((game_ball.ball_y + 1) == USER_Y) && (game_ball.ball_x == player_1.get_paddle_left()))
        {
          game_ball.direction[0] = BALL_MOVE_UP;
          game_ball.direction[1] = BALL_MOVE_LEFT;

        }
        else if (((game_ball.ball_y + 1) == USER_Y) && (game_ball.ball_x == player_1.get_paddle_right()))
          //REFLECT RIGHT
          {
          game_ball.direction[0] = BALL_MOVE_UP;
          game_ball.direction[1] = BALL_MOVE_RIGHT;

        }
      }
    break;
    case (BALL_MOVE_UP):
    //Check if moving in a certain direction
      if(game_ball.direction[1] != BALL_MOVE_STRAIGHT)
      {
        if (game_ball.direction[1] == BALL_MOVE_LEFT)
        {
          //CHECK LEFT UP
          if (((game_ball.ball_y - 1) == OPPONENT_Y ) &&
          (game_ball.ball_x - 1 ) == computer_player.get_paddle_left())
          {
            //Reflect Left
            game_ball.direction[0] = BALL_MOVE_DOWN;
            game_ball.direction[1] = BALL_MOVE_LEFT;


          }
          else if (((game_ball.ball_y - 1) == OPPONENT_Y ) &&
              (game_ball.ball_x - 1 ) == computer_player.get_paddle_right())
              {
                //Reflect right
                game_ball.direction[0] = BALL_MOVE_DOWN;
                game_ball.direction[1] = BALL_MOVE_RIGHT;

              }

        }
        else
        {
          // It's going right
          //CHECK right UP
          if (((game_ball.ball_y - 1) == OPPONENT_Y ) &&
          (game_ball.ball_x + 1 ) == computer_player.get_paddle_left())
          {
            //Reflect Left
            game_ball.direction[0] = BALL_MOVE_DOWN;
            game_ball.direction[1] = BALL_MOVE_LEFT;

          }
          else if (((game_ball.ball_y - 1) == OPPONENT_Y ) &&
              (game_ball.ball_x + 1 ) == computer_player.get_paddle_right())
              {
                //Reflect right
                game_ball.direction[0] = BALL_MOVE_DOWN;
                game_ball.direction[1] = BALL_MOVE_RIGHT;
                  //THIS ONE
              }
        }
      }
      else
      {
        // just check with the [0]
        if (((game_ball.ball_y - 1) == OPPONENT_Y) && (game_ball.ball_x == computer_player.get_paddle_left()))
        {
          game_ball.direction[0] = BALL_MOVE_DOWN;
          game_ball.direction[1] = BALL_MOVE_LEFT;

        }
        else if (((game_ball.ball_y - 1) == OPPONENT_Y) && (game_ball.ball_x == computer_player.get_paddle_right()))
          //REFLECT RIGHT
          {
          game_ball.direction[0] = BALL_MOVE_DOWN;
          game_ball.direction[1] = BALL_MOVE_RIGHT;

        }
      }
    break;

  }

}

/*
*Purpose: Draws the opponent paddle on the grid
*Returns: Void
*Accepts: N/A
*/
void draw_opponent_paddle()
{
  if (finish)
  {

    release_fiber();
  }
  while(1)
  {

    if(new_round)
    {
      //draw the paddle for the computer in the top right
      screen.setPixelValue(OPPONENT_START_X,OPPONENT_Y,1);
      screen.setPixelValue(OPPONENT_START_X + 1 ,OPPONENT_Y,1);
      //Update the class co-ordinates
      computer_player.set_paddle_left(OPPONENT_START_X);
      computer_player.set_paddle_right(OPPONENT_START_X + 1);


    }
    else if (new_round == false)
    {
      //Check if the ball is coming towards the computer
      if (game_ball.direction[0] == BALL_MOVE_UP)
      {
        computer_movement.trying_to_move = true;
        if ((game_ball.ball_x ) < computer_player.get_paddle_left())
        {
          //go left
          computer_movement.direction = LEFT_DIR;
        }
        else if((game_ball.ball_x ) > computer_player.get_paddle_right())
        {
          //go right
          computer_movement.direction = RIGHT_DIR;
        }
      }
      if (computer_movement.trying_to_move)
        {
        if (computer_movement.direction == LEFT_DIR )
        {
          if (computer_player.get_paddle_left() != MAX_LEFT_CORD ) //Check if we're at max left
          {
            //set the right px to turn off
            screen.setPixelValue(computer_player.get_paddle_right(),OPPONENT_Y,0);
            //set the px on the left of the player left to onUSER_X
            screen.setPixelValue((computer_player.get_paddle_left() -1 ),OPPONENT_Y,1);
            //Set the right value in the player class
            computer_player.set_paddle_right(computer_player.get_paddle_left());
            //Set the left paddle_right
            computer_player.set_paddle_left(computer_player.get_paddle_left() -1);
          }
        }
        else
        {
          if(computer_player.get_paddle_right() != MAX_RIGHT_CORD)
            {
            //Turn off the left pixel
            screen.setPixelValue(computer_player.get_paddle_left(),OPPONENT_Y,0);
            //Set the px on the right of the player right to be on
            screen.setPixelValue((computer_player.get_paddle_right() +1),OPPONENT_Y,1);
            //Set the left value in the player class
            computer_player.set_paddle_left(computer_player.get_paddle_right());
            //Set the right padle right one more
            computer_player.set_paddle_right(computer_player.get_paddle_right() +1);
          }
        }
            computer_movement.trying_to_move = false; //reset flag
      }
    }
    uBit.sleep(OPPONENT_PADDLE_SPEED);//Slow down paddle
  }
}
/*
*Purpose: Draws the balll
*Returns: Void
*Accepts: N/A
*/
void draw_ball()
{
   speed_increase = 0;

  if (finish)
  {
    release_fiber();
  }
  bool skip = false;
  while(1)
  {
    if((new_round) && (skip == false))
    {
      rally = 0;
      //Draw the ball in the middle of the screen
      screen.setPixelValue(BALL_START_X,BALL_START_Y,1);
      //Update the game ball
      speed_increase = 0;
      game_ball.ball_x = BALL_START_X;
      game_ball.ball_y = BALL_START_Y;
      game_ball.direction[0] = BALL_MOVE_DOWN;
      game_ball.direction[1] = BALL_MOVE_STRAIGHT;
      skip = true;//Do not re-initiliase the ball
      if ((new_round) && (restart))
      {
        return;
      }

    }
    else
    {
      if (rally!= 0) //don't divide by 0 (This increases the ball speed over time)
      {
        if (rally % 2 == 0)
        {
          //every 2
          if(rally * 20 < (BALL_FALL_SPEED - 100) )//Don't fall too fast
          {
          speed_increase = rally * 37;
          }
        }
      }
      else{
        speed_increase = 0;
      }
     new_round = false;

     detect_border();

     detect_paddle();

     detect_border();

     update_ball(); //Move the ball

    }

      uBit.sleep(BALL_FALL_SPEED - speed_increase ); //Can't sleep at the start as new_round flag wont work
    }
}
/*
*Purpose: tells the ball where the next pixel it should update is
*Returns: Void
*Accepts: N/A
*/
void update_ball()
{
  //Up/Down?
  switch(game_ball.direction[0])
  {
    case (BALL_MOVE_UP):
              //turn off the current pixel
              screen.setPixelValue(game_ball.ball_x,game_ball.ball_y,0);
              game_ball.ball_y = game_ball.ball_y - 1;
        break;

    case (BALL_MOVE_DOWN):
            //turn off the current pixel
            screen.setPixelValue(game_ball.ball_x,game_ball.ball_y,0);
            //turn on the below pixel
            game_ball.ball_y = game_ball.ball_y + 1;
            rally = rally + 1; //game has either started or has been returned
    break;
}
//Left/Right

  switch(game_ball.direction[1])
  {

    case(BALL_MOVE_STRAIGHT):
        if (game_ball.direction[0] == BALL_MOVE_DOWN)
        {
          //Turn on below pixel
        screen.setPixelValue((game_ball.ball_x ), (game_ball.ball_y ),1 );

        }
        else if (game_ball.direction[0] == BALL_MOVE_UP)
        {
          //Turn on Above Pixel
          screen.setPixelValue((game_ball.ball_x ), (game_ball.ball_y ),1 );

        }
          break;
    case (BALL_MOVE_RIGHT):
          //Turn off the current pixel

          //Update the ball struct
          game_ball.ball_x = game_ball.ball_x + 1;
          //Turn on the pixel to the right
          screen.setPixelValue((game_ball.ball_x),game_ball.ball_y,1);

          break;


    case (BALL_MOVE_LEFT):
          //Update the ball struct
          game_ball.ball_x = game_ball.ball_x - 1;
          //Turn on the pixel to the left
          screen.setPixelValue((game_ball.ball_x ),game_ball.ball_y,1);
          break;

  }

}
/*
*Purpose: Draws the users paddle on the grid
*Returns: Void
*Accepts: N/A
*/
void draw_user_paddle()
{

  if (finish)
  {
    release_fiber();
  }
  uBit.sleep(PADDLE_SPEED);
  if (new_round)
  {
    //Draw the paddle in the bottom left
    screen.setPixelValue(USER_START_X,USER_Y,1);
    screen.setPixelValue(1,USER_Y,1);
    //Update the player calss with the co-ordinates
    player_1.set_paddle_left(USER_START_X);
    player_1.set_paddle_right(USER_START_X + 1);
    //new_round = false; //

  }
  //The user has moved
  else if ( (new_round == false) && (user_movement.trying_to_move == true))
  {

    if (user_movement.direction == LEFT_DIR )
    {


      if (player_1.get_paddle_left() != MAX_LEFT_CORD ) //Check if we're at max left
      {
        //set the right px to turn off
        screen.setPixelValue(player_1.get_paddle_right(),USER_Y,0);
        //set the px on the left of the player left to onUSER_X
        screen.setPixelValue((player_1.get_paddle_left() -1 ),USER_Y,1);
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
        screen.setPixelValue(player_1.get_paddle_left(),USER_Y,0);
        //Set the px on the right of the player right to be on
        screen.setPixelValue((player_1.get_paddle_right() +1),USER_Y,1);
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
*Purpose: Resets the game state
*Returns: Void
*Accepts: N/A
*/
void reset()
{   //Clear all the pixel

    screen.clear();
    user_movement.trying_to_move = false;
    computer_movement.trying_to_move = false;

    //Draw the paddle in the bottom left
    screen.setPixelValue(USER_START_X,USER_Y,1);
    screen.setPixelValue(1,USER_Y,1);
    //Update the player calss with the co-ordinates
    player_1.set_paddle_left(USER_START_X);
    player_1.set_paddle_right(USER_START_X + 1);

    //opponent      //draw the paddle for the computer in the top right
          screen.setPixelValue(OPPONENT_START_X,OPPONENT_Y,1);
          screen.setPixelValue(OPPONENT_START_X + 1 ,OPPONENT_Y,1);
          //Update the class co-ordinates
          computer_player.set_paddle_left(OPPONENT_START_X);
          computer_player.set_paddle_right(OPPONENT_START_X + 1);
          //Ball
          rally = 0;
          //Draw the ball in the middle of the screen
          screen.setPixelValue(BALL_START_X,BALL_START_Y,1);
          //Update the game ball
          speed_increase = 0;
          game_ball.ball_x = BALL_START_X;
          game_ball.ball_y = BALL_START_Y;
          game_ball.direction[0] = BALL_MOVE_DOWN;
          game_ball.direction[1] = BALL_MOVE_STRAIGHT;
    restart = false;
    new_round = false;

}
/*
*Purpose: Handles the score of the game
*Returns: Void
*Accepts: N/A
*/

void update_score()
{
  switch(scorer)
  {
    case (USER):
    player_1.adjust_score(1);
    scorer = 99;
      break;
    case (CPU):
    if (player_1.get_score() > 0)
    {
    player_1.adjust_score(-1);
    }
    scorer = 99;
      break;

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
  create_fiber(draw_opponent_paddle);
  create_fiber(draw_ball);



  while(1) //Quit Condition
  {
    if (reset_y)
    {
      reset_y = false;
      game_ball.ball_y = BALL_START_Y - 1;
    }
    uBit.display.image.paste(screen); //refresh the screen
    uBit.sleep(100);//Yield main fiber (let the user play the game and )

    if (restart)
    {
      screen.clear();
      uBit.display.image.paste(screen);
      update_score();
      uBit.display.scroll("Score");
      uBit.display.scroll(player_1.get_score());
      if (player_1.get_score() == 3)
      {
        uBit.display.scroll("Winner!!!");
        finish = true;
        release_fiber();

      }
        reset();
        reset_y = true;
    }

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
