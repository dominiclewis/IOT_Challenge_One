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
#define USER_X 4
#define OPPONENT_Y 0
#define MAX_LEFT_CORD 0
#define MAX_RIGHT_CORD 4
#define LEFT_DIR 0x01
#define RIGHT_DIR 0x02
#define BALL_MOVE_LEFT 22
#define BALL_MOVE_RIGHT 23
#define BALL_MOVE_STRAIGHT 24
#define BALL_MOVE_UP 20
#define BALL_MOVE_DOWN 21
#define PADDLE_SPEED 80 //This is how long to sleep
#define BALL_FALL_SPEED 1200

//Prototypes
void draw_user_paddle();
void update_ball();
MicroBit uBit;//Instance of the MicroBit class
MicroBitImage screen(5,5); //Create an instance of 5x5 Led Matrix
Player player_1(true); //instantiate player
Player computer_player(false);//Instantiate computer program
bool new_round = true;

struct movement //Stores related user movement data
{
bool trying_to_move; //Is the user trying to move
int direction; //Which direction
};

struct ball //Stores information regarding the ball
{
  unsigned int ball_x;
  unsigned int ball_y;
  int direction[1]; // 0 = Up/Down, 1 = Right/Left/Straight
  /*
  #define BALL_MOVE_LEFT 22
  #define BALL_MOVE_RIGHT 23
  #define BALL_MOVE_UP 20
  #define BALL_MOVE_DOWN 21
  */
};

ball game_ball;
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
*Purpose: Draws the opponent paddle on the grid
*Returns: Void
*Accepts: N/A
*/
void draw_opponent_paddle()
{
  uBit.sleep(PADDLE_SPEED); //Slows down paddle
  if(new_round)
  {
  //  uBit.display.scroll("Test");
    //draw the paddle for the computer in the top right
    screen.setPixelValue(3,OPPONENT_Y,1);
    screen.setPixelValue(4,OPPONENT_Y,1);
    //Update the class co-ordinates
    computer_player.set_paddle_left(3);
    computer_player.set_paddle_right(4);
    new_round = false; //The round has been set up now

  }

}
/*
*Purpose: Draws the balll
*Returns: Void
*Accepts: N/A
*/
void draw_ball()
{
  while(1)
  {
    //uBit.sleep(100);
    if(new_round)
    {
      //Draw the ball in the middle of the screen
      screen.setPixelValue(BALL_START_X,BALL_START_Y,1);
      //Update the game ball
      game_ball.ball_x = BALL_START_X;
      game_ball.ball_y = BALL_START_Y;
      game_ball.direction[0] = BALL_MOVE_DOWN;
      game_ball.direction[1] = BALL_MOVE_STRAIGHT;
    }
    else
    {
      update_ball(); //Start the ball moving
    }

      uBit.sleep(BALL_FALL_SPEED); //Can't sleep at the start as new_round flag wont work
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
              //turn on the above pixel
              screen.setPixelValue((game_ball.ball_x), (game_ball.ball_y - 1),1 );
              //Update the ball struct
              game_ball.ball_y = game_ball.ball_y - 1;
        break;

    case (BALL_MOVE_DOWN):
            //turn off the current pixel
            screen.setPixelValue(game_ball.ball_x,game_ball.ball_y,0);
            //turn on the above pixel
            screen.setPixelValue((game_ball.ball_x ), (game_ball.ball_y + 1 ),1 );
            //Update the ball struct
            game_ball.ball_y = game_ball.ball_y + 1;

    break;
}
//Left/Right

  switch(game_ball.direction[1])
  {
    case (BALL_MOVE_RIGHT):
          //Turn off the current pixel
          screen.setPixelValue(game_ball.ball_x,game_ball.ball_y,0);
          //Turn on the pixel to the right
          screen.setPixelValue((game_ball.ball_x + 1),game_ball.ball_y,1);
          //Update the ball struct
          game_ball.ball_x = game_ball.ball_x + 1;


    case (BALL_MOVE_LEFT):
          //Turn off the current pixel
          screen.setPixelValue(game_ball.ball_x,game_ball.ball_y,0);
          //Turn on the pixel to the left
          screen.setPixelValue((game_ball.ball_x - 1),game_ball.ball_y,1);
          //Update the ball struct
          game_ball.ball_x = game_ball.ball_x - 1;





  }




}
/*
*Purpose: Draws the users paddle on the grid
*Returns: Void
*Accepts: N/A
*/
void draw_user_paddle()
{
  uBit.sleep(PADDLE_SPEED);
  if (new_round)
  {
    //Draw the paddle in the bottom left
    screen.setPixelValue(0,USER_X,1);
    screen.setPixelValue(1,USER_X,1);
    //Update the player calss with the co-ordinates
    player_1.set_paddle_left(0);
    player_1.set_paddle_right(1);
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
  create_fiber(draw_ball);
  create_fiber(draw_opponent_paddle);

  while(player_1.get_score() != 3) //Quit Condition
  {
    uBit.sleep(20);//Yield main fiber (let the user play the game and )
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
    //uBit.display.scroll("Pong!!!");
    pong();
}
  release_fiber();//Release the main fiber
}
