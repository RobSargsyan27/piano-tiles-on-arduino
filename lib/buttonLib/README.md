### Library Description
The `buttonLib` is responsible for enabling button(s) as well as for checking their value at any given time.


---
#### Defined function

- `void enableButton(int button)`: Enables the button, sets the pull-up resistor as well the `ISR` for the buttons port and pin.
- `void enableAllButtons()`: Enables all buttons, sets the pull-up resistor as well the `ISR` for the buttons port and pin.
- `int buttonPushed(int button)`: Checks if the given button pushed.
- `uint8_t buttonsPushed()`: Checks if the given buttons pushed.
- `int buttonReleased(int button)`: Checks if the given button released. 
- `uint8_t buttonsReleased()`: Checks if the given buttons released.