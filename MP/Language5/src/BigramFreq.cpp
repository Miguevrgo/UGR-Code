/**
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 **/

/**
 * @file BigramFreq.cpp
 * @author Miguel Ángel De la Vega Rodríguez <miguevrod@correo.ugr.es>
 * @version 0.1
 * @date 2023-13-5
 * 
 */

#include <BigramFreq.h>


BigramFreq::BigramFreq(Bigram bigram,int frequency){
    _bigram=bigram;
    _frequency=frequency;
}

const Bigram& BigramFreq::getBigram() const{
    return _bigram;
}

int BigramFreq::getFrequency() const{
    return _frequency;
}

void BigramFreq::setBigram(const Bigram &bigram){
    _bigram=bigram;
}

void BigramFreq::setFrequency(int frequency){
    if (frequency<0){
        throw std::out_of_range(std::string("invalid frequency") + std::to_string(frequency));
    }
    else{
        _frequency=frequency;
    }
}

std::string BigramFreq::toString() const{
    return(_bigram.toString() + " " + std::to_string(_frequency));
}

void BigramFreq::serialize(std::ostream &outputStream){
    this->_bigram.serialize(outputStream);
    outputStream.write(reinterpret_cast<const char*>(&_frequency), sizeof(_frequency));
}

void BigramFreq::deserialize(std::istream& inputStream){
    this->_bigram.deserialize(inputStream);
    inputStream.read(reinterpret_cast<char*>(&_frequency), sizeof(_frequency));
}

std::ostream &operator<<(std::ostream &os,const BigramFreq& bigramFreq){
    os << bigramFreq.toString();
    return os;
}

std::istream &operator>>(std::istream &is, BigramFreq& bigramFreq){
    std::string text;
    unsigned int frequency;

    is >> text >> frequency;
    bigramFreq = BigramFreq(Bigram(text),frequency);

    return is;
}

bool operator>(const BigramFreq& bigramFreq1, const BigramFreq& bigramFreq2) {
    bool greater = false;

    if (bigramFreq1.getFrequency() > bigramFreq2.getFrequency()) {
        greater = true;
    } else if (bigramFreq1.getFrequency() == bigramFreq2.getFrequency()) {
        if (bigramFreq1.getBigram().getText().compare(bigramFreq2.getBigram().getText()) < 0) {
            greater = true;
        }
    }

    return greater;
}

bool operator<(const BigramFreq& bigramFreq1,const BigramFreq& bigramFreq2){
    return !((bigramFreq1 > bigramFreq2) || (bigramFreq1 == bigramFreq2));
}

bool operator==(const BigramFreq& bigramFreq1,const BigramFreq& bigramFreq2){
    bool equal = false;

    if (bigramFreq1.getFrequency() == bigramFreq2.getFrequency()){
        if (bigramFreq1.getBigram().getText().compare(bigramFreq2.getBigram().getText()) == 0){
            equal = true;
        }
    }

    return equal;
}

bool operator!=(const BigramFreq& bigramFreq1,const BigramFreq& bigramFreq2){
    return(!(bigramFreq1 == bigramFreq2));
}

bool operator<=(const BigramFreq& bigramFreq1,const BigramFreq& bigramFreq2){
    return(!(bigramFreq1 > bigramFreq2));
}

bool operator>=(const BigramFreq& bigramFreq1,const BigramFreq& bigramFreq2){
    return(!(bigramFreq1 < bigramFreq2));
}