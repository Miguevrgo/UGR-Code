/**
 * @file ruta.cpp
 * @author Miguel Angel De la Vega Rodriguez
 * @author Joaquín Aviles De la Fuente
 * @brief Definición de la clase ruta que representa una ruta aerea
 * Y de las clases iterator y const_iterator que permiten recorrer la ruta
 * 
 */

#ifndef PRACTICAFINAL_RUTA_H
#define PRACTICAFINAL_RUTA_H

#include <list>
#include <string>
#include "punto.h"




class Ruta {
    class const_iterator{
    private:
        friend class Ruta;
        std::list<Punto>::const_iterator it;
    public:
        const_iterator() : it() {};
        const_iterator(const const_iterator &rhs) : it(rhs.it) {};
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
        friend class Ruta;
        friend class const_iterator;
        std::list<Punto>::const_iterator it;
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
    Ruta() : id(""), ruta() {};
    Ruta(std::string id, std::list<Punto> ruta) : id(id), ruta(ruta) {};
    Ruta(const Ruta &rhs) : id(rhs.id), ruta(rhs.ruta) {};
    Ruta &operator=(const Ruta &rhs);
    ~Ruta() = default;
    std::string GetId() const { return id;};
    void SetId(std::string id) { this->id = id;};
    Punto GetPunto(int pos) const;
    int GetNumPuntos() const;
    bool operator==(const Ruta &rhs) const;
    bool operator!=(const Ruta &rhs) const;
    void Insert(const Punto &punto, int pos = -1);
    void RemovePunto(int pos);
    void Clear();
    void Append(const Ruta &rhs);
    Ruta& operator+(const Ruta &rhs) const;
    void ReverseRuta();
    int GetSize() const { return ruta.size();};
    friend std::ostream& operator<<(std::ostream &os, const Ruta &ruta);
    friend std::istream& operator>>(std::istream &is, Ruta &ruta);

private:
    std::list<Punto> ruta;
    std::string id;
};

#endif //PRACTICAFINAL_RUTA_H
