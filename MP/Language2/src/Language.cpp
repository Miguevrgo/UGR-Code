/*
 * Metodología de la Programación: Language2
 * Curso 2022/2023
 */

#include <fstream>
#include "Language.h"

/** 
 * @file Language.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Miguel Angel De La Vega Rodríguez <miguevrod@correo.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */


const std::string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";

Language::Language(): _languageId("unknown"),_size(0){}

Language::Language(int numberBigrams){
    if(numberBigrams>DIM_VECTOR_BIGRAM_FREQ){
        throw std::out_of_range(std::string("Language::Language(int numberBigrams)") +
         "invalid number of bigrams" + std::to_string(numberBigrams));
    }
    else{
        _languageId="unknown";
        _size=numberBigrams;
    }
   
}

const std::string& Language::getLanguageId() const{
    return _languageId;
}

void Language::setLanguageId(std::string id){
    _languageId=id;
}

const BigramFreq& Language::at(int index) const{
    if(index<0 || index>=_size){
        throw std::out_of_range(std::string("const BigramFreq& Language::at(int index) const") +
         "invalid position" + std::to_string(index));
    }
    else{
        return _vectorBigramFreq[index];
    }
}

BigramFreq& Language::at(int index){
    if(index<0 || index>=_size){
        throw std::out_of_range(std::string("BigramFreq& Language::at(int index)") +
         "invalid position" + std::to_string(index));
    }
    else{
        return _vectorBigramFreq[index];
    }
}

int Language::getSize() const{
    return _size;
}

int Language::findBigram(const Bigram& bigram) const{
    bool found=false;
    int pos=0;
    for (int i=0;i<getSize();i++){
        if (bigram.getText() == _vectorBigramFreq[i].getBigram().getText()){
            found=true;
            pos=i;
        }
    }
    return (found) ? pos : -1; //If found return pos else return -1

}

std::string Language::toString() const{
    std::string cad = MAGIC_STRING_T + "\n" + _languageId + "\n" + std::to_string(_size);
    for (int i=0;i<_size;i++){
        cad += "\n" + _vectorBigramFreq[i].toString();
    }
    return cad;
}

void swapElementsArrayBigramFreq(BigramFreq array[], int nElements, int first,int second){
    if (first<0 || first >= nElements){
        throw std::out_of_range(std::string("invalid position ") + std::to_string(first));
    }
    else if (second<0 || second >= nElements){
        throw std::out_of_range(std::string("invalid position ") + std::to_string(second));
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

void Language::sort(){
    quickSort(_vectorBigramFreq,_size,0,_size-1);
}

void Language::save(const char fileName[]) const{
    std::ofstream outputStream;
    outputStream.open(fileName);
    if (!outputStream){
        throw std::ios_base::failure(std::string("void Language::save(const char fileName[]) const") 
        + "failed opening the file");
    }
    
    outputStream << toString() << "\n";

    if(!outputStream){
        throw std::ios_base::failure(std::string("void Language::save(const char fileName[]) const") 
        + "failed writing in the file");
    }

    outputStream.close();
}

void Language::load(const char fileName[]) {
    std::ifstream inputStream;
    std::string cadena_magica;
    inputStream.open(fileName);
    if (!inputStream){
        throw std::ios_base::failure(std::string("void Language::load(const char fileName[])") 
        + "failed opening the file");
    }

    inputStream >> cadena_magica;
    if (cadena_magica != MAGIC_STRING_T){
        throw std::invalid_argument(std::string("void Language::load(const char fileName[])") 
        + "MAGIC_STRING_T invalid name " + cadena_magica);
    }
    
    inputStream >> _languageId;
    inputStream >> _size;
    if(_size>DIM_VECTOR_BIGRAM_FREQ){
        throw std::out_of_range(std::string("void Language::load(const char fileName[])") 
        + "invalid number of Bigrams " + std::to_string(_size));
    }
    
    int frequency;
    char first,second;
    for(int i=0;i<_size;i++){
        inputStream >> first;
        inputStream >> second;
        inputStream >> frequency;
        _vectorBigramFreq[i] = BigramFreq(Bigram(first,second),frequency);
    }
    
    inputStream.close(); 
}

void Language::append(const BigramFreq& bigramFreq){
    if(findBigram(bigramFreq.getBigram())==-1){
        if(_size==DIM_VECTOR_BIGRAM_FREQ){
            throw std::out_of_range(std::string("void Language::append(const BigramFreq& bigramFreq)")
            + "number of elements already full" + std::to_string(_size));
        }
        else{
            _vectorBigramFreq[_size]=bigramFreq;
            _size++;
        }
    }
    else{
        int pos=findBigram(bigramFreq.getBigram());
        //We could have used an auxiliary method to increment the frequency, however, i find
        //this implementation better to avoid creating unncecesary methods
        _vectorBigramFreq[pos]
        .setFrequency(_vectorBigramFreq[pos].getFrequency()+bigramFreq.getFrequency());        
    }
}

void Language::join(const Language& language){
    for (int i=0;i<language.getSize();i++){
        append(language.at(i));
    }
}