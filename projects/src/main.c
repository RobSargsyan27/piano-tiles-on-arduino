#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <avr/interrupt.h>
#include <buttonLib.h>
#include <buzzerLib.h>
#include <ledLib.h>
#include <display.h>
#include <usart.h>

#define GRAVITY 1.622
#define BURN_FULE_IN_MS 0.05

volatile int aboveLandDistance = 9999;
volatile int remainingFuel = 1500;
volatile int currentSpeed = 100;
volatile int pressCounterInMs = 0;
volatile int landsSafely = 0;

float FAILURE_MUSIC[4] = {C5, E5, G5, C6};
float FAILURE_MUSIC_DURATION[4] = {150, 150, 150, 400};
float SUCCESS_MUSIC[] = {C5, C5, G5, G5, A5, A5, G5, F5, F5, E5, E5, D5, D5, C5};

void initTimer0()
{
    TCCR0B |= (1 << WGM02);
    TCCR0B &= ~(1 << CS01) & ~(1 << CS00);
    OCR0A = 250;

    TIMSK0 |= (1 << OCIE0A);
}

void startTimer0()
{
    TCCR0B |= (1 << CS01) | (1 << CS00);
}

void stopTimer0()
{
    TCCR0B &= ~(1 << CS01) & ~(1 << CS00);
}

void initTimer1()
{
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    OCR1A = 15624;

    TIMSK1 |= (1 << OCIE1A);
}

void stopTimer1()
{
    TCCR1B &= ~(1 << CS12) & ~(1 << CS10);
}

void calculateNewParameters()
{
    currentSpeed += GRAVITY - (pressCounterInMs * BURN_FULE_IN_MS) / 5;
    aboveLandDistance = aboveLandDistance - currentSpeed;
    remainingFuel -= pressCounterInMs * BURN_FULE_IN_MS;
    pressCounterInMs = 0;
}

ISR(TIMER0_COMPA_vect)
{
    pressCounterInMs++;
}

ISR(TIMER1_COMPA_vect)
{
    calculateNewParameters();
    writeNumberAndWait(aboveLandDistance, 300, 2);
    clearDisplay();
}

ISR(PCINT1_vect)
{
    if (buttonPushed(2))
    {
        startTimer0();
    }
    else if (buttonReleased(2))
    {
        stopTimer0();
    }
}


void showFuleLevel()
{
    for (int i = 4; i > 0; i--)
    {
        if (remainingFuel > 1500 * ((i - 1) * 0.25))
        {
            turnOnLed(i);
        }
        else
        {
            toggleLed(i, 200);
        }
    }
}

void setup()
{
    sei();
    enableAllLeds();
    enableButton(2);
    enableBuzzer();
    enableDisplay();
    initUSART();
    initTimer0();
    initTimer1();
}


void launch()
{
    while (aboveLandDistance > 0)
    {
        showFuleLevel();
        if (aboveLandDistance <= 3 && currentSpeed <= 5)
        {
            landsSafely++;
        }
    }

    stopTimer0();
    stopTimer1();
    if(landsSafely)
    {
        playMusic(SUCCESS_MUSIC, 14, 150);
    }else
    {
        int duration = 3000;
        while(duration > 0)
        {
            for(int i = 0; i < 4; i++)
            {
                playTone(FAILURE_MUSIC[i], FAILURE_MUSIC_DURATION[i]);
            }

            duration -= 14;
        }
    }
}


int main()
{
    setup();
    launch();
}