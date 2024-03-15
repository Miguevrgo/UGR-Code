#!/bin/bash
# Este archivo tiene la finalidad de obtener las graficas de 
# la eficiencia hibrida de los metodos de burbuja,insercción y selección

name="insercion"
rm -r AjusteHibrido/Hibrido$name

# Crear un directorio para guardar los archivos
mkdir AjusteHibrido/Hibrido$name

# Crear un script de Gnuplot para generar los archivos, todo lo que hay entre EOF y EOF se escribe en un archivo,
# en este caso, script_gnuplot.gp
cat << EOF > script_gnuplot.gp
# Configuración del gráfico, se define el nombre de los ejes
set xlabel "Tamaño de entrada"
set ylabel "Tiempo de ejecución"



EOF

# Bucle para generar gráficos para cada algoritmo y tipo de dato
cat << EOF >> script_gnuplot.gp

# Algoritmo $name
# Da un nombre a la gráfica
set title "Algoritmo - $name"
#Definimos unna función para los métodos cuadraticos
f(x) = a0*x*x+a1*x+a2
g(x) = b0*x*x+b1*x+b2
h(x) = c0*x*x+c1*x+c2
p(x) = d0*x*x+d1*x+d2

#Indicamos al gnuplot que haga la regresión
fit f(x) "Resultados/Salida1$name.txt" via a0,a1,a2
fit g(x) "Resultados/Salida2$name.txt" via b0,b1,b2
fit h(x) "Resultados/Salida3$name.txt" via c0,c1,c2
fit p(x) "Resultados/Salida4$name.txt" via d0,d1,d2


#Imprimimos las graficas a excepción del tipo string que estará en otra gráfica distinta
plot "Resultados/Salida1$name.txt", f(x) title "Curva ajustada int " , "Resultados/Salida2$name.txt", g(x) title "Curva ajustada float" , "Resultados/Salida3$name.txt", h(x) title "Curva ajustada double" 
# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./AjusteHibrido/Hibrido$name/${name}_hib.png"
replot

plot "Resultados/Salida4$name.txt", p(x) title "Curva ajustada string"
#Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./AjusteHibrido/Hibrido$name/${name}string_hib.png"
replot
EOF


# Ejecutar Gnuplot con el script generado
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp


#Esta parte tiene la finalidad de obtener las graficas de 
# la eficiencia hibrida de los metodos de floyd,fibonacci y hanoi

rm -r AjusteHibrido/Hibrido_fibonacci_floyd_hanoi

# Crear un directorio para guardar los archivos
mkdir AjusteHibrido/Hibrido_fibonacci_floyd_hanoi

# Crear un script de Gnuplot para generar los archivos, todo lo que hay entre EOF y EOF se escribe en un archivo,
# en este caso, script_gnuplot.gp
cat << EOF > script_gnuplot.gp
# Configuración del gráfico, se define el nombre de los ejes
set xlabel "Tamaño de entrada"
set ylabel "Tiempo de ejecución"

EOF

# Bucle para generar gráficos para cada algoritmo y tipo de dato
cat << EOF >> script_gnuplot.gp

# Algoritmo Floyd
# Da un nombre a la gráfica
set title "Algoritmo - Floyd"
#Definimos unna función para el metodo Floyd
fl(x) = a0*x*x*x

#Indicamos al gnuplot que haga la regresión
fit fl(x) "Resultados/Salidafloyd.txt" via a0

#Imprimimola gráfica
plot "Resultados/Salidafloyd.txt", fl(x) title "Curva ajustada "  
# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./AjusteHibrido/Hibrido_fibonacci_floyd_hanoi/Floyd_hib.png"
replot

#Algoritmo Fibonacci
# Da un nombre a la gráfica
set title "Algoritmo - Fibonacci"
#Definimos unna función para el metodo Fibonacci
fi(x) = b0*((1+sqrt(5))/2)**x

#Indicamos al gnuplot que haga la regresión
fit fi(x) "Resultados/Salidafibonacci.txt" via b0

#Imprimimola gráfica
plot "Resultados/Salidafibonacci.txt", fi(x) title "Curva ajustada "  
# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./AjusteHibrido/Hibrido_fibonacci_floyd_hanoi/Fibonacci_hib.png"
replot

#Algoritmo Hanoi
# Da un nombre a la gráfica
set title "Algoritmo - Hanoi"
#Definimos unna función para el metodo Hanoi
h(x) = c0*2**x

#Indicamos al gnuplot que haga la regresión
fit h(x) "Resultados/Salidahanoi.txt" via c0

#Imprimimola gráfica
plot "Resultados/Salidahanoi.txt", h(x) title "Curva ajustada "  
# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./AjusteHibrido/Hibrido_fibonacci_floyd_hanoi/Hanoi_hib.png"
replot

EOF


# Ejecutar Gnuplot con el script generado
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp

# Esta parte tiene la finalidad de obtener las graficas de 
# la eficiencia hibrida de los metodos mergesort y quicksort

name="quicksort"
rm -r AjusteHibrido/Hibrido$name

# Crear un directorio para guardar los archivos
mkdir AjusteHibrido/Hibrido$name

# Crear un script de Gnuplot para generar los archivos, todo lo que hay entre EOF y EOF se escribe en un archivo,
# en este caso, script_gnuplot.gp
cat << EOF > script_gnuplot.gp
# Configuración del gráfico, se define el nombre de los ejes
set xlabel "Tamaño de entrada"
set ylabel "Tiempo de ejecución"

EOF

# Bucle para generar gráficos para cada algoritmo y tipo de dato
cat << EOF >> script_gnuplot.gp

# Algoritmo $name
# Da un nombre a la gráfica
set title "Algoritmo - $name"
#Definimos unna función para los métodos cuadraticos
f(x) = a0*x*log(x)
g(x) = b0*x*log(x)
h(x) = c0*x*log(x)
p(x) = d0*x*x+d1*x+d2

#Indicamos al gnuplot que haga la regresión
fit f(x) "Resultados/Salida1$name.txt" via a0
fit g(x) "Resultados/Salida2$name.txt" via b0
fit h(x) "Resultados/Salida3$name.txt" via c0
fit p(x) "Resultados/Salida4$name.txt" via d0,d1,d2


#Imprimimos las graficas a excepción del tipo string que estará en otra gráfica distinta
plot "Resultados/Salida1$name.txt", f(x) title "Curva ajustada int " , "Resultados/Salida2$name.txt", g(x) title "Curva ajustada float" , "Resultados/Salida3$name.txt", h(x) title "Curva ajustada double" 
# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./AjusteHibrido/Hibrido$name/${name}_hib.png"
replot

plot "Resultados/Salida4$name.txt", p(x) title "Curva ajustada string"
#Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./AjusteHibrido/Hibrido$name/${name}string_hib.png"
replot
EOF


# Ejecutar Gnuplot con el script generado
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp

