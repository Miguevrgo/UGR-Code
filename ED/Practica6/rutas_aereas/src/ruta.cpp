//TODO: Corregir iteradores y operador de entrada

/**
 * @file ruta.cpp
 * @author Miguel Angel De la Vega Rodriguez
 * @author Joaquín Aviles De la Fuente
 * @brief Implementación de la clase ruta
 * 
 */

#include "ruta.h"

Ruta &Ruta::operator=(const Ruta &rhs){
    if(this != &rhs){
        id = rhs.id;
        ruta = rhs.ruta;
    }
    return *this;
}

Punto Ruta::GetPunto(int pos) const{
    std::list<Punto>::const_iterator it = ruta.begin();
    std::advance(it, pos);
    return *it;
}

int Ruta::GetNumPuntos() const{
    return ruta.size();
}

bool Ruta::operator==(const Ruta &rhs) const{
    return (id == rhs.id && ruta == rhs.ruta);
}

bool Ruta::operator!=(const Ruta &rhs) const{
    return !(*this == rhs);
}

void Ruta::Insert(const Punto &punto, int pos){
    if(pos == -1){
        ruta.push_back(punto);
    }
    else{
        ruta.insert(std::next(ruta.begin(),pos), punto);
    }
}

void Ruta::RemovePunto(int pos){
    ruta.erase(std::next(ruta.begin(), pos));
}

void Ruta::Clear(){
    ruta.clear();
}

void Ruta::Append(const Ruta &rhs)
{
    ruta.insert(ruta.end(), rhs.ruta.begin(), rhs.ruta.end());
}

Ruta& Ruta::operator+(const Ruta &rhs) const{
    Ruta aux(*this);
    aux.Append(rhs);
    return aux;
}

void Ruta::ReverseRuta(){
    ruta.reverse();
}

Ruta::const_iterator& Ruta::const_iterator::operator=(const Ruta::const_iterator &rhs)
{
    if(this != &rhs){
        it = rhs.it;
    }
    return *this;
}

Ruta::const_iterator& Ruta::const_iterator::operator++() {
    ++it;
    return *this;
}

Ruta::const_iterator Ruta::const_iterator::operator++(int) {
    const_iterator tmp(*this);
    ++it;
    return tmp;
}

Ruta::const_iterator &Ruta::const_iterator::operator--() {
    --it;
    return *this;
}

Ruta::const_iterator Ruta::const_iterator::operator--(int) {
    const_iterator tmp(*this);
    --it;
    return tmp;
}

const Punto &Ruta::const_iterator::operator*() const {
    return *it;
}

bool Ruta::const_iterator::operator==(const const_iterator &rhs) const {
    return (it == rhs.it);
}

bool Ruta::const_iterator::operator!=(const const_iterator &rhs) const {
    return !(*this == rhs);
    }

std::ostream &operator<<(std::ostream &os, const Ruta &ruta) {
    os << ruta.id << " ";
    os << ruta.GetSize() << " ";
    for(auto it = ruta.ruta.begin(); it != ruta.ruta.end(); ++it){
        os << " (" << *it << ") ";
    }
    return os;    
}

std::istream &operator>>(std::istream &is, Ruta &ruta) {
    int size;
    is >> ruta.id >> size;
    for(int i = 0; i < size; ++i){
        Punto aux;
        is >> aux;
        ruta.Insert(aux);
    }
    return is;
}
