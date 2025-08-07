#include <string.h>
#include <usart.h>

#define MAX 7

void printFirstLetters(char (*names)[MAX][10])
{
    for(int i = 0; i < MAX; i++)
    {
        printf("%c", (*names)[i][0]);
    }
}

void printLastLetters(char (*names)[MAX][10])
{
    for(int i = 0; i < MAX; i++)
    {
        for(int j = 0; (*names)[i][j] != '\0'; j++)
        {
            if((*names)[i][j+1] == '\0')
            {
                printf("%c", (*names)[i][j]);
            }
        }
    }
}

void enhancedPrintLastLetters(char (*names)[MAX][10])
{
    for(int i = 0; i < MAX; i++)
    {
        printf("%c", (*names)[i][strlen((*names)[i]) - 1]);
    }
}


int main()
{
    initUSART();
    char names[MAX][10] = {"Abo", "Avo", "Bobo", "Bgo", "Hamo", "Tiko", "Sargis"};
    char (*namesPointer)[MAX][10] = names;
    enhancedPrintLastLetters(namesPointer);
}