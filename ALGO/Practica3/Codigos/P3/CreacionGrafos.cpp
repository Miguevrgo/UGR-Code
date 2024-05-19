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

// Función para la creación de grafos a partir de un vector de puntos en 2D
void creacionGrafos(const vector<Point>& vec, vector<vector<double>>& matriz) {
    int size = vec.size();

    // Inicialización de srand con resolución más alta
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);

    for (int i = 0; i < size; i++) {
        // Num nodos que conectaremos con el nodo i
        int conexiones = rand() % (size/5 - 1) + 1; // Asegura al menos una conexión por nodo
        for (int j = 0; j < conexiones; j++) {
            int nodo_conectar;
            do {
                nodo_conectar = rand() % size;
            } while (nodo_conectar == i); // Asegura no conectarse a sí mismo

            // Añadimos su distancia a la matriz de forma simétrica
            double distancia = vec[i].distanceTo(vec[nodo_conectar]);
            matriz[i][nodo_conectar] = distancia;
            matriz[nodo_conectar][i] = distancia; // Simetría
        }
    }

    // Garantizar que al menos un nodo (p_inicio) esté conectado a todos los demás
    int p_inicio = rand() % size;
    for (int i = 0; i < size; i++) {
        if (i != p_inicio) {
            double distancia = vec[p_inicio].distanceTo(vec[i]);
            matriz[p_inicio][i] = distancia;
            matriz[i][p_inicio] = distancia; // Simetría
        }
        matriz[i][i] = 0; // Distancia a sí mismo es cero
    }
}


// Función para la creación de grafos a partir de un vector de puntos en 2D
void creacionGrafos2(const vector<Point>& vec, vector<vector<double>>& matriz) {
    int size = vec.size();
    vector<Point> conectados(size);
    vector<Point> noConectados=vec;

    // Inicialización de srand con resolución más alta
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);

    int nodo_inicial=rand()%noConectados.size();
    conectados[0]=noConectados[nodo_inicial];
    // Eliminados dicho nodo
    noConectados.erase(noConectados.begin()+nodo_inicial);

    for(int i=1; i<size; i++){
        int nodo_conectar=rand()%noConectados.size();
        int nodo_conectado= rand()%conectados.size();
        matriz[nodo_conectado][nodo_conectar]=vec[nodo_conectado].distanceTo(vec[nodo_conectar]);
        matriz[nodo_conectar][nodo_conectado]=vec[nodo_conectado].distanceTo(vec[nodo_conectar]); // Parte simétrica
        conectados[i]=noConectados[nodo_conectar];
        noConectados.erase(noConectados.begin()+nodo_conectar);
    }

    for (int i = 0; i < size; i++) {
        // Num nodos que conectaremos con el nodo i
        int conexiones = rand() % (size/20 - 1) + 1; // Asegura al menos una conexión por nodo
        for (int j = 0; j < conexiones; j++) {
            int nodo_conectar;
            do {
                nodo_conectar = rand() % size;
            } while (nodo_conectar == i); // Asegura no conectarse a sí mismo

            // Añadimos su distancia a la matriz de forma simétrica
            double distancia = vec[i].distanceTo(vec[nodo_conectar]);
            matriz[i][nodo_conectar] = distancia;
            matriz[nodo_conectar][i] = distancia; // Simetría
        }
    }
}

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

int main (int argc, char *argv[]) {

    if (argc != 3){
        cout << "Uso: " << argv[0] << " <nombreArchivoEntrada> <nombreArchivoSalida>" << endl;
        return 1;
    }
    
    ifstream lectura((string)argv[1]);

    if (!lectura.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    string linea;
    Point point;
    vector<Point> puntos;

    while(lectura >> point){
        puntos.emplace_back(point);
    }

    lectura.close();

    ofstream escritura((string)argv[2]);

    if (!escritura.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    int dimension=puntos.size();
    vector<vector<double>> matriz(dimension, vector<double>(dimension, numeric_limits<double>::max()));
    
    creacionGrafos2(puntos, matriz);
    mostrarMatriz(escritura, matriz);

    escritura.close();

    return 0;
}