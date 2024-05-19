#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")
cd $script_directory

initial_point=4 # Punto inicial
final_point=11 # Punto final

# Todo LO QUE SE CAMBIE AQUI SE CAMBIA TAMBIÉN EN CreacionCasos.sh
# ---------------------------------------------------------
# Número de ejecuciones
num_puntos=15
num_archivos_puntos=10
num_grafos=1 # Número de grafos por archivo de puntos

# ---------------------------------------------------------

rm -r Resultados
mkdir Resultados

# Ejecutar CreacionPuntos.cpp varias veces
for ((i=1; i <=$num_archivos_puntos; i++)); do
    # Ejecutar CreacionGrafos.cpp varias veces para cada archivo de puntos
    for ((j=1; j<=$num_grafos; j++)); do
        # Nombre del archivo de salida de la matriz
        matriz_file="Instancias/matriz_$i-$j.txt"
        resultados_file="Resultados/resultados_$i-$j.txt"

        # Procesar puntos y generar matriz
        ./Ejecutables/Dijkstra $matriz_file $initial_point $final_point >> $resultados_file
    done
done

