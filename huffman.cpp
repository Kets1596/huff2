// CSCI 2530
// Assignment: 8
// Author:     Ketu Patel
// File:       huffman.cpp
// Tab stops:  4

// This module uses huffman algorithm to create a huffman tree based on input
// file given from command line. It also includes the tracing ability which can
// be turned off or on from the command line.


#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "trace.h"
#include "tree.h"
#include "binary.h"
#include "pqueue.h"


using namespace std;

// Function prototypes

void setFreqs(int* arr);
bool freqsCount(int *arr, int argc, char **argv);
void readFile(FILE* f, int* array);
Tree huffmanTree(int *array);
void insertToQueue(PriorityQueue& q, int* charArray);
Tree huffTreeHelper(PriorityQueue &q);
void codeBuilder(Tree t, char** code, const char* prefix);
void setArrayToNull(char** code);
void writeTreeBinary(BFILE* f, Tree t);
void encodeChar(char** code, BFILE* b, const char* inputF);
void encodeCharHelper(BFILE* write, char** code, int x);

const int maxChars = 256;

// setFreqs(array) sets all of the character frequencies to zero.

void setFreqs(int* array) 
{
	for(int i = 0; i < maxChars; i++) 
	{
		array[i] = 0;
	}
}

// readFile(f, array) reads characters from 'f' and increment their
// frequencies in 'array'.

void readFile(FILE* f, int* array)
{
	int ch = getc(f);

	while(ch != EOF)
	{
		array[ch]++;
		ch = getc(f);
	}
}

// freqsCount(array,argc,argv) counts the frequencies of characters  
// that occures in a given file. Also, returns true if it successfully open the file, and false
// otherwise.

bool freqsCount(int *array, int argc, char *argv[])
{

	setFreqs(array);
	
	FILE* f = fopen(argv[argc-2], "r");

	if(f == NULL)

	{
		return false;
	
	}

	else
	{

		readFile(f, array);

	}	


	fclose(f);
	return true;

}


//huffmanTree(array) returns the huffman tree of all the available characters
// in the 'array'.

Tree huffmanTree(int *array)
{

	PriorityQueue queue = PriorityQueue();
	insertToQueue(queue, array);

	Tree huffmanTree = huffTreeHelper(queue);

	return huffmanTree;
}


// insertToQueue(q,charArray) inserts the characters from 'charArray'
// into  priority queue 'q'.

void insertToQueue(PriorityQueue& q, int* charArray)
{
	for(int i = 0; i < maxChars; i++)
	{
		if(charArray[i] > 0)
		{
			Tree t = new Node((unsigned char)i);
			insert(q, t, i);
		}
	}
}


// huffTreeHelper(q) returns the huffman tree found in priority 
// queue 'q'.

Tree huffTreeHelper(PriorityQueue &q)
{
	Tree k = NULL;

	int num = 0;

	while(!isEmpty(q))
	{
		remove(q, k, num);

		if(!isEmpty(q))
		{
			Tree f;
			int pr;

			remove(q, f, pr);

			Tree t = new Node(k, f);

			insert(q, t, num + pr);
		}
	}
	return k;
}

/**
 * codeBuilder(t, code, pref) builds the character codes for tree 't'
 * and stores it in the string array 'code' starting with the prefix
 * value of 'pref'.
 */

void codeBuilder(Tree t, char** code, const char* prefix)
{
	if(t != NULL)
	{
		if (t->kind == leaf)
		{
			char* copyStr = new char[8];

			strcpy(copyStr, prefix);
			code[(int)(unsigned char) t->ch] = copyStr;
		}

		else
		{
			char *copyLeft = new char[8];
			strcpy(copyLeft, prefix);

			char* concatLeft = strcat(copyLeft, "0");
			codeBuilder(t->left, code, concatLeft);

			delete[] copyLeft;

			char *copyRight = new char[8];
			strcpy(copyRight, prefix);

			char* catRight = strcat(copyRight, "1");
			codeBuilder(t->right, code, catRight);

			delete[] copyRight;
		}
	}
}

/**
 * setArrayToNull(code) sets the entire array 'code' to null.
 */

void setArrayToNull(char** code)
{
	for(int i = 0; i < maxChars; i++)
	{
		code[i] = NULL;
	}
}

// writeTreeBinary(f, t) writes a description of given tree 't' 
// into the given binary file 'f'.

void writeTreeBinary(BFILE* f, Tree t)
{
	if(t->kind == leaf)
	{
		writeBit(f, 1);
		writeByte(f, t->ch);
	}
	else
	{
		writeBit(f, 0);
		writeTreeBinary(f, t->left);
		writeTreeBinary(f, t->right);
	}
}



/**
 * encodeChar(code, b, inputFile) re-reads the input file
 * 'inputF' and writes the character code from array 'code'
 * for each character that is being read in the binary file 'b'.
*/

void encodeChar(char* code[], BFILE* b, const char* readF)
{
	FILE* rRead = fopen(readF, "r");

	int temp;

	if(rRead != NULL) 
	{
		

		while ((temp = getc(rRead)) != EOF) 
		{
			encodeCharHelper(b, code, temp);
		}
	}

	fclose(rRead);
}

/**
 * encodeCharHelper(write, code, x)  encodes the character 'x' in
 * the open binary file 'write'.
 */

void encodeCharHelper(BFILE* write, char** code, int x)
{
	for(int i = 0; code[x][i] != '\0'; i++)
	{
		int bit = (code[x][i] == '1');
		writeBit(write, bit);
	}
}


int main(int argc, char* argv[])
{
		
	setTracing(argc, argv);
	int* charsArr = new int[maxChars];


	bool ans;
			
	ans = freqsCount(charsArr,argc, argv);


	if(ans)
	{
	
		Tree t = huffmanTree(charsArr);

		char** code = new char*[maxChars];
		
		setArrayToNull(code);
		codeBuilder(t, code, "");

		BFILE* openWriteFile = openBinaryFileWrite(argv[argc-1]);
		writeTreeBinary(openWriteFile, t);

		// Add something below
		encodeChar(code, openWriteFile, argv[argc-2]);

		if (tracelevel)
		{
			showFrequencies(charsArr);
			printf("\nThe huffman tree is:");
			showTree(t);
			showCode(code);

			printf("\nInput File: %s", argv[argc - 2]);

		}

		closeBinaryFileWrite(openWriteFile);

	}

	else
	{
		printf("Cannot open the file.\n Program terminating.");
	}

	putchar('\n');

	return 0;

}

