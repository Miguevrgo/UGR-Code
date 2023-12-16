/**
* @file ruta_aerea.cpp
* @brief Obtiene un mapa del mundo sobre el que se pinta una ruta aerea
*/

#include <iostream>
#include "imagenES.h"
#include "imagen.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc!=7){
        cout<<"Los parametros son :"<<endl;
        cout<<"1.-El fichero de paises"<<endl;
        cout<<"2.-El mapa"<<endl;
        cout<<"3.-Directorio donde se almacenan las banderas"<<endl;
        cout<<"4.-Almacen de rutas"<<endl;
        cout<<"5.-Imagen de un avión"<<endl;
        cout<<"6.-Máscara del avión"<<endl;
        return 0;
    }

    // Cargar el fichero de paises
    string fichero_paises = argv[1];
    // Cargar el mapa
    string mapa = argv[2];
    // Cargar el directorio de banderas
    string dir_banderas = argv[3];
    // Cargar el almacen de rutas
    // Cargar la imagen del avión
    // Cargar la máscara del avión
    // Pintar el mapa



    return 0;
}