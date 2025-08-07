#include <usart.h>
#include <stdlib.h>
#include <string.h>

int storage = 0;

char* enhancedMalloc(long size)
{
    storage += size;
    return malloc(size);
}

char** enhancedCalloc(long size, int nitems)
{
    storage += size * nitems;
    return calloc(nitems, sizeof(char*));
}

int main(){
    initUSART();

    char** pointer = enhancedCalloc(sizeof(char*), 100);
    char* string = enhancedMalloc(sizeof("I am not allowed to speak in class."));
    strcpy(string, "I am not allowed to speak in class.");

    for(int i = 0; i < 100; i++)
    {
        pointer[i] = string;
    }

    for(int i = 0; i < 100; i++)
    {
        printf("%d: %s\n", i, pointer[i]);
    }

    printf("Storage: %d", storage);
    free(string);
    free(pointer);
}