/**
 * @file pais.h
 * @author Miguel Angel De la Vega Rodriguez
 * @author Joaquín Aviles De la Fuente
 * @brief Fichero cabecera del TDA Pais
 *
 * Gestiona la informacion relativa a un pais como su nombre, su bandera y sus coordenadas
 */

#ifndef PRACTICAFINAL_PAIS_H
#define PRACTICAFINAL_PAIS_H

#include "punto.h"

class Pais {
private:
    Punto pais; // Coordenadas del pais
    std::string nombre; // Nombre del pais
    std::string bandera; // Fichero de la bandera
public:

    /**
     * @brief Constructor por defecto.
     */
    Pais() = default;

    /**
     * @brief Constructor de copia.
     * @param rhs Objeto @b Pais a copiar.
     */
    Pais(const Pais &rhs) : pais(rhs.pais), nombre(rhs.nombre), bandera(rhs.bandera) {};

    /**
     * @brief Operador de asignación por defecto.
     * @param rhs Objeto @b Pais a asignar.
     * @return Referencia al objeto @b Pais asignado.
     */
    Pais &operator=(const Pais &rhs) = default;

    /**
     * @brief Destructor por defecto.
     */
    ~Pais() = default;

    /**
     * @brief Obtiene las coordenadas del país.
     * @return Referencia constante a las coordenadas del país.
     */
    const Punto &GetPais() const { return pais; };

    /**
     * @brief Obtiene el nombre del país.
     * @return Referencia constante al nombre del país.
     */
    const std::string &GetNombre() const { return nombre; };

    /**
     * @brief Obtiene la ruta al fichero de la bandera del país.
     * @return Referencia constante a la ruta de la bandera del país.
     */
    const std::string &GetBandera() const { return bandera; };

    /**
     * @brief Establece las coordenadas del país.
     * @param pais Coordenadas a establecer.
     */
    void SetPais(const Punto &pais) { this->pais = pais; };

    /**
     * @brief Establece el nombre del país.
     * @param nombre Nombre a establecer.
     */
    void SetNombre(const std::string &nombre) { this->nombre = nombre; };

    /**
     * @brief Establece la ruta al fichero de la bandera del país.
     * @param bandera Ruta de la bandera a establecer.
     */
    void SetBandera(const std::string &bandera) { this->bandera = bandera; };

    /**
     * @brief Operador de comparación menor que.
     * @param rhs Objeto Pais a comparar.
     * @return true si el país es menor que el país de rhs, false en caso contrario.
     */
    bool operator<(const Pais &rhs) const { return pais < rhs.pais; };

    /**
     * @brief Operador de comparación mayor que.
     * @param rhs Objeto Pais a comparar.
     * @return true si el país es mayor que el país de rhs, false en caso contrario.
     */
    bool operator>(const Pais &rhs) const { return rhs < *this; };

    /**
     * @brief Operador de igualdad.
     * @param rhs Objeto @b Pais a comparar.
     * @return true si los países son iguales, false en caso contrario.
     */
    bool operator==(const Pais &rhs) const { return pais == rhs.pais; };

    /**
     * @brief Operador de igualdad con Punto.
     * @param rhs Punto a comparar con las coordenadas del país.
     * @return true si las coordenadas del país son iguales a rhs, false en caso contrario.
     */
    bool operator==(const Punto &rhs) const { return pais == rhs; };

    /**
     * @brief Operador de igualdad con string.
     * @param rhs String a comparar con nombre o bandera del país.
     * @return true si el nombre o la bandera del país son iguales a rhs, false en caso contrario.
     */
    bool operator==(const std::string &rhs) const { return (nombre == rhs || bandera == rhs); };

    /**
     * @brief Operador de desigualdad.
     * @param rhs Objeto Pais a comparar.
     * @return true si los países son diferentes, false en caso contrario.
     */
    bool operator!=(const Pais &rhs) const { return !(*this == rhs); };

    /**
     * @brief Sobrecarga del operador de salida para mostrar un pais en el formato:
     *
     * Latitud Longitud Nombre Bandera
     *
     * @param os Flujo de salida
     * @param pais Pais a mostrar por el flujo
     * @return Flujo de salida
     */
    friend std::ostream &operator<<(std::ostream &os, const Pais &pais);

    /**
     * @brief Sobrecarga del operador de entrada para leer un pais en el formato:
     *
     * Latitud Longitud Nombre Bandera
     *
     * @param is Flujo de entrada
     * @param pais Pais a leer por el flujo
     * @return Flujo de entrada
     */
    friend std::istream &operator>>(std::istream &is, Pais &pais);
};


#endif //PRACTICAFINAL_PAIS_H
