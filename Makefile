CC=gcc
CFLAGS=-std=c99 -Wall

all: huffman

huffman: huffman.o bit_buffer.o frequenceAnalysis.o trie.o\
 pqueue.o list.o huffmanEncoder.o
	$(CC) $(CFLAGS) huffman.o bit_buffer.o frequenceAnalysis.o\
    trie.o pqueue.o huffmanEncoder.o list.o -o huffman
huffman.o: huffman.c huffman.h
	$(CC) $(CFLAGS) -c huffman.c
bit_buffer.o: bit_buffer.c bit_buffer.h
	$(CC) $(CFLAGS) -c bit_buffer.c
frequenceAnalysis.o: frequenceAnalysis.c frequenceAnalysis.h 
	$(CC) $(CFLAGS) -c frequenceAnalysis.c
trie.o: trie.c trie.h 
	$(CC) $(CFLAGS) -c trie.c
list.o: list.c list.h 
	$(CC) $(CFLAGS) -c list.c
huffmanEncoder.o: huffmanEncoder.c huffmanEncoder.h 
	$(CC) $(CFLAGS) -c huffmanEncoder.c
pqueue.o: pqueue.c pqueue.h 
	$(CC) $(CFLAGS) -c pqueue.c
clean:
	rm -f *.o huffman
