#include <usart.h>

#define MAX 5
#define SEVENFOLD(number) (number * 7);


void makeArray(int* arrayPointer)
{
    for(int i = 0; i < MAX; i++)
    {
        *(arrayPointer + i) = SEVENFOLD(i);
    }
}

void printArray(int* arrayPointer)
{
    for(int i = 0; i < MAX; i++)
    {
        printf("Address: %p has value: %d\n", (void*)(arrayPointer + i), *(arrayPointer + i));
    }
}

int main()
{
    initUSART();

    int array[5] = {0};

    printf("Content of array: \n");
    printArray(array);
    printf("Content of array: \n");
    makeArray(array);
    printArray(array);

}