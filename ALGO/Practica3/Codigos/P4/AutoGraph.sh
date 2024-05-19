#!/bin/bash
# Script solo para crear gráficas
script_directory=$(dirname "$0")
cd $script_directory

name="PrecisionMejora"
# Crear un script de Gnuplot para generar la gráfica, todo lo que hay entre EOF y EOF se escribe en un archivo,
# en este caso, script_gnuplot.gp
cat << EOF > script_gnuplot.gp
# Configuración del gráfico, se define el nombre de los ejes
set xlabel "Tamaño de entrada"
set ylabel "Tiempo de ejecución"

EOF
# Bucle para generar gráficos para cada algoritmo y tipo de dato
cat << EOF >> script_gnuplot.gp

# Comparación Tiempos
# Da un nombre a la gráfica
set title "Comparación Precision Mejora"
# Establece la leyenda, donde 
    # primer "" indica el lugar de donde tomar los datos
    # 1:2 indica que se tomará la primera columna para el eje x y la segunda para el eje y
    # with linespoints indica que se dibujarán líneas uniendo los puntos
    # segundo "" indica el nombre que se le dará a la serie
plot "Instancias/EjecucionPaisesCirc.txt" using 1:2 with linespoints title "Circ" , \
        "Instancias/EjecucionPaisesSort.txt" using 1:2 with linespoints title "Sort" , \
        "Instancias/EjecucionPaisesNNA.txt" using 1:2 with linespoints title "NNA" , \
        "Instancias/PaisesOptimo.txt" using 1:2 with linespoints title "Optimo"
        

# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "Graficas/${name}.png"
replot
EOF
# Ejecutar Gnuplot con el script generado
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp
