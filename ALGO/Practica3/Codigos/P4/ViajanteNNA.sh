#!/bin/bash

# ----------------------------|Ruta y Compilacion|-----------------------------#

script_directory=$(dirname "$0")
cd $script_directory
gcc -O2 ViajanteNNA.cpp -o Ejecutables/ViajanteNNA -lstdc++ -lm

# ----------------------------|Variables de Test|------------------------------#

opcion=2 # [1] Random test || [2] Made test
size2=50 
files=(
    "Paises/Djibouti.txt" 
    "Paises/Uruguay.txt"
    "Paises/Oman.txt"
    "Paises/Nicaragua.txt" 
    "Paises/Canada.txt"
    "Paises/Egypt.txt" 
    "Paises/Greece.txt"
    "Paises/Japan.txt"
    "Paises/Finland.txt" 
    "Paises/Vietnam.txt"
    "Paises/Burma.txt"
    "Paises/China.txt"
    )

#---------------------------|Soluciones Optimas|-------------------------------#

# Djibouti =    6656
# Uruguay =     79114 
# Oman =        86891
# Nicaragua =   96132
# Canada =      1290319 
# Egypt =       172387
# Greece =      300899 
# Japan =       491924 
# Finland =     520527
# Vietnam =     569288  
# Burma =       959304
# China =       4566563

#---------------------------|Ejecucion Viajante|-------------------------------#

if [ $opcion -eq 1 ]; then
    rm -f Instancias/EjecucionRandomNNA.txt
    ./Ejecutables/ViajanteNNA $size2 1 >> Instancias/EjecucionRandomNNA.txt

fi
if [ $opcion -eq 2 ]; then
    rm -f Instancias/EjecucionPaisesNNA.txt

    for ((i=0; i < ${#files[@]}; i++)) do
        ./Ejecutables/ViajanteNNA ${files[i]} 2 >> Instancias/EjecucionPaisesNNA.txt
    done
fi

