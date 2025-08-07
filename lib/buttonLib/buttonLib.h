#ifndef buttonLib
#define buttonLib

#include <stdint.h>

// Exercises 2.7.1
void enableButton(int button);
void enableAllButtons();
int buttonPushed(int button);
uint8_t buttonsPushed();
int buttonReleased(int button);
uint8_t buttonsReleased();

#endif
