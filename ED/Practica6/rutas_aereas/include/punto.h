/**
 * @file punto.h
 * @brief Fichero cabecera para la clase Punto
 */

#ifndef PRACTICAFINAL_PUNTO_H
#define PRACTICAFINAL_PUNTO_H

#include <fstream>
//TODO 1: Implementar la clase Punto
//TODO 2: Preguntar si lat y lon son enteros o reales

class Punto {
public:
    Punto(int lat = 0, int lon = 0) : lat(lat), lon(lat) {};
    Punto(const Punto &rhs) : lat(rhs.lat), lon(rhs.lon) {};
    ~Punto() = default;
    Punto &operator=(const Punto &rhs) = default;
    int GetLat() const {return lat;};
    int GetLon() const {return lon;};
    void SetLat(int lat) {this->lat = lat;};
    void SetLon(int lon) {this->lon = lon;};
    bool operator<(const Punto &rhs) const {return lat < rhs.lat || (lat == rhs.lat && lon < rhs.lon);};
    bool operator>(const Punto &rhs) const {return rhs < *this;};
    bool operator==(const Punto &rhs) const {return lat == rhs.lat && lon == rhs.lon;};
    bool operator!=(const Punto &rhs) const {return !(*this == rhs);};
    friend std::ostream &operator<<(std::ostream &os, const Punto &punto);
    friend std::istream &operator>>(std::istream &is, Punto &punto);
private:
    int lat; // Latitud
    int lon; // Longitud
};


#endif //PRACTICAFINAL_PUNTO_H
