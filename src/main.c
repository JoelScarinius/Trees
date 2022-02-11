#include <stdio.h> SIDAN 321 i I BOKEN BESKRIVER BINARY SEARCHTREES.

#define SECPERTASK 2 // On average there will be one print task in 2 seconds.

static void printWelcomeMessage(); // This function prints a short welcome message.

void main() { 
    printWelcomeMessage(); // Prints welcome message to the screen.
    
    fflush(stdin);
    getchar();
}
static void printWelcomeMessage() { // Prints welcome message to the screen.
    puts("****************************************************************************************************\n"
        "Welcome!\n"
        "This is a program that uses a queue implemented as a linkedlist to create a simulation of a printer.\n"
        "Please enjoy!\n"
        "****************************************************************************************************");
}