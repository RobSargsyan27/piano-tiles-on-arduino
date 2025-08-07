#include <avr/io.h>
#include <avr/interrupt.h>
#include <usart.h>
#include <ledLib.h>
#include <util/delay.h>
#include <buttonLib.h>

void setup()
{
    //Configure ISR
    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PC1);
    sei();

    //Enable button
    enableButton(1);

    //Enable led
    enableLed(1);
    turnOffLed(1);
}

ISR(PCINT1_vect)
{
    if(buttonPushed(1))
    {
        _delay_us(1000);
        if(buttonPushed(1))
        {
            if(PINB & (1 << PB2))
            {
                turnOnLed(1);
            }else
            {
                turnOffLed(1);
            }
        }
    }
}

int main()
{
    enableLed(1);
    turnOffLed(1);
    while (1)
    {
        turnOnLed(1);
    }
}