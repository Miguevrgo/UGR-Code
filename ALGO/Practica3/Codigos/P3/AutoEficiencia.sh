#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")
cd $script_directory

initial_point=4 # Punto inicial
final_point=11 # Punto final

# Todo LO QUE SE CAMBIE AQUI SE CAMBIA TAMBIÉN EN CreacionCasos.sh
# ---------------------------------------------------------
# Número de ejecuciones
num_puntos=25 #Número de puntos con los que se crea el grafo
max_puntos=100000 #Número de puntos que puede tener el grafo como máximo
num_archivos_puntos=10
num_grafos=1 # Número de grafos por archivo de puntos
rangue=1000


# ---------------------------------------------------------

rm -r Eficiencia
mkdir Eficiencia

# # Ejecutar CreacionPuntos.cpp varias veces
# for ((i=1; i <=$num_archivos_puntos; i++)); do
#     # Ejecutar CreacionGrafos.cpp varias veces para cada archivo de puntos
#     for ((j=1; j<=$num_grafos; j++)); do
#         # Nombre del archivo de salida de la matriz
#         matriz_file="Instancias/matriz_$i-$j.txt"
#         resultados_file="Resultados/resultados_$i-$j.txt"

#         # Procesar puntos y generar matriz
#         ./Ejecutables/Dijkstra $matriz_file $initial_point $final_point >> $resultados_file
#     done
# done
touch Eficiencia/gnu.txt

for ((i=1000; i < max_puntos; i+=1000)); do 
    touch Eficiencia/entrada.txt
    touch Eficiencia/matriz.txt
    ./Ejecutables/CreacionPuntos $i $rangue Eficiencia/entrada.txt 
    ./Ejecutables/CreacionGrafos Eficiencia/entrada.txt Eficiencia/matriz.txt
    ./Ejecutables/Dijkstra Eficiencia/matriz.txt $initial_point $final_point Eficiencia/gnu.txt
    rm -f Eficiencia/entrada.txt
    rm -f Eficiencia/matriz.txt
done