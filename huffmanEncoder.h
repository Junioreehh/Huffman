/**
 * @defgroup huffmanEncoder_h Huffman encoder
 *
 * @brief Encodes textfile or decodes file
 *
 * huffmanEncoder Encodes a textfile with the help of a huffman table
 * or decodes, with the help of a trie, an already encoded file back
 * to the original textfile lossless. The trie used to create the 
 * huffman table when encoding must be the same when decoding back.
 *
 * @author  Jesper Riekkola dv17jra
 * @since   2020-08-15
 *
 * @{
 */
#include "trie.h"
#include "bit_buffer.h"

/**
 * @brief           A struct used to pair a character and its path
 *
 *                  The path of a character from the root of a trie
 *                  is saved along with the ascii value of the
 *                  character
 *
 * @elem path       A string filled with a bunch of 0 and 1 with
 *                  0 indicating left and 1 indicating right
 * @elem character  The ascii value of the character
 */
typedef struct {
    char* path;
    int character;
}huffmanTable;

/**
 * @brief           Encodes the infile and writes the result to
 *                  the outfile
 *
 *                  For each character read from infile the path
 *                  to that character is saved in a buffer ending
 *                  with the path to the character '\4' to mark the end
 *                  of the text. Afterwards the buffer is emptied in
 *                  chunks of 8 and the value of the 0s and 1s
 *                  removed is translated to base 10 and saved
 *                  onto outfile. If the buffer size isn't a
 *                  multiple of 8 0 is added until it is.
 *
 * @param table     The huffmanTable containing the paths of
 *                  each character
 * @param infile    The name of the file to be encoded
 * @param outfile   The name of the file to be created and written to
 * @return          -
 */
void encode(huffmanTable* table,char* infile,char* outfile);

/**
 * @brief           Decodes infile and writes the result to the outfile
 *
 *                  For each character read from the infile the ascii
 *                  value of that is converted into binary and used
 *                  to traverse the trie to reach the characters and
 *                  are written to outfile. Every time a characters is
 *                  found it goes back to the root and keeps traversing
 *                  until the character '\4' is found.
 *
 * @param root      The root of the trie structure
 * @param infile    The name of the file to be decoded
 * @param outfile   The name of the file to be written to
 * @return          -
 */
void decode(trie* root,char* infile,char* outfile);

/**
 * @brief               Converts an int to binary
 *
 * @param integer       The integer
 * @param bitsequence   An eight long int array being filled with
 *                      0 and 1
 * @return              -
 */
void intToBinary(int integer,int* bitsequence);

/**
 * @}
 */