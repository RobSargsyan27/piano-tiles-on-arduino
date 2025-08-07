#include <stdio.h>
#include <usart.h>

double pow2(const double *number)
{
    return *number * *number;
}

int main()
{
    int var =  5;
    initUSART();
    printf("Power 2 of 5 is %d", pow2(&var));
    return 0;
}