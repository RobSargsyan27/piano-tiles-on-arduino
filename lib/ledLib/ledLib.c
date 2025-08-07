#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ledLib.h>
#include <usart.h>
#include <avr/io.h>

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PINS PINB

int checkLedOn(int ledNumber)
{
    return !(LED_PINS & (1 << ledNumber));
}

int checkLedOff(int ledNumber)
{
    return LED_PINS & (1 << ledNumber);
}

void countDown(int duration)
{
    turnOnAllLeds();
    for(int i = 4; i >= 0; i--)
    {
        _delay_ms(duration / 4);
        turnOffLed(i);
    }
}

void disableLed(int ledNumber)
{
    LED_DDR &= ~(1 << (ledNumber + 1));
}

void disableMultipleLeds(uint8_t pinsBinary)
{
    LED_DDR &= pinsBinary;
}

void disableAllLeds()
{
    LED_DDR &= ~(15 << 2);
}

void displayScore(int score)
{
    int ledNumber = score / 9;

    if(ledNumber == 0)
    {
        turnOffAllLeds();
    }else
    {
        for(int i = 1; i <= ledNumber; i++)
        {
            turnOnLed(i);
        }
    }
}

void dimLed(int ledNumber, int percentage, double duration)
{
    double durationInMs = duration * 1000;
    double onTime = percentage / 100.0;
    double offTime = 1 - onTime;

    while (durationInMs > 0)
    {
        turnOnLed(ledNumber);
        _delay_ms(onTime);
        turnOffLed(ledNumber);
        _delay_ms(offTime);
        durationInMs -= onTime + offTime;
    }
}

void dimAllLeds(int percentage, double duration)
{
    double durationInMs = duration * 1000;
    double onTime = percentage / 100.0;
    double offTime = 1 - onTime;

    while (durationInMs > 0)
    {
        turnOnAllLeds();
        _delay_ms(onTime);
        turnOffAllLeds();
        _delay_ms(offTime);
        durationInMs -= onTime + offTime;
    }
}

void enableLed(int ledNumber)
{
    LED_DDR |= (1 << (ledNumber + 1));
}

void enableMultipleLeds(uint8_t pinsBinary)
{
    LED_DDR |= pinsBinary;
}

void enableAllLeds()
{
    LED_DDR |= (15 << 2);
    turnOffAllLeds();
}

void fadeIn(int ledNumber, double duration)
{
    for (int i = 0; i < 100; i += 3)
    {
        dimLed(ledNumber, i, duration);
    }
}

void fadeInAllLeds(double duration)
{
    turnOffAllLeds();
    for (int i = 0; i < 100; i += 3)
    {
        dimAllLeds(i, duration);
    }
}

void fadeOut(int ledNumber, double duration)
{
    for (int i = 100; i > 0; i -= 3)
    {
        dimLed(ledNumber, i, duration);
    }
}

void fadeOutAllLeds(double duration)
{
    for(int i = 100; i > 0; i -= 3)
    {
        dimAllLeds(i, duration);
    }
}

void increaseLedBurnByPeriod(int ledNumber, int startDuration, int endDuration)
{
    for (int i = startDuration; i < endDuration; i += 50)
    {
        turnOnLed(ledNumber);
        _delay_ms(i);
        turnOffLed(ledNumber);
        _delay_ms(100);
    }
}

void increaseLedBurn(int ledNumber)
{
    int duration[22];
    for(int i = 0; i < 22; i++)
    {
        if(i == 0)
        {
            duration[i] = 10;
        }else if(i == 21)
        {
            duration[i] = 1000;
        }else
        {
            duration[i] = duration[i - 1] + 100;
        }
    }
    int durationSize = sizeof(duration) / sizeof(duration[0]);

    for(int i = 0; i < durationSize; i++ )
    {
        turnOnLed(ledNumber);
        _delay_ms(duration[i]);
        turnOffLed(ledNumber);
        _delay_ms(50);
    }
}

void ledChaos()
{
    int randomNumberOfLeds = rand() % 4;
    int randomOnDuration;

    do
    {
        randomOnDuration = rand() % 1000 + 100;
    }
    while (randomOnDuration > 1000);

    for (int i = 0; i < randomNumberOfLeds; i++)
    {
        int randomLed = (rand() % 4) + 1;
        turnOnLed(randomLed);
    }
    _delay_ms(randomOnDuration);

    turnOffAllLeds();
}

void toggleLed(int ledNumber, int duration)
{
    turnOnLed(ledNumber);
    _delay_ms(duration);
    turnOffLed(ledNumber);
    _delay_ms(duration);
}

void toggleLedForGivenTime(int ledNumber, int times, int duration)
{
    for (int i = 0; i < times; i++)
    {
        toggleLed(ledNumber, duration);
    }
}

void turnOnAllLeds()
{
    LED_PORT &= ~(15 << 2);
}

void turnOnAllLedsAndWait(int duration)
{
    LED_PORT &= ~(15 << 2);
    _delay_ms(duration);
}

void turnOnLed(int ledNumber)
{
    LED_PORT &= ~(1 << (ledNumber + 1));
}

void turnOnMultipleLeds(uint8_t pinsBinary)
{
    LED_PORT &= ~(pinsBinary);
}

void turnOnLedsConsecutively(int duration)
{
    turnOffAllLeds();
    _delay_ms(duration);

    for (int i = 2; i < 6; i++)
    {
        LED_PORT &= ~(1 << i);
        _delay_ms(duration);
    }
}

void turnOnLedsRandomly(int duration)
{
    int randomLeds[10];
    for (int i = 0; i < 10; i++)
    {
        randomLeds[i] = rand() % 4 + 1;
    }

    turnOffAllLeds();
    for (int i = 0; i < 10; i++)
    {
        turnOnLed(randomLeds[i]);
        _delay_ms(duration);
        turnOffLed(randomLeds[i]);
        _delay_ms(duration);
    }
}

void turnOnLedsRandomlyByAlphabet(const char *message)
{
    turnOffAllLeds();
    for(int i = 0; message[i] != '\0'; i++)
    {
        int ledNumber = message[i] % 4 == 0 ? 4 : message[i] % 4;
        toggleLed(ledNumber, 200);
    }
}

void turnOnLedsByAlphabet(const char *message)
{
    turnOffAllLeds();
    for(int i = 0; message[i] != '\0'; i++)
    {
        switch (message[i])
        {
        case 'a':
            toggleLed(1, 500);
            break;
        case 'b':
            toggleLed(2, 500);
            break;
        case 'c':
            toggleLed(3, 500);
            break;
        case 'd':
            toggleLed(4, 500);
            break;
        default:
            toggleLed(1, 500);
        }
    }
}

void turnOffLed(int ledNumber)
{
    LED_PORT |= (1 << (ledNumber + 1));
}

void turnOffMultipleLeds(uint8_t pinsBinary)
{
    LED_PORT |= pinsBinary;
}

void turnOffAllLeds()
{
    LED_PORT |= (15 << 2);
}

void turnOffAllLedsAndWait(int duration)
{
    LED_PORT |= (15 << 2);
    _delay_ms(duration);
}
