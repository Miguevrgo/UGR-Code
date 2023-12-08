/**
 * Metodología de la Programación: Language4
 * Curso 2022/2023
 **/

/**
 * @file Bigram.cpp
 * @author Miguel Ángel De la Vega Rodríguez<miguevrod@correo.ugr.es>
 * @version 0.1
 * @date 2023-04-24
 * 
 */


#include "Bigram.h"

Bigram::Bigram(const std::string& text) {
    if (text.length() == 2){
        strcpy (_text, text.c_str());
    }
    else{
        strcpy (_text,"__");
    }
}

Bigram::Bigram(char first, char second) : _text{first, second, '\0'} {}

Bigram::Bigram(const char text[]){
    if (strlen(text) == 2){
        strcpy (_text,text);
    }
    else{
        strcpy (_text,"__");
    }
}

std::string Bigram::getText() const{  
    return _text;
}

std::string Bigram::toString() const{
    return _text;
}

const char& Bigram::at(int index) const{
    if(index<0 || index >1){ //the violation of the precondition
        throw std::out_of_range(std::string("const char&Bigram::at(int index) const:") + "invalid position " + std::to_string(index));
    } 
    else{
        return (_text[index]);
    }
}

char &Bigram::at(int index){
    if(index<0 || index >1){ //the violation of the precondition
        throw std::out_of_range(std::string("const char&Bigram::at(int index) const:") + "invalid position " + std::to_string(index));
    } 
    else{
        return (_text[index]);
    }
}

void Bigram::toUpper(){
    for (int i=0;i<2;i++){
        _text[i] = toupper(_text[i]);
    }
    
}



bool isValidCharacter(char character, const std::string& validCharacters){
    return(validCharacters.find(character) != std::string::npos); //If we were using C++23 we could have used the string function contains()
}

