// CSCI 2530
// Assignment: 8
// Author:     Ketu Patel
// File:       trace.cpp
// Tab stops:  4

/*
 * This module provides tracing which is enabled whenever the user enters 't'
 * in the command line.
 *
 */

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <iomanip>
#include <cctype>
#include "trace.h"

using namespace std;

int tracelevel = 0;

/**
 * setTracing(argc, argv) sets variable to 1 if '-t' is entered in
 * the command line.
 */

void setTracing(int argc, char** argv)
{
    int i;

    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0) 
	{
            tracelevel = 1;
        }
    }
}

/**
 * showFrequencies(array) shows the frequencies of characters in the
 * array 'arr' that occur at least once.
 */

void showFrequencies(int* array)
{
    if(array != NULL)
    {
        printf("\nThe character frequencies are:\n"); 

        for (int i = 0; i < 256; i++)
        {
            if (array[i] > 0)
            {
	       printf("      ");
               printf("      ");
               showChar(i);

               printf("      ");
	       printf("%i\n", array[i]);

            }
        }
    }
}

/**
 * showChar(b) prints the character name that go with 'b'
 * to the standard output.
 */

void showChar(char b)
{
    int ch = (int) b;

    if (isspace(ch))
    {
      spaceChar(ch);
    }
  	 else if (isprint(ch))
    {
        printf("%c",(unsigned char) b);
    }
    else
    {
        printf("%c", b );
	
   }
}

/**
 * spaceChar(n) checks if parameter 'n' is a space character, and when it is,
 * it prints the type of space character to the output. 
 */

void spaceChar(int n)
{

	if 	(n == ('\n'))
	{
		printf("newline");
	}
	
	else if (n == (' '))
	{
		printf("space");
	
	}

    	else if (n == ('\t'))
	{
		printf("tab");

	}

	else
	{
   	        printf( "spaceChar");
   
    	}
}

/**
 * showTree(b) prints the character tree contained in tree 'b' to the standard
 * output.
 *
 */

void showTree(Tree b)
{
    if(b->kind == leaf)
    {
        showChar(b->ch);
    }
    else
    {
        printf("(");
        showTree(b->left);
        printf(" , ");
        showTree(b->right);
        printf(")");
    }
}

/**
 * showCode(code) displays the huffman code of each character that is
 * present inside the array 'code'.
 */

void showCode(char* code[])
{


    if(code != NULL) 
	{
        
	printf("\n\nThe huffman code is as follows: \n\n"); 

        for (int i = 0; i < 256; i++) 
	{
            if (code[i] != NULL) 
	    {
             
                showChar(i);
		
		printf(": ");

		printf("%s \n", code[i]);
            }
        }
    }
}
