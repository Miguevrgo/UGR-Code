/**
 * @file barajar.cpp
 * @brief Programa que baraja filas de una imagen
 *
 */

#include <iostream>
#include "image.h"

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[]){

    // Comprueba validez de la llamada
    if (argc != 3){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: barajar <fich_orig> <fich_rdo> \n";
        exit (1);
    }

    char* origen; // Fichero origen
    char* destino; // Fichero destino

    Image image; // Imagen para almacenar el resultado

    // Obtenencion de argumentos origen y destino
    origen  = argv[1];
    destino = argv[2];

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "Barajando filas de la imagen: " << origen << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Barajar filas de la imagen
    image.ShuffleRows();

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