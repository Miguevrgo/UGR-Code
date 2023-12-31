/**
 * @file zoom.cpp
 * @brief Programa que genera una subimagen de nxn píxeles a partir de una imagen original
 */

#include <iostream>
#include "image.h"

using std::cout;
using std::cerr;
using std::stoi;
using std::endl;

int main(int argc, char *argv[]){

    // Comprueba validez de la llamada
    if (argc != 6){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: zoom <fich_orig> <fich_rdo> <fila> <col> <lado> \n";
        exit (1);
    }

    char* origen; // Fichero origen
    char* destino; // Fichero destino

    int nrow = stoi(argv[3]); // Fila de inicio
    int ncol = stoi(argv[4]);  // Columna de inicio
    int lado = stoi(argv[5]); // Lado de la subimagen

    Image image; // Imagen para almacenar el resultado

    // Obtenencion de argumentos origen y destino
    origen  = argv[1];
    destino = argv[2];

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "Imagen tras aplicar zoom de tamaño: " << lado << "x" << lado << " desde la posicion (" << nrow
         << "," << ncol << ") de la imagen " << origen << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Generar subimagen a partir de la imagen original
    image = image.Crop(nrow, ncol, lado, lado);
    // Aplicar zoom 2x
    image = image.Zoom2X();


    // Guardar la imagen resultado en el fichero
    if (image.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}