// CSCI 2530
// Assignment: 8
// Author:     Ketu Patel
// File:       trace.h
// Tab stops:  4

#ifndef trace_h
#define trace_h

#include "tree.h"

extern int tracelevel;

// Function prototypes

void setTracing(int argc, char** argv);
void showFrequencies(int* arr);
void showChar(char b);
void spaceChar(int n);
void showTree(Tree b);
void showCode(char** code);

#endif
