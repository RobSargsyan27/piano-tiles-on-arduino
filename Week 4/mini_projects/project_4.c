#include <avr/io.h>
#include <avr/interrupt.h>
#include <buzzerLib.h>
#include <buttonLib.h>
#include <songLib.h>
#include <usart.h>

volatile int buzzerState = 0;
volatile int buttonPreviousState = 0;
ISR(PCINT1_vect)
{
    if (buttonPushed(1))
    {
        buzzerState = !buzzerState;
        printf("Buzzer state %d\n", buzzerState);
    }
}

void setup()
{
    enableButton(1);
    enableButton(2);
    enableBuzzer();
    initUSART();
}

void loop()
{
    if (buzzerState)
    {
        SONG* song = generateSong("Masquerade", 3);
        for (int i = 0; i < 4; i++)
        {
            if(buzzerState)
            {
                playSong(song);
            }
        }
        deleteSong(song);
    }
}

int main()
{
    setup();

    while (1)
    {
        loop();
    }
}
