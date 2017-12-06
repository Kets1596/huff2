// Author:     Karl Abrahamson
// File:       binary1.cpp
// Tab stops:  none

#include <cstdio>
#include "binary.h"
using namespace std;

struct BFILE
{
  FILE* file;

  BFILE(FILE* f)
  {
    file = f;
  }
};

/***********************************************
 *          openBinaryFileWrite                *
 ***********************************************
 * Return an open file for writing bits into   *
 * file filename.                              *
 ***********************************************/

BFILE* openBinaryFileWrite(const char* filename)
{
  FILE* f = fopen(filename, "w");

  if(f == NULL) return NULL;
  else return new BFILE(f);
}

/***********************************************
 *               writeBit                      *
 ***********************************************
 * Write bit b into open file f.  b must be    *
 * 0 or 1.                                     *
 ***********************************************/

void writeBit(BFILE* f, int b)
{
  if(b < 0 || b > 1)
  {
    printf("Bad bit %i passed to writeBit\n", b);
    fflush(stdout);
  }
  putc(b + '0', f->file);
}

/***********************************************
 *               writeByte                     *
 ***********************************************
 * Write one byte (8 bits) holding b into open *
 * file f.  It is requied that 0 <= b <= 255.  *
 ***********************************************/

void writeByte(BFILE* f, int b)
{
  int r = b;
  if(r < 0) r = r + 256;
  for(int i = 0; i < 8; i++) 
  {
    putc((r >> 7) + '0', f->file);
    r = (r << 1) & 0xFF;
  }
}

/***********************************************
 *          closeBinaryFileWrite               *
 ***********************************************
 * Close file f.  It should have been opened   *
 * using openBinaryFileWrite.                  *
 ***********************************************/

void closeBinaryFileWrite(BFILE*& f)
{
  if(f != NULL) 
  {
    fclose(f->file);
    delete f;
    f = NULL;
  }
}

/***********************************************
 *          openBinaryFileRead                 *
 ***********************************************
 * Return an open file for reading bits from   *
 * file filename.                              *
 ***********************************************/

BFILE* openBinaryFileRead(const char* filename)
{
  FILE* f = fopen(filename, "r");
  if(f == NULL) return NULL;
  else return new BFILE(f);
}

/***********************************************
 *                 readBit                     *
 ***********************************************
 * Read one bit from file f and return it (0   *
 * or 1).  At end of file, return EOF.         *
 ***********************************************/

int readBit(BFILE* f)
{
  int c = getc(f->file);
  if(c == EOF) return EOF;
  else return c - '0';
}

/***********************************************
 *                 readByte                    *
 ***********************************************
 * Read one byte from file f and return it.    *
 * At end of file, return EOF.                 *
 ***********************************************/

int readByte(BFILE* f)
{
  int r = 0;
  int b;

  for(int i = 0; i < 8; i++) 
  {
    b = readBit(f);
    if(b == EOF) return EOF;
    r = (r << 1) | b;
  }
  return r;
}

/***********************************************
 *          closeBinaryFileRead                *
 ***********************************************
 * Close file f.  It should have been opened   *
 * using openBinaryFileRead.                   *
 ***********************************************/

void closeBinaryFileRead(BFILE*& f)
{
  if(f != NULL) 
  {
    fclose(f->file);
    delete f;
    f = NULL;
  }
}

