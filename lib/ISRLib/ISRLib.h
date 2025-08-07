#ifndef ISRLib
#define ISRLib

#include <stdint.h>

void enablePinISR(char port, int button);
void enableMultiplePinsISR(char port, uint8_t pinsBinary);

#endif