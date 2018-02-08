# Building Instructions
### Files to Download
1. _/source/_
    1. _main.cpp_ - Main application code
    1. _player.h_ - Header file containing my player class definition
2. _module.json_ - Contains instructions for yotta on how to build
3. **Optional** _.yotta.json_ - Specifies the target and that is was explicitly set

### Commands Required Initially
**Note**. Step 1 only needs top be done if _.yotta.json_ has not downloaded.
1. yt target bbc-microbit-classic-gcc
2. yt build

# Running Instructions
The executable can be found inside _/build/bbc-microbit-classic-gcc/source_,
with the executable being named _project_name-combined.hex_

Copy this file to _/media/student/MICROBIT_

# Game Instructions
## Pong
The user's Paddle is at the bottom of the LED Matrix. The opponent is opposite.
A ball will spawn in the middle of the game. The objective of the game is to get the ball past the opponent.
The opponent will try to prevent you from scoring. The ball will slowly speed up as the round progresses to add an element of difficulty.
#### Operation
The left and right buttons on the MicroBit are used to set the direction of the next user move.
#### Scoring
* 3 Point game.
* If the ball goes past the opponent's paddle then the user gets 1 point.
* If the user loses a round by the opponent hitting the ball past them then the player loses 1 point if the user's score is > 0
* After 3 points the game will output a message stating that the user has one and all of the Fibers in use will be released entering BBC Microbit into the low power sleep

#### Performance
This program makes use of Fibers, specifically three excluding the main Fiber.
I required the use of three as my game as three key elements that need to happen
quasi-simultaneously.

1. The users paddles position needs to be constantly updated depending on the button inputs which are in turn
toggled by interrupts manage by Event Handlers. These Event handlers allow me to ensure that user input is not missed and the use of the Fiber updating the players position means that it allows me to control the speed the user can move at to regulate the game.

2. The opponents paddle also needs to be updated on the screen however only at certain times does it need to be updated. In my Pong game the opponent can only moves when the ball is traveling them, as such allows the user paddle fiber to take precedent when the user would be interacting with the game the most (when the ball is traveling towards the user). Once the ball is traveling back to the opponent I control the speed at which the opponent can move on the screen the same way as I control the users movement, using uBit.sleep(DURATION);

3. The third and final Fiber is one which updates the ball on the screen. This fiber is essential as it also maintains the ball on the grid by checking for walls and paddles. Triggering scoring when required. I make use of the uBit.sleep method once again to control the speed of this fiber.

Once the win conditions of the game have been accomplished I then proceed to release_fiber all of my fibers to allow the user microbit to enter the low power sleep.
