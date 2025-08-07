#include "display.h"

#include <avr/io.h>
#include <util/delay.h>

#define LATCH_DIO PD4
#define CLK_DIO PD7
#define DATA_DIO PB0

const uint8_t SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
const uint8_t SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};
const uint8_t ALPHABET_MAP[] = {
    0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0xC2, 0x89, 0xCF, 0xE1, 0x8A, 0xC7, 0xEA, 0xC8,
    0xC0, 0x8C, 0x4A, 0xCC, 0x92, 0x87, 0xC1, 0xC1, 0xD5, 0x89, 0x91, 0xA4
};

void shift(uint8_t val)
{
    uint8_t bit;

    for (uint8_t i = 0; i < 8; i++)
    {
        bit = !!(val & (1 << (CLK_DIO - i)));

        if (bit == 1)
        {
            PORTB |= (1 << DATA_DIO);
        }
        else
        {
            PORTB &= ~(1 << DATA_DIO);
        }

        PORTD |= (1 << CLK_DIO);
        PORTD &= ~(1 << CLK_DIO);
    }
}

void blankSegment(uint8_t segment)
{
    PORTD &= ~(1 << LATCH_DIO);
    shift(SPACE);
    shift(SEGMENT_SELECT[segment]);
    PORTD |= (1 << LATCH_DIO);
}

void clearDisplay()
{
    for(int i = 0; i < 4; i++)
    {
        blankSegment(i);
    }
}

void enableDisplay()
{
    DDRD |= (1 << LATCH_DIO);
    DDRD |= (1 << CLK_DIO);
    DDRB |= (1 << DATA_DIO);

    clearDisplay();
}

uint8_t mapLetterWithHex(char letter)
{
    letter = letter > 0x5A ? (letter - 32) : letter;
    if (letter >= 0x41 && letter <= 0x5A)
    {
        return ALPHABET_MAP[letter - 0x41];
    }
    return SPACE;
}

void writeAlphabet()
{
    int alphabetSize = sizeof(ALPHABET_MAP) / sizeof(ALPHABET_MAP[0]);
    for(int i = 0; i < alphabetSize; i++)
    {
        uint8_t string[4];
        for(int j = 0; j < 4; j++)
        {
            if(i + j > 25)
            {
                string[j] = ALPHABET_MAP[i + j - 26];
            }else
            {
                string[j] = ALPHABET_MAP[i + j];
            }
        }

        int totalDelay = 0;
        while(totalDelay < 1000)
        {
            for(int i = 0; i < 4; i++)
            {
                PORTD &= ~( 1 << LATCH_DIO);
                shift(string[i]);
                shift(SEGMENT_SELECT[i]);
                PORTD |= (1 << LATCH_DIO);
                _delay_ms(5);
            }

            totalDelay += 20;
        }
    }
}

void writeCharToSegment(uint8_t segment, char character)
{
    PORTD &= ~( 1 << LATCH_DIO);
    if(character == '.')
    {
        shift(DOT);
    }else if(character == ' ')
    {
        shift(SPACE);
    }else if(character == '-')
    {
        shift(~(1 << 6));
    }else
    {
        shift(mapLetterWithHex(character));
    }
    shift(SEGMENT_SELECT[segment]);
    PORTD |= (1 << LATCH_DIO);
}

void writeDashToSegment(uint8_t segment, uint8_t value)
{
    PORTD &= ~( 1 << LATCH_DIO);
    shift(value);
    shift(SEGMENT_SELECT[segment]);
    PORTD |= (1 << LATCH_DIO);
}

void writeDifficultyAndWait(int difficulty, int duration)
{
    writeCharToSegment(0, 'D');
    _delay_ms(duration);
    writeCharToSegment(1, '-');
    _delay_ms(duration);
    switch (difficulty)
    {
    case 1:
        writeCharToSegment(2, 'E');
        break;
    case 2:
        writeCharToSegment(2, 'M');
        break;
    case 3:
        writeCharToSegment(2, 'H');
        break;
    }
    _delay_ms(duration);
}

void writeDot(uint8_t segment)
{
    PORTD &= ~( 1 << LATCH_DIO);
    shift(DOT);
    shift(SEGMENT_SELECT[segment]);
    PORTD |= (1 << LATCH_DIO);
}

void writeLevelAndWait(int duration)
{
    int level = ADC / 102.3 < 1 ? 1 : ADC / 102.3;
    writeCharToSegment(0, 'L');
    _delay_ms(duration);
    writeCharToSegment(1, ' ');
    _delay_ms(duration);
    writeNumberToSegment(2, level / 10);
    _delay_ms(duration);
    writeNumberToSegment(3, level % 10);
    _delay_ms(duration);
}

void writeSongAndWait(int song, int duration)
{
    writeCharToSegment(0, 'S');
    _delay_ms(duration);
    writeDot(0);
    _delay_ms(duration);
    writeNumberToSegment(1, song);
    _delay_ms(duration);
}

void writeNumber(int number)
{
    writeNumberToSegment(0, number / 1000);
    writeNumberToSegment(1, (number / 100) % 10);
    writeNumberToSegment(2, (number / 10) % 10);
    writeNumberToSegment(3, number % 10);
}

void writeNumberAndWait(int number, int duration, float delay)
{
    for (int i = 0; i < duration; i += delay * 4)
    {
        writeNumberToSegment(0, number / 1000);
        _delay_ms(delay);
        writeNumberToSegment(1, (number / 100) % 10);
        _delay_ms(delay);
        writeNumberToSegment(2, (number / 10) % 10);
        _delay_ms(delay);
        writeNumberToSegment(3, number % 10);
        _delay_ms(delay);
    }
}

void writeNumberToSegment(uint8_t segment, uint8_t value)
{
    PORTD &= ~(1 << LATCH_DIO);
    shift(SEGMENT_MAP[value]);
    shift(SEGMENT_SELECT[segment]);
    PORTD |= (1 << LATCH_DIO);
}

void writeScoreAndWait(int score, int duration)
{
    if(score != 0)
    {
        if(score % 9 == 0)
        {
            writeNumberToSegment(3, 9);
        }else
        {
            int _score = score - (score / 9) * 9;
            writeNumberToSegment(3, _score);
        }
        _delay_ms(duration);
    }
}

void writeString(char* string)
{
    for(int i = 0; i < 4 && string[i] != '\0'; i++)
    {
        writeCharToSegment(i, string[i]);
        _delay_ms(2);
    }
}

void writeStringifyNumberAndWait(char* number, int delay)
{
    long totalDelay = 0;
    while (totalDelay < delay)
    {
        writeStringifyNumbers(number);
        totalDelay += 20;
    }
}

void writeStringifyNumbers(char* number)
{
    for (int i = 0; i < 4 && number[i] != '\0'; i++)
    {
        int digit = number[i] - '0';
        writeNumberToSegment(i, digit);
        _delay_ms(5);
    }
}

void writeTime(int seconds)
{
    writeNumberToSegment(0, seconds / 600);
    writeNumberToSegment(1, (seconds / 60) % 10);
    writeDot(1);
    writeNumberToSegment(2, (seconds % 60) / 10);
    writeNumberToSegment(3, (seconds % 60) % 10);
}
