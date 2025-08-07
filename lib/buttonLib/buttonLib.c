#include <buttonLib.h>
#include <ISRLib.h>
#include <avr/io.h>
#include <util/delay.h>

#define BUTTONS_DDR DDRC
#define BUTTONS_PINS PINC
#define BUTTONS_PORT PORTC

void enableButton(int button)
{
    BUTTONS_DDR &= ~(1 << button);
    BUTTONS_PORT |= (1 << button);
    enablePinISR('C', button);
}

void enableAllButtons()
{
    BUTTONS_DDR &= ~(7 << 1);
    BUTTONS_PORT |= (7 << 1);
    enableMultiplePinsISR('C', (7 << 1));
}

int buttonPushed(int button)
{
     if(!(BUTTONS_PINS & (1 << button)))
     {
         _delay_us(1000);
         if(!(BUTTONS_PINS & (1 << button)))
         {
             return 1;
         }
         return 0;
     }
    return 0;
}

uint8_t buttonsPushed()
{
    if(BUTTONS_PINS ^ (7 << 1))
    {
        _delay_us(1000);
        if(BUTTONS_PINS ^ (7 << 1))
        {
            return BUTTONS_PINS ^ (7 << 1);
        }
        return 0;
    }
    return 0;
}

int buttonReleased(int button)
{
    if(BUTTONS_PINS & (1 << button))
    {
        _delay_us(1000);
        if(BUTTONS_PINS & (1 << button))
        {
            return 1;
        }
        return 0;
    }
    return 0;
}

uint8_t buttonsReleased()
{
    if(BUTTONS_PINS & (7 << 1))
    {
        _delay_us(1000);
        if(BUTTONS_PINS & (7 << 1))
        {
            return BUTTONS_PINS & (7 << 1);
        }
        return 0;
    }
    return 0;
}