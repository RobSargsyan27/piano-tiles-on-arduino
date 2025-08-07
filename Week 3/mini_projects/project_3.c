#include <display.h>
#include <ADCLib.h>
#include <usart.h>
#include <avr/io.h>
#include <util/delay.h>

void setup()
{
    initDisplay();
    initUSART();
    enableADC();
    enableAutoSampling();
}

void loop()
{
    uint16_t value = ADC;
    writeNumberAndWait(value, 20);
}

int main()
{
    setup();

    while (1)
    {
        loop();
    }
}
