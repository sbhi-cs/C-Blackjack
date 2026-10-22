#include <stdio.h>
#include <windows.h>

// THIS PROGRAM IS A TEST FOR THE CARD ART
// CARD ART WILL BE IMPLEMENTED IN blackjack.c LATER
// THIS IS JUST A TEST FOR ME TO SEE ALL THE CARD ART AND HOW IT WORKS
// 10 WILL STAY AS 10 ON CARD ART WHEN IMPLEMENTED IN BLACKJACK.C

int main(void)
{

    SetConsoleOutputCP(CP_UTF8);
    int suitnum = 6;
    int displaynum = 15;

    while(displaynum > 13)
    {
        printf("What value? (J Q K = 11 12 13) ");
        scanf("%i", &displaynum);
    }
    while(suitnum > 3)
    {
        printf("What suit? (CHSD, 0 = clubs ...) ");
        scanf("%i", &suitnum);
    }

    char *suitsymbols[4] = {"\u2663", "\u2665", "\u2660", "\u2666"};
    char displayvalues[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    // 'T' means 10 but 10 isnt a char so i cant use it

    printf(" ┌───────┐ \n │ %c     │\n │   %s   │ \n │     %c │ \n └───────┘ \n", displayvalues[displaynum-1], suitsymbols[suitnum], displayvalues[displaynum-1]);
}