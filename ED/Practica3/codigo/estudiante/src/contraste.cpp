/**
 * @file contraste.cpp
 * @brief Programa que ajusta el contraste de una imagen
 */

#include <iostream>
#include "image.h"

using std::cout;
using std::cerr;
using std::stoi;
using std::stoi;
using std::endl;

int main(int argc, char *argv[]){

    // Comprueba validez de la llamada
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: contraste <fich_orig> <fich_rdo> <e1> <e2> <s1> <s2>\n";
        exit (1);
    }

    char* origen; // Fichero origen
    char* destino; // Fichero destino

    // Obtenencion de argumentos origen y destino
    origen  = argv[1];
    destino = argv[2];

    Image image; // Imagen para almacenar el resultado

    // Obtenencion de argumentos
    byte e1 = stoi(argv[3]);
    byte e2 = stoi(argv[4]);
    byte s1 = stoi(argv[5]);
    byte s2 = stoi(argv[6]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "Generando imagen tras aplicar transformacion lineal con e1: " << int(e1) << " e2: " << int(e2);
    cout << " s1: " << int(s1) << " s2: " << int(s2) << " de la imagen: " << origen << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Se ajusta el contraste a los nuevos valores
    image.AdjustContrast(e1, e2, s1, s2);

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