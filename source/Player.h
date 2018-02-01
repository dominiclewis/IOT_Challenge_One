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

  private: //Private variables
    int player_score = 0;
    bool player_is_user;
    struct paddle {
      unsigned int top = 0; //Co-Ord
      unsigned int bottom = 1; //Co-Ord
    };
};
