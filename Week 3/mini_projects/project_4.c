#include <usart.h>
#include <stdlib.h>
#include <string.h>

int main(){
    initUSART();

    char** pointer = calloc(100, sizeof(char*));
    char* string = malloc(sizeof("I am not allowed to speak in class."));
    strcpy(string, "I am not allowed to speak in class.");

    for(int i = 0; i < 100; i++)
    {
        pointer[i] = string;
    }

    for(int i = 0; i < 100; i++)
    {
        printf("%d: %s\n", i, pointer[i]);
    }

    free(string);
    free(pointer);
}