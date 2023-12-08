/**
 * @file comparar.cpp
 * @brief Programa que compara dos imagenes de ficheros distintos y dice si son iguales
 */

#include <iostream>
#include "image.h"

using namespace std;

int main(int argc, char *argv[]){

    // Comprueba validez de la llamada
    if (argc != 3){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: icono <fich_orig> <fich_rdo> \n";
        exit (1);
    }

    char* fichero1; // Fichero origen
    char* fichero2; // Fichero destino

    Image image1, image2; // Imagen para almacenar el resultado

    // Obtenencion de argumentos origen y destino
    fichero1  = argv[1];
    fichero2 = argv[2];

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero de la imagen 1: " << fichero1 << endl;
    cout << "Fichero de la imagen 2: " << fichero2 << endl;

    // Leer la imagen del fichero de entrada
    if (!image1.Load(fichero1)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    if (!image2.Load(fichero2)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Compueba si las dos imágenes son iguales
    if (image1 == image2){
        cout << "Son iguales las dos imágenes" << endl;
    }
    else
        cout << "Son distintas las dos imágenes" << endl;

    return 0;
}