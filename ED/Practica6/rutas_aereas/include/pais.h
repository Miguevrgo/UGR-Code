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
    Pais() = default;
    Pais(const Pais &rhs) : pais(rhs.pais), nombre(rhs.nombre), bandera(rhs.bandera) {};
    Pais &operator=(const Pais &rhs) = default;
    ~Pais() = default;
    const Punto &GetPais() const {return pais;};
    const std::string &GetNombre() const {return nombre;};
    const std::string &GetBandera() const {return bandera;};
    void SetPais(const Punto &pais) {this->pais = pais;};
    void SetNombre(const std::string &nombre) {this->nombre = nombre;};
    void SetBandera(const std::string &bandera) {this->bandera = bandera;};
    bool operator<(const Pais &rhs) const {return pais < rhs.pais;};
    bool operator>(const Pais &rhs) const {return rhs < *this;};
    bool operator==(const Pais &rhs) const {return pais == rhs.pais;};
    bool operator==(const Punto &rhs) const {return pais == rhs;};
    bool operator==(const std::string &rhs) const {return (nombre == rhs || bandera == rhs);};
    bool operator!=(const Pais &rhs) const {return !(*this == rhs);};
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
