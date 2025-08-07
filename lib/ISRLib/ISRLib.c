#include <ISRLib.h>
#include <usart.h>
#include <avr/interrupt.h>

void enablePinISR(char port, int button)
{
    sei();
    switch (port)
    {
    case 'B':
        PCICR |= (1 << PCIE0);
        PCMSK0 |= (1 << button);
        break;
    case 'C':
        PCICR |= (1 << PCIE1);
        PCMSK1 |= (1 << button);;
        break;
    case 'D':
        PCICR |= (1 << PCIE2);
        PCMSK2 |= (1 << button);
        break;
    }
}

void enableMultiplePinsISR(char port, uint8_t pinsBinary)
{
    sei();
    switch (port)
    {
    case 'B':
        PCICR |= (1 << PCIE0);
        PCMSK0 |= pinsBinary;
        break;
    case 'C':
        PCICR |= (1 << PCIE1);
        PCMSK1 |= pinsBinary;
        break;
    case 'D':
        PCICR |= (1 << PCIE2);
        PCMSK2 |= pinsBinary;
        break;
    }
}

