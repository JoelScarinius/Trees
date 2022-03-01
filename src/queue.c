#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

static int n = 0;

Minheap *create_heap() { // Creates the heap where tasks will be stored.
    Minheap *h = (Minheap*)malloc(sizeof(Minheap)); // Allocates memmory on the heap for the heap;
    // Minheap *h = malloc(sizeof(int)*MAX); // Allocates memmory on the heap for the heap;
    if (h == NULL) { // If memory wasn't possible to allocate for any reason.
        puts("Failed to allocate memory on the heap!");
        exit(-1);
    }
    for (size_t i = 0; i < MAX; i++) h->heap[i] = 0;
    return h;
}

int insert_heap(Minheap *h, Task *t) { // Inserts a task at the end of the heap.
    int pos;
    if (n == MAX) return 0; // Heap is full.
    else {
        n =+ n;
        pos = n;
        h->t = t; // Känns mer rätt men vetifan hur det ska placera min task i arrayen?
        h->heap[pos] = h->t->pages; // Vetifan hur jag ska använda mig av arrayen men paus nu tror jag.
        while (pos < 1) {
            int par = pos % 2;
            if (h->heap[pos] <= h->heap[par]) return 1; // Task was inserted to heap.
            else { // Swaps the inserted value with the parents value.
                int temp = h->heap[pos];
                h->heap[pos] = h->heap[par];
                h->heap[par] = temp;
                pos = par;
            }
        }
    }
    return 1;
}

int delete_heap(Minheap *h) { // Delete a task from the heap.
    if (is_empty == 1) return 0;
    else {
        int ptr = 0, left = 1, right = 2;
        int last = h->heap[n];
        n =- n;
        h->heap[ptr] = last;
        while (left <= n) {
            if (h->heap[ptr] >= h->heap[left] && h->heap[ptr] >= h->heap[right]) return 1;
            if(h->heap[right] <= h->heap[left]) {
                int temp = h->heap[ptr];
                h->heap[ptr] = h->heap[left];
                h->heap[left] = temp;
                ptr = left;
            }
            else {
                int temp = h->heap[ptr];
                h->heap[ptr] = h->heap[right];
                h->heap[right] = temp;
                ptr = right;
            }
            left = 2 * ptr;
            right = left + 1;
        }
    }
    return 1;
}

Task *findmin(Minheap *h) {
    if (is_empty == 1) return NULL;
    else {
        for (size_t i = 0; i < MAX; i++) {
            int minPages = (h->heap[i] < minPages) ? h->heap[i] : minPages;
        }
    }
    Task *t; // Vet inte än hur jag ska göra här...
    return t;
}

void destroy_heap(Minheap *h) {
    free(h);
    if (h != NULL) {
        puts("failed to destroy heap");
    }
}

void display_heap(Minheap *h) { // Displays all the tasks in the heap.
    if(is_empty(h) == 1) puts("HEAP IS EMPTY");
    else {
        puts("TASKS IN HEAP:");
        for(size_t i; i < MAX; i++) {
            printf("TASK [arravies at %d second, %d pages]\n", h->t->time_stamp, h->t->pages);
        }
        printf("TASK [arravies at %d second, %d pages]\n", h->t->time_stamp, h->t->pages);
    }
}

int is_empty(Minheap *h) { // Checks whether the heap is empty
    return (h->heap[0] == 0) ? 1 : 0;
}