### Library Description
The `displayLib` library contains functions for writing number/strings/chars and other characters on LED display.

---
#### Defined function

- `void blankSegment(uint8_t segment)`: Clears the LED segment of the display.
- `void enableDisplay()`: Enables the display.
- `void writeNumberToSegment(uint8_t segment, uint8_t value)`: Writes number to the segment but doesn't wait.
- `void writeNumber(int number)`: Write number to the display. Max length is 9999.
- `void writeNumberAndWait(int number, int duration, float delay)`: Writes number to the display and waits. Max length is 9999.
- `void writeCharToSegment(uint8_t segment, char character)`: Writes char to the segment but doesn't wait.
- `void writeString(char* str)`: Writes string of maximum 4 characters.
- `void clearDisplay()`: Clears display's by turning it off.
- `uint8_t mapLetterWithHex(char letter)`: Maps letter with respective hex values.
- `void writeAlphabet()`: Writes the 26 letters in a loop.
- `void writeDashToSegment(uint8_t segment, uint8_t value)`: Writes up/middle/down dashes for the given segment.
- `void writeDifficultyAndWait(int difficulty, int duration)`: Final project specific function.
- `void writeDot(uint8_t segment)`: Writes dots to the given segment. 
- `void writeLevelAndWait(int duration)`: Final project specific function.
- `void writeScoreAndWait(int score, int duration)`: Final project specific function.
- `void writeSongAndWait(int song, int duration)`: Final project specific function.
- `void writeStringifyNumberAndWait(char* number, int delay)`: Writes stringify number to LED display and waits for given time.
- `void writeStringifyNumbers(char* number)`: Writes stringify number to LED display.
- `void writeTime(int seconds)`: Writes time by given seconds.