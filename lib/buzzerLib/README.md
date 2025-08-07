### Library Description
The `buzzerLib` is responsible for functions related to buzzer. There are also predefined frequencies. 

---
#### Defined function

- `void disableBuzzer()`: Disables the buzzer, by clearing the respective DDR pin.
- `void enableBuzzer()`: Enables the buzzer, by setting the respective DDR pin.
- `void playMusic(float* notes, int size, int duration)`: Plays musing using the array of frequency for given duration.
- `void playTone(float frequency, uint32_t duration)`: Plays given frequency for given duration.
