/**
 * @file Bigram.cpp
 * @author Miguel Ángel De La Vega Rodríguez <miguevrod@correo.ugr.es>
 * 
 * @date 2023-03-02
 * 
 */

#include <iostream>
#include "Bigram.h"



using namespace std;

Bigram::Bigram(const string& text) {
    if (text.length() == 2){
        _text = text;
    }
    else{
        _text= "__";
    }
}

Bigram::Bigram(char first, char second){
    _text = string(1, first) + string(1, second);
}

string Bigram::getText() const{  
    return _text;
}

string Bigram::toString() const{
    return _text;
}

const char& Bigram::at(int index) const{
    if(index<0 || index >1){ //the violation of the precondition
        throw out_of_range(string("const char&Bigram::at(int index) const:") + "invalid position " + to_string(index));
    } 
    else{
        return (_text[index]); // could have used .at(), however, it is checked in the previous condition that we are getting a valid index
    }
}

char &Bigram::at(int index){
    if(index<0 || index >1){ //the violation of the precondition
        throw out_of_range(string("const char&Bigram::at(int index) const:") + "invalid position " + to_string(index));
    } 
    else{
        return (_text[index]); // could have used .at(), however, it is checked in the previous condition that we are getting a valid index
    }
}



bool isValidCharacter(char character, const string& validCharacters){
    return(validCharacters.find(character) != string::npos); //If we were using C++23 we could have used the string function contains()
}

void toUpper(Bigram &bigram){
    for (int i=0;i<2;i++){
        bigram.at(i) = toupper(bigram.at(i));
    }
    
}