/* 
 * File:   VectorDinamico.cpp
 * Author: Silvia Acid y Andrés Cano
 * 
 * Created on 28 April 2023, 13:05
 */

#include "VectorDinamico.h"

using namespace std;

/**
 * @brief Devuelve true si el Dispositivo @p d  está dentro del alcance de 
 * la antena @p antena al encontrarse en su radio de acción.
 * @param d Dispositivo que se comprueba si está cubierto por esa antena 
 * o no (parámetro de entrada)
 * @param antena Dispositivo antena (parámetro de entrada)
 * @param radio Radio de acción de la antena (parámetro de entrada)
 * @return devuelve true si el dispositivo @p d queda dentro del alcance de la
 * antena; false en caso contrario.
 */
bool dentroDeAlcance(const Dispositivo &d,const Dispositivo &antena, double radio){
    float dist = d.distancia(antena);
    bool in_range=false;
    
    if (d.distancia(antena) < radio){
        in_range=true;
    }
    return in_range;
}

/**
 * Imprime en la salida estándar los dispositivos contenidos en el vector de 
 * dispositivos proporcionado.
 * @param v Puntero a los dispositivos (parámetro de entrada)
 * @param n Número de dispositivos en el vector de dispositivos (parámetro de entrada)
 */
void imprimirVector(const Dispositivo* const v, int n){
    cout << n << endl;
    for (int i = 0; i < n; i++)
        cout << v[i].getId() << "->(" << v[i].getX() << "," << v[i].getY() << "," << v[i].getPotencia() << ")," << endl;
}

/**
 * @brief Reserva memoria dinámica para alojar n dispositivos en un vector dinámico
 * @param n Número de Dispositivos a reservar (parámetro de entrada)
 * @return Dirección de inicio de la memoria reservada
 */
Dispositivo* reservarM(int n) {
    Dispositivo *aux = new Dispositivo[n];
    return aux;
}

/**
 * @brief Libera la memoria dinámica usada por el vector dinámico pasado como 
 * argumento
 * @param v Puntero al vector de dispositivos. Debe quedar con el valor nullptr, 
 * tras ejecutar la función (parámetro de salida).
 */
void liberarM(Dispositivo* &v) {
    delete [] v;
    v = nullptr;
}

/**
 * @brief Añade un dispositivo adicional al vector dinámico @p v. El vector @p v debe 
 * redimensionarse para almacenar el contenido del vector anterior más el nuevo 
 * dispositivo (@p nuevo). La función actualiza convenientemente el número de
 * elementos del vector @p v (@p tam)
 * @param nuevo El nuevo dispositivo a añadir al vector 
 * dinámico @p v (parámetro de entrada)
 * @param v Puntero al vector dinámico de dispositivos (parámetro de salida)
 * @param tam El número de dispositivos almacenados en el vector dinámico de 
 * dispositivos (parámetro de salida). 
 */
void agnadeDispositivo(const Dispositivo &nuevo, Dispositivo* &v, int &tam) {
    Dispositivo *aux = reservarM(tam+1);
    for (int i=0;i<tam;i++){
        aux[i]=v[i];
    }
    aux[tam]=nuevo;
    
    delete [] v;
    
    v = aux;
    tam++;
}

/**
 * @brief Selecciona los dispositivos de vMovil que no tengan cobertura de
 * ningún dispositivo antena. En vSalida se vuelcan los dispositivos que no
 * tengan cobertura de ningún dispositivo antena.
 * @param vMovil Vector de dispositivos móviles (parámetro de entrada)
 * @param nMovil Número de elementos en el vector vMovil (parámetro de entrada)
 * @param vAntena vector de dispositivos antena (parámetro de entrada)
 * @param nAntena  Número de elementos en el vector vAntena (parámetro de entrada)
 * @param vSalida, vector de dispositivos resultante (parámetro de salida)
 * @param nSalida Número de elementos en el vector vSalida (parámetro de 
 * salida)
 * @param radio Rango de distancia en la que un dispostivo tiene cobertura de 
 * una antena (parámetro de entrada).
 * 
 * Algoritmo
 * =========
 * Para cada dispositivo d
 *    Para cada antena 
 *         Comprobar si el dispositivo d tiene cobertura o no de la antena
 *    Añadir d al vector de salida, solo si no tiene cobertura de NINGUNA ANTENA
 */

void sinCobertura(Dispositivo* &vMovil, int nMovil, 
        Dispositivo* &vAntena, int nAntena, Dispositivo* &vSalida, int  &nSalida, 
        double radio){
    bool tiene_cobertura;
    for (int i=0;i<nMovil;i++){
        tiene_cobertura=false;
        for (int j=0;j<nAntena;j++){
            if (dentroDeAlcance(vMovil[i],vAntena[j],radio)){
                tiene_cobertura=true;
            }
        }
        if (!tiene_cobertura){
            agnadeDispositivo(vMovil[i],vSalida,nSalida);
        }
    }
    
}

/**
 * @brief Realiza la lectura desde teclado de la lista de dispositivos y los almacena 
 * en un vector dinámico, el cual se va redimensionando con cada lectura. 
 * Los datos de cada dispositivo se leen en el orden id, x, y y potencia. La 
 * lectura de dispositivos finaliza cuando se lee el valor -1 para un id. 
 * En ese caso no se seguirá leyendo el resto de datos de un dispositivo, 
 * (x, y y potencia).
 * @param v puntero de comienzo del vector de dispositivos (parámetro de salida)
 * @param n Número de elementos del vector. Este dato se modifica cuando se 
 * inserta un nuevo dispositivo (parámetro de salida).
 */
void lectura(Dispositivo* &v, int &n){
    bool flag = true;
    long id;
    float x,y;
    double potencia;
    while(flag){
        cin >> id;
        if (id!=-1){
            cin >> x;
            cin >> y;
            cin >> potencia;
            agnadeDispositivo(Dispositivo(id,x,y,potencia),v,n);
        }
        else{
            flag=false; //Se termina la lectura
        }
        
    }
}