#!/bin/bash

# Verificar que se hayan pasado los argumentos correctos
if [ "$#" -ne 3 ]; then
    echo "Uso: $0 <archivo_puntos> <archivo_resultado> <archivo_salida>"
    exit 1
fi

archivo_puntos=$1
archivo_resultado=$2
archivo_salida=$3

# Leer los puntos
declare -a puntos_x
declare -a puntos_y
while IFS=' ' read -r x y; do
    puntos_x+=($x)
    puntos_y+=($y)
done < "$archivo_puntos"

# Leer el resultado
read -a orden < "$archivo_resultado"

# Crear un archivo de datos para GNUplot
datos_gnuplot=$(mktemp)
for i in "${orden[@]}"; do
    echo "${puntos_x[$i]} ${puntos_y[$i]} $i" >> "$datos_gnuplot"
done
# Añadir el primer punto al final para cerrar el ciclo
echo "${puntos_x[${orden[0]}]} ${puntos_y[${orden[0]}]} ${orden[0]}" >> "$datos_gnuplot"

# Generar el gráfico con GNUplot
gnuplot <<- EOF
    set terminal pngcairo size 800,600
    set output '$archivo_salida'
    set title 'Camino del Viajante'
    set xlabel 'X'
    set ylabel 'Y'
    set grid
    set key off
    plot '$datos_gnuplot' using 1:2 with linespoints lt rgb "blue" lw 2 pt 7, \
         '' using 1:2:(sprintf("(%d)", \$3)) with labels offset char 1,1 notitle
EOF

# Limpiar archivo temporal
rm "$datos_gnuplot"
