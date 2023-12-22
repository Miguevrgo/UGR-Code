/**
 * @file almacen.h
 * @brief Fichero cabecera del TDA Almacen que se usará para almacenar las rutas aéreas
 * Y de las clases iterator y const_iterator que permiten recorrer el almacen
 * @author Miguel Angel De la Vega Rodríguez
 * @author Joaquin Avilés De la Fuente
 * 
 */

#ifndef PRACTICAFINAL_ALMACEN_H
#define PRACTICAFINAL_ALMACEN_H

#include "ruta.h"
#include <map>


class Almacen {
    /**
     * @brief Class iterator que permite recorrer el almacen y modificarlo
     */
    std::map<std::string, Ruta>::iterator begin() {return rutas.begin();};
    std::map<std::string, Ruta>::iterator end() {return rutas.end();};
    class iterator{
    private:
        std::map<std::string, Ruta>::iterator it;
    public:
        iterator() = default;
        iterator(const iterator &rhs) : it(rhs.it) {};
        ~iterator() = default;
        iterator &operator=(const iterator &rhs) {it = rhs.it; return *this;};
        iterator &operator++() {++it; return *this;};
        iterator &operator--() {--it; return *this;};
        bool operator==(const iterator &rhs) const {return it == rhs.it;};
        bool operator!=(const iterator &rhs) const {return !(*this == rhs);};
    };

    /**
     * @brief Class const_iterator que permite recorrer el almacen sin modificarlo 
     */
    std::map<std::string, Ruta>::const_iterator cbegin() const {return rutas.cbegin();};
    std::map<std::string, Ruta>::const_iterator cend() const {return rutas.cend();};
    class const_iterator{
    private:
        std::map<std::string, Ruta>::const_iterator it;
    public:
        const_iterator() = default;
        const_iterator(const const_iterator &rhs) : it(rhs.it) {};
        ~const_iterator() = default;
        const_iterator &operator=(const const_iterator &rhs) {it = rhs.it; return *this;};
        const_iterator &operator++() {++it; return *this;};
        const_iterator &operator--() {--it; return *this;};
        bool operator==(const const_iterator &rhs) const {return it == rhs.it;};
        bool operator!=(const const_iterator &rhs) const {return !(*this == rhs);};
    };

public:
    Almacen() = default;
    Almacen(const Almacen &rhs) { rutas = rhs.rutas; };
    Almacen &operator=(const Almacen &rhs);
    ~Almacen() = default;
    const Ruta& operator[](const std::string &id) const;
    const Ruta& GetRuta(const std::string &id);
    Ruta GetRuta(const std::string &id) const;
    std::string GetId(){ return rutas.begin()->first; }
    void InsertarRuta(const Ruta &newRuta);
    void EliminarRuta(const std::string &id);
    void ModificarRuta(const std::string &id, const Ruta &newRuta);
    friend std::ostream& operator<<(std::ostream &os, const Almacen &almacen);
    friend std::istream& operator>>(std::istream &is, Almacen &almacen);   
private:
    std::map<std::string, Ruta> rutas;
};


#endif //PRACTICAFINAL_ALMACEN_H
