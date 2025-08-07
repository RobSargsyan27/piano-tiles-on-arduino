#ifndef buzzerLib
#define buzzerLib

#include <stdint.h>

//FREQUENCIES OF THE NOTES
#define C5 523.250
#define D5 587.330
#define E5 659.250
#define F5 698.460
#define G5 783.990
#define A5 880.00
#define B5 987.770
#define C6 1046.500


void disableBuzzer();
void enableBuzzer();
void playMusic(float* notes, int size, int duration);
void playTone(float frequency, uint32_t duration);

#endif
