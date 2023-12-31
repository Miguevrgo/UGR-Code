/**
 * @file imagen.h
 * @author Miguel Angel De la Vega Rodriguez
 * @author Joaquín Aviles De la Fuente
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
        r = (r + rhs.r) >> 1;
        g = (g + rhs.g) >> 1;
        b = (b + rhs.b) >> 1;
        return *this;
    };
};

class Imagen{
public:
    /**
     * @brief Constructor por defecto.
     * Inicializa la imagen con datos nulos y dimensiones 0x0.
     */
    Imagen() : datos(nullptr), nfil(0), ncol(0) {};

    /**
     * @brief Constructor de copia.
     * @param rhs Imagen a copiar.
     */
    Imagen(const Imagen &rhs);

    /**
     * @brief Constructor que crea una imagen con las dimensiones especificadas.
     * @param filas Número de filas.
     * @param columnas Número de columnas.
     */
    Imagen(int filas, int columnas);

    /**
     * @brief Destructor.
     * Libera la memoria asignada a la matriz de píxeles.
     */
    ~Imagen();

    /**
     * @brief Sobrecarga del operador de asignación.
     * @param rhs Imagen a asignar.
     * @return Referencia a la imagen asignada.
     */
    Imagen &operator=(const Imagen &rhs);

    /**
     * @brief Obtiene el número de filas de la imagen.
     * @return Número de filas.
     */
    int GetFils() const { return nfil; };

    /**
     * @brief Obtiene el número de columnas de la imagen.
     * @return Número de columnas.
     */
    int GetCols() const { return ncol; };

    /**
     * @brief Sobrecarga del operador de acceso a los píxeles.
     * @param fil Fila del píxel.
     * @param col Columna del píxel.
     * @return Referencia al píxel en la posición (fil, col).
     */
    Pixel &operator()(int fil, int col);

    /**
     * @brief Sobrecarga del operador de acceso constante a los píxeles.
     * @param fil Fila del píxel.
     * @param col Columna del píxel.
     * @return Referencia constante al píxel en la posición (fil, col).
     */
    const Pixel &operator()(int fil, int col) const;

    /**
     * @brief Escribe la imagen en un fichero de tipo PGM o PPM.
     * @param nombre Nombre del fichero de salida.y
     * @pre La extensión del fichero debe ser .pgm o .ppm.
     */
    void EscribirImagen(const char *nombre);

    /**
     * @brief Lee una imagen de un fichero de tipo PGM o PPM y la almacena en la matriz
     * de píxeles de la clase, también se puede leer una imagen con máscara de transparencia.
     * @param nimagen Nombre del fichero de entrada.
     * @param mascara Nombre del fichero de máscara de transparencia.
     */
    void LeerImagen(const char *nimagen, std::string mascara = "");

    /**
     * @brief Pega una imagen sobre otra en la posición indicada por los parámetros i y j
     * con el tipo de pegado indicado por el parámetro tipo.
     * @param i Posición de la fila donde pegar la imagen.
     * @param j Posición de la columna donde pegar la imagen.
     * @param Ip Imagen a pegar.
     * @param tipo Tipo de pegado.
     */
    void PutImagen(int i, int j, const Imagen &Ip, TipoPegado tipo);

    /**
     * @brief Pega una imagen sobre otra en la posición indicada por los parámetros i y j
     * con el blending indicado por el parámetro blend.
     * @param i Posición de la fila donde pegar la imagen.
     * @param j Posición de la columna donde pegar la imagen.
     * @param Ip Imagen a pegar.
     * @param blend Porcentaje de transparencia (default = 50).
     * @pre 0 <= blend <= 100.
     */
    void PutImagen(int i, int j, const Imagen &Ip, char blend = 50);

private:
    Pixel **datos; // Matriz de píxeles.
    int nfil, ncol; // Filas y columnas de la imagen.

    /**
     * @brief Asigna memoria para la matriz que contiene los píxeles de la imagen.
     * @param filas Filas de la imagen.
     * @param columnas Columnas de la imagen.
     * @pre filas > 0 && columnas > 0.
     */
    void AllocateMemory(int filas, int columnas);

    /**
     * @brief Libera la memoria asignada a la matriz de píxeles.
     * @post datos == nullptr
     * @post nfil == 0
     * @post ncol == 0
     */
    void DeallocateMemory();
};

#endif //PRACTICAFINAL_IMAGEN_H
