#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// struct definitions
typedef struct card 
{
    // creates a struct for all the cards
    int value;
    char *suit;
    // TODO: add suit symbol
    bool isdealt;
} card;

typedef struct hand
{
    card cardsinhand[7]; // yes I know this line is poorly written but i am not tryna make a dynamic array rn especially in a struct
    int cardamount;
} hand;

// constant values
#define decksize 52
#define suitcount 4
#define valcount 13
#define loop 1

// function prototypes
void printdeck(card *deck);

void swap(card *a, card *b);

void shuffle(card *deck);

int hit(card *deck, int cardamnt, hand *userhand);

int main(void)
{
    // define arrays for the suits and values of each card
    char *suits[suitcount] = {"Clubs", "Hearts", "Spades", "Diamonds"}; // MAYBE CHANGE THESE TO ACTUAL SUIT SYMBOLS FOR OUTPUT STUFF ♠ ♣ ♥ ♦
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
        cards[i].isdealt = false;
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
            hand *player = malloc(sizeof(hand)); // REMEMBER TO FREE!!! IMPORTANT
            if(player == NULL)
            {
                free(cards);
                return 1;
            }
            player->cardamount = 0;

            printf("\033[2J\033[H"); 
            fflush(stdout); // clears command line like CTRL + L
            printf("press q to quit\n");
            
            while(loop == 1)
            {
                char input[10];
                    player->cardamount = hit(cards, player->cardamount, player);
                    printf("the %ist card in your hand is the: %i of %s\n", player->cardamount, player->cardsinhand[0].value, player->cardsinhand[0].suit);
                    player->cardamount = hit(cards, player->cardamount, player);
                    printf("the %ind card you have in your hand is the: %i of %s\n", player->cardamount, player->cardsinhand[1].value, player->cardsinhand[1].suit);
                    printf("Action (Hit or Stand): ");
                    scanf("%s", input);
                    return 2;
                    // this is just a test program for now i'll write the actual deal program tmr
                    // the hit func works, so it gives out the first non-dealt card from the shuffled deck :D
                    // btw 1 is ace, 11 is jack, 12 is queen, 13 is king, ill make them actual values later
            }
        }
        else if(gamecheck == 'n' || gamecheck == 'N')
        {
            printf("Closing game, Money will not save\n");
            break;
        }
        else
        {
            printf("Bro just type Y or N not whatever the hell\n");
            continue;
        }

    }

    free(cards);
    return 0;

}


// ---FUNCTION DEFINITIONS---


void printdeck(card *deck)
{
    for(int i = 0; i < decksize; i++)
    {
        printf("%i of %s\n", deck[i].value, deck[i].suit);
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

int hit(card *deck, int cardamnt, hand *userhand)
{
    for(int i = 0; i < decksize; i++)
    {
        if(deck[i].isdealt == true)
        {
            continue;
        }
        userhand->cardsinhand[cardamnt] = deck[i];
        deck[i].isdealt = true;
        cardamnt++;
        return cardamnt;
    }
    return cardamnt;
}

void deal(card *deck, int cardamnt,  hand userhand)
{
    return; //do this in a sec
    // literally just hit but twice and only used at the start of the game to deal cards
}