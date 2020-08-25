/**
 * @defgroup trie_h Trie
 *
 * @brief A data type representing a trie
 *
 * The data type represents a trie where
 * left indicates a 0 and right indicates a 1
 *
 * @author  Jesper Riekkola dv17jra
 * @since   2020-03-08
 *
 * @{
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief         A trie structure also holding a symbol and its weight
 */
typedef struct trie trie;

/**
 * @brief           A struct used to represent a trie
 *
 * @elem parent     A pointer to the parent trie or null
 * @elem leftChild  A pointer to a child or null
 * @elem rightChild A pointer to a child or null
 * @elem symbol     Ascii value of the a symbol or -1 if not leaf
 * @elem weight     Frequency of the symbol or -1 if not leaf
 */
struct trie {
    trie* parent;
    trie* leftChild;
    trie* rightChild;
    int symbol;
    int weight;
};

/**
 * @brief           Returns a trie
 *
 *                  Configures the trie to hold the
 *                  values supplied by the parameters
 *
 * @param symbol    The Ascii value of the symbol
 * @param weight    The frequency of the symbol
 * @return          The trie
 */
trie* trie_empty(int symbol,int weight);

/**
 * @brief           Connects to trie
 *
 *                  Connects to trie to a common
 *                  parent and returns the parent
 *
 * @param trieOne   The first trie
 * @param trieTwo   The second trie
 * @return          The parent connecting the two
 */
trie* trie_connect(trie* trieOne,trie* trieTwo);

/**
 * @brief           Compares the weight of two trie
 *
 *                  A function given to a priority queue
 *                  to help determine where it should go
 *
 *
 * @param trieOne   A void pointer to the first trie
 * @param trieTwo   A void pointer to the second trie
 * @return          1 if trieOne > trieTwo, 0 if equal and -1 if
 *                  trieTwo > trieOne
 */
int trieCompare(void* trieOne,void* trieTwo);

/**
 * @brief           Returns the path to the trie
 *
 *                  Finds the path of the trie
 *                  as seen from the root and returns it
 *
 * @param trieChild The trie
 * @return          A string of the path
 */
char* trie_path(trie* trieChild);


/**
 * @brief       Deallocates all memory
 *
 *              Frees all the memory of all
 *              trie "below" this one, best used
 *              on the root
 *
 * @param trie  The trie
 * @return      -
 */
void trie_kill(trie* trie);

/**
 * @}
 */
