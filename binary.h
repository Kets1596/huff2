// Author:     Karl Abrahamson
// File:       binary.h
// Tab stops:  none

struct BFILE;
BFILE* openBinaryFileWrite(const char* filename);
void   writeBit(BFILE* f, int b);
void   writeByte(BFILE* f, int b);
void   closeBinaryFileWrite(BFILE*& f);

BFILE* openBinaryFileRead(const char* filename);
int    readBit(BFILE* f);
int    readByte(BFILE* f);
void   closeBinaryFileRead(BFILE*& f);

