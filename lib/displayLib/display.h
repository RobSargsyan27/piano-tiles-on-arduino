#ifndef display
#define display

#define SPACE 0xFF
#define DOT 0x7F

#include <stdint.h>

void blankSegment(uint8_t segment);
void enableDisplay();
void writeNumberToSegment(uint8_t segment, uint8_t value);
void writeNumber(int number);
void writeNumberAndWait(int number, int duration, float delay);

//Exercise 3.5.2
void writeCharToSegment(uint8_t segment, char character);
void writeString(char* str);

//Extra
void clearDisplay();
uint8_t mapLetterWithHex(char letter);
void writeAlphabet();
void writeDashToSegment(uint8_t segment, uint8_t value);
void writeDifficultyAndWait(int difficulty, int duration);
void writeDot(uint8_t segment);
void writeLevelAndWait(int duration);
void writeScoreAndWait(int score, int duration);
void writeSongAndWait(int song, int duration);
void writeStringifyNumberAndWait(char* number, int delay);
void writeStringifyNumbers(char* number);
void writeTime(int seconds);

#endif
