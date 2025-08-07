#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <avr/interrupt.h>
#include <ADCLib.h>
#include <buttonLib.h>
#include <ledLib.h>
#include <stdlib.h>
#include <display.h>
#include <string.h>
#include <util/delay.h>
#include <usart.h>

#define startNumber 21
#define maxNumber 3
typedef struct
{
    char competitor[10];
    int takenMatches;
    int leftMathces;
}ANALYTICS;

volatile int generatedSeed = 0;
volatile int turn = 0;
volatile int totolNumberOfTurns = 0;
volatile int currentChoosenNumber = 3;
volatile int currentLeftMatches = startNumber;
ANALYTICS* analytics;

int getComputerNumber()
{
    int result = (currentLeftMatches - 1) % (maxNumber + 1);

    if(result == 0)
    {
        return rand() % maxNumber + 1;
    }

    return result;
}

ISR(PCINT1_vect)
{
    if(buttonPushed(1) && !generatedSeed)
    {
        srand(ADC * 9.7741935);
        generatedSeed = 1;
        turn = rand() % 2;
    }else if(buttonPushed(1) && generatedSeed && turn % 2 != 0)
    {
        if(currentChoosenNumber - 1 > 0)
        {
            currentChoosenNumber--;
        }
    }else if(buttonPushed(2) && turn % 2 == 0)
    {
        turn++;
        strcpy(analytics[totolNumberOfTurns].competitor, "COMPUTER");
        analytics[totolNumberOfTurns].takenMatches = getComputerNumber();
        currentLeftMatches -= getComputerNumber();
        analytics[totolNumberOfTurns].leftMathces = currentLeftMatches;
        currentChoosenNumber = 3;
        totolNumberOfTurns++;
    }else if(buttonPushed(2) && turn % 2 != 0)
    {
        turn++;
        strcpy(analytics[totolNumberOfTurns].competitor, "PLAYER");
        analytics[totolNumberOfTurns].takenMatches = currentChoosenNumber;
        currentLeftMatches -= currentChoosenNumber;
        analytics[totolNumberOfTurns].leftMathces = currentLeftMatches;
        currentChoosenNumber = getComputerNumber();
        totolNumberOfTurns++;
    }else if(buttonPushed(3) && turn % 2 != 0)
    {
        if(currentChoosenNumber + 1 < 4)
        {
            currentChoosenNumber++;
        }
    }
}

void displayGenerateSeedInterface()
{
    while (!generatedSeed)
    {
        writeNumberAndWait(ADC * 9.7741935, 12, 3);
    }
}

void displayGameState(int index)
{
    writeNumberToSegment(0, currentLeftMatches / 10);
    _delay_ms(2);
    writeNumberToSegment(1, currentLeftMatches % 10);
    _delay_ms(2);

    if(index % 180 == 0)
    {
        if(turn % 2 == 0)
        {
            writeCharToSegment(2, 'C');
        }else
        {
            writeCharToSegment(2, 'P');
        }
        _delay_ms(2);
    }

    writeNumberToSegment(3, currentChoosenNumber);
    _delay_ms(2);
}

void displayWinner()
{
    if(turn % 2 == 0)
    {
        for(int i = 0; i < 6000; i += 20)
        {
            writeString("WINP");
            writeDot(3);
        }

    }else
    {
        for(int i = 0; i < 6000; i += 20)
        {
            writeString("WINC");
            writeDot(2);
        }
    }

    clearDisplay();
}

void setup()
{
    enableADC();
    enableAllButtons();
    enableAllLeds();
    enableAutoSampling();
    enableDisplay();
    initUSART();

    analytics = calloc(25, sizeof(ANALYTICS));
}


void playGame()
{
    int index = 0;
    while(currentLeftMatches != 1)
    {
        displayGameState(index);
        index = index == 999 ? 0 : index + 1;
    }
}


int main()
{
    setup();

    displayGenerateSeedInterface();
    playGame();
    displayWinner();

    for(int i = 0; i < totolNumberOfTurns; i++)
    {
        printf("Competitor: %s, taken matches: %d, leftMatches: %d\n", analytics[i].competitor, analytics[i].takenMatches, analytics[i].leftMathces);
    }
    free(analytics);
}