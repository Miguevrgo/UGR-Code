/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file Language.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */

#include "Language.h"

const std::string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";
const std::string Language::MAGIC_STRING_B="MP-LANGUAGE-B-1.0";


Language::Language(): _languageId("unknown"){
    allocate(0);
}

Language::Language(int numberBigrams){
    if(numberBigrams<0){
        throw std::out_of_range(std::string("Language::Language(int numberBigrams)") +
         "invalid number of bigrams" + std::to_string(numberBigrams));
    }
    else{
        _languageId="unknown";
        allocate(numberBigrams);
    }
   
}

Language::Language(const Language& orig){
    this->allocate(orig.getSize());
    this->_languageId=orig._languageId;
    for (unsigned int i=0;i<_size;i++){
        _vectorBigramFreq[i] = orig._vectorBigramFreq[i];
    }
}

Language::~Language(){
    delete [] _vectorBigramFreq; 
}

Language& Language::operator=(const Language& orig){
    if (this!=&orig){
        this->deallocate();
        this->allocate(orig.getSize());
        this->_languageId=orig._languageId;
        for (unsigned int i=0;i<_size;i++){
            this->_vectorBigramFreq[i]=orig._vectorBigramFreq[i];
        }
    }
    /*
    else{
        throw std::invalid_argument(std::string("Language& Language::operator=(const Language& orig"))
         + "Cannot assign object to itself.");
    }
     */
    return *this;
}

const std::string& Language::getLanguageId() const{
    return this->_languageId;
}

void Language::setLanguageId(const std::string& id){
    this->_languageId=id;
}

const BigramFreq& Language::at(int index) const{
    if(index<0 || index>=_size){
        throw std::out_of_range(std::string("const BigramFreq& Language::at(int index) const") +
         "invalid position" + std::to_string(index));
    }
    else{
        return this->_vectorBigramFreq[index];
    }
}

BigramFreq& Language::at(int index){
    if(index<0 || index>=_size){
        throw std::out_of_range(std::string("BigramFreq& Language::at(int index)") +
         "invalid position" + std::to_string(index));
    }
    else{
        return this->_vectorBigramFreq[index];
    }
}

int Language::getSize() const{
    return _size;
}

double Language::getDistance(const Language& otherLanguage) const{
    if(_size==0){
        throw std::invalid_argument(std::string("double Language::getDistance(const Language& otherLanguage) const") +
            "this language is empty (_size=0)" );
    }
    
    double sum=0;
    for(int i=0;i<_size;i++){
        if(otherLanguage.findBigram(this->_vectorBigramFreq[i].getBigram())==-1){
            sum += std::fabs(i-_size);
        }
        else{
            sum += std::fabs(i-otherLanguage.findBigram(this->_vectorBigramFreq[i].getBigram()));
        }
    }
    return (sum/std::pow(_size,2));
}

int Language::findBigram(const Bigram& bigram) const{
    bool found=false;
    unsigned int pos=0;
    unsigned int i=0;
    while(!found && i<_size){
        if (bigram.getText() == this->_vectorBigramFreq[i].getBigram().getText()){
            found=true;
            pos=i;
        }
        else{
            i++;
        }
        
    }
    return (found) ? pos : -1; //If found return pos else return -1

}

std::string Language::toString() const{
    std::string cad = _languageId + "\n" + std::to_string(_size);
    for (unsigned int i=0;i<_size;i++){
        cad += "\n" + this->_vectorBigramFreq[i].toString();
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
        while (array[i] > pivot) {
            i++;
        }
        while (array[j] < pivot) {
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
    quickSort(this->_vectorBigramFreq,_size,0,_size-1);
}

void Language::save(const char fileName[], char mode) const{
    std::ofstream outputStream;
    
    if (mode == 't'){ // Text 
        
        outputStream.open(fileName, std::ios::out);
        if (!outputStream){
            throw std::ios_base::failure(std::string("void Language::save(const char fileName[]) const") 
            + "failed opening the file");
        }
        outputStream << MAGIC_STRING_T + "\n";
        outputStream << *this << "\n";
        
    }
    else{ // Binary
        
        outputStream.open(fileName, std::ios::out | std::ios::binary);
        if (!outputStream){
            throw std::ios_base::failure(std::string("void Language::save(const char fileName[]) const") 
            + "failed opening the file");
        }
        outputStream << MAGIC_STRING_B << "\n";
        outputStream << _languageId << "\n";
        outputStream << _size << "\n";
        for(unsigned int i=0; i<_size;i++){
            _vectorBigramFreq[i].serialize(outputStream);
        }
    }
    

    if(!outputStream){
        throw std::ios_base::failure(std::string("void Language::save(const char fileName[]) const") 
        + "failed writing in the file");
    }

    outputStream.close();
}

void Language::load(const char fileName[]) {
    std::ifstream inputStream;
    std::string cadena_magica;
    deallocate();
    inputStream.open(fileName, std::ios::in | std::ios::binary);
    if (!inputStream){
        throw std::ios_base::failure(std::string("void Language::load(const char fileName[])") 
        + "failed opening the file");
    }
    
    inputStream >> cadena_magica;
    
    if(cadena_magica == MAGIC_STRING_T){
        inputStream >> (*this);
    }
    else if(cadena_magica == MAGIC_STRING_B){
        inputStream >> this->_languageId;
        inputStream >> this->_size;
        
        inputStream.ignore();

        if(_size < 0){
            throw std::out_of_range(std::string("void Language::load(const char fileName[])")
                    + "invalid negative size " + std::to_string(_size));
        }
        
        allocate(_size);
        
        for(unsigned int i=0; i<_size;i++){
            _vectorBigramFreq[i].deserialize(inputStream);
        }
    }
    else{
        throw std::invalid_argument(std::string("void Language::load(const char fileName[])") 
        + "MAGIC_STRING invalid name " + cadena_magica);
    }
    

    
    inputStream.close(); 
}

void Language::append(const BigramFreq& bigramFreq){
    if(findBigram(bigramFreq.getBigram())==-1){
        reallocate(_size+1);
        this->_vectorBigramFreq[_size-1]=bigramFreq;
        
    }
    else{
        unsigned int pos=findBigram(bigramFreq.getBigram());
        //We could have used an auxiliary method to increment the frequency, however, i find
        //this implementation better to avoid creating unnececesary methods
        this->_vectorBigramFreq[pos]
        .setFrequency(_vectorBigramFreq[pos].getFrequency()+bigramFreq.getFrequency());        
    }
}

BigramFreq& Language::operator[](int index){
    if (index<0){
        std::cerr << "Index provided is lower than 0" << std::endl;
    }
    return _vectorBigramFreq[index];
}

const BigramFreq& Language::operator[](int index) const{
    if (index<0){
        std::cerr << "Index provided is lower than 0" << std::endl;
    }
    return _vectorBigramFreq[index];
}

Language& Language::operator+=(const Language &language){
    unsigned int size = language.getSize();
    for (unsigned int i = 0; i < size; i++) {
        append(language.at(i));
    }

    return *this;
}



void Language::allocate(int n_elements){
    // if (new_size<0){
    //     throw std::out_of_range(std::string("void Language::resize(int new_size)")+" Invalid new size ( <0 )");
    // }
    if (n_elements>0){
        this->_vectorBigramFreq = new BigramFreq[n_elements];
        this->_size=n_elements;
    }
    else{
        _vectorBigramFreq = nullptr;
        _size=0;
    }
        
}

void Language::deallocate(){
    delete [] this->_vectorBigramFreq;
    _vectorBigramFreq = nullptr;
    this->_size = 0;
}

void Language::reallocate(int new_size){
    // if (new_size<0){
    //     throw std::out_of_range(std::string("void Language::resize(int new_size)")+" Invalid new size ( <0 )");
    // }
    if (new_size>0){
        BigramFreq *resized_v = new BigramFreq[new_size];
        for (unsigned int i=0;i<_size;i++){
            resized_v[i]=this->_vectorBigramFreq[i];
        }

        delete [] this->_vectorBigramFreq;

        this->_vectorBigramFreq = resized_v;
        this->_size = new_size;
    }
    else{
        _vectorBigramFreq = nullptr;
        _size=0;
    }
}


std::ostream &operator<<(std::ostream &os, const Language &language){
    os << language.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Language& language) {
    language.deallocate();

    is >> language._languageId;
    is >> language._size;

    if (language._size<0){
        throw std::out_of_range(std::string("std::istream& operator>>(std::istream& is, Language& language)") 
        + "invalid size");
    }

    language.allocate(language._size);

    // Read each bigram frequency pair
    for (int i = 0; i < language._size; i++) {
        BigramFreq bigramFreq;
        is >> bigramFreq;
        language.at(i) = bigramFreq;
    }

    return is;
}
