#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <chrono>

using namespace std;

int main(int argc, char * argv[]) {

    // Verificar que se hayan pasado los argumentos correctos
    if (argc != 4) {
        std::cerr << "Uso: " << argv[0] << " <numPuntos> <nombreArchivo> <rangoMax>" << std::endl;
        return 1;
    }

    // Número de puntos a generar
    int numPuntos = atoi(argv[1]);

    // Rango de los valores para las coordenadas
    int rangoMax = atoi(argv[2]);

    // Nombre del archivo donde se guardarán las coordenadas
    string filename (argv[3]);

    // Abrir archivo para escritura
    std::ofstream file(filename);

    // Verificar si el archivo está abierto
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura." << std::endl;
        return 1;
    }

    // Inicialización de srand con resolución más alta
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);

    // Generar puntos aleatorios y escribirlos en el archivo
    for (int i = 0; i < numPuntos; i++) {
        int coordX = rand() % (rangoMax + 1); // Generar coordenada x
        int coordY = rand() % (rangoMax + 1); // Generar coordenada y
        file << coordX << " " << coordY << endl; // Escribir coordenadas al archivo
    }

    // Cerrar el archivo
    file.close();

    return 0;
}
