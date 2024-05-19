#include <iostream>
#include <chrono>
using namespace std::chrono;   
#include <limits>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>

using namespace std;

// Número máximo de vértices en el grafo

const double INF = numeric_limits<double>::max();

// Función auxiliar para encontrar el vértice con la distancia mínima
int minDistance(const vector<double>& dist, const vector<bool>& visited) {
    double min = INF;
    int min_index = -1; // Inicializado a -1 para detectar errores si no se encuentra ninguno
  
    for (int v = 0; v < dist.size(); v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Función para imprimir el camino recorrido
void printPath(const vector<int>& parent, int src, int dst) {
    stack<int> path;
    int current = dst;
    while (current != src) {
        path.push(current);
        current = parent[current];
    }
    path.push(src);

    cout << "Camino desde el nodo " << src << " al nodo " << dst << ": ";
    while (!path.empty()) {
        cout << path.top() << " ";
        path.pop();
    }
    cout << endl;
}

// Función para implementar el algoritmo de Dijkstra desde inicio hasta un nodo destino w
void dijkstra(const vector<vector<double>>& graph, int inicio, int final) {
    int V = graph.size();
    vector<double> dist(V, INF); // Distancias mínimas
    vector<bool> visited(V, false); // Nodos visitados
    vector<int> parent(V, -1); // Para rastrear el camino

    // Inicializar la distancia del nodo inicial a sí mismo como 0
    dist[inicio] = 0;
  
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = true;
  
        // Si el nodo seleccionado es el nodo destino, terminar el algoritmo
        if (u == final)
            break;
  
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; // Registrar el nodo padre para rastrear el camino
            }
        }
    }
  
    // Imprimir la distancia mínima
    cout << "Distancia mínima desde el nodo " << inicio << " al nodo " << final << ": " << dist[final] << endl;

    // Imprimir el camino recorrido
    printPath(parent, inicio, final);
}
 

// Función para leer la matriz desde un archivo
void lecturaMatriz(ifstream &leer, vector<vector<double>>& matrix) {
    string line;
    while (getline(leer, line)) {
        vector<double> row;
        stringstream ss(line);
        string val_str;
        while (ss >> val_str) {
            if (val_str == "INF") {
                row.push_back(numeric_limits<double>::max());
            } else {
                row.push_back(stod(val_str));
            }
        }
        matrix.push_back(row);
    }
}



int main(int argc, char *argv[]) {
    if (argc != 4 && argc != 5) {
        cerr << "Uso: " << argv[0] << " <archivo_matriz> <nodo_inicial> <nodo_final>" << endl;
        return 1;
    }
    high_resolution_clock::time_point tantes, tdespues;
    ifstream lectura(argv[1]);

    if(!lectura.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    int inicio = stoi(argv[2]);
    int final = stoi(argv[3]);

    vector<vector<double>> graph;
    lecturaMatriz(lectura, graph);

    if (graph.empty()) {
        cerr << "No se pudo leer la matriz desde el archivo." << endl;
        return 1;
    }
    
    tantes = high_resolution_clock::now();
    dijkstra(graph, inicio, final);
    tdespues = high_resolution_clock::now();
    duration<double> transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    if (argc==5){
        ofstream os(argv[4], ios::app);
        if (!os.is_open()){
            cout << "Error al abrir el archivo" << endl;
            return 1;
        }
        else{
            os << graph.size() << " " << transcurrido.count() << "\n";


        }
    }
    return 0;
}
