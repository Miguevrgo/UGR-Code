/* 
 * File:   main.cpp
 * Author: De la vega Rodriguez Miguel Angel
 * 
 * Created on 28 April 2023, 13:05
 */

/**
 * Se trata de gestionar la información de unos dispositivos distribuidos  
 * en el espacio 2D. Concretamente se dispone de un conjunto de dispositivos
 * móviles y de un conjunto de dispositivos emisores de señal (antenas), 
 * cada uno almacenado en un vector de dispositivos en memoria dinamica.
 * 
 * Un dispositivo tiene un id único (long), coordenadas x e y (float), y una 
 * potencia (double).
 * 
 * Un Dispositivo d no tiene cobertura por una antena cuando la distancia 
 * entre d y la antena es superior al radio de alcance (parámetro del main).
 * En caso contrario queda cubierto por esa antena.
 * Un dispositivo móvil se considera que no tiene cobertura de ninguna antena 
 * cuando no está dentro del área de cobertura de ningún dispositivo antena.
 * 
 * El objetivo de este programa es obtener un vector con los dispositivos móviles 
 * que no tienen cobertura de ninguna antena.
 * 
 * Con la ayuda de la clase Dispositivo COMPLETAMENTE DEFINIDA 
 * y unos argumentos opcionales [ -r num ]  de main(), donde num es un 
 * radio (número real), la función main() debe realizar los siguientes pasos:
 * 
 * 1. Leer datos desde la entrada estándar a un vector de Dispositivo movil, 
 * y al vector de Dispositivo antenas.
 * Ambos vectores deben alojarse con el tamaño adecuado, para contener los 
 * dispositivos en memoria dinámica.  
 * Para la lectura de los dispositivos desde la entrada, se leen los 
 * dispositivos mientras el id sea distinto de -1, que es la condición de parada. 
 *
 * 2. Mostrar el contenido de los vectores movil y antena leídos.
 *
 * 3. Elaborar un vector (también dinámico) con los dispositivos móviles que
 * no tienen cobertura de ninguna antena. 
 * 
 * 
  Se ha preparado el fichero data/prueba1.txt con los datos siguientes: 
 

1 9.1 9.1 1.5 
2 10.5 10.5 1.0
3 11.0 11.0 1.7
4 3.5 1.2 2.3
5 2.7 10.3 2.9
6 4.5 6.7 2.1
7 19.9 10.10 3
8 1.1 2.4 3.9
9 10.0 9.0 3.3
10 0.0 0.0 1.2
-1
100 8.5 9.0 12.0
200 1.0 1.0 10
300 2.0 2.0 15
-1 
 * 
 * para el valor de radio = 2.0
La salida del programa sería:

5
2->(10.5,10.5,1),
3->(11,11,1.7),
5->(2.7,10.3,2.9),
6->(4.5,6.7,2.1),
7->(19.9,10.1,3),

Si quieres utilizar valgrind
 valgrind --leak-check=full      

Especificación de las TAREAS A REALIZAR:

0. Rellenar nombre y apellidos tras el token Author.

1. Revisar las cabeceras de las funciones externas, 
bool dentroDeAlcance()
void imprimirVector()
Robot *reservarM()
void liberarM()
void agnadeDispositivo()
void sinCobertura()

void lectura()
 
Se han de respectar tanto el número de parámetros como sus tipos. 
La forma de pasar los argumentos (por valor, referencia etc.) lo decides tú.

2. Completar las funciones:
bool dentroDeAlcance()
Robot *reservarM()
void liberarM() 
void agnadeDispositivo()
void sinCobertura()
void lectura()

3. Completar el main, que puede recibir un argumento opcional -r <num> 
   donde num es el radio que se debe de considerar para establecer el alcance 
   de una antena. Si no se da un nuevo valor, el radio por defecto es 2.0;

*/

// Alumno:

#include <iostream>
#include "Dispositivo.h"
#include "VectorDinamico.h"

using namespace std;


/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char* args[]) {
    double radio = 2.0;

    Dispositivo *vMovil;  // vector de Dispositivos movil
    Dispositivo *vAntena;  // vector de Dispositivos antena
    Dispositivo *vResultado;  // vector de Dispositivos resultante
    int nMovil, nResultado, nAntena; // longitudes respectivas
    
    
    //leer parámetro radio
    // radio = atof("7.3"); ejemplo de como transformar un cstring en un float
    if (nargs > 2){
        radio = atof(args[2]);
    }
        
    // inicializacion variables locales
    
    nMovil=0;
    nAntena=0;
    nResultado=0;
    vMovil=nullptr;
    vAntena=nullptr;
    vResultado=nullptr;
    
    
    // leer e imprimir dispositivos móviles
    lectura(vMovil, nMovil);
    cout << "Vector de dispositivos móviles " << endl;
    imprimirVector(vMovil, nMovil);
    
    // leer e imprimir dispositivos antena
    lectura(vAntena, nAntena);
    cout << "Vector de dispositivos antena" << endl;
    imprimirVector(vAntena, nAntena);
    
    // hallar los dispositivos sin obertura
  
    sinCobertura(vMovil,nMovil,vAntena,nAntena,vResultado,nResultado,radio);
            
    cout << "Se filtra el vector resultado" << endl;
    imprimirVector(vResultado, nResultado);
    
    liberarM(vMovil);
    liberarM(vAntena);
    liberarM(vResultado);
    
    return 0;
}
