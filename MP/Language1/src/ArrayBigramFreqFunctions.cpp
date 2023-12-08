/**
 * @file Bigram.cpp
 * @author Miguel Ángel De la Vega Rodríguez(miguevrod@correo.ugr.es)
 * @version 0.1
 * @date 2023-03-13
 * 
 */


#include <iostream>
#include "ArrayBigramFreqFunctions.h"

using namespace std;

void readArrayBigramFreq(BigramFreq array[], int dim, int &nElements){
    int frequency;
    char first;
    char second;
    cin >> nElements;

     //We ensure that we don't read more elements than the array can hold
    nElements=min(nElements,dim);

    for (int i=0;i<nElements;i++){
        cin >> first;
        cin >> second;
        cin >> frequency;
        array[i]= BigramFreq(Bigram(first,second),frequency);
    }
}


void printArrayBigramFreq(const BigramFreq array[], int nElements){
    cout << nElements << "\n";
    for (int i=0;i<nElements;i++){
        cout << array[i].toString() << "\n";
    }
}


void swapElementsArrayBigramFreq(BigramFreq array[], int nElements, int first,int second){
    if (first<0 || first >= nElements){
        throw out_of_range(string("invalid position ") + to_string(first));
    }
    else if (second<0 || second >= nElements){
        throw out_of_range(string("invalid position ") + to_string(second));
    }
    else{
        BigramFreq aux;
        aux = array[first];
        array[first] = array[second];
        array[second] = aux;
    }
}


void quickSort(BigramFreq array[], int nElements, int start, int end){
    if (start >= end) {
        //In this case the array is sorted
        return;
    }
    
    //Choosing the pivot
    int pivotIndex = start + (end - start) / 2;
    BigramFreq pivot = array[pivotIndex];
    
    //We divide the array around the pivot element
    int i = start;
    int j = end;
    while (i <= j) {
        while (array[i].getFrequency() > pivot.getFrequency() || 
               (array[i].getFrequency() == pivot.getFrequency() && 
                array[i].getBigram().toString() < pivot.getBigram().toString())) {
            i++;
        }
        while (array[j].getFrequency() < pivot.getFrequency() || 
               (array[j].getFrequency() == pivot.getFrequency() && 
                array[j].getBigram().toString() > pivot.getBigram().toString())) {
            j--;
        }
        if (i <= j) {
            swapElementsArrayBigramFreq(array, nElements, i, j);
            i++;
            j--;
        }
    }
    
    //Sorting the two subarrays using a recursive method
    if (start < j) {
        quickSort(array, nElements, start, j);
    }
    if (i < end) {
        quickSort(array, nElements, i, end);
    }
}


void sortArrayBigramFreq(BigramFreq array[], int nElements){
    //Done so that the arguments of the given function sortArrayBigramFreq are not modified
    quickSort(array, nElements, 0, nElements - 1); 
}




void toUpperArrayBigramFreq(BigramFreq array[], int nElements){
    for (int i=0;i<nElements;i++){
        Bigram b = array[i].getBigram();
        b.toUpper();
        array[i].setBigram(b);
    }
}
