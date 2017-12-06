// Author:     Karl Abrahamson
// File:       binary2.cpp
// Tab stops:  none

#include <cstdio>
#include "binary.h"
using namespace std;

struct BFILE
{
  FILE* file;
  int bitCount, theByte, readAhead1, readAhead2;

  BFILE(FILE* f)
  {
    file     = f;
    bitCount = 0;
    theByte  = 0;
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
  FILE* f = fopen(filename, "wb");

  if(f == NULL) return NULL;
  else return new BFILE(f);
}

/***********************************************
 *               writeBit                      *
 ***********************************************
 * Write bit into open file f.  bit must be    *
 * 0 or 1.                                     *
 ***********************************************/

void writeBit(BFILE* f, int b)
{
  if(b < 0 || b > 1)  
  {
    printf("Bad bit %i passed to writeBit\n", b);
    fflush(stdout);
  }
  f->theByte = (f->theByte << 1) | b;
  f->bitCount++;
  if(f->bitCount == 8) {
    putc(f->theByte, f->file);
    f->bitCount = 0;
    f->theByte  = 0;
  }
}

/***********************************************
 *               writeByte                     *
 ***********************************************
 * Write one byte (8 bits) holding b into open *
 * file f.  It is requied that 0 <= b <= 255.  *
 ***********************************************/

void writeByte(BFILE* f, int b)
{
  if(b < 0) b = b + 256;

  int bitCount = f->bitCount;
  f->theByte = (f->theByte << (8 - bitCount)) | (b >> bitCount);
  putc(f->theByte, f->file);
  f->theByte = b & ((1 << bitCount) - 1);
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
    if(f->bitCount > 0) 
    {
      putc(f->theByte << (8 - f->bitCount),  f->file);
      putc(f->bitCount, f->file);
    }
    else 
    {
      putc(8, f->file);
    }
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
  FILE* f = fopen(filename, "rb");
  if(f == NULL) return NULL;
  else 
  {
    BFILE* ff = new BFILE(f);
    ff->readAhead1 = getc(f);
    ff->readAhead2 = getc(f);
    return ff;
  }
}

/***********************************************
 *                 readBit                     *
 ***********************************************
 * Read one bit from file f and return it (0   *
 * or 1).  At end of file, return EOF.         *
 ***********************************************/

int readBit(BFILE* f)
{
  if(f->bitCount == 0) 
  {
    if(f->readAhead2 == EOF) return EOF;
    f->theByte    = f->readAhead1;
    f->readAhead1 = f->readAhead2;
    f->readAhead2 = getc(f->file);
    if(f->readAhead2 == EOF) f->bitCount = f->readAhead1;
    else f->bitCount = 8;
  }
  int r = f->theByte >> 7;
  f->theByte = (f->theByte << 1) & 0xFF;
  f->bitCount--;
  return r;
}

/***********************************************
 *                 readByte                    *
 ***********************************************
 * Read one byte from file f and return it.    *
 * At end of file, return EOF.                 *
 ***********************************************/

int readByte(BFILE* f)
{
  if(f->bitCount == 8) 
  {
    f->bitCount = 0;
    return f->theByte;
  }
  else if(f->readAhead2 == EOF) return EOF;
  else
  {
    int bcComp = 8 - f->bitCount;
    int r = f->theByte | (f->readAhead1 >> f->bitCount);
    f->theByte    = (f->readAhead1 << bcComp) & 0xFF;
    f->readAhead1 = f->readAhead2;
    f->readAhead2 = getc(f->file);
    if(f->readAhead2 == EOF) 
    {
      f->bitCount = f->readAhead1 - bcComp;
      if(f->bitCount < 0) return EOF;
      else return r;
    }
    return r;
  }
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

