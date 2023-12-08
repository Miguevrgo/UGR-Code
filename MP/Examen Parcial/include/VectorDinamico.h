/* 
 * File:   VectorDinamico.h
 * Author: Silvia Acid y Andrés Cano
 *
 * Created on 2 de mayo de 2023, 10:00
 */

#ifndef VECTORDINAMICO_H
#define VECTORDINAMICO_H

#include "Dispositivo.h"

bool dentroDeAlcance(const Dispositivo &d,const Dispositivo &antena, double radio);
void imprimirVector(const Dispositivo* const v, int n);
Dispositivo* reservarM(int n);
void liberarM(Dispositivo* &v);
void agnadeDispositivo(const Dispositivo &nuevo, Dispositivo* &v, int &tam);
void sinCobertura(Dispositivo* &vMovil, int nMovil,  
        Dispositivo* &vAntena, int nAntena, Dispositivo* &vSalida, int  &nSalida, 
        double radio);
void lectura(Dispositivo* &v, int &n);

#endif /* VECTORDINAMICO_H */

