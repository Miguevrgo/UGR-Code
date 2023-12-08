/**
 * @file almacen.cpp
 * @brief Fichero implementación del TDA Almacen que se usará para almacenar las rutas aéreas
 */

#include "almacen.h"

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
    rutas.at(id).SetId(id); //TODO: Esto es necesario?
}

std::ostream &operator<<(std::ostream &os, const Almacen &almacen){
    os << "#Rutas" << std::endl;
    for (Almacen::const_iterator it = almacen.begin(); it != almacen.end(); ++it){
        os << *it << std::endl;
    }
    return os;
}

std::istream &operator>>(std::istream &is, Almacen &almacen){
    std::string MAGIC;
    is >> MAGIC;
    if (MAGIC != "#Rutas"){
        is.setstate(std::ios::failbit);
        return is;
    }
    
    while(!is.eof()){
        Ruta ruta;
        is >> ruta;
        if (is.good()){
            almacen.InsertarRuta(ruta);
        }
    }
    return is;
}
