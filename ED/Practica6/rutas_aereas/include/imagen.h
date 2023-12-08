/**
 * @file imagen.h
 * @brief Fichero cabecera para la clase Imagen
 */

#ifndef PRACTICAFINAL_IMAGEN_H
#define PRACTICAFINAL_IMAGEN_H

#include <string>
#include <iostream>
#include "imagenES.h"

using byte = unsigned char;

enum TipoPegado {OPACO, BLENDING};

struct Pixel{
    byte r,g,b;
    byte transparencia;

    /**
     * @brief Sobrecarga del operador de suma para píxeles
     * 
     * Calcula el píxel resultante de la media de los dos píxeles
     * 
     * @param rhs Pixel a sumar
     * @return Pixel& Referencia al píxel resultante media de los dos píxeles
     */
    Pixel& operator+(const Pixel &rhs){
        r = (r + rhs.r)/2;
        g = (g + rhs.g)/2;
        b = (b + rhs.b)/2;
        return *this;
    };
};

//TODO: Assert con herramientas definidas en un debug (Mirar C++ Primer en el capítulo anterior a clases)
class Imagen{
public:
    Imagen() : datos(nullptr), nfil(0), ncol(0) {};
    Imagen(const Imagen &rhs);
    Imagen(int filas, int columnas);
    ~Imagen();
    Imagen& operator=(const Imagen &rhs);
    int GetFils() const {return nfil;};
    int GetCols() const {return ncol;};
    Pixel& operator()(int fil, int col);
    const Pixel& operator()(int fil, int col) const;
    
    /**
     * @brief Escribe la imagen en un fichero de tipo PGM o PPM
     * 
     * @param nombre nombre del fichero de salida
     * @pre La extensión del fichero debe ser .pgm o .ppm
     */
    void EscribirImagen(const char* nombre);
    
    /**
     * @brief Lee una imagen de un fichero de tipo PGM o PPM y la almacena en la matriz 
     * de píxeles de la clase, también se puede leer una imagen con máscara de transparencia
     * 
     * @param nimagen nombre del fichero de entrada
     * @param mascara nombre del fichero de máscara de transparencia
     */
    void LeerImagen(const char* nimagen, std::string mascara = "");

    /**
     * @brief Pega una imagen sobre otra en la posición indicada por los parámetros i y j 
     * con el tipo de pegado indicado por el parámetro tipo
     * 
     * Si el tipo de pegado es BLENDING, se hace una media de los píxeles de la imagen a pegar
     * Si el tipo de pegado es OPACO, se pega la imagen a pegar sin hacer media
     * 
     * @param i posición de la fila donde pegar la imagen
     * @param j posición de la columna donde pegar la imagen
     * @param Ip Imagen a pegar
     * @param tipo Tipo de pegado
     */
    void PutImagen(int i, int j, const Imagen &Ip, TipoPegado tipo);

    /**
     * @brief Pega una imagen sobre otra en la posición indicada por los parámetros i y j
     * con el blending indicado por el parámetro blend
     *
     * blend va del 0 al 100, siendo 0 totalmente transparente y 100 totalmente opaco
     *
     * @param i posición de la fila donde pegar la imagen
     * @param j posición de la columna donde pegar la imagen
     * @param Ip Imagen a pegar
     * @param blend Porcentaje de transparencia (default = 50)
     * @pre 0 <= blend <= 100
     */
    void PutImagen(int i, int j, const Imagen &Ip, char blend = 50);


private:
    Pixel **datos; // matriz de píxeles
    int nfil,ncol; // filas y columnas de la imagen

    /**
     * @brief Asigna memoria para la matriz que contiene los píxeles de la imagen
     * 
     * @param filas filas de la imagen 
     * @param columnas columnas de la imagen
     * @pre filas > 0 && columnas > 0
     */ 
    void AllocateMemory(int filas, int columnas);
    
    /**
     * @brief Libera la memoria asignada a la matriz de píxeles
     * @post datos == nullptr
     * @post nfil == 0
     * @post ncol == 0
     */
    void DeallocateMemory();
};

#endif //PRACTICAFINAL_IMAGEN_H
