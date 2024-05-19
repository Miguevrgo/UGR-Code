#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <chrono>

using namespace std;


//-----------Estructura de datos--------------------

struct tiempo{
    int hora;
    int min;
    tiempo(int h , int m){
        hora = h;
        min = m ;
    }
};
struct examen{
    tiempo inicio;
    tiempo final;
    examen(tiempo t , tiempo t1) : inicio(t), final(t1){}
};

struct compare{
    bool operator()(const examen&a,const examen&b){
        if(a.inicio.hora==b.inicio.hora){
            return a.inicio.min < b.inicio.min;
        }
        return a.inicio.hora < b.inicio.hora;
    }
};


//---------Generador de casos---------------------

/**
 * @brief generador de examenes 
 * 
 * @param n numero de examenes que se quieren 
 * @param dm limite de duracion de minutos del examen
 * @param v vector de examenes
 */
void generadorExamen(int n,int dm,vector<examen> & v){
    srand(time(nullptr));
    for(int i =0; i<n; i++) {
        int h_inicio = rand()%24;
        int m_inicio = rand()%60;
        int duracion = rand()%dm; 

        int h_final = h_inicio + duracion / 60;
        int m_final = m_inicio + duracion % 60;

        // Ajustar si los minutos son más de 60
        if (m_final >= 60) {
            h_final++;
            m_final -= 60;
        }



        // Si la hora final es 24, ajustar a 23:59
        if (h_final <= 24) {
            h_final = 23;
            m_final = 59;
        }
        // Ajustar si las horas son más de 24
        h_final %= 24;
        v.push_back(examen(tiempo(h_inicio, m_inicio), tiempo(h_final, m_final)));
    }
}
//------------------- Imprimir vector de examenes para comprobar-----------------------
void printv(const vector<examen>&v){
    for(int i = 0; i< v.size(); i++){
        cout<<v[i].inicio.hora << ":" << v[i].inicio.min << " - "<< v[i].final.hora << ":" << v[i].final.min << " \n";
    }
}

// Función para imprimir el contenido de una cola
void imprimirCola(queue<examen> cola) {
    // Mientras la cola no esté vacía
    while (!cola.empty()) {
        // Imprimir el frente de la cola
        cout<<cola.front().inicio.hora << ":" << cola.front().inicio.min << " - "<< cola.front().final.hora << ":" << cola.front().final.min << " \n";
        // Eliminar el elemento del frente de la cola
        cola.pop();
    }
    cout << endl;
}

//--------------Solucion del problema------------------
bool sesolapan(examen e1,examen e2){
    if(e1.final.hora == e2.inicio.hora){
        return e1.final.min >e2.inicio.min;
    }
    return e1.final.hora > e2.inicio.hora;
}

int minAulas(const vector<examen> & v){

    // Conjunto de candidatos v

    int naulas = 1;
    vector<queue<examen>> horario;
    //Conjunto de seleccionados horario (vector de colas , cada cola es un aula)
    
    horario.emplace_back(queue<examen>());
    horario[0].push(v[0]);
    int i;
    //
    for(int nex = 1;nex < v.size();nex++){
        i=0;
        //Funcion de seleccion
        while(i<horario.size() && (sesolapan(horario[i].back(),v[nex]))){i++;}
        //Funcion de factibilidad
        if(i==horario.size()){
            horario.emplace_back(queue<examen>());
            horario[i].push(v[nex]);
            naulas++;
        }
        else{
            horario[i].push(v[nex]);
        }
    }
    
   for(int i = 0; i<horario.size();i++){
        cout <<i<< endl;
        imprimirCola(horario[i]);
    }
    
    return naulas; //Funcion objetivo 
}

int main(int argc, char* argv[]) {

    vector<examen> horarios;
    generadorExamen(atoi(argv[1]),atoi(argv[2]), horarios);
    sort(horarios.begin(),horarios.end(),compare());
    printv(horarios);
    cout << "=========================================="<<endl;
    int n;
    auto start = chrono::high_resolution_clock::now();
    n = minAulas(horarios);
    auto end = chrono::high_resolution_clock::now();
    //cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()<<std::endl;
   
    cout << "numero de aulas : "<<n<<endl;

    return 0;
}
