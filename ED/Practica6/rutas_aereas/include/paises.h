/**
 * @file paises.h
 * @author Miguel Angel De la Vega Rodriguez
 * @author Joaquín Aviles De la Fuente
 * @brief Fichero cabecera del TDA Paises
 *
 * Gestiona los paises de un mapa
 */

#ifndef PRACTICAFINAL_PAISES_H
#define PRACTICAFINAL_PAISES_H

#include "pais.h"
#include <set>

class Paises {

    /**
     * @brief Devuelve un iterador que apunta al inicio del set de paises.
     * @return Iterador al inicio del set de paises.
     */
    std::set<Pais>::iterator begin() const {return paises.begin();};

    /**
     * @brief Devuelve un iterador que apunta al final del set de paises.
     * @return Iterador al final del set de paises.
     */
    std::set<Pais>::iterator end() const {return paises.end();};

    /**
     * @brief Class iterator que permite recorrer los paises y modificarlos
     */
    class iterator{
    private:
        std::set<Pais>::iterator it;
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
         * @brief Establece el iterador interno con uno dado.
         * @param it Iterador a establecer.
         */
        void setIt(const std::set<Pais>::iterator &it) { this->it = it; };

        /**
         * @brief Operador de asignación.
         * @param rhs Objeto iterator a asignar.
         * @return Referencia al objeto iterator asignado.
         */
        iterator &operator=(const iterator &rhs) { it = rhs.it; return *this; };

        /**
         * @brief Operador de incremento prefijo.
         * @return Referencia al objeto iterator después de incrementar.
         */
        iterator &operator++() { ++it; return *this; };

        /**
         * @brief Operador de decremento prefijo.
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
         * @brief Operador de igualdad con std::set<Pais>::iterator.
         * @param rhs Iterador de conjunto a comparar.
         * @return true si el iterator es igual al iterator del conjunto, false en caso contrario.
         */
        bool operator==(const std::set<Pais>::iterator &rhs) const { return it == rhs; };

        /**
         * @brief Operador de desigualdad.
         * @param rhs Objeto iterator a comparar.
         * @return true si ambos iterators son diferentes, false en caso contrario.
         */
        bool operator!=(const iterator &rhs) const { return !(*this == rhs); };

        /**
         * @brief Operador de desigualdad con std::set<Pais>::iterator.
         * @param rhs Iterador de conjunto a comparar.
         * @return true si el iterator es diferente al iterator del conjunto, false en caso contrario.
         */
        bool operator!=(const std::set<Pais>::iterator &rhs) const { return !(*this == rhs); };

        /**
         * @brief Operador de desreferenciación constante (*).
         * @return Referencia constante a un objeto @b Pais al que apunta el iterador constante.
         */
        const Pais &operator*() { return *it;};

        // Declaramos amigas la clase Paises y la clase const_iterator
        friend class Paises;
        friend class const_iterator;
    };

    /**
     * @brief Devuelve un iterador constante que apunta al inicio del set de paises.
     * @return Iterador constante al inicio del set de paises.
     */
    std::set<Pais>::const_iterator cbegin() const {return paises.cbegin();};

    /**
     * @brief Devuelve un iterador constante que apunta al final del set de paises.
     * @return Iterador constante al final del set de paises.
     */
    std::set<Pais>::const_iterator cend() const {return paises.cend();};

    /**
     * @brief Class const_iterator que permite recorrer los paises sin modificarlos
     */
    class const_iterator{
    private:
        std::set<Pais>::const_iterator it;
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
         * @brief Operador de desreferenciación constante (*).
         * @return Referencia constante a un objeto @b Pais al que apunta el iterador constante.
         */
        const Pais &operator*() const { return *it; };

        // Declaramos amiga la clase Almacen, para que el iterator pueda acceder a los campos privados.
        friend class Almacen;
    };
private:
    std::set<Pais> paises;
public:
    /**
     * @brief Constructor por defecto.
     */
    Paises() = default;

    /**
     * @brief Constructor de copia.
     * @param paises Objeto @b Paises a copiar.
     */
    Paises(const Paises &paises) { this->paises = paises.paises; };

    /**
     * @brief Destructor por defecto.
     */
    ~Paises() = default;

    /**
     * @brief Operador de asignación.
     * @param paises Objeto @b Paises a asignar.
     * @return Referencia al objeto @b Paises asignado.
     */
    Paises &operator=(const Paises &paises) { this->paises = paises.paises; return *this; };

    /**
     * @brief Busca un pais en el conjunto de paises
     * @param nombre Nombre del pais a buscar
     * @return Devuelve un iterador al pais buscado
     * @pre El pais debe estar en el conjunto de paises
     */
    iterator find(const std::string &nombre);

    /**
     * @brief Busca un pais en el conjunto de paises
     * @param punto Punto del pais a buscar
     * @return Devuelve un iterador al pais buscado
     * @pre El pais debe estar en el conjunto de paises
     */
    iterator find(const Punto &punto);

    /**
     * @brief Retorna el pais que se corresponde con el nombre pasado por parametro
     * @param nombre Nombre del pais a buscar
     * @return Devuelve el pais que se corresponde con el nombre pasado por parametro
     * @pre El pais debe estar en el conjunto de paises
     */
    Pais GetPais(const std::string &nombre);
    /**
     * @brief Retorna el pais que se corresponde con el punto pasado por parametro
     * @param punto Punto del pais a buscar
     * @return Devuelve el pais que se corresponde con el punto pasado por parametro
     * @pre El pais debe estar en el conjunto de paises
     */
    Pais GetPais(const Punto &punto);

    /**
     * @brief Inserta un pais en el conjunto de paises si no esta ya
     * @param pais
     */
    void InsertPais(const Pais &pais);
    /**
     * @brief Elimina un pais del conjunto de paises, si no esta no hace nada
     * @param nombre Nombre del pais a eliminar
     */
    void ErasePais(const std::string& nombre);

    /**
     * @brief Comprueba si el objeto @b Paises está vacío
     * @return true si está vacío, en caso contrario false
     */
    bool Empty() const {return paises.empty();};

    /**
     * @brief Imprime en un flujo de salida los paises en el formato:
     *
     * #Latitud Longitud Pais Bandera
     *
     * Y cada pais en una linea diferente
     *
     * @param paises Paises a asignar
     * @return Devuelve una referencia al flujo de salida
     */
    friend std::ostream &operator<<(std::ostream &os, const Paises &paises);


    /**
     * @brief Lee de un flujo de entrada los paises en el formato:
     *
     * #Latitud Longitud Pais Bandera
     *
     * Y cada pais en una linea diferente
     *
     * @param paises Paises a leer del flujo de entrada
     * @return Devuelve una referencia al flujo de entrada
     */
    friend std::istream &operator>>(std::istream &is, Paises &paises);

};


#endif //PRACTICAFINAL_PAISES_H
