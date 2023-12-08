/* 
 * File:   Dispositivo.cpp
 * Author: Silvia Acid y Andrés Cano
 * 
 * Created on 28 April 2023, 13:05
 */

#include <cmath>

#include "Dispositivo.h"

using namespace std;

Dispositivo::Dispositivo(){
    _x = _y = 0;
    _id = 0;
    _potencia = 0.0;
}
Dispositivo::Dispositivo(long id){
    _x = _y = 0;
    _id = id;
    _potencia = 0.0;
}
Dispositivo::Dispositivo(long id, float x, float y, double potencia){
    _x = x;
    _y = y;
    _id = id;
    if (esPositivo(potencia))
       _potencia = potencia;
    else _potencia = 0.0;
}
long Dispositivo::getId() const{
    return _id;
}
float Dispositivo::getX() const{
    return _x;
}
float Dispositivo::getY() const{
    return _y;
}
double Dispositivo::getPotencia()const{
    return _potencia;
}
void Dispositivo::set(long id, float x, float y, double potencia){
    _x = x;
    _y = y;
    _id = id;
    if (esPositivo(potencia))
       _potencia = potencia;
    else potencia = 0.0;
}

string Dispositivo::toString() const{
      string ss = to_string(getId()) + "->(" + to_string(getX()) + "," + to_string(getY())
              + "," + to_string(getPotencia()) + "),";
      return ss;
}

float Dispositivo::distancia(const Dispositivo &d) const{
    float x = fabs(this->getX() - d.getX());
    float y = fabs(this->getY() - d.getY());

    return (sqrt(x * x + y * y));
}

