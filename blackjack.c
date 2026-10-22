#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <locale.h>
#endif

// struct definitions
typedef struct card 
{
    // creates a struct for all the cards
    int value;
    char displayvalue;
    char *suit;
    char *suitsym;
    bool isdealt;
} card;

typedef struct hand
{
    // creates a struct for player and enemy hands
    card cardsinhand[7]; // yes I know this line is poorly written but i am not tryna make a dynamic array rn especially in a struct
    int cardamount;
    int totalvalue;
} hand;

// constant values
#define decksize 52
#define suitcount 4
#define valcount 13
#define loop 1

// function definition to set terminal
void set_terminal(void)
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #else
        setlocale(LC_ALL, "");
    #endif // allows unicode printing on terminal on all OS
}

// function prototypes
void printdeck(card *deck);

void swap(card *a, card *b);

void shuffle(card *deck);

int hit(card *deck, int cardamnt, hand *userhand);

int main(void)
{
    set_terminal(); // calls function to allow unicode printing in terminal
    
    // define arrays for the suits and values of each card
    char *suits[suitcount] = {"Clubs", "Hearts", "Spades", "Diamonds"}; // MAYBE CHANGE THESE TO ACTUAL SUIT SYMBOLS FOR OUTPUT STUFF ♠ ♣ ♥ ♦
    char *suitsymbols[suitcount] = {"\u2663", "\u2665", "\u2660", "\u2666"};
    char displayvalues[valcount] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
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
        cards[i].suitsym = suitsymbols[i % 4];
        cards[i].value = values[i / 4];
        cards[i].displayvalue = displayvalues[i/4];
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
            char input[10];

            printf("\033[2J\033[H"); 
            fflush(stdout); // clears command line like CTRL + L
            printf("press q to quit\n");

            player->cardamount = hit(cards, player->cardamount, player);
            player->cardamount = hit(cards, player->cardamount, player); // deals the cards

            while(loop == 1)
            {
                player->totalvalue = 0;
                printf("\033[2J\033[H");
                fflush(stdout); // clear cli

                // prints all cards
                printf("Your cards are:\n");
                for(int i = 0; i < player->cardamount; i++)
                {
                    if(player->cardsinhand[i].displayvalue == 'T')
                    {
                        printf("%i %s\n", player->cardsinhand[i].value, player->cardsinhand[i].suitsym); // since we want to display 10 as "10" and not as "T"
                    }
                    else
                    {
                        printf("%c %s\n", player->cardsinhand[i].displayvalue, player->cardsinhand[i].suitsym);
                    }
                }

                for(int i = 0; i < player->cardamount; i++)
                {
                    if(player->cardsinhand[i].value > 10)
                    {
                        player->totalvalue += 10;
                    }
                    else
                    {
                        player->totalvalue += player->cardsinhand[i].value;
                    }
                } // adds up total card value and sets j q and k to 10

                for(int i = 0; i < player->cardamount; i++)
                {
                    if(player->cardsinhand[i].value == 1 && (player->totalvalue+10) <= 21)
                    {
                        player->totalvalue += 10;
                    } // aces either become 1 or 11 depending on whats better
                }
                printf("Hand Value: %i\n", player->totalvalue); // print players hand value for QoL
            
                // checks if player went over 21 or got a blackjack    
                if(player->totalvalue > 21)
                {
                    printf("Bust! You lost D:\n"); // change this when adding money system
                    return 0; // maybe change this later to ask restart game (unless no money system)
                }
                else if(player->totalvalue == 21)
                {
                    printf("Blackjack! You won! :D\n");
                    free(player);
                    free(cards);
                    return 0;
                    // add option to play again (unless no money system)
                }

                // --SCANF in COMMAND LINE LOOP

                printf("Action (Hit or Stand): ");
                scanf("%s", input); // add case for if they type anything but hit or stand

                if(strcmp(input, "hit") == 0 || strcmp(input, "Hit") == 0 || strcmp(input, "HIT") == 0) // case where user hits for another card
                {
                    player->cardamount = hit(cards, player->cardamount, player);
                }
                else if(strcmp(input, "stand") == 0 || strcmp(input, "Stand") == 0 || strcmp(input, "STAND") == 0)
                {
                    printf("You ended with a %i", player->totalvalue); // change this when you add a dealer ai to see if you win or lose
                    free(player);
                    free(cards);
                    return 0;
                }
                // TODO: ADD ENEMY DEALER AI

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