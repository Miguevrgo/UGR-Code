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
     * @brief Devuelve un iterador que apunta al inicio del map de rutas.
     * @return Iterador al inicio del map de rutas.
     */
    std::map<std::string, Ruta>::iterator begin() {return rutas.begin();};

    /**
     * @brief Devuelve un iterador que apunta al final del map de rutas.
     * @return Iterador al final del map de rutas.
     */
    std::map<std::string, Ruta>::iterator end() {return rutas.end();};

    /**
     * @brief Class iterator que permite recorrer el almacen y modificarlo
     */
    class iterator{
    private:
        std::map<std::string, Ruta>::iterator it;
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
         * @brief Operador de desigualdad.
         * @param rhs Objeto iterator a comparar.
         * @return true si ambos iterators son diferentes, false en caso contrario.
         */
        bool operator!=(const iterator &rhs) const { return !(*this == rhs); };

        /**
         * @brief Operador de desreferenciación de iterador
         * @return Referencia al @b Ruta que apunta el iterator
         */
        Ruta &operator*() { return it->second; };

        // Declaramos amigas la clase Almacen y la clase const_iterator
        friend class Almacen;
        friend class const_iterator;
    };

    /**
     * @brief Devuelve un iterador constante que apunta al inicio del map de rutas.
     * @return Iterador constante al inicio del map de rutas.
     */
    std::map<std::string, Ruta>::const_iterator cbegin() const {return rutas.cbegin();};

    /**
     * @brief Devuelve un iterador constante que apunta al final del map de rutas.
     * @return Iterador constante al final del map de rutas.
     */
    std::map<std::string, Ruta>::const_iterator cend() const {return rutas.cend();};

    /**
     * @brief Class const_iterator que permite recorrer el almacen sin modificarlo
     */
    class const_iterator{
    private:
        std::map<std::string, Ruta>::const_iterator it;
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
         * @return Referencia constante al @b Ruta que apunta el iterator
         */
        const Ruta &operator*() const { return it->second; };

        // Declaramos amiga la clase Almacen, para que el iterator pueda acceder a los campos privados.
        friend class Almacen;
    };

public:
    /**
     * @brief Constructor por defecto.
     */
    Almacen() = default;

    /**
     * @brief Constructor de copia.
     * @param rhs Objeto @b Almacen a copiar.
     */
    Almacen(const Almacen &rhs) { rutas = rhs.rutas; };

    /**
     * @brief Operador de asignación.
     * @param rhs Objeto @b Almacen a asignar.
     * @return Referencia al objeto @b Almacen asignado.
     */
    Almacen &operator=(const Almacen &rhs);

    /**
     * @brief Destructor por defecto.
     */
    ~Almacen() = default;

    /**
     * @brief Operador de acceso para obtener una referencia constante a una Ruta a través de su identificador.
     * @param id Identificador de la Ruta.
     * @return Referencia constante a la Ruta correspondiente al identificador.
     */
    const Ruta& operator[](const std::string &id) const;

    /**
     * @brief Obtiene una referencia a una Ruta por su identificador.
     * @param id Identificador de la Ruta.
     * @return Referencia a la Ruta correspondiente al identificador.
     */
    const Ruta& GetRuta(const std::string &id);

    /**
     * @brief Obtiene una copia constante de una Ruta por su identificador.
     * @param id Identificador de la Ruta.
     * @return Copia constante de la Ruta correspondiente al identificador.
     */
    Ruta GetRuta(const std::string &id) const;

    /**
     * @brief Obtiene el identificador de la primera Ruta en el Almacén.
     * @return Identificador de la primera Ruta.
     */
    std::string GetId(){ return rutas.begin()->first; }

    /**
     * @brief Inserta una nueva Ruta en el Almacén.
     * @param newRuta Ruta a insertar.
     */
    void InsertarRuta(const Ruta &newRuta);

    /**
     * @brief Elimina una Ruta del Almacén por su identificador.
     * @param id Identificador de la Ruta a eliminar.
     */
    void EliminarRuta(const std::string &id);

    /**
     * @brief Modifica una Ruta en el Almacén por su identificador.
     * @param id Identificador de la Ruta a modificar.
     * @param newRuta Nueva Ruta que reemplazará a la existente.
     */
    void ModificarRuta(const std::string &id, const Ruta &newRuta);

    /**
     * @brief Operador de salida que imprime el Almacén en el flujo de salida.
     * @param os Flujo de salida.
     * @param almacen Objeto Almacen a imprimir.
     * @return Flujo de salida modificado.
     */
    friend std::ostream& operator<<(std::ostream &os, const Almacen &almacen);

    /**
     * @brief Operador de entrada que lee el Almacén desde el flujo de entrada.
     * @param is Flujo de entrada.
     * @param almacen Objeto Almacen a leer.
     * @return Flujo de entrada modificado.
     */
    friend std::istream& operator>>(std::istream &is, Almacen &almacen);

private:
    std::map<std::string, Ruta> rutas;
};


#endif //PRACTICAFINAL_ALMACEN_H
