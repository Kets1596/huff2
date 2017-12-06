// CSCI 2530
// Assignment: 8
// Author:     kETU PATEL
// File:       pqueue.h
// Tab stops:  4

#ifndef pqueue_h
#define pqueue_h

#include <cstdio>
#include "tree.h"

// Type definitions.

typedef Tree PQItemType;
typedef int  PQPriorityType;

typedef void (ItemPrinter)(PQItemType);
typedef void (PriorityPrinter)(PQPriorityType);

// Structures.

struct PQCell;

// Structure PriorityQueue holds a pointer to the PQCell linked list.
// By default it sets the pointer to null.

struct PriorityQueue {
    PQCell* toLinkedList; // pointer to linked list

    PriorityQueue() {
        toLinkedList = NULL;
    }
};

// Function Prototypes

bool isEmpty(const PriorityQueue& q);
void insert(PriorityQueue& q, PQItemType item, PQPriorityType pri);
void remove(PriorityQueue& q, PQItemType& item, PQPriorityType& pri);
void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi,
                        PriorityPrinter pp);

#endif /* pqueue_h */
