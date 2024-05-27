#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")
cd $script_directory

# Compilar los programas
g++ -g -o Ejecutables/backtracking backtracking.cpp
