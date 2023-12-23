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
#include <iterator>
#include "punto.h"


class Ruta {

    /**
     * @brief Devuelve un iterador que apunta al inicio de la lista de puntos.
     * @return Iterador al inicio de la lista de puntos.
     */
    std::list<Punto>::iterator begin() {return ruta.begin();};

    /**
     * @brief Devuelve un iterador que apunta al final de la lista de puntos.
     * @return Iterador al final de la lista de puntos.
     */
    std::list<Punto>::iterator end() {return ruta.end();};

    /**
     * @brief Clase interna iterator que proporciona funcionalidades para recorrer y modificar la ruta.
     */
    class iterator{
    private:
        std::list<Punto>::iterator it;
    public:
        /**
         * @brief Constructor por defecto.
         */
        iterator() = default;

        /**
         * @brief Constructor de copia.
         * @param rhs Objeto iterator a copiar.
         */
        iterator(const iterator &rhs) : it(rhs.it) {};

        /**
         * @brief Destructor por defecto.
         */
        ~iterator() = default;

        /**
         * @brief Operador de asignación.
         * @param rhs Objeto iterator a asignar.
         * @return Referencia al objeto iterator asignado.
         */
        iterator &operator=(const iterator &rhs) { it = rhs.it; return *this; };

        /**
         * @brief Operador de incremento.
         * @return Referencia al objeto iterator después de incrementar.
         */
        iterator &operator++() { ++it; return *this; };

        /**
         * @brief Operador de decremento.
         * @return Referencia al objeto iterator después de decrementar.
         */
        iterator &operator--() { --it; return *this; };

        /**
         * @brief Operador de igualdad.
         * @param rhs Objeto iterator a comparar.
         * @return true si ambos iterators son iguales, false en caso contrario.
         */
        bool operator==(const iterator &rhs) const { return it == rhs.it; };

        /**
         * @brief Operador de desigualdad.
         * @param rhs Objeto iterator a comparar.
         * @return true si ambos iterators son diferentes, false en caso contrario.
         */
        bool operator!=(const iterator &rhs) const { return !(*this == rhs); };

        /**
         * @brief Operador de desreferenciación de iterador
         * @return Referencia al @b Punto que apunta el iterator
         */
        Punto &operator*(){return *it;};

        // Declaramos amigas la clase Ruta y la clase const_iterator
        friend class Ruta;
        friend class const_iterator;
    };

    /**
     * @brief Devuelve un iterador constante que apunta al inicio de la lista de puntos.
     * @return Iterador constante al inicio de la lista de puntos.
     */
    std::list<Punto>::const_iterator cbegin() const {return ruta.cbegin();};

    /**
     * @brief Devuelve un iterador constante que apunta al final de la lista de puntos.
     * @return Iterador constante al final de la lista de puntos.
     */
    std::list<Punto>::const_iterator cend() const {return ruta.cend();};

    /**
     * @brief Clase interna const_iterator que proporciona funcionalidades para recorrer la ruta sin modificarla.
     */
    class const_iterator{
    private:
        std::list<Punto>::const_iterator it;
    public:
        /**
         * @brief Constructor por defecto.
         */
        const_iterator() = default;

        /**
         * @brief Constructor de copia.
         * @param rhs Objeto const_iterator a copiar.
         */
        const_iterator(const const_iterator &rhs) : it(rhs.it) {};

        /**
         * @brief Destructor por defecto.
         */
        ~const_iterator() = default;

        /**
         * @brief Operador de asignación.
         * @param rhs Objeto const_iterator a asignar.
         * @return Referencia al objeto const_iterator asignado.
         */
        const_iterator &operator=(const const_iterator &rhs) { it = rhs.it; return *this; };

        /**
         * @brief Operador de incremento prefijo.
         * @return Referencia al objeto const_iterator después de incrementar.
         */
        const_iterator &operator++() { ++it; return *this; };

        /**
         * @brief Operador de decremento prefijo.
         * @return Referencia al objeto const_iterator después de decrementar.
         */
        const_iterator &operator--() { --it; return *this; };

        /**
         * @brief Operador de igualdad.
         * @param rhs Objeto const_iterator a comparar.
         * @return true si ambos const_iterators son iguales, false en caso contrario.
         */
        bool operator==(const const_iterator &rhs) const { return it == rhs.it; };

        /**
         * @brief Operador de desigualdad.
         * @param rhs Objeto const_iterator a comparar.
         * @return true si ambos const_iterators son diferentes, false en caso contrario.
         */
        bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); };

        /**
         * @brief Operador de desreferenciación de iterador
         * @return Referencia constante al @b Punto que apunta el iterator
         */
        const Punto &operator*() const{return *it;};

        // Declaramos amiga la clase Ruta, para que el iterator pueda acceder a los campos privados.
        friend class Ruta;
    };

public:

    /**
     *  @brief Constructor por defecto. Inicializa el ID a una cadena vacía y la lista de puntos a una lista vacía.
     */
    Ruta() : id(""), ruta() {};

    /**
     * @brief Constructor con parámetros.
     *
     * @param id Identificador de la ruta.
     * @param ruta Lista de puntos que forman la ruta.
     */
    Ruta(std::string id, std::list<Punto> ruta) : id(id), ruta(ruta) {};

    /**
     * @brief Constructor de copia.
     *
     * @param rhs Objeto @b Ruta a copiar.
     */
    Ruta(const Ruta &rhs) : id(rhs.id), ruta(rhs.ruta) {};

    /**
     * @brief Operador de asignación.
     *
     * Asigna los valores de otra ruta al objeto actual.
     * @param rhs Ruta a asignar.
     * @return Referencia a la ruta asignada.
     */
    Ruta &operator=(const Ruta &rhs);

    /**
     * @brief Destructor por defecto.
     */
    ~Ruta() = default;

    /**
     * @brief Obtiene el ID de la ruta.
     * @return ID de la ruta.
     */
    std::string GetId() const { return id; };

    /**
     * @brief Establece el ID de la ruta.
     * @param id Nuevo ID de la ruta.
     */
    void SetId(std::string id) { this->id = id; };

    /**
     * @brief Obtiene un punto de la ruta por posición.
     * @param pos Posición del punto en la ruta.
     * @return Punto en la posición especificada.
     */
    Punto GetPunto(int pos) const;

    /**
     * @brief Obtiene la cantidad de puntos en la ruta.
     * @return Tamaño de la ruta.
     */
    int GetSize() const { return ruta.size(); };


    /**
     * @brief Compara dos rutas para determinar si son iguales.
     * @param rhs Ruta a comparar.
     * @return true si las rutas son iguales, false en caso contrario.
     */
    bool operator==(const Ruta &rhs) const;

    /**
     * @brief Compara dos rutas para determinar si son diferentes.
     * @param rhs Ruta a comparar.
     * @return true si las rutas son diferentes, false en caso contrario.
     */
    bool operator!=(const Ruta &rhs) const;

    /**
     * @brief Inserta un punto en la ruta en una posición específica.
     * @param punto Punto a insertar.
     * @param pos Posición de inserción. Si es -1, se inserta al final.
     */
    void Insert(const Punto &punto, int pos = -1);

    /**
     * @brief Elimina un punto de la ruta en una posición específica.
     * @param pos Posición del punto a eliminar.
     */
    void RemovePunto(int pos);

    /**
     * @brief Elimina todos los puntos de la ruta.
     */
    void Clear() { ruta.clear(); };

    /**
     * @brief Agrega los puntos de otra ruta al final de la ruta actual.
     * @param rhs Ruta a agregar.
     */
    void Append(const Ruta &rhs);

    /**
     * @brief Concatena dos rutas y devuelve una referencia a la ruta concatenada
     * 
     * @param rhs Ruta a concatenar
     * @return Ruta& Referencia a la ruta concatenada
     */
    Ruta& operator+(const Ruta &rhs) const;

    /**
     * @brief Le da la vuelta a la ruta
     */
    void ReverseRuta() { ruta.reverse();};
    
    /**
     * @brief Operador de salida de la ruta, imprime la ruta en el flujo de salida
     * con el siguiente formato:
     * ID: id_ruta
     * TAM: num_puntos
     * (lat,lon) (lat,lon) ... (lat,lon)
     * 
     * @return iterator Iterador al principio de la ruta
     */
    friend std::ostream& operator<<(std::ostream &os, const Ruta &ruta);

    /**
     * @brief Operador de entrada de la ruta, lee la ruta del flujo de entrada
     * con el siguiente formato:
     * ID: id_ruta
     * TAM: num_puntos
     * (lat,lon) (lat,lon) ... (lat,lon)
     * 
     * @param is 
     * @param ruta 
     * @return std::istream& 
     */
    friend std::istream& operator>>(std::istream &is, Ruta &ruta);

private:
    std::list<Punto> ruta;
    std::string id;
};

#endif //PRACTICAFINAL_RUTA_H
