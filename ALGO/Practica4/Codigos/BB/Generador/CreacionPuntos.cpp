#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>

using namespace std;

int main(int argc, char * argv[]) {
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <numPuntos> <nombreArchivo> <rangoMax>" << endl;
        return 1;
    }

    int numPuntos = atoi(argv[1]);
    string filename(argv[2]);
    int rangoMax = atoi(argv[3]);

    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return 1;
    }

    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);

    for (int i = 0; i < numPuntos; i++) {
        int coordX = rand() % (rangoMax + 1);
        int coordY = rand() % (rangoMax + 1);
        file << coordX << " " << coordY << endl;
    }

    file.close();
    return 0;
}
