# Building Instructions
### Files to Download
1. _/source/_ (Directory - Contains two files)
    1. _main.cpp_ - Main application code
    1. _player.h_ - Header file containing my player class definition
2. _module.json_ (Contains instructions for yotta on how to build)
3. **Optional** _.yotta.json_

### Commands Required Initially
**Note** - Only do step 1 if _.yotta.json_ is not downloaded.
1. yt target bbc-microbit-classic-gcc
2. yt build

# Running Instructions
The executable can be found inside _/build/bbc-microbit-classic-gcc/source_.
with the executable being named _project_name-combined.hex_.
Copy this file to _/media/student/MICROBIT_.

# Game Instructions
## Pong
The user's Paddle is at the bottom of the LED Matrix. The opponent is opposite.
A ball will spawn in the middle of the game. The objective of the game is to get the ball past the opponent.
The opponent will try to prevent you from scoring.
### Scoring
3 Point game. If the ball goes past the opponent's paddle then the user gets 1 point.
If the user loses a round by the opponent hitting the ball past them then the player loses 1 point if the user's score is > 0
After 3 points the game will output a message stating that the user has one and all of the Fibers in use will be released entering BBC Microbit into the low power sleep
