CFLAGS = -g -Wall -Wshadow -Wuninitialized -O
CC     = g++
LINK   = g++
OFILESH = huffman.o trace.o binary1.o pqueue.o
OFILESU = unhuffman.o trace.o binary1.o
OFILES  = huffman.o unhuffman.o trace.o binary1.o pqueue.o

runh: huffman
	./huffman

debugh: huffman
	gdb ./huffman

runu: unhuffman
	./unhuffman

debugu: unhuffman
	gdb ./unhuffman

huffman : $(OFILESH)
	$(LINK) -o huffman $(OFILESH) 

unhuffman : $(OFILESU)
	$(LINK) -o unhuffman $(OFILESU) 

huffman.o: huffman.cpp trace.h binary.h
	$(CC) $(CFLAGS) -c huffman.cpp

unhuffman.o: unhuffman.cpp trace.h binary.h
	$(CC) $(CFLAGS) -c unhuffman.cpp

trace.o: trace.cpp trace.h
	$(CC) $(CFLAGS) -c trace.cpp

pqueue.o: pqueue.cpp pqueue.h
	$(CC) $(CFLAGS) -c pqueue.cpp

binary1.o: binary1.cpp
	$(CC) $(CFLAGS) -c binary1.cpp

clean: 
	rm $(OFILES) huffman unhuffman

