#include <avr/io.h>
#include <avr/interrupt.h>
#include <buttonLib.h>
#include <ledLib.h>
#include <stdlib.h>
#include <util/delay.h>
#include <usart.h>

#define LONG_TIME 2500
#define SHORT_TIME 600
#define WAIT_FOR_USER 5000
#define TURNS_NUMBER 5


volatile int score = 0;
int choiceState[3] = {0,0,0};

int morseFrequencyForAlphabet[26][5] = {
    {SHORT_TIME, LONG_TIME, 0}, {LONG_TIME, SHORT_TIME, SHORT_TIME, SHORT_TIME, 0},
    {LONG_TIME, SHORT_TIME, LONG_TIME, SHORT_TIME, 0}, {LONG_TIME, SHORT_TIME, SHORT_TIME, 0}, {SHORT_TIME, 0},
    {SHORT_TIME, SHORT_TIME, LONG_TIME, SHORT_TIME, 0}, {LONG_TIME, LONG_TIME, SHORT_TIME, 0},
    {SHORT_TIME, SHORT_TIME, SHORT_TIME, SHORT_TIME, 0}, {SHORT_TIME, SHORT_TIME, 0},
    {SHORT_TIME, LONG_TIME, LONG_TIME, LONG_TIME, 0}, {LONG_TIME, SHORT_TIME, LONG_TIME, 0},
    {SHORT_TIME, LONG_TIME, SHORT_TIME, SHORT_TIME, 0}, {LONG_TIME, LONG_TIME, 0}, {LONG_TIME, SHORT_TIME, 0},
    {LONG_TIME, LONG_TIME, LONG_TIME, 0}, {SHORT_TIME, LONG_TIME, LONG_TIME, SHORT_TIME ,0},
    {LONG_TIME, LONG_TIME, SHORT_TIME, LONG_TIME, 0}, {SHORT_TIME, LONG_TIME, SHORT_TIME, 0},
    {SHORT_TIME, SHORT_TIME, SHORT_TIME, 0}, {LONG_TIME, 0}, {SHORT_TIME, SHORT_TIME, LONG_TIME, 0},
    {SHORT_TIME, SHORT_TIME, SHORT_TIME, LONG_TIME, 0}, {SHORT_TIME, LONG_TIME, LONG_TIME, 0},
    {LONG_TIME, SHORT_TIME, SHORT_TIME, LONG_TIME, 0}, {LONG_TIME, SHORT_TIME, LONG_TIME, LONG_TIME, 0},
    {LONG_TIME, LONG_TIME, SHORT_TIME, SHORT_TIME, 0}
};

ISR(PCINT1_vect)
{
    if(buttonPushed(1))
    {
        choiceState[0] = 1;
    }else if(buttonPushed(2))
    {
        choiceState[1] = 1;
    }else if(buttonPushed(3))
    {
        choiceState[2] = 1;
    }
}

void showCountDownPattern()
{
    turnOnAllLeds();
    _delay_ms(800);

    for(int i = 4; i > 0; i--)
    {
        turnOffLed(i);
        _delay_ms(800);
    }
}

int showPossibleAnswers(char correctAnswer)
{
    int correctAnswerIsShown = 0;
    int correctAnswerIndex = 0;

    for(int i = 0; i < 3; i++)
    {
        if((rand() % 1000 < 333 || i == 2) && correctAnswerIsShown == 0 )
        {
            printf("Possible answer: %c\n", correctAnswer );
            correctAnswerIsShown++;
            correctAnswerIndex = i;
        }else
        {
            printf("Possible answer: %c\n", 'A' + (rand() % 26));
        }
    }

    return correctAnswerIndex;
}

void finishGameLed()
{
    for(int i = 0; i < 5; i++)
    {
        fadeInAllLeds(0.003);
        fadeOutAllLeds(0.003);
    }
}

void setup()
{
    enableAllButtons();
    enableAllLeds();
    initUSART();
}


void loop()
{
    int randomLetterIndex = rand() % 26;
    char randomLetter = 'A' + randomLetterIndex;
//printf("Hint: Correct answer %c\n", randomLetter);
    int* morseFrequencyForLetter = morseFrequencyForAlphabet[randomLetterIndex];
    for(int i = 0; morseFrequencyForLetter[i] != 0; i++)
    {
        turnOnAllLedsAndWait(morseFrequencyForLetter[i]);
        turnOffAllLedsAndWait(100);
    }

    int correctAnswerIndex = showPossibleAnswers(randomLetter);
    _delay_ms(1000);
    countDown(3000);

    if(choiceState[correctAnswerIndex])
    {
        printf("Yes, you are right the correct answer is %c.\n", randomLetter);
        score++;
        printf("Score: %d\n", score);
    }else
    {
        printf("No the right answer is %c.\n", randomLetter);
    }

    choiceState[0] = 0;
    choiceState[1] = 0;
    choiceState[2] = 0;
}


int main()
{
    setup();

    showCountDownPattern();

    for(int i = 0; i < TURNS_NUMBER; i++)
    {
        loop();
    }

    _delay_ms(5000);
    finishGameLed();
}