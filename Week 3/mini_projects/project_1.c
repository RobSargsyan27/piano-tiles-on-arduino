#include <display.h>
#include <usart.h>


void setup()
{
    initDisplay();
}

void loop()
{
    for(int i = 0; i < 10; i++)
    {
        char numberToDisplay[4];
        for(int j = 0; j < 4; j++)
        {
            if(i + j > 9)
            {
                numberToDisplay[j] = i + j - 10 + '0';
            }else
            {
                numberToDisplay[j] = i + j + '0';
            }
        }
        writeStringfyNumberAndWait(numberToDisplay, 300);
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