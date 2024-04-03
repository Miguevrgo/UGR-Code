#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")

# Cambiar al directorio del archivo
cd $script_directory
chmod +x AutoCompile.sh
./AutoCompile.sh

# --------------------------|Ejecución de SumaMax|-----------------------------#
rm -f Salidas/SumaMax.txt
size=10000
opcion=2 # [1] Time Test || [2] Correctness Test

for ((i=100; i <= $size; i+=100)); do
    if [ $opcion -eq 1 ]; then
        printf "$i " >> Salidas/SumaMax.txt
    fi
    if [ $opcion -eq 2 ]; then
        ./Ejecutables/SumaMax $i $opcion >> Salidas/SumaMax.txt
    fi
done

#---------------------------|Ejecucion Viajante|-------------------------------#

rm -f Salidas/Viajante.txt
size2=200 # Para el caso brute force a partir de 12 no se puede ejecutar
opcion2=2 # [1] Random test || [2] Made test 
files=("Paises/Finland.txt" "Paises/Nicaragua.txt" "Paises/Djibouti.txt" "Paises/Egypt.txt" "Paises/Oman.txt")
#Solucion: Finland = 520527, Djibouti= 6656, Oman = 86891, Nicaragua = 96132, Egypt = 172387

if [ $opcion2 -eq 1 ]; then
    for ((i=5; i <= $size2; i+=10)) do
        ./Ejecutables/Viajante $i $opcion2 >> Salidas/Viajante.txt
    done
fi
if [ $opcion2 -eq 2 ]; then
    for ((i=0; i < ${#files[@]}; i++)) do
        ./Ejecutables/Viajante ${files[i]} $opcion2 >> Salidas/Viajante.txt
    done
fi


