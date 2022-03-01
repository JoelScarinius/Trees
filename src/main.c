#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "task.h"
#include "queue.h"
#include "printer.h"

// #define SECPERTASK 2 // On average there will be one print task in 2 seconds.

static void printWelcomeMessage(); // This function prints a short welcome message.

void main() { 
    printWelcomeMessage(); // Prints welcome message to the screen.
    srand(time(NULL)); // Seeds the random function to not create the same sequences.
    int ct = 1; // Variable used to display current time in second.
    Printer *p = (Printer*)malloc(sizeof(Printer)); // Allocates memory for the printer.
    p->page_rate = 60; // One page per second.
    Minheap *h = create_heap();
    // Task *t = NULL;
    Task *t = create_task(ct);
    int flag = insert_heap(h, t);
    (flag == 0) ? puts("Heap is full") : puts("Insertion was successful");
    // p->time_remaining = 0; // Sets remaining time to 0 to kick of the printer simulation.
    // while (ct != 10) { // Loops until current time has reached 10 seconds
    //     printer_status(p); // Displays the printers status to the screen.
    //     if ((1 + rand() % 10) > 5 || ct == 1) { // 50/50 chans to create a task, but always creates a task at first iteration.
    //         t = create_task(ct); // Creates a new task.
    //         // Puts the new task in the end of the queue.
    //     }
    //     if (p->time_remaining > 0) printf("%d seconds to complete the current task\n", p->time_remaining);
    //     // Displays the entire queue.
    //     if (is_empty(h) == 0 && is_busy(p) == 0) { // If the queue isn't empty and the printer isn't busy dequeue and start task.
    //          // Deletes the first task from the queue.
    //         start_next(p, t); // Starts printing the task that was deleted from the queue.
    //         p->time_remaining = t->pages + SECPERTASK; // Initialize time remaining with proper time in seconds to preform task.
    //     }
    //     if (p->time_remaining > 0) tick(p); // Decrement the remaining time with 1 second.
    //     ct++; // Increment current time by 1 second.
    // }
    puts("\nSIMULATION ENDS");
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