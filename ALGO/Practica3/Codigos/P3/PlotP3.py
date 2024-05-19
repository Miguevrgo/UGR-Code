import matplotlib.pyplot as plt
import os

def main():
    # Configurar las rutas de los archivos basadas en la estructura de carpetas
    ruta_carpeta_padre = os.path.dirname(__file__)  # Asume que el script se ejecuta desde la carpeta 'ejecutable'

    # Obtener la lista de archivos puntos_j.txt
    archivos_puntos = [f for f in os.listdir(os.path.join(ruta_carpeta_padre, "Ciudades")) if f.startswith("puntos_") and f.endswith(".txt")]

    for archivo_puntos in archivos_puntos:
        ruta_puntos = os.path.join(ruta_carpeta_padre, "Ciudades", archivo_puntos)
        # Obtener el número de instancia 'j' desde el nombre del archivo de puntos
        j = int(archivo_puntos.split("_")[1].split(".")[0])

        # Leer coordenadas de los nodos desde el archivo puntos_j.txt
        with open(ruta_puntos, "r") as file:
            nodos = [list(map(float, line.strip().split())) for line in file]

        # Número máximo de archivos de resultados y matriz a procesar (ajustar según necesidad)
        num_archivos = 10

        for i in range(1, num_archivos + 1):
            ruta_resultados = os.path.join(ruta_carpeta_padre, f"Resultados", f"resultados_{j}-{i}.txt")
            ruta_matriz = os.path.join(ruta_carpeta_padre, f"Instancias", f"matriz_{j}-{i}.txt")

            try:
                # Leer la línea del camino mínimo desde resultados_j-i.txt
                with open(ruta_resultados, "r") as file:
                    lines = file.readlines()
                    camino_minimo_info = lines[-1]
                    partes = camino_minimo_info.split(':')
                    camino_minimo = list(map(int, partes[1].strip().split()))

                # Leer la matriz de distancias desde matriz_j-i.txt
                matriz_distancias = []
                with open(ruta_matriz, "r") as file:
                    for line in file:
                        fila = [float(x) if x != 'INF' else float('inf') for x in line.strip().split()]
                        matriz_distancias.append(fila)

                # Crear un gráfico
                plt.figure(figsize=(8, 6))

                # Trazar los puntos y las líneas entre ellos
                for k, (x, y) in enumerate(nodos):
                    plt.scatter(x, y, color='blue', marker='o')
                    plt.text(x, y, f'{k}', fontsize=9, ha='right')

                # Trazar la ruta mínima
                for k in range(len(camino_minimo) - 1):
                    nodo_actual = camino_minimo[k]
                    nodo_siguiente = camino_minimo[k + 1]
                    x1, y1 = nodos[nodo_actual]
                    x2, y2 = nodos[nodo_siguiente]
                    plt.plot([x1, x2], [y1, y2], color='red', linestyle='-', linewidth=2)

                # Trazar posibles caminos basados en la matriz de distancias
                for k in range(len(matriz_distancias)):
                    for l in range(len(matriz_distancias[k])):
                        distancia = matriz_distancias[k][l]
                        if distancia != 0 and distancia != float('inf'):
                            x1, y1 = nodos[k]
                            x2, y2 = nodos[l]
                            plt.plot([x1, x2], [y1, y2], color='gray', linestyle='--', linewidth=0.3)

                # Agregar título y etiquetas
                plt.xlabel("X-Coordinate")
                plt.ylabel("Y-Coordinate")
                plt.title(f"Visualization of Minimum Distance Path and Possible Paths for Instance {j}-{i}")
                plt.grid(True)

                # Guardar el gráfico en la carpeta de resultados
                plt.savefig(os.path.join(ruta_carpeta_padre, "Graficas", f"GraficaCaminoMinimo-{j}-{i}.png"))

                # Mostrar el gráfico
                plt.show()

            except FileNotFoundError:
                print(f"Alguno de los archivos para la instancia {j}-{i} no existe. Continuando con la siguiente instancia.")
                continue

if __name__ == "__main__":
    main()
