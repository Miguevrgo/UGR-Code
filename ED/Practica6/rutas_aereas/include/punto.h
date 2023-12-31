/**
 * @file punto.h
 * @brief Fichero cabecera para la clase Punto
 */

#ifndef PRACTICAFINAL_PUNTO_H
#define PRACTICAFINAL_PUNTO_H

#include <fstream>


class Punto {
public:
    /**
     * @brief Constructor por defecto, si no se pasan parámetros
     * inicializa a 0
     * @param lat Latitud del punto
     * @param lon Longitud del punto
     */
    Punto(double lat = 0, double lon = 0) : lat(lat), lon(lon) {};

    /**
     * @brief Constructor de copia
     * @param rhs Objeto @b Punto a copiar
     */
    Punto(const Punto &rhs) : lat(rhs.lat), lon(rhs.lon) {};

    /**
     * @brief Destructor por defecto.
     */
    ~Punto() = default;

    /**
     * @brief Operador de asignación.
     * @param rhs Objeto @b Punto a asignar.
     * @return Referencia al objeto @b Punto asignado.
     */
    Punto &operator=(const Punto &rhs) = default;

    /**
     * @brief Obtiene la latitud del punto.
     * @return Valor de la latitud.
     */
    double GetLat() const { return lat; };

    /**
     * @brief Obtiene la longitud del punto.
     * @return Valor de la longitud.
     */
    double GetLon() const { return lon; };

    /**
     * @brief Establece la latitud del punto.
     * @param lat Nuevo valor de latitud.
     */
    void SetLat(double lat) { this->lat = lat; };

    /**
     * @brief Establece la longitud del punto.
     * @param lon Nuevo valor de longitud.
     */
    void SetLon(double lon) { this->lon = lon; };

    /**
     * @brief Compara dos puntos para determinar si uno es menor que el otro.
     * @param rhs Punto a comparar.
     * @return true si el punto actual es menor que el punto dado, false en caso contrario.
     */
    bool operator<(const Punto &rhs) const { return lat < rhs.lat || (lat == rhs.lat && lon < rhs.lon); };

    /**
     * @brief Compara dos puntos para determinar si uno es mayor que el otro.
     * @param rhs Punto a comparar.
     * @return true si el punto actual es mayor que el punto dado, false en caso contrario.
     */
    bool operator>(const Punto &rhs) const { return rhs < *this; };

    /**
     * @brief Compara dos puntos para determinar si son iguales.
     * @param rhs Punto a comparar.
     * @return true si los puntos son iguales, false en caso contrario.
     */
    bool operator==(const Punto &rhs) const { return lat == rhs.lat && lon == rhs.lon; };

    /**
     * @brief Compara dos puntos para determinar si son diferentes.
     * @param rhs Punto a comparar.
     * @return true si los puntos son diferentes, false en caso contrario.
     */
    bool operator!=(const Punto &rhs) const { return !(*this == rhs); };

    /**
     * @brief Sobrecarga del operador de salida, se imprime el punto en formato (lat, lon)
     * @param os Flujo de salida
     * @param punto Punto a imprimir
     * @return Flujo de salida
     */
    friend std::ostream &operator<<(std::ostream &os, const Punto &punto);

    /**
     * @brief Sobrecarga del operador de entrada, se lee el punto en formato (lat, lon)
     * @param is Flujo de entrada
     * @param punto Punto a leer
     * @return Flujo de entrada
     */
    friend std::istream &operator>>(std::istream &is, Punto &punto);
private:
    double lat; // Latitud
    double lon; // Longitud
};


#endif //PRACTICAFINAL_PUNTO_H
