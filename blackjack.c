// BIG IMPORTANT NOTE: THERE ARE 2 MAJOR ISSUES WITH THIS CODE THAT I SHOULD FIX NEXT SESSION
// 1. ABSTRACT THAT STRING OF CODE THAT RESTARTS THE GAME, ITS MAKING THE CODE TOO LONG AND UNREADABLE
// 2. WHEN THAT'S DONE, FIX IT SO THAT WHEN THE DEALER BUSTS AFTER YOU STAND WE GET TO SEE OUR VALUE COMPARED TO HIS VALUE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // for online compiler compatibility
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
    // yes I know this line is poorly written but i am not tryna make a dynamic array rn especially in a struct
    int cardamount;
    card cardsinhand[9]; 
    int totalvalue;
    bool standstatus;
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

int gethandval(hand *userhand);

void dealerplay(hand *dealerhand, card *deck);

bool rescheck(char restartcheck);

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
            char name[50];
            printf("Dealer's name (ONE WORD): ");
            scanf("%s", name);

            hand *player;
            hand *dealer;

            printf("\033[2J\033[H"); 
            fflush(stdout); // clears command line like CTRL + L

            gamerestart: ; // marker to send user to if they want to play again

            if(cards[40].isdealt == true)
            {
                for(int i = 0; i < decksize; i++)
                {
                    cards[i].isdealt = false;
                }
                shuffle(cards);
            }

            player = malloc(sizeof(hand)); // initializes the players hand
            if(player == NULL)
            {
                free(cards);
                return 1;
            }
            dealer = malloc(sizeof(hand)); // initializes the dealers hand
            if(dealer == NULL)
            {
                free(cards);
                free(player);
                return 1;
            }

            player->cardamount = 0;
            dealer->cardamount = 0;
            player->standstatus = false;
            dealer->standstatus = false;
            char input[10];

            printf("\033[2J\033[H"); 
            fflush(stdout); // clears command line like CTRL + L
            printf("press q to quit\n");

            player->cardamount = hit(cards, player->cardamount, player);
            player->cardamount = hit(cards, player->cardamount, player); // deals the cards to the user
            dealer->cardamount = hit(cards, dealer->cardamount, dealer);
            dealer->cardamount = hit(cards, dealer->cardamount, dealer); // deals cards to the dealer

            while(loop == 1)
            {
                player->totalvalue = 0;
                dealer->totalvalue = 0;
                input[1] = '\0';

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

                player->totalvalue = gethandval(player);
                printf("Hand Value: %i\n", player->totalvalue); // print players hand value for QoL

                // checks if player went over 21 or got a blackjack    
                if(player->totalvalue > 21)
                {
                    char restartinput = '\0';
                    printf("Bust! You lost D:\n"); // change this when adding money system
                    free(player);
                    free(dealer);
                    
                    bool restartcheck;

                    while(loop == 1)
                    {
                        printf("Play again? (Y/N) ");
                        scanf(" %c", &restartinput);
                        while(getchar() != '\n');
                        restartcheck = rescheck(restartinput);
                        if(restartcheck == true || restartcheck == false)
                        {
                            break;
                        }
                    }
                    if(restartcheck == true)
                    {
                        goto gamerestart; // go back to the memory allocation definitions
                    }
                    else if(restartcheck == false)
                    {
                        goto endofcode; // go to end of program and close program if user tired of blackjack
                    }
                }
                else if(player->totalvalue == 21)
                {
                    char restartinput = '\n';
                    printf("Blackjack! You won! :D\n");
                    free(player);
                    free(dealer);

                    bool restartcheck;
                    
                    while(loop == 1)
                    {
                        printf("Play again? (Y/N) ");
                        scanf(" %c", &restartinput);
                        while(getchar() != '\n');
                        restartcheck = rescheck(restartinput);
                        if(restartcheck == true || restartcheck == false)
                        {
                            break;
                        }
                    }

                    if(restartcheck == true)
                    {
                        goto gamerestart;
                    }
                    else if(restartcheck == false)
                    {
                        goto endofcode;
                    }
                }
            

                printf("%s's cards are:\n", name);
                for(int i = 0; i < dealer->cardamount; i++)
                {
                    if(dealer->cardsinhand[i].displayvalue == 'T')
                    {
                        printf("%i %s\n", dealer->cardsinhand[i].value, dealer->cardsinhand[i].suitsym);
                    }
                    else if(dealer->cardamount == 2 && i == 1)
                    {
                        printf("?\n");
                    }
                    else
                    {
                        printf("%c %s\n", dealer->cardsinhand[i].displayvalue, dealer->cardsinhand[i].suitsym);
                    }
                }


                
                dealer->totalvalue = gethandval(dealer);
                if(dealer->cardamount == 2)
                {
                    printf("Hand value : ?\n");
                }
                else
                {
                    printf("Hand Value: %i\n", dealer->totalvalue); // print players hand value for QoL
                }
            
                // checks if dealer went over 21 or got a blackjack    
                if(dealer->totalvalue > 21)
                {
                    char restartinput = '\n';
                    printf("%s Busted! You won!\n", name); // change this when adding money system
                    free(player);
                    free(dealer);

                    bool restartcheck;
                    
                    while(loop == 1)
                    {
                        printf("Play again? (Y/N) ");
                        scanf(" %c", &restartinput);
                        while(getchar() != '\n');
                        restartcheck = rescheck(restartinput);
                        if(restartcheck == true || restartcheck == false)
                        {
                            break;
                        }
                    }

                    if(restartcheck == true)
                    {
                        goto gamerestart;
                    }
                    else if(restartcheck == false)
                    {
                        goto endofcode;
                    }
                }
                else if(dealer->totalvalue == 21)
                {
                    char restartinput = '\0';
                    printf("%s got a Blackjack! You Lost D:\n", name);
                    free(player);
                    free(dealer);

                    bool restartcheck;

                    while(loop == 1)
                    {
                        printf("Play again? (Y/N) ");
                        scanf(" %c", &restartinput);
                        while(getchar() != '\n');
                        restartcheck = rescheck(restartinput);
                        if(restartcheck == true || restartcheck == false)
                        {
                            break;
                        }
                    }

                    if(restartcheck == true)
                    {
                        goto gamerestart;
                    }
                    else if(restartcheck == false)
                    {
                        goto endofcode;
                    }                    
                }


                // --SCANF in COMMAND LINE LOOP

                if(player->standstatus == false)
                {
                    printf("Action (Hit or Stand): ");
                    scanf("%s", input); // add case for if they type anything but hit or stand
                }
                
                if(strcmp(input, "hit") == 0 || strcmp(input, "Hit") == 0 || strcmp(input, "HIT") == 0 || strcmp(input, "h") == 0 || strcmp(input, "H") == 0) // case where user hits for another card
                {
                    player->cardamount = hit(cards, player->cardamount, player);
                }
                else if(strcmp(input, "stand") == 0 || strcmp(input, "Stand") == 0 || strcmp(input, "STAND") == 0 || strcmp(input, "s") == 0 || strcmp(input, "S") == 0)
                {
                    printf("\033[2J\033[H");
                    fflush(stdout); // clear cli
                    player->standstatus = true;

                    while(dealer->standstatus == false)
                    {
                        dealer->totalvalue = 0;
                        gethandval(dealer);
                        dealerplay(dealer, cards);
                if(dealer->totalvalue > 21)
                {
                    char restartinput = '\n';
                    printf("%s Busted! You won!\n", name); // change this when adding money system
                    free(player);
                    free(dealer);

                    bool restartcheck;
                    
                    while(loop == 1)
                    {
                        printf("Play again? (Y/N) ");
                        scanf(" %c", &restartinput);
                        while(getchar() != '\n');
                        restartcheck = rescheck(restartinput);
                        if(restartcheck == true || restartcheck == false)
                        {
                            break;
                        }
                    }

                    if(restartcheck == true)
                    {
                        goto gamerestart;
                    }
                    else if(restartcheck == false)
                    {
                        goto endofcode;
                    }
                }
                else if(dealer->totalvalue == 21)
                {
                    char restartinput = '\0';
                    printf("%s got a Blackjack! You Lost D:\n", name);
                    free(player);
                    free(dealer);

                    bool restartcheck;

                    while(loop == 1)
                    {
                        printf("Play again? (Y/N) ");
                        scanf(" %c", &restartinput);
                        while(getchar() != '\n');
                        restartcheck = rescheck(restartinput);
                        if(restartcheck == true || restartcheck == false)
                        {
                            break;
                        }
                    }

                    if(restartcheck == true)
                    {
                        goto gamerestart;
                    }
                    else if(restartcheck == false)
                    {
                        goto endofcode;
                    }                    
                }
                    }

                    if(dealer->standstatus == true)
                    {
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
                        } // reveals the players cards
                        printf("Player's Final Value: %i\n", player->totalvalue); // reveals the players final value

                        for(int i = 0; i < dealer->cardamount; i++)
                        {
                            if(dealer->cardsinhand[i].displayvalue == 'T')
                            {
                                printf("%i %s\n", dealer->cardsinhand[i].value, dealer->cardsinhand[i].suitsym);
                            }
                            else
                            {
                                printf("%c %s\n", dealer->cardsinhand[i].displayvalue, dealer->cardsinhand[i].suitsym);
                            }
                        } // reveals the dealers cards
                        printf("%s's Final Value: %i\n", name, dealer->totalvalue); // reveals the dealers final value

                        if(player->totalvalue > dealer->totalvalue)
                        {
                            printf("You Won by Value! :D\n");
                        }
                        else if(dealer->totalvalue > player->totalvalue)
                        {
                            printf("You Lost by Value D:\n");
                        }
                        else
                        {
                            printf("You tied with %s!\n", name);
                        }
                        
                        free(player);
                        free(dealer);

                        char restartinput = '\0';
                        bool restartcheck;

                        while(loop == 1)
                        {
                            printf("Play again? (Y/N) ");
                            scanf(" %c", &restartinput);
                            while(getchar() != '\n');
                            restartcheck = rescheck(restartinput);
                            if(restartcheck == true || restartcheck == false)
                            {
                                break;
                            }
                        }

                        if(restartcheck == true)
                        {
                            goto gamerestart;
                        }
                        else if(restartcheck == false)
                        {
                            goto endofcode;
                        }
                    }
                }
                else
                {
                    continue;
                }

            }
        }
        else if(gamecheck == 'n' || gamecheck == 'N')
        {
            break;
        }
        else
        {
            printf("Bro just type Y or N not whatever the hell\n");
            continue;
        }

    }


    endofcode: ; // marker to send people to if they dont want to play blackjack anymore
    printf("Closing game, Money will not save\n"); // change this when adding a wallet system
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
            int k = rand() % (i + 1);
            swap(&deck[i], &deck[k]);
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

int gethandval(hand *userhand)
{
    for(int i = 0; i < userhand->cardamount; i++)
    {
        if(userhand->cardsinhand[i].value > 10)
        {
            userhand->totalvalue += 10;
        }
        else
        {
            userhand->totalvalue += userhand->cardsinhand[i].value;
        }
    } // adds up total card value and sets j q and k to 10

    for(int i = 0; i < userhand->cardamount; i++)
    {
        if(userhand->cardsinhand[i].value == 1 && (userhand->totalvalue+10) <= 21)
        {
            userhand->totalvalue += 10;
        } // aces either become 1 or 11 depending on whats better
    }
    return userhand->totalvalue;
}

void dealerplay(hand *dealerhand, card *deck)
{
    if(dealerhand->totalvalue < 17)
    {
        dealerhand->cardamount = hit(deck, dealerhand->cardamount, dealerhand);
    }
    else
    {
        dealerhand->standstatus = true;
    }
    return;
}

bool rescheck(char restartcheck)
{
    if(restartcheck == 'y' || restartcheck == 'Y')
    {
        return true;
    }
    else if(restartcheck == 'n' || restartcheck == 'N')
    {
        return false;
    }
}