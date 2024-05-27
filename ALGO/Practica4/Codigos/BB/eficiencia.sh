#!/bin/bash

# Verificar que se haya pasado el archivo de tiempos como argumento
if [ "$#" -ne 2 ]; then
    echo "Uso: $0 <archivo_tiempos> <archivo_grafico>"
    exit 1
fi

archivo_tiempos=$1
grafico_salida=$2

# Comprobar si el archivo de tiempos existe
if [ ! -f "$archivo_tiempos" ]; then
    echo "El archivo de tiempos '$archivo_tiempos' no existe."
    exit 1
fi

# Generar el gráfico con GNUplot
gnuplot <<- EOF
    set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
    set output '$grafico_salida'
    set title "Tiempos de Ejecución"
    set xlabel "Tamaño de Entrada"
    set ylabel "Tiempo (ns)"
    set grid
    set style data linespoints
    plot '$archivo_tiempos' using 1:2 title 'Tiempo de Ejecución' with linespoints lw 2 pt 7
EOF

echo "Gráfico generado en $grafico_salida"
