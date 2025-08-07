#include <avr/io.h>
#include <avr/interrupt.h>
#include <buttonLib.h>
#include <ledLib.h>
#include <stdlib.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <usart.h>

volatile int waitingMode = 1;
int ledsSequence[11] = {0};
int userAnswerIndex = 0;
int wrongSequence = 0;

ISR(PCINT1_vect)
{
    if(buttonPushed(1) && waitingMode)
    {
        waitingMode = !waitingMode;
    }else if(buttonPushed(1))
    {
        if(ledsSequence[userAnswerIndex] == 4)
        {
            printf("You pressed button 1, correct!");
        }else
        {
            printf("You pressed button 1, wrong!");
            wrongSequence = 1;
        }
        userAnswerIndex++;
    }else if(buttonPushed(2))
    {
        if(ledsSequence[userAnswerIndex] == 3)
        {
            printf("You pressed button 2, correct!");
        }else
        {
            printf("You pressed button 2, wrong!");
            wrongSequence = 1;
        }
        userAnswerIndex++;
    }else if(buttonPushed(3))
    {
        if(ledsSequence[userAnswerIndex] == 2)
        {
            printf("You pressed button 3, correct!");
        }else
        {
            printf("You pressed button 3, wrong!");
            wrongSequence = 1;
        }
        userAnswerIndex++;
    }
}

void gameStartIndication()
{
    for(int i = 0; i < 4; i++)
    {
        fadeInAllLeds(0.003);
        fadeOutAllLeds(0.003);
    }

    while (waitingMode)
    {
        toggleLed(1, 400);
    }
}

void turnOnRandomLeds(int count)
{
    for(int i = 0; i < count; i++)
    {
        int randomLed = rand() % 3 + 2;
        ledsSequence[i] = randomLed;
        toggleLed(randomLed, 700);
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
    int level = 1;
    while(level < 11)
    {
        turnOnRandomLeds(level);
        _delay_ms(level * 1100);

        if(wrongSequence || userAnswerIndex != level)
        {
            printf("Wrong, the correct pattern was: [");
            for(int j = 0; ledsSequence[j] != 0; j++ )
            {
                printf(" %d ", ledsSequence[j]);
            }
            printf("]\n");
        }else
        {
            printf("Correct, we go to level %d\n", level + 1);
            level++;
        }

        wrongSequence = 0;
        userAnswerIndex = 0;
    }

    printf("Congratulations, you are the Simon Master!");
}


int main()
{
    setup();

    gameStartIndication();
    loop();
}