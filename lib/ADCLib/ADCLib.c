#include <ADCLib.h>

#include <avr/io.h>

void enableADC()
{
    ADMUX |= ( 1 << REFS0); //sets reference volatage
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); //sets prescaler
    ADCSRA |= (1 << ADEN); // enables ADC
}

void enableAutoSampling()
{
    ADCSRA |= (1 << ADATE); //enables auto sampling
    ADCSRB = 0; //Trigger mode is set to free mode
    ADCSRA |= (1 << ADSC); // Turns the ADC sampling on
}