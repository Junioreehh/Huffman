/*
 * A module to facilitate frequency analysis on a file
 *
 * Contributes a function which performs a frequency analysis of all
 * the characters in a given file and returns it
 *
 * author  Jesper Riekkola dv17jra 2020-03-08
 *
 * For more information see .h file
 */
#include "frequenceAnalysis.h"

int* frequenceAnalysis(char* argv){
    int asciiValue = 0;
    int* arr = calloc(256,sizeof(int));
    FILE* fileStream = fopen(argv,"r");

    if(fileStream == NULL){
        return NULL;
    }

    /* Each spot in arr represents a char according to its
     * ascii value, so when 'A' is found arr[65] is increased by one
     */
    while((asciiValue = fgetc(fileStream)) != EOF){
        arr[asciiValue]++;
    }
    arr['\4']++;

    fclose(fileStream);

    return arr;

}