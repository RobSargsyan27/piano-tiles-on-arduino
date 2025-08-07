#include <ADCLib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <buttonLib.h>
#include <buzzerLib.h>
#include <display.h>
#include <ledLib.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <usart.h>

typedef struct
{
   char username[10];
    int record;
}USER;

volatile USER** topUsers;
volatile char currentUsername[10];

volatile int levelSpeed = 0;
volatile int difficultySelected = 0;
volatile int selectedDifficulty = 1;
volatile int currentLevel = 0;

volatile int songSelected = 0;
volatile int selectedSongNumber = 1;
volatile int selectedSongNotesSize = 0;
volatile float* selectedSong;
float** availableSongs;
int availableSongsSize[] = {3, 3, 3, 6, 7, 7, 26};
volatile int noteIndex = 0;

volatile int currentScore = 0;
volatile int totalHits = 0;
volatile int currentToneDuration = 140;


volatile int S0U = 0; // Segment 0 Up
volatile int S0M = 0; // Segment 0 Middle
volatile int S0D = 0; // Segment 0 Down

volatile int S1U = 0;
volatile int S1M = 0;
volatile int S1D = 0;

volatile int S2U = 0;
volatile int S2M = 0;
volatile int S2D = 0;

volatile float S0UF = 0; // Segment 0 Up Frequency
volatile float S0MF = 0; // Segment 0 Middle Frequency
volatile float S0DF = 0; // Segment 0 Down Frequency

volatile float S1UF = 0;
volatile float S1MF = 0;
volatile float S1DF = 0;

volatile float S2UF = 0;
volatile float S2MF = 0;
volatile float S2DF = 0;

volatile float BF = 0; // Button Frequency

volatile int B0 = 0; // Button 0
volatile int B1 = 0;
volatile int B2 = 0;


void checkRecord()
{
    for(int i = 0; i < 3; i++)
    {
        if(topUsers[i]->record < totalHits)
        {
            for(int j = 2; j > i; j--)
            {
                topUsers[j]->record = topUsers[j - 1]->record;
                strcpy(topUsers[j]->username,  topUsers[j - 1]->username);
            }
            topUsers[i]->record = totalHits;
            strcpy(topUsers[i]->username,  currentUsername);
            break;
        }
    }
}

void displayLevelConfiguration()
{
    while (!currentLevel)
    {
        writeLevelAndWait(2);
    }
    clearDisplay();
}

void displaySongConfiguration()
{
    while (!songSelected)
    {
        writeSongAndWait(selectedSongNumber, 2);
    }

    clearDisplay();
}

void displayGameDifficultyConfiguration()
{
    while (!difficultySelected)
    {
        writeDifficultyAndWait(selectedDifficulty, 2);
    }
    clearDisplay();
}

void initTopUsersTable()
{
    topUsers = calloc(3, sizeof(USER*));
    for(int i = 0; i < 3; i++)
    {
        topUsers[i] = malloc(sizeof(USER));
        topUsers[i]->record = 0;
        strcpy(topUsers[i]->username, "");
    }
}

void deleteTopUsersTable()
{
    for(int i = 0; i < 3; i++)
    {
        free(topUsers[i]);
    }

    free(topUsers);
}

void printTopUsersTable()
{
    for(int i = 0; i < 3; i++)
    {
        printf("User: %s", (const char*)topUsers[i]->username);
        printf("Record: %d", topUsers[i]->record);
    }
}

void setUsername()
{
    printString("Enter your username (max 10 characters): ");
    readString(currentUsername, sizeof(currentUsername));
    printf("\n");
}

void uploadSongs()
{
    float songs[7][26] = {
        {C5, D5, E5}, {E5, D5, C5}, {G5, A5, B5}, {C5, D5, E5, F5, G5, A5}, {C5, C6, G5, A5, F5, E5, D5},
        {E5, F5, G5, A5, B5, C6, D5},
        {E5, D5, C5, D5, E5, E5, E5, D5, D5, D5, E5, E5, E5, E5, D5, C5, D5, E5, E5, E5, E5, D5, D5, E5, D5, C5}
    };

    availableSongs = calloc(7, sizeof(float*));
    for (int i = 0; i < 7; i++)
    {
        availableSongs[i] = calloc(availableSongsSize[i], sizeof(float));
        for (int j = 0; j < availableSongsSize[i]; j++)
        {
            availableSongs[i][j] = songs[i][j];
        }
    }
}

void deleteSpareSongs()
{
    for (int i = 0; i < 6; i++)
    {
        free(availableSongs[i]);
    }

    free(availableSongs);
}

void levelUpIfNeeded()
{
    if (currentScore % 36 == 0 && currentScore != 0)
    {
        currentScore = 0;
        currentLevel++;
        currentToneDuration = currentToneDuration * 0.9;
        OCR1A -= levelSpeed;
        for (int i = 0; i < 2; i++)
        {
            playTone(C5, 25);
            playTone(G5, 25);
        }
    }
}

void setRandomSegmentPerNote(float note)
{
    int randomSegment = random() % 3;
    switch (randomSegment)
    {
    case 0:
        S0UF = note;
        S0U = 1;
        break;
    case 1:
        S1UF = note;
        S1U = 1;
        break;
    case 2:
        S2UF = note;
        S2U = 1;
        break;
    default:
        S0UF = note;
        S0U = 1;
    }
}

void updateFlow()
{
    S0D = S0M;
    S0M = S0U;
    S0U = 0;

    S0DF = S0MF;
    S0MF = S0UF;
    S0UF = 0;

    S1D = S1M;
    S1M = S1U;
    S1U = 0;

    S1DF = S1MF;
    S1MF = S1UF;
    S1UF = 0;

    S2D = S2M;
    S2M = S2U;
    S2U = 0;

    S2DF = S2MF;
    S2MF = S2UF;
    S2UF = 0;
}

void updateDisplaySegmentAndWait(int segment, int duration)
{
    uint8_t bin = 0xFF;
    if (segment == 0)
    {
        if (S0U)
        {
            bin &= ~(1 << 0);
        }
        if (S0M)
        {
            bin &= ~(1 << 6);
        }
        if (S0D)
        {
            bin &= ~(1 << 3);
        }
    }
    else if (segment == 1)
    {
        if (S1U)
        {
            bin &= ~(1 << 0);
        }
        if (S1M)
        {
            bin &= ~(1 << 6);
        }
        if (S1D)
        {
            bin &= ~(1 << 3);
        }
    }
    else
    {
        if (S2U)
        {
            bin &= ~(1 << 0);
        }
        if (S2M)
        {
            bin &= ~(1 << 6);
        }
        if (S2D)
        {
            bin &= ~(1 << 3);
        }
    }

    writeDashToSegment(segment, bin);
    _delay_ms(duration);
}

void checkHits()
{
    if (S0D)
    {
        if (B0)
        {
            currentScore++;
            totalHits++;
            BF = S0DF;
            B0 = 0;
        }
        else
        {
            currentScore = 0;
        }
    }


    if (S1D)
    {
        if (B1)
        {
            currentScore++;
            totalHits++;
            BF = S1DF;
            B1 = 0;
        }
        else
        {
            currentScore = 0;
        }
    }

    if (S2D)
    {
        if (B2)
        {
            currentScore++;
            totalHits++;
            BF = S2DF;
            B2 = 0;
        }
        else
        {
            currentScore = 0;
        }
    }
}

void initTimer1()
{
    TCCR1B |= (1 << WGM12);
    TCCR1B &= ~(1 << CS12) & ~(1 << CS10);
    OCR1A = 15624;

    TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    checkHits(); // Checks if the players succesfully hits the note for the current state of the game.
    updateFlow(); // Updates the game display by moving existing dashes/notes downwards.

    noteIndex = noteIndex < selectedSongNotesSize ? noteIndex : 0;
    setRandomSegmentPerNote(selectedSong[noteIndex]);               // Randomly sets new note to be played.
    noteIndex++;
}


ISR(PCINT1_vect)
{
    if (buttonPushed(2) && !currentLevel)
    {
        currentLevel = ADC / 102.3 < 1 ? 1 : ADC / 102.3;
    }
    else if (buttonPushed(1) && !songSelected)
    {
        if (selectedSongNumber - 1 > 0)
        {
            selectedSongNumber -= 1;
        }
    }
    else if (buttonPushed(2) && !songSelected)
    {
        songSelected = !songSelected;
        selectedSong = availableSongs[selectedSongNumber - 1];
        selectedSongNotesSize = availableSongsSize[selectedSongNumber - 1];
    }
    else if (buttonPushed(3) && !songSelected)
    {
        if (selectedSongNumber + 1 < 8)
        {
            selectedSongNumber += 1;
        }
    }
    else if(buttonPushed(1) && !difficultySelected)
    {
        if (selectedDifficulty - 1 > 0)
        {
            selectedDifficulty -= 1;
        }
    }
    else if (buttonPushed(2) && !difficultySelected)
    {
        difficultySelected = !difficultySelected;
        levelSpeed = 460 * selectedDifficulty;
        OCR1A = OCR1A - currentLevel * levelSpeed;
    }
    else if(buttonPushed(3) && !difficultySelected)
    {
        if(selectedDifficulty + 1 < 4)
        {
            selectedDifficulty += 1;
        }
    }
    else if (buttonPushed(1) && S0D)
    {
        B0 = 1;
    }
    else if (buttonPushed(2) && S1D)
    {
        B1 = 1;
    }
    else if (buttonPushed(3) && S2D)
    {
        B2 = 1;
    }
}

void setup()
{
    sei();
    enableADC();
    enableAutoSampling();
    enableAllButtons(); // Implicitly enables ISR for the given port and pins.
    enableAllLeds(); // Implicitly turns all leds off.
    enableBuzzer(); // Implicitly turns buzzer off.
    enableDisplay();
    initUSART();
    initTopUsersTable(); //Creates table in HEAP
    uploadSongs(); //Uploads songs in HEAP
    initTimer1(); //Implicitly turns the timmer off by setting the scaling factor to 0.
}

void triggerBuzzer()
{
    if (BF > 0)
    {
        playTone(BF, currentToneDuration);
        BF = 0;
    }
}

void startTimer1()
{
    TCCR1B |= (1 << CS12) | (1 << CS10); // 1024
}

void updateDisplay()
{
    updateDisplaySegmentAndWait(0, 2);
    updateDisplaySegmentAndWait(1, 2);
    updateDisplaySegmentAndWait(2, 2);
    writeScoreAndWait(currentScore, 2);
}

int main()
{
    setup();

    setUsername();
    displayLevelConfiguration();
    displaySongConfiguration();
    displayGameDifficultyConfiguration();
    startTimer1();

    while (currentLevel < 11)
    {
        updateDisplay();
        triggerBuzzer();
        levelUpIfNeeded();
        displayScore(currentScore); // Displays on 4 LEDs
    }

    checkRecord();
    printTopUsersTable();
    deleteTopUsersTable();
    deleteSpareSongs();
    clearDisplay();
}