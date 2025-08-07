#include <stdlib.h>
#include <usart.h>
#include <string.h>

typedef struct
{
    int value;
    char* suit;
}CARD;

void checkMemoryAllocation(void* pointer)
{
    if(pointer == NULL)
    {
        printf("Error occurred while allocating a memory");
    }
}

void fullDeck(CARD* deck)
{
    char suits[4][10] = {"hearts", "diamonds", "spades", "clubs"};
    int index;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            index = (i * 13) + j;
            deck[index].suit = malloc(strlen(suits[i]) + 1);
            checkMemoryAllocation(deck[index].suit);

            strcpy(deck[index].suit, suits[i]);
            deck[index].value = j + 1;
        }
    }
}

void showCard(CARD* theCard)
{
    switch (theCard->value)
    {
    case 1:
        printf("ace of %s", theCard->suit);
        break;
    case 11:
        printf("jack of %s", theCard->suit);
        break;
    case 12:
        printf("queen of %s", theCard->suit);
        break;
    case 13:
        printf("king of %s", theCard->suit);
        break;
    default:
        printf("%d of %s", (*theCard).value, theCard->suit);
    }
}

//BEWARE: the return value is a pointer!
CARD* drawCard(CARD* deck)
{
    int randm = rand() % 52;
    return &deck[randm];
}

int main()
{
    initUSART();
    //TODO: use calloc to make the deck of cards
    CARD* deck = calloc(4 * 13, sizeof(CARD));
    fullDeck(deck);

    //TODO: update the following code so that it compiles
    for (int i = 0; i < 10; i++)
    {
        CARD* cardPtr = drawCard(deck);
        showCard(cardPtr);
        printf("\n");
    }

    //TODO: free all allocated memory:
    for(int i = 0; i < 4 * 13; i++)
    {
        free(deck[i].suit);
    }
    free(deck);
    return 0;
}
