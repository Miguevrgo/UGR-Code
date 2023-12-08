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
    class const_iterator{ //TODO: Copiadas de ruta.h, cambiar si es necesario
    private:
        friend class Almacen;
        std::map<std::string, Ruta>::const_iterator it;
    public:
        const_iterator() : it() {};
        const_iterator(const const_iterator &rhs) : it(rhs.it) {};
        const_iterator(const std::map<std::string, Ruta>::const_iterator &rhs) : it(rhs) {};
        const_iterator& operator=(const const_iterator &rhs);
        ~const_iterator() = default;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        const Punto& operator*() const;
        bool operator==(const const_iterator &rhs) const;
        bool operator!=(const const_iterator &rhs) const;
    };

    class iterator{
    private:
        friend class Almacen;
        friend class const_iterator;
        std::map<std::string, Ruta>::iterator it;
    public:
        iterator() : it() {};
        iterator(const iterator &rhs) : it(rhs.it) {};
        iterator& operator=(const iterator &rhs);
        ~iterator() = default;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        Punto& operator*() const;
        bool operator==(const iterator &rhs) const;
        bool operator!=(const iterator &rhs) const;
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
    const_iterator begin() const { return const_iterator{rutas.begin()}; };
    const_iterator end() const { return const_iterator{rutas.end()}; };
    void ModificarRuta(const std::string &id, const Ruta &newRuta);
    friend std::ostream& operator<<(std::ostream &os, const Almacen &almacen);
    friend std::istream& operator>>(std::istream &is, Almacen &almacen);   
private:
    std::map<std::string, Ruta> rutas;
};


#endif //PRACTICAFINAL_ALMACEN_H
