/* 
 * File:   Dispositivo.h
 * Author: Silvia Acid y Andrés Cano
 *
 * Created on 28 April 2023, 13:05
 */

#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include <iostream>

class Dispositivo{
public:
    /**
     * @brief Constructor sin parámetros
     * Inicializa a 0 los datos id, x, y, y potencia
     */
    Dispositivo();
    
    /**
     * Constructor 
     * Inicializa a 0 los datos x, y, potencia. Inicializa id con el parámetro 
     * proporcionado
     * @param id Valor identificador
     */  
    Dispositivo(long id);
    
    /**
     * Constructor 
     * Inicializa los datos id, x, y y potencia con los argumentos proporcionados.
     * @param id Valor identificador. Si el parámetro no es positivo,
     * la potencia se inicializa a 0.
     * @param x coordenada x
     * @param y coordenada y
     * @param valor Valor de potencia
     */
    Dispositivo(long id, float x, float y, double potencia=0.0);

    /**
     * @brief Devuelve el id del dispositivo
     * @return el id del dispositivo
     */
    long getId() const;
    
    /**
     * @brief Devuelve coordenada x del dispositivo
     * @return la coordenada x del dispositivo
     */
    float getX() const;
    
    /**
     * @brief Devuelve coordenada y del dispositivo
     * @return la coordenada y del dispositivo
     */
    float getY() const;
    
    /**
     * @brief Devuelve la potencia del dispositivo
     * @return la potencia del dispositivo
    */
    double getPotencia() const;

    /**
     * @brief Actualiza los datos del dispositivo. La potencia solo es 
     * actualizada con el valor proporcionado si es mayor o igual a 0; 
     * en caso contrario se pone a 0.
     * @param id Identificador
     * @param x Coordenada x
     * @param y Coordenada y
     * @param potencia Potencia
     */
    void set(long id, float x, float y, double potencia=0.0);
    
    /**
     * @brief Devuelve un string con la información completa del dispositivo
     * @return string
    */
    std::string toString() const;
    
    /**
     * @brief Calcula la distancia entre el dispositivo implícito
     * y el dispositivo proporcionado.
     * El cálculo de la distancia es simétrica y positiva.
     * @param d dispositivo hasta el que se quiere medir la distancia. 
     * @return La distancia calculada
     */
    float distancia(const Dispositivo &d) const;
    
private:

    bool esPositivo(double v) {
        return v >= 0;
    }
    long _id;
    float _x, _y;
    double _potencia;
};

#endif /* DISPOSITIVO_H */

