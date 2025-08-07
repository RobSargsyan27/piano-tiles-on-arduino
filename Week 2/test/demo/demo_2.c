#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>

#define LOW(PORT, PIN) (PORT |= (1 << PIN))
#define HIGH(PORT, PIN) (PORT &= ~(1 << PIN))

void writePin( volatile uint8_t *dataDirectionRegister, uint8_t pin, uint8_t value )
{
    *dataDirectionRegister |= (value << pin);
}


int main()
{
    writePin(&DDRB, 2, 1);

    while(1)
    {
        LOW(PORTB, 2);
        _delay_ms(500);
        HIGH(PORTB, 2);
        _delay_ms(500);
    }
}