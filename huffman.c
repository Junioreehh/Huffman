/*
 * A program used to compress files and decompress them lossless
 *
 * Capable of encoding a file into a smaller file and decoding it
 * afterwards, important is that frequency analysis is done on
 * the same file when encoding and decoding
 *
 * Author  Jesper Riekkola dv17jra 2020-08-15
 *
 * For more information see .h file
 */
 
#include "huffman.h"

int main(int argc, char* argv[]) {

    if (argc != 5) {
        errorMessage();
        exit(EXIT_FAILURE);
    }

    if(checkCommandLine(argv[1])){
        errorMessage();
        exit(EXIT_FAILURE);
    }
    validateFile(argv[2]);
    validateFile(argv[3]);


    if (access(argv[4], F_OK) == 0) {
        printf("A file with the name %s already exists\n",argv[4]);
        return 1;
    }

    int* frequencyArr = frequenceAnalysis(argv[2]);

    //Create a trie for each character and insert it into the pqueue
    pqueue* queue = pqueue_empty(trieCompare);
    for(int i = 0; i < 256;i++){
        pqueue_insert(queue,trie_empty(i,frequencyArr[i]));
    }

    trie* huffTrie = huffmanTrie(queue);
    huffmanTable* table = malloc(256*sizeof(huffmanTable));

    get_paths(huffTrie,table);

    if(strcmp(argv[1],"-encode") == 0){
        encode(table,argv[3],argv[4]);
    } else if(strcmp(argv[1],"-decode") == 0) {
        decode(huffTrie,argv[3],argv[4]);
    }

    for(int k = 0; k < 256; k++){
        free(table[k].path);
    }

    trie_kill(huffTrie);
    pqueue_kill(queue);
    free(frequencyArr);
    free(table);

    return 0;

}

void errorMessage(void) {

    printf("USAGE: \n");
    printf("huffman [OPTION] [FILE0] [FILE1] [FILE2]\n");
    printf("Options: \n-encode encodes ");
    printf("FILE1 according to frequence analysis done on ");
    printf("FILE0. Stores the result in FILE2\n-decode ");
    printf("decodes FILE1 according to frequence analysis done");
    printf(" on FILE0. Stores the result in FILE2\n");

}

int checkCommandLine(char* argv){

    if(strcmp(argv,"-encode") == 0){
        return 0;
    } else if(strcmp(argv,"-decode") == 0){
        return 0;
    } else {
        return 1;
    }

}

void validateFile(char* argv) {

    if (access(argv, R_OK) != 0) {
        printf("Opening file has gone wrong, check if FILE0 or");
        printf(" FILE1 is spelled correctly\n");
        errorMessage();
        printf("%s\n",argv);
        exit(EXIT_FAILURE);
    }

}

trie* huffmanTrie(pqueue* queue){
    trie *trieOne;
    trie *trieTwo;


    //connects the two trie nodes with the lowest weight and inserts
    //them back in the queue and repeats this until only one is left
    while(!pqueue_is_empty(queue)) {
        trieOne = pqueue_inspect_first(queue);
        pqueue_delete_first(queue);

        if(pqueue_is_empty(queue)){
            return trieOne;
        }

        trieTwo = pqueue_inspect_first(queue);
        pqueue_delete_first(queue);
        pqueue_insert(queue,trie_connect(trieOne,trieTwo));

    }

    return NULL;

}

void get_paths(trie* trie,huffmanTable* table){

    if(trie == NULL){
        return;
    }
    if(trie->leftChild != NULL){
        get_paths(trie->leftChild,table);
    }
    if(trie->rightChild != NULL){
        get_paths(trie->rightChild,table);
    }
    if(trie->rightChild == NULL && trie->leftChild == NULL){
        table[trie->symbol].path = trie_path(trie);
        table[trie->symbol].character = trie->symbol;
    }

}



