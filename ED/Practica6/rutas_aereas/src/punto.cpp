/**
 * @file punto.cpp
 * @author Miguel Angel de la vega Rodriguez
 * @author Joaquin Aviles De la Fuente 
 * @brief Definicion de los métodos de la clase punto
 */

#include "punto.h"
#include <sstream>

std::ostream &operator<<(std::ostream &os, const Punto &punto){
    os << " (" << punto.lat << "," << punto.lon << ")";
    return os;
}

std::istream &operator>>(std::istream &is, Punto &punto){
    while (is.peek() == ' ' || is.peek() == '(' || is.peek() == '\t' || is.peek() == '\n'){
        is.ignore();
    }
    is >> punto.lat;

    while (is.peek() == ' ' || is.peek() == ',' || is.peek() == '\t' || is.peek() == '\n'){
        is.ignore();
    }
    is >> punto.lon;
    while (is.peek() == ' ' || is.peek() == ')' || is.peek() == '\t' || is.peek() == '\n'){
        is.ignore();
    }
    return is;
}
