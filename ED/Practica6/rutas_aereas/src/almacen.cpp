/**
 * @file almacen.cpp
 * @brief Fichero implementación del TDA Almacen que se usará para almacenar las rutas aéreas
 */

#include "almacen.h"
#include <sstream>

Almacen &Almacen::operator=(const Almacen &rhs){
    if (this != &rhs){
        rutas = rhs.rutas;
    }
    return *this;
}

const Ruta &Almacen::operator[](const std::string &id) const{
    return rutas.at(id);
}

const Ruta &Almacen::GetRuta(const std::string &id){
    return rutas.at(id);
}

Ruta Almacen::GetRuta(const std::string &id) const{
    return rutas.at(id);
}

void Almacen::InsertarRuta(const Ruta &newRuta){
    rutas.insert(std::pair<std::string, Ruta>(newRuta.GetId(), newRuta));
}

void Almacen::EliminarRuta(const std::string &id){
    rutas.erase(id);
}

void Almacen::ModificarRuta(const std::string &id, const Ruta &newRuta){
    rutas.at(id) = newRuta;
    rutas.at(id).SetId(id);
}

std::ostream &operator<<(std::ostream &os, const Almacen &almacen){
    for (auto it = almacen.cbegin(); it != almacen.cend(); ++it){
        os << it->second << std::endl;
    }
    return os;
}

std::istream &operator>>(std::istream &is, Almacen &almacen) {
    std::string MAGIC;
    getline(is, MAGIC);
    if (MAGIC != "#Rutas") {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::string linea, nombreActual;
    int tamActual = 0, puntosLeidos = 0;
    std::list<Punto> puntosActuales;
    bool esNuevaRuta = true;

    while (getline(is, linea)) {
        std::istringstream iss(linea);

        if (linea[0] != 'R' && esNuevaRuta) {
            // Leer la siguiente linea
            continue;
        }
        if (esNuevaRuta) {
            iss >> nombreActual >> tamActual;
            puntosLeidos = 0;
            esNuevaRuta = false;
        }

        while (puntosLeidos < tamActual && iss) {
            char aux;
            double primero, segundo;
            if (!(iss >> aux >> primero >> aux >> segundo >> aux)) {
                break; // Error de formato o fin de línea
            }
            puntosActuales.emplace_back(primero, segundo);
            puntosLeidos++;
        }

        if (puntosLeidos == tamActual) {
            almacen.InsertarRuta(Ruta(nombreActual, puntosActuales));
            puntosActuales.clear();
            esNuevaRuta = true; // Prepararse para la próxima ruta
        }
    }

    return is;
}


