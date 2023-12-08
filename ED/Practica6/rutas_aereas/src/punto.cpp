/**
 * @file punto.cpp
 * @author Miguel Angel de la vega Rodriguez
 * @author Joaquin Aviles De la Fuente 
 * @brief Definicion de los metodos de la clase punto
 */

#include "punto.h"

std::ostream &operator<<(std::ostream &os, const Punto &punto){
    os << punto.lat << "," << punto.lon;
    return os;
}

std::istream &operator>>(std::istream &is, Punto &punto){
    char aux;
    is >> aux >> punto.lat >> aux >> punto.lon >> aux;
    return is;
}
