#include <buttonLib.h>
#include <avr/io.h>
#include <display.h>
#include <usart.h>
#include <avr/interrupt.h>

volatile int counter = 0;
volatile int seconds = 0;

void initTimer1()
{
    TCCR1B |= (1 << WGM12);

    TIMSK1 |= (1 << OCIE1A);

    OCR1A = 15624;

    sei();
}

void startTimer()
{
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

void stopTimer()
{
    TCCR1B &= ~(_BV(CS12)) & ~(_BV(CS10));
}

ISR( TIMER1_COMPA_vect )
{
    seconds++;
}

ISR(PCINT1_vect)
{
    if(buttonPushed(1))
    {
        startTimer();
    }else if(buttonPushed(2))
    {
        stopTimer();
    }else if(buttonPushed(3))
    {
        counter = 0;
        seconds = 0;
    }
}


void setup()
{
    enableAllButtons();
    enableDisplay();
    initTimer1();
    initUSART();
}

void loop()
{
    writeTime(seconds);
}

int main()
{
    setup();
    while (1)
    {
        loop();
    }
}