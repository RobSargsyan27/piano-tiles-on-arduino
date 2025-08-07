#include <ledLib.h>
#include <buttonLib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <cstdint>
#include <usart.h>

volatile int ledsState[] = {0, 0, 0};
volatile int count = 0;


ISR(PCINT1_vect)
{
    const uint8_t buttonsState = buttonsPushed();

    for (int i = 1; i < 4; i++)
    {
        if (buttonsState & (1 << i))
        {
            if (ledsState[i - 1])
            {
                turnOffLed(i);
                ledsState[i - 1] = 0;
            }
            else
            {
                ledsState[i - 1] = 1;
            }
        }
    }
}

void setup()
{
    enableAllButtons();
    enableAllLeds();
}

void loop()
{
    for (int i = 0; i < 3; i++)
    {
        if (ledsState[i])
        {
            toggleLed(i + 1, 100);
        }
    }
}

int main()
{
    initUSART();

    setup();
    while (1)
    {
        loop();
    }
}
