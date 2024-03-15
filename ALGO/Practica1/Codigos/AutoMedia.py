def convert_file(input_file, output_file):
    # Abre el fichero de entrada en modo lectura y el fichero de salida en modo escritura
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        # Itera sobre cada línea del fichero de entrada
        for line in f_in:
            # Divide la línea en dos partes a partir del caracter ':', el tamaño y los tiempos
            parts = line.split(':') 
            # Se queda con el tamaño de cada ejecución. Elimina los espacios en blanco al principio 
            # y al final con el método strip
            size = parts[0].strip()
            # Crea el array de valores de tiempos. Convierte los valores de los tiempos a float.
            # El split separa los valores por el espacio en blanco, es decir, elimina los espacios en blanco
            # y crea un array con los valores de los tiempos
            values = list(map(float, parts[1].split()))
            avg = sum(values) / len(values) # Crea el array con los valores de los tiempos promedios
            # Formatea el promedio para evitar la notación científica, convirtiendolo en una cadena
            # de caracteres con 10 decimales
            avg_str = '{:.10f}'.format(avg) 
            # Escribe el tamaño en el fichero y el tiempo promedio de ejecución. Destacar que f indica
            # que se va a utilizar una cadena de caracteres con formato, y que se pueden incluir variables
            f_out.write(f'{size} {avg_str}\n') 

# Sirve para poder utilizar los parámetros de entrada
import sys

# Dos argumentos: el archivo de entrada y el archivo de salida
if len(sys.argv) != 3:
    print('Usage: python3 AutoMedia.py input_file output_file')
    sys.exit(1)
else:
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    convert_file(input_file, output_file)



