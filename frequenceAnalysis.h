/**
 * @defgroup frequenceAnalysis_h Frequency analysis
 *
 * @brief   A module to facilitate frequency analysis on a file
 *
 *          Contributes a function which performs a frequency analysis
 *          of all the characters in a given file and returns it
 *
 * @author  Jesper Riekkola dv17jra
 * @since   2020-03-08
 *
 * @{
 */


#include <stdio.h>
#include <stdlib.h>

/**
 * @brief       Performs a frequency analysis on the given file
 *
 *              Opens the file given and a counts how many
 *              times each character is used and returns that in
 *              an array where each characters ascii value is the
 *              position it has in the array, so '0' has the ascii
 *              value of 48 and would have that position in the array
 *
 * @param argv  The name of the file
 * @return      A 256 long array of ints
 */
int* frequenceAnalysis(char* argv);

/**
 * @}
 */
