#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")
cd $script_directory

# Compilar los programas
g++ -o Ejecutables/CreacionPuntos CreacionPuntos.cpp
g++ -o Ejecutables/CreacionGrafos CreacionGrafos.cpp
g++ -o Ejecutables/Dijkstra Dijkstra.cpp