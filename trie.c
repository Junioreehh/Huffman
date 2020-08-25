/*A data type representing a trie
 *
 * The data type represents a trie where
 * left indicates a 0 and right indicates a 1
 *
 * Author  Jesper Riekkola dv17jra 2020-03-08
 *
 * For more information see .h file
*/

#include "trie.h"

trie* trie_empty(int symbol,int weight){
    trie* node = malloc(sizeof(trie));

    node->leftChild = NULL;
    node->rightChild = NULL;
    node->parent = NULL;
    node->weight = weight;
    node->symbol = symbol;

    return node;

}

trie* trie_connect(trie* trieOne,trie* trieTwo){
    trie* parent = trie_empty(-1,0);

    trieOne->parent = parent;
    trieTwo->parent = parent;

    //prefer bigger weight to be leftchild
    if(trieOne->weight > trieTwo->weight){
        parent->leftChild = trieOne;
        parent->rightChild = trieTwo;
    } else {
        parent->leftChild = trieTwo;
        parent->rightChild = trieOne;
    }

    parent->weight = trieOne->weight+trieTwo->weight;

    return parent;

}

int trieCompare(void* trieOne,void* trieTwo){
    trie* one = (trie*)trieOne;
    trie* two = (trie*)trieTwo;

    if(one->weight > two->weight){
        return 1;
    } else if(two->weight > one->weight){
        return -1;
    } else {
        return 0;
    }

}

char* trie_path(trie* trieChild){
    char* path = malloc(256);
    trie* parent = trieChild->parent;
    int i = 0;

    //Gathers the path of the node seen from the root, the path will
    //initally be reversed
    while(parent != NULL){

        if(parent->rightChild == trieChild){
            path[i] = '1';
            i++;
        } else if(parent->leftChild == trieChild){
            path[i] = '0';
            i++;
        } else {
            path = NULL;
            break;
        }

        trieChild = parent;
        parent = parent->parent;
    }

    if(path != NULL){
        path[i] = '\0';
    }

    //reverse the string
    int j = 0;
    int k = strlen(path)-1;
    char temp;

    while(j <= k){
        temp = path[j];
        path[j] = path[k];
        path[k] = temp;
        j++;
        k--;
    }

    return path;

}

void trie_kill(trie* trie){

    if(trie == NULL){
        return;
    }
    if(trie->leftChild != NULL){
        trie_kill(trie->leftChild);
    }
    if(trie->rightChild != NULL){
        trie_kill(trie->rightChild);

    }

    free(trie);

}