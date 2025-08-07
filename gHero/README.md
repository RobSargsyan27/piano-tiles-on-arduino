## Guitar Hero

This is a package where you can find the source code for the final project which is Nintendo "Guitar Hero" game.
Various libraries' functions are used from `./lib` package to implement the logic of the game. 

-----
#### Main Features
 
- You can specify your username, which will be saved in case you had top 3 scores.
- You can define the starting level using Potentiometer and ADC. `./ADC.lib` library is the once responsible for enabling ADC and auto sampling. PC0 is the default pins which is listens to  for input analog signal.
- You can choose one of the 7 songs you want to play. The songs have different notes and different length of notes. 
- You can choose the difficulty level `Easy/Medium/Hardcore`. The difficulty level effects the speed by which the notes "fall down".
- LEDs identify how much it is left to level up.
- After the end of the game see on Serial Monitor the top 3 players' username and record score.

#### Core Logic Of The Game
The core logic is written in `Timer1` which updates the falling notes, by setting their corresponding variables either 0 or 1. As well as randomly selects 
segment of the LED display for the next note. `SxU`, `SxM`, `SxD` are responsible for passing the light state value for segment `x` and dash `U/M/D`. 
The `updateDisplay()` function uses these values to turn on/off the corresponding up, middle or down dashes for given `x` segment.
The `SxUF`, `SxMF`, `SxDF` are responsible for passing the frequency associated which each note of the segment X and dash `U/M/D`.
These variables are used by `triggerBuzzer()` function to play the frequency is the button is pushed on time. 
The `Bx` is variable for indicating if the given button `x` is pushed on time or not.
The 'displayScore(int currentScore)' function is used to turn on/off the below 4 LEDs according to the current score. 

The speed/difficulty of the game is being configured by altering `OCR1A` value, which is the top border, reaching which the display will be updated and 
dashes will "fall down". After each level up, this value is getting smaller according to the chosen configuration.
The potentiometer sets the initial value for `OCR1A`.

The main goal was to use the Timer to update the LED display but at the same time keeps the operations executed in ISR simple.

Other functions and variables are pretty straight forward by just looking at it.

### Libraries
In libraries additional functions are defined in order to abstract most of the code as well as make it more reusable. The 
additional functionality can be found under `//Extra` comment in libraries header filer.  