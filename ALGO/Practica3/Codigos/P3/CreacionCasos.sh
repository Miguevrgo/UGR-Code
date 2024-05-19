#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")
cd $script_directory

# Todo LO QUE SE CAMBIE AQUI SE CAMBIA TAMBIÉN EN AutoTest.sh
# ---------------------------------------------------------
# Número de ejecuciones
num_puntos=25
num_archivos_puntos=10
num_grafos=1 # Número de grafos por archivo de puntos

rango_max_puntos=100 # Rango máximo de puntos en el plano

# ---------------------------------------------------------

rm -r Ciudades/
rm -r Instancias/
mkdir Ciudades
mkdir Instancias 

# Ejecutar CreacionPuntos.cpp varias veces
for ((i=1; i <=$num_archivos_puntos; i++)); do
    # Nombre del archivo de puntos
    puntos_file="Ciudades/puntos_$i.txt"

    # Generar puntos
    ./Ejecutables/CreacionPuntos $num_puntos $rango_max_puntos $puntos_file

    # Ejecutar CreacionGrafos.cpp varias veces para cada archivo de puntos
    for ((j=1; j<=$num_grafos; j++)); do
        # Nombre del archivo de salida de la matriz
        matriz_file="Instancias/matriz_$i-$j.txt"

        # Procesar puntos y generar matriz
        ./Ejecutables/CreacionGrafos $puntos_file $matriz_file
    done
done

echo "Proceso completado."
