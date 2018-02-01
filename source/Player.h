/*
*Purpose: Contains information on the players in the game
*/
class Player
{
  public:   //Access specifier
    Player(bool user) : player_is_user(user) //Constructor
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
    /*
    *Purpose: Getter for paddle left value.
    *Accepts: N/A
    *Returns: Unsigned int that is the corresponding X axis co-ordinate for left
    *part of the paddle
    */
    unsigned int get_paddle_left()
    {
      return paddle_left;
    }
    /*
    *Purpose: Getter for paddle right value.
    *Accepts: N/A
    *Returns: Unsigned int that is the corresponding X axis co-ordinate for right
    *part of the paddle
    */
    unsigned int get_paddle_right()
    {
      return paddle_right;
    }
    /*
    *Purpose: Setter for paddle left value.
    *Accepts: unsigned int for the paddle left x axis co-orinate
    *Returns: void
    */
    void set_paddle_left(unsigned int paddle_left_cord)
    {
      paddle_left = paddle_left_cord;
    }
    /*
    *Purpose: Setter for paddle right value.
    *Accepts: unsigned int for the paddle right x axis co-orinate
    *Returns: void
    */
    void set_paddle_right(unsigned int paddle_right_cord)
    {
      paddle_right = paddle_right_cord;
    }
  private: //Private variables
    int player_score = 0;
    bool player_is_user;
    unsigned int paddle_left = 0; //Co-Ord
    unsigned int paddle_right = 1; //Co-Ord

};
