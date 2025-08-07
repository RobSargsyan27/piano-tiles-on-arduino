#include <ADCLib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <buzzerLib.h>
#include <buttonLib.h>
#include <display.h>
#include <ledLib.h>
#include <usart.h>

int buzzerState = 0;
ISR(PCINT1_vect)
{
    if(buttonPushed(1))
    {
        buzzerState = !buzzerState;
    }
}

void setup()
{
    enableADC();
    enableAutoSampling();
    enableAllButtons();
    enableAllLeds();
    enableBuzzer();
    enableDisplay();
    initUSART();
}

void loop()
{
    writeNumberAndWait(ADC, 5, 0.5);
    if(buzzerState)
    {
        playTone(ADC, 150);
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