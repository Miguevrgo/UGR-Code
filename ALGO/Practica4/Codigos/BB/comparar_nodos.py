import sys
import os
import matplotlib.pyplot as plt

def extraer_nodos(file_path):
    with open(file_path, 'r') as file:
        for line in file:
            if line.startswith("Nodos desarrollados:"):
                return int(line.split(":")[1].strip())
    return None

def comparar_nodos(out_dir, size, output_file):
    cotas = [1, 2, 3]
    nodos_desarrollados = []

    for cota in cotas:
        file_path = os.path.join(out_dir, f'Cota{cota}', f'resultado_{size}_1.txt')
        nodos = extraer_nodos(file_path)
        if nodos is not None:
            nodos_desarrollados.append(nodos)
        else:
            nodos_desarrollados.append(0)

    plt.figure()
    plt.bar(cotas, nodos_desarrollados, tick_label=[f'Cota {cota}' for cota in cotas])
    plt.xlabel('Cota')
    plt.ylabel('Nodos Desarrollados')
    plt.title(f'Comparación de Nodos Desarrollados para Tamaño {size}')
    plt.savefig(output_file)
    plt.close()

if __name__ == "__main__":
    out_dir = sys.argv[1]
    size = int(sys.argv[2])
    output_file = sys.argv[3]
    comparar_nodos(out_dir, size, output_file)
