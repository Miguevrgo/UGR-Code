#!/bin/bash

# ----------------------------|Ruta y Compilacion|-----------------------------#

script_directory=$(dirname "$0")
cd $script_directory
gcc -O2 ViajanteSort.cpp -o Ejecutables/ViajanteSort -lstdc++ -lm

# ----------------------------|Variables de Test|------------------------------#

opcion=2 # [1] Random test || [2] Made test
size2=50000 
files=(
    "Paises/Djibouti.txt" 
    "Paises/Uruguay.txt"
    "Paises/Oman.txt"
    "Paises/Canada.txt"
    "Paises/Nicaragua.txt" 
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
# Egypt =       172387
# Greece =      300899 
# Japan =       491924 
# Finland =     520527
# Vietnam =     569288  
# Burma =       959304
# Canada =      1290319 
# China =       4566563

#---------------------------|Ejecucion Viajante|-------------------------------#

if [ $opcion -eq 1 ]; then
    rm -f Instancias/EjecucionRandomSort.txt
    
    for ((i=50; i <= $size2; i+=1000)) do
        ./Ejecutables/ViajanteSort $i 1 >> Instancias/EjecucionRandomSort.txt
    done
fi
if [ $opcion -eq 2 ]; then
    rm -f Instancias/EjecucionPaisesSort.txt

    for ((i=0; i < ${#files[@]}; i++)) do
        ./Ejecutables/ViajanteSort ${files[i]} 2 >> Instancias/EjecucionPaisesSort.txt
    done
fi
