#ifndef ledLib
#define ledLib

#include <stdint.h>

//Exercises 11.1
void enableLed(int ledNumber);
void enableMultipleLeds(uint8_t pinsBinary);
void enableAllLeds();
void toggleLed(int ledNumber, int duration);
void turnOnLed(int ledNumber);
void turnOnMultipleLeds(uint8_t pinsBinary);
void turnOnAllLeds();
void turnOffLed(int ledNumber);
void turnOffMultipleLeds(uint8_t pinsBinary);
void turnOffAllLeds();

//Exercises 11.2
void dimLed(int ledNumber, int percentage, double duration);
void fadeIn(int ledNumber, double duration);
void fadeOut(int ledNumber, double duration);

//Exercise 11.3
void ledChaos();

//Exercise 11.4
void increaseLedBurnByPeriod(int ledNumber, int startDuration, int endDuration);
void increaseLedBurn(int ledNumber);
void toggleLedForGivenTime(int ledNumber, int times, int duration);
void turnOnLedsConsecutively(int duration);
void turnOnLedsRandomly(int duration);
void turnOnLedsByAlphabet(const char *message);
void turnOnLedsRandomlyByAlphabet(const char *message);

//Extra
int checkLedOn(int ledNumber);
int checkLedOff(int ledNumber);
void countDown(int duration);
void dimAllLeds(int percentage, double duration);
void disableLed(int ledNumber);
void disableMultipleLeds(uint8_t pinsBinary);
void disableAllLeds();
void displayScore(int score);
void fadeInAllLeds(double duration);
void fadeOutAllLeds(double duration);
void turnOnAllLedsAndWait(int duration);
void turnOffAllLedsAndWait(int duration);
#endif
