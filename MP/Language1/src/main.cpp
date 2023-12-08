/*
 * Metodología de la Programación: Language1
 * Curso 2022/2023
 */

/**
 * File:   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Miguel Ángel De La Vega Rodríguez <miguevrod@correo.ugr.es>
 * Created on 7 de febrero de 2023, 14:02
 */

#include <iostream>
#include "ArrayBigramFreqFunctions.h"

/**
 * This program reads from the stardard input, an integer n (number of elements) 
 * and a list of n pairs bigram-frequency. The pairs are stored in an array, 
 * and then it is sorted in decreasing order of frequency. After that, 
 * all the bigrams are changed to uppercase. The sorted array is finally shown 
 * in the stardard output. 
 * Running example:
 * > language1 < data/miniquijotebigrams.txt 
 */
using namespace std;

int main(int argc, char* argv[]) {
    const int MAX = 1000;
    int nElements = 0; //Number of elements of the array
    BigramFreq bigrams[MAX]; 
    
    //Read the array of BigramFreq from the standard input
    readArrayBigramFreq(bigrams, MAX , nElements);
    
    //Sort the array of BigramFreq
    sortArrayBigramFreq(bigrams, nElements);

    //Convert to uppercase the Bigrams
    toUpperArrayBigramFreq(bigrams, nElements);

    //Print the sorted array
    printArrayBigramFreq(bigrams,nElements);
}

