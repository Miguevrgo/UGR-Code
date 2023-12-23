/**
 * @file paises.cpp
 * @author Miguel Angel De la Vega Rodriguez
 * @author Joaquín Aviles De la Fuente
 * @brief Fichero implementacion del TDA Paises
 *
 */

#include <sstream>
#include "paises.h"

Paises::iterator Paises::find(const std::string &nombre) {
    for (auto it = paises.begin(); it != paises.end(); ++it) {
        if (it->GetNombre() == nombre) {
            Paises::iterator pit;
            pit.setIt(it);
            return pit;
        }
    }
    Paises::iterator pit;
    pit.setIt(paises.end());
    return pit; // Retorna end() si no se encuentra el país
}


Paises::iterator Paises::find(const Punto &punto) {
    for (auto it = paises.begin(); it != paises.end(); ++it) {
        if (it->GetPais()== punto) {
            Paises::iterator pit;
            pit.setIt(it);
            return pit;
        }
    }
    Paises::iterator pit;
    pit.setIt(paises.end());
    return pit; // Retorna end() si no se encuentra el país
}

Pais Paises::GetPais(const Punto &punto){
    iterator it = find(punto);
    if (it != end()) {
        return *it;
    }
    else {
        throw std::out_of_range("El país con el nombre especificado no se encuentra en la colección.");
    }
}

Pais Paises::GetPais(const std::string &nombre){
    iterator it = find(nombre);
    if (it != end()) {
        return *it;
    }
    else {
        throw std::out_of_range("El país con el nombre especificado no se encuentra en la colección.");
    }
}

void Paises::InsertPais(const Pais &pais) {
    if (find(pais.GetNombre()) == end()) {
        paises.insert(pais);
    }
}

void Paises::ErasePais(const std::string& nombre) {
    iterator it = find(nombre);
    if (it != end()) {
        paises.erase(*it);
    }
}

std::ostream &operator<<(std::ostream &os, const Paises &paises) {
    os << "#Latitud " << "Longitud " << "Nombre " << "Bandera" << std::endl;
    for (const auto & pais : paises) {
        os << pais << " " << std::endl;
    }

    return os;
}

std::istream &operator>>(std::istream &is, Paises &paises) {
    std::string line;
    std::getline(is, line);
    while (!is.eof()) {
        std::getline(is, line);
        std::istringstream iss(line);
        Pais pais;
        iss >> pais;
        paises.InsertPais(pais);
    }
    return is;
}
