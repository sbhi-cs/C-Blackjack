#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// struct definitions
typedef struct card 
{
    // creates a struct for all the cards
    int value;
    char suit;
    bool isdealt;
} card;

// function prototypes
void printdeck(card *deck);

void swap(card *a, card *b);

void shuffle(card *deck);

int main(void)
{
    // define constant values
    #define decksize 52
    #define suitcount 4
    #define valcount 13
    #define loop 1

    // define arrays for the suits and values of each card
    char suits[suitcount] = {'c', 'h', 's', 'd'}; // MAYBE CHANGE THESE TO ACTUAL SUIT SYMBOLS FOR OUTPUT STUFF ♠ ♣ ♥ ♦
    int values[valcount] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    // 1 = ace, 11 = jack, 12 = queen, 13 = king (i know their values are 10 in the actual game)

    // define all cards and null check
    card *cards = malloc(decksize * sizeof(card));
    if(cards == NULL)
    {
        return 1;
    }

    // give values to all cards (ace of clubs to king of diamonds)
    for(int i = 0; i < decksize; i++)
    {
        cards[i].suit = suits[i % 4];
        cards[i].value = values[i / 4];
        cards[i].isdealt = true;
    }

    // shuffles the cards based on the written function
    shuffle(cards);

    while(loop == 1)
    {
        // gets user input to start game
        char gamecheck;
        printf("Play a game of Blackjack? (Y/N) ");
        scanf("%c", &gamecheck);
        // the while clears out any extra characters if the user is stupid and types more than one char
        while(getchar() != '\n');

        // checks if user wants to play game or not, or just types some random bs
        if(gamecheck == 'y' || gamecheck == 'Y')
        {
            printf("game still under construction gng\n");
            return 2; // remove this line when you actually make the program for the game
            // CONTINUTE WRITING CODE HERE THIS IS WHERE THE ACTUAL GAME WILL TAKE PLACE
            // TODO: MAKE THE GAME, ADD SPLIT MAYBE, ADD CARD ART
        }
        else if(gamecheck == 'n' || gamecheck == 'N')
        {
            printf("Closing game, Money will not save\n");
            break;
        }
        else
        {
            printf("bro are you slow its Y or N not whatever the hell else\n");
            continue;
        }

    }

    free(cards);
    return 0;

}

void printdeck(card *deck)
{
    for(int i = 0; i < decksize; i++)
    {
        printf("%i of %c\n", deck[i].value, deck[i].suit);
    }
}

void swap(card *a, card *b)
{
    // this function swaps two cards, which is used in the shuffle function
    card temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(card *deck)
{
    // this function shuffles the cards
    srand(time(NULL));

    // shuffle 3 times to be extra safe
    for(int j = 0; j < 3; j++)
    {
        // this is the Fisher-Yates shuffle algorithm
        // i may or may not have taken this from a website
        for(int i = decksize-1; i > 0; i--)
        {
            int j = rand() % i;
            swap(&deck[i], &deck[j]);
        }
    }
}
