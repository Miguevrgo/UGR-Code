#!/bin/bash
script_directory=$(dirname "$0")
cd $script_directory
gcc -O2 Herencia.cpp -o Ejecutables/Herencia -lstdc++ -lm

num_bienes=100000


rm -r Salidas/
mkdir Salidas
mkdir Salidas/Resultados

for ((i=1000; i < $num_bienes; i+=1000)); do

    # Nombre del archivo de salida
    salida="Salidas/Resultados/Herencia_$i.txt"
    ./Ejecutables/Herencia $i $salida

    printf "$i " >> Salidas/Herencia_tiempos.txt
    ./Ejecutables/Herencia $i $salida  >> Salidas/Herencia_tiempos.txt

    
done