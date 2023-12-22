/**
 * @file pais.cpp
 * @author Miguel Angel De la Vega Rodriguez
 * @author Joaquín Aviles De la Fuente
 * @brief Implementación de los metodos de la clase pais
 */

#include "pais.h"

std::ostream &operator<<(std::ostream &os, const Pais &pais) {
    os << pais.GetPais().GetLat() << " " << pais.GetPais().GetLon()
       << " " << pais.GetNombre() << " " << pais.GetBandera();
    return os;
}

std::istream &operator>>(std::istream &is, Pais &pais) {
    Punto p;
    std::string nombre, bandera;
    is >> p >> nombre >> bandera;
    pais.SetPais(p);
    pais.SetNombre(nombre);
    pais.SetBandera(bandera);
    return is;
}
