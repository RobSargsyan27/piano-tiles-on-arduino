#include <ledLib.h>
#include <buttonLib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void setUp()
{
    enableMultipleLeds(0b111000);
    turnOffMultipleLeds(0b111000);
    enableButton(1);
    enableButton(2);

    sei();
    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PC1);
    PCMSK1 |= (1 << PC2);
}

void toggleLeds(int durationInSec, int ledNumber, int ledNumber2)
{
    turnOnLed(ledNumber);
    turnOnLed(ledNumber2);
    _delay_ms(durationInSec * 1000);
    turnOffLed(ledNumber);
    turnOffLed(ledNumber2);
    _delay_ms(durationInSec * 1000);
}

ISR(PCINT1_vect)
{
    if(buttonPushed(1))
    {
        toggleLeds(5, 2, 3);
    }

    if(buttonPushed(2))
    {
        for(int i = 0; i < 7; i++)
        {
            toggleLed(3, 500);
        }
    }
}

int main()
{
    setUp();

    while(1)
    {
        toggleLeds(2, 3, 4);
    }
}