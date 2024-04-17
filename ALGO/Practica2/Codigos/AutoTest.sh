#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")

# Cambiar al directorio del archivo
cd $script_directory
chmod +x AutoCompile.sh
./AutoCompile.sh

# Cada numero indicará el código que queremos ejecutar segun estan descritos
# en este archivo en orden descendente, es decir,
# numero=1 indica SumaMax
# numero=2 indica Losetas
# numero=3 indica Viajante
# numero=4 indica TODOS

n=3

# --------------------------|Ejecución de SumaMax|-----------------------------#

if(($n == 1 || $n==4)) then
    size=5000000
    opcion=2 # [1] Time Test Kadane || [2] Time Test DyV || [3] Correctness Test
    if [ $opcion -eq 1 ]; then
        rm -f Salidas/SumaMaxKadane.txt
    fi
    if [ $opcion -eq 2 ]; then
        rm -f Salidas/SumaMaxDyV.txt
    fi
    if [ $opcion -eq 3 ]; then
        rm -f Salidas/SumaMax.txt
    fi

    for ((i=25000; i <= $size; i+=25000)); do
        if [ $opcion -eq 1 ]; then
            printf "$i " >> Salidas/SumaMaxKadane.txt
            ./Ejecutables/SumaMax $i $opcion >> Salidas/SumaMaxKadane.txt
        fi
        if [ $opcion -eq 2 ]; then
            printf "$i " >> Salidas/SumaMaxDyV.txt
            ./Ejecutables/SumaMax $i $opcion >> Salidas/SumaMaxDyV.txt
        fi
        if [ $opcion -eq 3 ]; then
            ./Ejecutables/SumaMax $i $opcion >> Salidas/SumaMax.txt
        fi
    done
fi
#--------------------------|Ejecución de Losetas|-----------------------------#

if(($n == 2 || $n==4)) then
    rm Salidas/Losetas.txt
    

    for ((i=1; i <= 16; i+=1)); do
        dim=$((2**$i))
        printf "$dim " >> Salidas/Losetas.txt
        ./Ejecutables/Losetas $i  >> Salidas/Losetas.txt

    done

fi


#---------------------------|Ejecucion Viajante|-------------------------------#

if(($n == 3 || $n==4)) then

    size2=50000 # Para el caso brute force a partir de 12 no se puede ejecutar
    opcion2=1 # [1] Random test || [2] Made test || [3] Get Umbral
    files=(
        "Paises/Finland.txt" 
        "Paises/Nicaragua.txt" 
        "Paises/Djibouti.txt" 
        "Paises/Egypt.txt" 
        "Paises/Oman.txt"
        "Paises/Vietnam.txt"
        "Paises/Uruguay.txt"
        "Paises/Canada.txt"
        "Paises/Greece.txt"
        "Paises/Japan.txt"
        "Paises/China.txt"
        "Paises/Burma.txt"
        )
    #Solucion: Finland = 520527, Djibouti = 6656, Oman = 86891, Nicaragua = 96132, Egypt = 172387
    # Vietnam = 569288  Uruguay = 79114 Canada = 1290319 Greece = 300899 Japan = 491924 China = 4566563
    # Burma = 959304

    if [ $opcion2 -eq 1 ]; then
        rm -f Salidas/ViajanteRandom.txt
        
        for ((i=50; i <= $size2; i+=1000)) do
            ./Ejecutables/Viajante $i 3 >> Salidas/ViajanteRandom.txt
            # python3 PlotP3.py
        done
    fi
    if [ $opcion2 -eq 2 ]; then
        rm -f Salidas/Viajante.txt
        for ((i=0; i < ${#files[@]}; i++)) do
            ./Ejecutables/Viajante ${files[i]} $opcion2 >> Salidas/Viajante.txt
        done
    fi

    if [ $opcion2 -eq 3 ]; then
        for ((i=4; i <= 9; ++i)) do
            # rm -f Salidas/Viajante$i.txt # Cuidado con borrarlo que tarda 1h en ejecutarse
            for ((j=0; j < ${#files[@]}; j++)) do
                ./Ejecutables/Viajante ${files[j]} $opcion2 $i >> Salidas/Viajante$i.txt
            done
        done
    fi
fi
