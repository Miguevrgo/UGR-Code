#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")

# Cambiar al directorio del archivo
cd $script_directory
gcc -O2 Aulas.cpp -o Ejecutables/Aulas -lstdc++ -lm

rm Salidas/Aulas.txt
duracion=180

for ((i=5000; i <= 125000; i+=5000)); do
    printf "$i " >> Salidas/Aulas.txt
    ./Ejecutables/Aulas $i $duracion  >> Salidas/Aulas.txt

done

