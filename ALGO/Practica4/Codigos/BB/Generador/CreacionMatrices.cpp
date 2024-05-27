#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <iomanip> // Para std::setw
#include <limits>
#include <chrono>

using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}
    Point (){
        x = 0;
        y = 0;
    }

    /**
     * @brief Calculates the distance between two points using the 
     * Euclidean distance formula.
     * 
     * @param p other point
     * @return Distance between the two points
     */
    double distanceTo(const Point &p) const {
        return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << "(" << point.x << "," << point.y << ")";
        return os;
    }

    friend istream &operator>>(istream &is, Point &point) {
        is >> point.x >> point.y;
        return is;
    }
};

// Función para mostrar un vector de puntos
void mostrarVector(const std::vector<Point>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

// Función para mostrar una matriz en un archivo de salida
void mostrarMatriz(std::ofstream &salida, const std::vector<std::vector<double>>& matriz) {
    int anchoMaximo = 0; // Variable para almacenar el ancho máximo encontrado en toda la matriz
    const std::string infStr = "INF";

    // Primero, vamos a calcular el ancho máximo para los números y "INF"
    for (const auto& fila : matriz) {
        for (double elemento : fila) {
            std::ostringstream ss;
            if (elemento != std::numeric_limits<double>::max()) {
                ss << std::fixed << std::setprecision(3) << elemento; // Convertir el número a string con 3 decimales
            } else {
                ss << infStr; // Si es infinito, usamos "INF"
            }
            anchoMaximo = std::max(anchoMaximo, static_cast<int>(ss.str().length())); // Actualizar el ancho máximo
        }
    }

    // Configuración de la salida con el ancho encontrado
    salida << std::fixed << std::setprecision(3);

    // Mostrar la matriz con el ancho máximo
    for (const auto& fila : matriz) {
        for (double elemento : fila) {
            if (elemento == std::numeric_limits<double>::max()) {
                salida << std::right << std::setw(anchoMaximo) << infStr << "\t";
            } else {
                salida << std::right << std::setw(anchoMaximo) << elemento << "\t";
            }
        }
        salida << std::endl;
    }
}

int main(int argc, char* argv[]) {

    // Verificar que se hayan pasado los argumentos correctos
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <archivo de puntos> <archivo de salida>" << std::endl;
        return 1;
    }

    const char* inputFileName = argv[1];
    const char* outputFileName = argv[2];

    std::vector<Point> puntos;
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (!inputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada: " << inputFileName << std::endl;
        return 1;
    }

    Point p;
    while (inputFile >> p) {
        puntos.push_back(p);
    }
    inputFile.close();

    int n = puntos.size();
    std::vector<std::vector<double>> matriz_adyacencia(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matriz_adyacencia[i][j] = puntos[i].distanceTo(puntos[j]);
        }
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida: " << outputFileName << std::endl;
        return 1;
    }

    outputFile << std::fixed << std::setprecision(2);  // Setting precision for output
    mostrarMatriz(outputFile, matriz_adyacencia);
    outputFile.close();

    return 0;
}