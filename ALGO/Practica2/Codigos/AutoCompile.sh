#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")
cd $script_directory

gcc SumaMax.cpp -o Ejecutables/SumaMax -lstdc++ -lm
gcc -O2 Losetas.cpp -o Ejecutables/Losetas -lstdc++ -lm
gcc -O2 Viajante.cpp -o Ejecutables/Viajante -lstdc++ -lm