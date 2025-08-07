#include <buzzerLib.h>

#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <stdio.h>
#include <util/delay.h>

#define BUZZER_DDR DDRD
#define BUZZER_PIN PD3
#define BUZZER_PORT PORTD


void disableBuzzer()
{
    BUZZER_DDR &= ~(1 << BUZZER_PIN);
}

void enableBuzzer()
{
    BUZZER_DDR |= (1 << BUZZER_PIN);
    BUZZER_PORT |= (1 << BUZZER_PIN);
}

void playMusic(float* notes, int size, int duration)
{
    for (int i = 0; i < size; i++)
    {
        playTone(notes[i], duration);
    }
}

void playTone(float frequency, uint32_t duration)
{
    uint32_t periodDurationInMicro = (uint32_t)(1000000 / frequency);
    uint32_t totalDurationInMicro = duration * 1000;
    for (uint32_t playTime = 0; playTime < totalDurationInMicro; playTime += periodDurationInMicro)
    {
        BUZZER_PORT &= ~(1 << BUZZER_PIN);
        _delay_us(periodDurationInMicro / 2);
        BUZZER_PORT |= (1 << BUZZER_PIN);
        _delay_us(periodDurationInMicro / 2);
    }
}