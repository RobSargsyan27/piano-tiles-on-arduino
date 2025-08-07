#include <display.h>

void setup()
{
    initDisplay();
}

void loop()
{
    writeString("EASY");
}

int main()
{
    setup();

    while (1)
    {
        loop();
    }
}