#!/bin/bash

# This Script executes the programs:
# opt variable for is the type of variable to execute (1 -> int , 2 -> float, 3 -> double)
# Then files is the executable files with O(n^2) complexity
# Then files2 is the executable files with O(nlogn) complexity
# If option "clean" is provided, the previous files are removed (CAUTION)
# Each file is executed with different sizes of data 5 times
# Once the files are executed, the python script AutoMedia.py is executed to get the average of the results
# The results are stored in the folder "Resultados"

# Option 1 to remove previous files if argument provided
if [ "$1" == "clean" ]; then
    rm -r Resultados
    rm -r Graficas
fi
mkdir Resultados
    

for ((opt=1; opt <= 3 ; ++opt)); do 

    files=("burbuja" "insercion" "seleccion") # Array de archivos ejecutables con eficiencia O(n^2)
    

    for file in "${files[@]}"; do # Se hace un bucle for para ejecutar cada archivo del array

        # Bucles principales de ejecucion
        # i = tamaño de los datos 
        # j = numero de ejecuciones

        for ((i=5000; i<=125000 ; i+=5000)) do
            printf "$i: \t\t" >> $file$opt.txt
            for ((j=1; j<=2 ; j++)) do
                # Ejecucion del programa y redireccion a archivo txt
                ./Ejecutables/$file $i $opt >> $file$opt.txt            
                printf " " >> $file$opt.txt
            done
            printf "\n" >> $file$opt.txt
        done
    done



    for file in "${files[@]}"; do
        python3 AutoMedia.py $file$opt.txt output$file$opt.txt
    done

    # ALGORITMOS DE ORDENACION CON EFICIENCIA O(nlogn)----------------------------------------------

    files2=("mergesort" "quicksort")

    for file in "${files2[@]}"; do

        # Bucles principales de ejecucion
        # i = tamaño de los datos 
        # j = numero de ejecuciones

        for ((i=50000; i<=1250000 ; i+=50000)) do
            printf "$i: \t\t" >> $file$opt.txt
            for ((j=1; j<=2 ; j++)) do
                # Ejecucion del programa y redireccion a archivo txt
                ./Ejecutables/$file $i $opt >> $file$opt.txt            
                printf " " >> $file$opt.txt
            done
            printf "\n" >> $file$opt.txt
        done
    done

    for file in "${files2[@]}"; do
        python3 AutoMedia.py $file$opt.txt output$file$opt.txt
    done





done

# ALGORITMOS DE ORDENACION CON EFICIENCIA O()----------------------------------------------
    
files5=("fibonacci")

for file in "${files5[@]}"; do
        
    # Bucles principales de ejecucion
    # i = tamaño de los datos 
    # j = numero de ejecuciones

    for ((i=2; i<=50 ; i+=2)) do
        printf "$i: \t\t" >> $file.txt
        for ((j=1; j<=2 ; j++)) do
            # Ejecucion del programa y redireccion a archivo txt
            ./Ejecutables/$file $i >> $file.txt            
            printf " " >> $file.txt
        done
        printf "\n" >> $file.txt
    done
done

for file in "${files5[@]}"; do
    python3 AutoMedia.py $file.txt output$file.txt
done

# ALGORITMOS DE ORDENACION CON EFICIENCIA O()----------------------------------------------
    
files3=("hanoi")

for file in "${files3[@]}"; do
    # Redireccion a archivo txt con los resultados con salto de linea tras cada archivo
    # printf "File: $file.cpp\n" >> $file.txt

    # Bucles principales de ejecucion-> i para el tamaño de los datos y j para el numero de ejecuciones
    for ((i=3; i<=33 ; i++)) do
        printf "$i: \t\t" >> $file.txt
        for ((j=1; j<=2 ; j++)) do
            # Ejecucion del programa y redireccion a archivo txt
            ./Ejecutables/$file $i >> $file.txt            
            printf " " >> $file.txt
        done
        printf "\n" >> $file.txt
    done
done

for file in "${files3[@]}"; do
    python3 AutoMedia.py $file.txt output$file.txt
done

# ALGORITMOS DE ORDENACION CON EFICIENCIA O(n³)----------------------------------------------

files4=("floyd")

for file in "${files4[@]}"; do
        
    # Bucles principales de ejecucion
    # i = tamaño de los datos 
    # j = numero de ejecuciones

    for ((i=50; i<=1250 ; i+=50)) do
        printf "$i: \t\t" >> $file.txt
        for ((j=1; j<=2 ; j++)) do
            # Ejecucion del programa y redireccion a archivo txt
            ./Ejecutables/$file $i >> $file.txt            
            printf " " >> $file.txt
        done
        printf "\n" >> $file.txt
    done
done

for file in "${files4[@]}"; do
    python3 AutoMedia.py $file.txt output$file.txt
done


filestr=("mergesort" "quicksort" "burbuja" "insercion" "seleccion")

for file in "${filestr[@]}"; do
    
    for ((i = 12308;i<=202308;i+=10000)) do
        printf "$i: \t\t" >> "$file"4.txt
        for ((j=1; j<=2 ; j++)) do
            # Ejecucion del programa y redireccion a archivo txt
            ./Ejecutables/$file $i 4 >> "$file"4.txt            
            printf " " >> "$file"4.txt
        done
        printf "\n" >> "$file"4.txt
    done
done

for file in "${filestr[@]}"; do
    python3 AutoMedia.py "$file"4.txt output"$file"4.txt
done









#----------------------|Se mueven los archivos a la carpeta de resultados|----------------

mv *.txt ./Resultados

#---------------------------|Se eliminan los archivos innecesarios|-----------------------

# Habilitar las expansiones de extglob
shopt -s extglob

# Eliminar archivos que no comiencen con "output" en la carpeta "Resultados"
rm Resultados/!("output"*)

#-----------------------------------------------------------------------------------------


# Generación de gráficos con Gnuplot
mkdir Graficas
# Archivo de script de Gnuplot
cat << EOF > script_gnuplot.gp
# Configuración del gráfico
set xlabel "Tamaño de entrada"
set ylabel "Tiempo de ejecución"

EOF

# Bucle para generar gráficos para cada algoritmo y tipo de dato
for algorithm in "mergesort" "quicksort" "burbuja" "insercion" "seleccion"; do
    cat << EOF >> script_gnuplot.gp

# Algoritmo $algorithm

set title "Algoritmo - $algorithm"
plot "Resultados/output${algorithm}1.txt" using 1:2 with linespoints title "int", \
     "Resultados/output${algorithm}2.txt" using 1:2 with linespoints title "float", \
     "Resultados/output${algorithm}3.txt" using 1:2 with linespoints title "double" \
     "Resultados/output${algorithm}4.txt" using 1:2 with linespoints title "string"

# Guardar la gráfica en un archivo de imagen
set term png
set output "./Graficas/${algorithm}.png"
replot
EOF

# Ejecutar Gnuplot con el script generado
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp
done


#----------------------------|El resto de algoritmos|-------------------------------

for algorithm in "fibonacci" "hanoi" "floyd"; do
    cat << EOF >> script_gnuplot.gp

# Algoritmo $algorithm

set title "Algoritmo - $algorithm"
plot "Resultados/output${algorithm}.txt" using 1:2 with linespoints title "int"

# Guardar la gráfica en un archivo de imagen
set term png
set output "./Graficas/${algorithm}.png"
replot
EOF
done

# Ejecutar Gnuplot con el script generado para los algoritmos adicionales
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp

