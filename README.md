# C-Blackjack

This is my C Blackjack Game!!

It plays like a normal game of blackjack, but without the betting (you just play some cards and thats it lol)
You can play over and over again! Perfect for if you are doing something but are bored!
This entire game was written in C, and runs on the command line. Here's how to play:

## If you don't feel like downloading a C compiler (It's a lot of work, I understand):
    - Copy all the code found in the file "blackjack.c"
    - Paste it into this link "<https://onecompiler.com/c>"
    - Press run!
    - This method has a few visual bugs, since the program was made for the command line, and not an online compiler

## If you really want to play this on your command line:
    Download the folder off of github, and save it in a place you know you can find it
    Download a C compiler:
        Windows: Use this tutorial: https://www.msys2.org/
        Mac: In the terminal, paste the command "xcode-select --install"
        Linux: It depends on your distro, I reccomend googling it

    In the terminal, use the "cd" command to go to the exact folder you stored the code 
    (ex: cd users\name\documents\blackjackcode)
    You can also do this step one folder at a time instead 
    (ex: cd documents then cd blackjackcode)

    Now, you can run the program!
    On Windows: 
    Paste into terminal: gcc blackjack.c -o blackjack
    Type: blackjack

    On Mac: 
    Paste into terminal: clang blackjack.c -o blackjack
    Type: ./blackjack

    On Linux:
    Paste into terminal: gcc blackjack.c -o blackjack
    Type: ./blackjack

    P.S: I'm not too sure if my info for Mac is correct since I've never used Mac. 
    Please notify me if anything is incorrect here

## **BOOM!** Now you can play blackjack on your command line!

## How to play blackjack (if you don't know):
* Each card has a value based on its number (Jack Queen and King are all worth 10)
* Aces are worth either 1 or 11
* You have 2 options: Hit and Stand
* Hitting means drawing another card
* Standing means locking in all your cards
* You have to keep drawing cards (hitting) and get your hand value as close to 21 as possible
* If you don't want to draw anymore (for safety), you stand
* If you go over 21, you lose! (bust)
* If you reach exactly 21, you win! (blackjack)
* When both parties stand, theres a showdown!
* The player closest to 21 without going over wins!
* (Unfortunately, betting, doubledown, and splitting isn't in this version)

## This game features:
* ASCII Card Art
* Replayability
* A dealer AI that YOU CAN NAME!!!

JUST LOOK AT THIS COOL ART!

<img width="307" height="357" alt="image" src="https://github.com/user-attachments/assets/2b02c861-261a-40ea-930e-6c90264ac976" />


## Inside this folder, there is:
* Main blackjack program, which is what you will be running to play the game
* Card art program (cardart.c), you can compile and get any card you want on the terminal!
    
## When playing, put your terminal in full screen for the best experience!
## Hope you have fun!
