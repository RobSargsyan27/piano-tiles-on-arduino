#ifndef songLib
#define songLib

#include <stdint.h>

typedef struct
{
    double frequency;
    uint16_t duration;
} NOTE;

typedef struct
{
    char* name;
    uint16_t* length;
    NOTE** notes;
} SONG;

//Exercise 4.6.2
SONG* generateSong(char* name, uint16_t length);
void playNote(NOTE* note);
void playSong(SONG* song);
void deleteSong(SONG* song);

#endif