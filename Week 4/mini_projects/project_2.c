#include <buzzerLib.h>


void setup()
{
    enableBuzzer();
}

void loop()
{
    float notes[] = Mary_Had_a_Little_Lamb;
    int notesSize = sizeof(notes) / sizeof(notes[0]);
    playMusic(notes, notesSize, 200);
}

int main()
{
    setup();

    while (1)
    {
        loop();
    }
}