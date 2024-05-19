#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <iomanip> 
#include <chrono>

using namespace std;



void vectorGenerator ( const int & size, vector<double> &v){
    
    const int MAX_ASSETS_VALUE=10;

    srand48(time(NULL));

    for (int i=0; i<size; i++){
        v.push_back(drand48()*MAX_ASSETS_VALUE);
    }
}


//Devuelve el vector donde se almacena el maximo beneficio
pair<double,vector<double>> inheritance(vector<double> & father, vector<double> & son1, vector <double> & son2){

    int size=father.size();

    //Ordenamos el vector
    sort(father.begin(),father.end());

    //Dividimos el vector entre dos por un numero aleatorio
    srand(time(NULL));
    int partition=rand() % size;

    //Vemos cual es el rango mas grande de las dos particiones y sobre ese rango incluiremos los
    //valores mas grandes
    int range=(partition > (size-partition))? partition : (size-partition);

    //Variable donde se almacena la maxima suma
    int sum1=0;
    for (int i = 0; i<size;++i){
        
        //En el if se encuentra son1 que sera el que obtenga el maximo beneficio
        //ya que se cogeran el mayor numero de elementos posibles, que tengan el
        //menor valor, ya que empezamos cogiendo los ultimos valores del vector ordenado de 
        //menor a mayor. Y en son2 se almacenara el menor numero de elementos
        //posibles con los menores valores
        if(i<range){
            son1.push_back(father.back());
            sum1+=father.back();
        }else{
            son2.push_back(father.back());
        }
        father.pop_back();
        
    }
    return {sum1,son1};
}

vector<double> inheritance2(vector<double> & father, vector<double> & son1, vector <double> & son2){

    int size=father.size();

    //Dividimos el vector entre dos por un numero aleatorio
    srand(time(NULL));
    int partition=rand() % size;

    //Vemos cual es el rango mas grande de las dos particiones y sobre ese rango incluiremos los
    //valores mas grandes
    int range=(partition > (size-partition))? partition : (size-partition);
    

    int contador=0;
    int i=0;
    bool bandera=false;


    //Hacemos un for para recorrer todos los elementos del vector
    for(int j=0; j<size;++j){
        
        //Hacemos de nuevo un bucle for para ver si un elemento es valido o no
        for (int i = 0; i<size && !bandera;i++){
            //Si el elemento de cogido como referente según la iteración del 
            //bulce anterior, father[j], es mayor que un elemento del vector
            //father[i], se incrementa el contador. Cuando father[j] es mayor 
            //que un numero de elementos father[i] tantas veces como size-range,
            //ponemos la bandera en true y salimos del bucle. Esto se debe a que
            //si hay como minimo size-range elementos menores que father[j],
            //father[j] debe estar dentro del range de los mayores del vector
            if (father[j]>father[i]){
                contador++;
                if(contador==(size-range)){
                    bandera=true;
                }
            }
            
        }
        //Si esta dentro de los mayores va a son1
        if(bandera){
            son1.push_back(father[j]);
            bandera=false;
        }else{
            son2.push_back(father[j]);
            
        }
        contador=0;
    }
    //Esto se debe a si si range==size, entonces se van a almacenar todos los bienes
    //en el segundo hijo pero como hemos decidido que sea el primero el que obtenga
    //e maximo benecifio, cambiamos los elementos;
    if(range==size){
        vector<double>aux;
        aux=son1;
        son1=son2;
        son2=aux;
    }
        
    return son1;
    
}


void showVector(ofstream &output,const int & range, const vector<double>& son1, const vector<double> & son2) {
    // Configurar la salida para mostrar números con tres decimales
    output << fixed << setprecision(3);
    double sum1=0,sum2=0;

    output<<"El rango aleatorio es: "<< range <<endl;

    output<<"\nHijo 1(mayor beneficio):\n";
    for (int i = 0; i<son1.size();++i ){
        output<<son1[i]<<endl;
        sum1+=son1[i];
    }
    output<<"El beneficio obtenido por el hijo 1 es: " << sum1 << endl;

    output << "\nHijo 2:\n";
    for (int i = 0; i<son2.size();++i ){
        output<<son2[i]<<endl;
        sum2+=son2[i];
    }
    output<<"El beneficio obtenido por el hijo 2 es: " << sum2 << endl;

    output << endl;
}

int main(int argc, char *argv[]) {

    if(argc != 3){
        cout << "Numero incorrecto de parametros\n";
        return 1; 
    }

    //Creamos el vector
    int v_size=atoi(argv[1]);
    vector<double> v,son1,son2;
    vectorGenerator(v_size,v);
    pair<double,vector<double>> solution;

    //Vemos cuanto tiempo tarda en ejecutarse la funcion
    auto start = chrono::high_resolution_clock::now();
    //Resolvemos problema 1
    solution=inheritance(v,son1,son2);
    auto end = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()<<std::endl;
    

    //Imprimimos por otro archivo el reultaddo de como quedarian los vectores
    ofstream output((string)argv[2]);

    if (!output.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    
    showVector(output,solution.second.size(),son1,son2);

    output.close();
    

    return 0;
  
}
