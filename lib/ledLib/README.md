### Library Description
The `ledLib` library contains functions to enable and control LEDs in various manners.

---
#### Defined function

 - `void enableLed(int ledNumber)`: Enables given led by setting DDR. Internally turns off all leds.
 - `void enableMultipleLeds(uint8_t pinsBinary)`: Enables multiple LEDs by setting DDR.
 - `void enableAllLeds()`: Enables all LEDs by setting DDR.
 - `void toggleLed(int ledNumber, int duration)`: Turn given led on and off one time.
 - `void turnOnLed(int ledNumber)`: Turns on given led.
 - `void turnOnMultipleLeds(uint8_t pinsBinary)`: Turns on multiple LEDs.
 - `void turnOnAllLeds()`: Turns on all LEDs.
 - `void turnOffLed(int ledNumber)`: Turns off given led. 
 - `void turnOffMultipleLeds(uint8_t pinsBinary)`: Turns off multiple LEDs.
 - `void turnOffAllLeds()`: Turns off all LEDs.

 - `void dimLed(int ledNumber, int percentage, double duration)`:  Dims given led for given percentage for given time.
 - `void fadeIn(int ledNumber, double duration)`: Fades in the given led for given duration.
 - `void fadeOut(int ledNumber, double duration)`: Fades out the given led for given duration.
 - `void ledChaos()`: Turns on/off randomly random LEDs.
 - `void increaseLedBurnByPeriod(int ledNumber, int startDuration, int endDuration)`: Constantly makes the given LED brighter.
 - `void increaseLedBurn(int ledNumber)`: Increase led burn for given led.
 - `void toggleLedForGivenTime(int ledNumber, int times, int duration)`: Turn given led on and off contentiously by given duration.
 - `void turnOnLedsConsecutively(int duration)`:Turns on LEDs consecutively one by one for given time.
 - `void turnOnLedsRandomly(int duration)`: Turns on LEDs randomly for given time.
 - `void turnOnLedsByAlphabet(const char *message)`: Morse Trainer specific function.
 - `void turnOnLedsRandomlyByAlphabet(const char *message)`: Morse Trainer specific function.
 - `int checkLedOn(int ledNumber)`: Check if the LED on.
 - `int checkLedOff(int ledNumber)`: Checks if the LED off.
 - `void countDown(int duration)`: Counts down the LEDs. Reverse of `void turnOnLedsConsecutively(int duration)`.
 - `void dimAllLeds(int percentage, double duration)`: Dims all LEDs for given percentage for given time. 
 - `void disableLed(int ledNumber)`: Disable given LED.
 - `void disableMultipleLeds(uint8_t pinsBinary)`: Disable multiple given LEDs.
 - `void disableAllLeds()`: Disable all LEDs.
 - `void displayScore(int score)`: Final project specific function.
 - `void fadeInAllLeds(double duration)`: Fades in all LEDs for given duration.
 - `void fadeOutAllLeds(double duration)`: Fades out all LEDs for given duration.
 - `void turnOnAllLedsAndWait(int duration)`: Turns on all LEDs and waits for given time.
 - `void turnOffAllLedsAndWait(int duration)`: Turns off all LEDs and waits for given time.