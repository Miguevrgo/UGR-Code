/**
 * @file BigramFreq.cpp
 * @author Miguel Ángel De la Vega Rodríguez(miguevrod@correo.ugr.es)
 * @version 0.1
 * @date 2023-03-13
 * 
 */


#include <string>
#include "BigramFreq.h"


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

