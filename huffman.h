/*! \mainpage Huffman
 *
 * \section intro_sec Introduction
 *
 * Huffman is a program used to compress and decompress text files
 * lossless. Firstly, analysis of a text file is used to get an idea
 * of most commonly used characters and a trie is built. It's important
 * that analysis is  

/**
 * @defgroup huffman_h Huffman
 *
 * @brief A program used to compress files and decompress them lossless
 *
 * Capable of encoding a file into a smaller file and decoding it
 * afterwards, important is that frequency analysis is done on
 * the same file when encoding and decoding.
 * Several files are used in this program, of which trie.c/h,
 * frequenceAnalysis.c/h, huffmanEncoder.c/h and huffman.c/h 
 * are written by me.
 * frequenceAnalysis.c is used to get the weights for the trie
 * from trie.c. The trie is used in huffman.c in tandem with
 * pqueue.c (and list.c is used by pqueue) to get the unique
 * and efficient paths for every character which is then
 * converted with help from bitbuffer.c and huffmanEncoder.c to
 * compress or decompress text.
 *
 * @author  Jesper Riekkola dv17jra
 * @since   2020-08-15
 *
 * @{
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "huffmanEncoder.h"
#include "frequenceAnalysis.h"
#include "pqueue.h"

/**
 * @brief       Checks if the arguments sent to the program are correct
 *
 *              Checks if either "-decode" or "-encode" exists within
 *              the commandline
 *
 * @param argv  The first argument of the program
 * @return      0 if correct, 1 if not
 */
int checkCommandLine(char* argv);

/**
 * @brief Prints a errormessage if the program is used incorrectly
 *
 * @return -
 */
void errorMessage(void);

/**
 * @brief       Checks if the file exists
 *
 *              Checks if the files exists, and if it doesn't then
 *              an errormessage is printed and the program shuts down
 *
 * @param argv  The name of the file
 * @return -
 */
void validateFile(char * argv);



/**
 * @brief       Connects all the trie in the queue and creates one
 *              containing all the other trie
 *
 *              The function picks out the two trie with the lowest
 *              weight and combines them with a common parent and
 *              puts the parent back in the queue having the combined
 *              weight of its children
 *
 * @param queue A priority queue containing trie
 * @return      The root of the new trie structure
 */
trie* huffmanTrie(pqueue* queue);

/**
 * @brief       Explores the whole trie and saves the path to all leafs
 *
 *              Saves the path to every symbol seen from the root in
 *              the huffmanTable
 *
 * @param trie  The root of a trie structure
 * @param table The huffmanTable
 * @return      -
 */
void get_paths(trie* trie,huffmanTable* table);

/**
 * @}
 */
