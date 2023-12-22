/**
 * @file punto.h
 * @brief Fichero cabecera para la clase Punto
 */

#ifndef PRACTICAFINAL_PUNTO_H
#define PRACTICAFINAL_PUNTO_H

#include <fstream>


class Punto {
public:
    Punto(double lat = 0, double lon = 0) : lat(lat), lon(lon) {};
    Punto(const Punto &rhs) : lat(rhs.lat), lon(rhs.lon) {};
    ~Punto() = default;
    Punto &operator=(const Punto &rhs) = default;
    double GetLat() const {return lat;};
    double GetLon() const {return lon;};
    void SetLat(double lat) {this->lat = lat;};
    void SetLon(double lon) {this->lon = lon;};
    bool operator<(const Punto &rhs) const {return lat < rhs.lat || (lat == rhs.lat && lon < rhs.lon);};
    bool operator>(const Punto &rhs) const {return rhs < *this;};
    bool operator==(const Punto &rhs) const {return lat == rhs.lat && lon == rhs.lon;};
    bool operator!=(const Punto &rhs) const {return !(*this == rhs);};

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
