/* 
 * A module supplying functions able to encode a textfile using a
 * huffman table or decode a file using a trie along with an int
 * to binary function
 *
 * Author  Jesper Riekkola dv17jra 2020-08-15
 *
 * For more information see .h file
 */
 
#include "huffmanEncoder.h"

void encode(huffmanTable* table,char* infile,char* outfile){
    FILE* read = fopen(infile,"r");
    FILE* write = fopen(outfile,"w");
    int asciiValue;
    int charsRead = 0;
    int charsWritten = 0;
    int i;
    int bitByte;
    bit_buffer* buffer = bit_buffer_empty();

    while((asciiValue = fgetc(read)) != EOF) {
        charsRead++;
        i = 0;
        while (table[asciiValue].path[i] != '\0') {
            bit_buffer_insert_bit(buffer,table[asciiValue].path[i]-48);
            i++;
        }
    }

    i = 0;
    while (table[4].path[i] != '\0') {
        bit_buffer_insert_bit(buffer,table[4].path[i]-48);
        i++;
    }

    while(bit_buffer_size(buffer)){

        if(bit_buffer_size(buffer) > 7){
            bitByte = bit_buffer_remove_byte(buffer);
        } else {
           while(bit_buffer_size(buffer) < 8){
               bit_buffer_insert_bit(buffer,0);
           }
           bitByte = bit_buffer_remove_byte(buffer);
        }
        charsWritten++;
        fputc(bitByte, write);
    }

    printf("%d bytes read from %s\n",charsRead,infile);
    printf("%d bytes used in encoded form\n",charsWritten);
    bit_buffer_free(buffer);
    fclose(read);
    fclose(write);

}

void decode(trie* root,char* infile,char* outfile){
    FILE* read = fopen(infile,"r");
    FILE* write = fopen(outfile,"w");
    int asciiValue;
    trie* node = root;
    int* bitSequence = malloc(8* sizeof(int));

    while((asciiValue = fgetc(read)) != EOF) {
        intToBinary(asciiValue,bitSequence);
        int i = 0;

        while(i < 8){

            if(node->rightChild == NULL && node->leftChild == NULL){
                if(node->symbol == 4){
                    fclose(read);
                    fclose(write);
                    free(bitSequence);
                    printf("File decoded succesfully\n");
                    return;
                } else {
                    fputc(node->symbol,write);
                    node = root;
                }
            } else if(bitSequence[i] == 1){
                node = node->rightChild;
                i++;
            } else {
                node = node->leftChild;
                i++;
            }

        }

    }

    free(bitSequence);
    fclose(read);
    fclose(write);

}

void intToBinary(int integer,int* bitsequence){
    int binary[8];
    int i = 0;
    int j = 0;

    if(integer < 2){ ;
        bitsequence[0] = integer;
    }

    //Convert integer into binary
    while(integer > 0){
        binary[i] = integer % 2;
        integer = integer / 2;
        i++;
    }

    while(i < 8){
        binary[i] = 0;
        i++;
    }

    i--;

    //binary[] is in reverse order,flip it
    while(i >= 0){
        bitsequence[j] = binary[i];
        i--;
        j++;
    }

}