/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramCounter.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 12 February 2023, 11:00
 */

#include "BigramCounter.h"

/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars). 
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

BigramCounter::BigramCounter(const std::string &validChars){
    unsigned int length = validChars.length(); // Length of the string validChars 
    this->_validCharacters = validChars;
    this->allocate(length);

    //Initialize the array to 0
    for (unsigned int i=0;i<length;i++){
        for (unsigned int j=0;j<length;j++){
            _frequency[i][j] = 0;
        }
    }
}
BigramCounter::BigramCounter(const BigramCounter &orig){
    unsigned int size = orig.getSize();
    this->_validCharacters =orig._validCharacters;
    this->allocate(size);
    for (unsigned int i=0;i<size;i++){
        for (unsigned int j=0;j<size;j++){
            _frequency[i][j]=orig._frequency[i][j];
        }
    }
}

BigramCounter::~BigramCounter(){
    deallocate();
}

int BigramCounter::getSize() const{
    return _validCharacters.length();
}

int BigramCounter::getNumberActiveBigrams() const{
    unsigned int length = _validCharacters.length();
    unsigned int counter = 0;
    for (unsigned int i=0;i<length;i++){
        for (unsigned int j=0;j<length;j++){
            if (_frequency[i][j] > 0){
                counter++;
            }
        }
    }
    return counter;
}

bool BigramCounter::setFrequency(const Bigram& bigram, int frequency){

    int fil = _validCharacters.find(bigram.at(0));
    int col = _validCharacters.find(bigram.at(1));
    
    bool found = (fil != std::string::npos) && (col != std::string::npos);
    
    if (found){
        _frequency[fil][col] = frequency;
    }

    return found;
}

void BigramCounter::increaseFrequency(const Bigram &bigram, int frequency){
    int fil = _validCharacters.find(bigram.at(0));
    int col = _validCharacters.find(bigram.at(1));
    
    bool found = (fil != std::string::npos) && (col != std::string::npos);
    
    if (!found){
        throw std::invalid_argument(std::string("void BigramCounter::increaseFrequency(const Bigram &bigram, int frequency)")
        + " invalid bigram provided ");
    }
    if(frequency==0){
        _frequency[fil][col] += 1;
    }
    else{
        _frequency[fil][col] += frequency; 
    } 
}

BigramCounter& BigramCounter::operator=(const BigramCounter &orig){
    if (this!=&orig){
        unsigned int size = orig.getSize();
        this->deallocate();
        this->allocate(size);
        this->_validCharacters = orig._validCharacters;
        for (unsigned int i=0;i<size;i++){
            for (unsigned int j=0;j<size;j++){
                this->_frequency[i][j] = orig._frequency[i][j];
            }
        }
    }
    /*
    else{
        throw std::invalid_argument(std::string("BigramCounter& BigramCounter::operator=(const BigramCounter &orig)"))
         + "Cannot assign object to itself.");
    }
     */
    return *this;
}

BigramCounter& BigramCounter::operator+=(const BigramCounter &rhs){
    unsigned int size = rhs.getSize();
    for (unsigned int i=0;i<size;i++){
        for (unsigned int j=0;j<size;j++){
            this->_frequency[i][j] += rhs._frequency[i][j];
        }
    }

    return *this;
}

void BigramCounter::calculateFrequencies(const char *const fileName){
    std::ifstream inputStream;
    inputStream.open(fileName);
    if(!inputStream){
        throw std::ios_base::failure(std::string("void BigramCounter::calculateFrequencies(const char *const fileName)") 
        + " file " + fileName + " could not be oppened");
    }

    this->resetMatrix();
        
    std::string text, line;
    while(getline(inputStream, line)){
        text += line;
        if (!inputStream.eof()) { // End of a line
            text += ' ';
        }
    }
    
    
    for(int i=0;i<text.length();i++){
        text[i] = tolower(text[i]);
    }

    
    int text_size = text.length();
    
    for (unsigned int i=0,j=1;j<text_size;i++,j++){
        if(text.at(i)!=' ' && text.at(j)!=' '){ //Optimization of the method (not necessary)
            if(isValidCharacter(text.at(i),_validCharacters) && isValidCharacter(text.at(j),_validCharacters)){
            this->increaseFrequency(Bigram(text[i],text[j]),1);

            }
            // If the second character is not valid we should skip two positions
            // to avoid unnecessary checks
            else if(!isValidCharacter(text.at(j),_validCharacters)){
                i++;
                j++;
            } 
        } 
    } // End for
    
    inputStream.close();
}

Language BigramCounter::toLanguage() const{
    Language lang;

    int num_chars = this->getSize();
    
    BigramFreq bigramfreq;
    Bigram bigram;

    for (unsigned int i=0;i<num_chars;i++){
        bigram.at(0) = this->_validCharacters[i];
        for (unsigned int j=0;j<num_chars;j++){
            bigram.at(1) = this->_validCharacters[j];

            bigramfreq.setBigram(bigram);
            bigramfreq.setFrequency((*this)(i, j));
            
            if(bigramfreq.getFrequency()!=0){
                lang.append(bigramfreq);
            }
            
        }
    }

    lang.sort();

    return lang;
}

const int& BigramCounter::operator()(int row, int column) const{
    return _frequency[row][column];
}

int& BigramCounter::operator()(int row, int column){
    return _frequency[row][column];
}

void BigramCounter::allocate(int n_elements){
    _frequency = new int*[n_elements];
    _frequency[0] = new int[n_elements*n_elements];
    for (unsigned int i=1;i<n_elements;++i){
        _frequency[i]=_frequency[i-1]+n_elements;
    }
}


void BigramCounter::deallocate(){
    delete [] _frequency[0];
    delete [] _frequency;
    _frequency=nullptr;
}

void BigramCounter::resetMatrix(){
    int length = this->getSize();

    for (unsigned int i=0;i<length;i++){
        for (unsigned int j=0;j<length;j++){
            _frequency[i][j]=0;
        }
    }
}