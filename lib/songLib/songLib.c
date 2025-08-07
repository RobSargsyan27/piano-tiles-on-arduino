#include <songLib.h>

#include <buzzerLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

double NOTE_FREQUENCY[] = { 523.250, 587.330, 659.250, 698.460, 783.990, 880.00, 987.770, 1046.500};

void deleteSong(SONG* song)
{
    if (song == NULL)
    {
        return;
    }

    if (song->length != NULL)
    {
        free(song->length);
    }

    if (song->name != NULL)
    {
        free(song->name);
    }

    if (song->notes != NULL)
    {
        int notesSize = sizeof(song->notes) / sizeof(song->notes[0]);
        for (int i = 0; i < notesSize; i++)
        {
            free(song->notes[i]);
        }
    }

    free(song);
}

NOTE* generateRandomNote()
{
    NOTE* note = malloc(sizeof(NOTE));
    note->frequency = NOTE_FREQUENCY[rand() % 8];
    note->duration = rand() % 1000 + 1;
    return note;
}

SONG* generateSong(char* name, uint16_t length)
{
    SONG* song = malloc(sizeof(SONG));
    song->name = malloc(sizeof(name));
    strcpy(song->name, name);
    song->length = malloc(sizeof(uint16_t));
    *(song->length) = length;
    song->notes = calloc(length, sizeof(NOTE));

    for (int i = 0; i < (int)length; i++)
    {
        song->notes[i] = generateRandomNote();
    }

    return song;
}

void playSong(SONG* song)
{
    NOTE** notes = song->notes;
    uint16_t lenght = *(song->length);

    for (int i = 0; i < lenght; i++)
    {
        playNote(notes[i]);
    }
}

void playNote(NOTE* note)
{
    if (note->frequency == 0)
    {
        _delay_ms(note->duration);
    }
    else
    {
        playTone(note->frequency, note->duration);
    }
}
