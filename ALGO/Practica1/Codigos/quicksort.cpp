/**
   @file Ordenaci�n r�pida (quicksort).
*/

 
#include <chrono>
#include <fstream>
using namespace std::chrono;  
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>






/* ************************************************************ */ 
/*  M�todo de ordenaci�n r�pida  */

/**
   @brief Ordena un vector por el m�todo quicksort.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo quicksort.
*/
template<typename P>
inline static 
void quicksort(P T[], int num_elem);



/**
   @brief Ordena parte de un vector por el m�todo quicksort.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo quicksort.
*/
template<typename P>
static void quicksort_lims(P T[], int inicial, int final);


/**
   @brief Ordena un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
template<typename P>
inline static 
void insercion(P T[], int num_elem);


/**
   @brief Ordena parte de un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
template<typename P>
static void insercion_lims(P T[], int inicial, int final);


/**
   @brief Redistribuye los elementos de un vector seg�n un pivote.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.
   @param pp: Posici�n del pivote. Es MODIFICADO.

   Selecciona un pivote los elementos de T situados en las posiciones
   entre inicial y final - 1. Redistribuye los elementos, situando los
   menores que el pivote a su izquierda, despu�s los iguales y a la
   derecha los mayores. La posici�n del pivote se devuelve en pp.
*/
template<typename P>
static void dividir_qs(P T[], int inicial, int final, int & pp);



/**
   Implementaci�n de las funciones
**/

template<typename P>
inline static void insercion(P T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}

template<typename P>
static void insercion_lims(P T[], int inicial, int final)
{
  int i, j;
  P aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((j > 0) && (T[j] < T[j-1])) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


const int UMBRAL_QS = 50;

template<typename P>
inline void quicksort(P T[], int num_elem)
{
  quicksort_lims(T, 0, num_elem);
}

template<typename P>
static void quicksort_lims(P T[], int inicial, int final)
{
  int k;
  if (final - inicial < UMBRAL_QS) {
    insercion_lims(T, inicial, final);
  } else {
    dividir_qs(T, inicial, final, k);
    quicksort_lims(T, inicial, k);
    quicksort_lims(T, k + 1, final);
  };
}

/* El objetivo de este método es modificar pp para que tenga un pivote que es encuentre
en medio de los elementos de T entre las posiciones inicial y final - 1, donde los elementos
mayores que el pivote se encuentran a la derecha y los menores e iguales a la izquierda.
*/
template<typename P>
static void dividir_qs(P T[], int inicial, int final, int & pp)
{
  P pivote, aux;
  int k, l;

  pivote = T[inicial];
  k = inicial;
  l = final;
  do {
    k++;
  } while ((T[k] <= pivote) && (k < final-1));
  do {
    l--;
  } while (T[l] > pivote);
  while (k < l) {
    aux = T[k];
    T[k] = T[l];
    T[l] = aux;
    do k++; while (T[k] <= pivote);
    do l--; while (T[l] > pivote);
  };
  aux = T[inicial];
  T[inicial] = T[l];
  T[l] = aux;
  pp = l;
};


int main(int argc, char * argv[]){

  int size = atoi(argv[1]);

  high_resolution_clock::time_point tantes, tdespues;
  duration<double> transcurrido;
  int tipo = atoi(argv[2]); // 1: int, 2: float, 3: double

    // Crear el array según el tipo especificado
    if (tipo == 1) { // int
        int *T = new int[size];
        // Verificación si la memoria fue asignada exitosamente
        assert(T);
        for (int i = 0; i < size; ++i) {
            // Hacer cast a int de random()
            T[i] = static_cast<int>(random());
        }
        tantes = high_resolution_clock::now();
        quicksort(T, size);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues - tantes);
        cout << transcurrido.count();
        delete[] T;
    } else if (tipo == 2) { // float
        float *T = new float[size];
        // Verificación si la memoria fue asignada exitosamente
        assert(T);
        for (int i = 0; i < size; ++i) {
            // Hacer cast a float de random()
            T[i] = static_cast<float>(random());
        }
        tantes = high_resolution_clock::now();
        quicksort(T, size);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues - tantes);
        cout << transcurrido.count();
        delete[] T;
    } else if (tipo==3){ // double
        double *T = new double[size];
        // Verificación si la memoria fue asignada exitosamente
        assert(T);
        for (int i = 0; i < size; ++i) {
            // Hacer cast a double de random()
            T[i] = static_cast<double>(random());
        }
        tantes = high_resolution_clock::now();
        quicksort(T, size);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues - tantes);
        cout << transcurrido.count();
        delete[] T;
    }else {
      ifstream is;  
      string aux, filename="quijote.txt"; // Variable usada para la lectura de las palabras en el caso de ser seleccionado el tipo 4
      is.open(filename);// Apertura del archivo de entrada

      string *T = new string[size];
      for (int i = 0; i < size; i++){
        is >> aux;
          // Se copia en el array las palabras leidas de quijote.txt
        T[i] = aux;
      }
      is.close();
      tantes = high_resolution_clock::now();
      quicksort(T, size);
      tdespues = high_resolution_clock::now();
      transcurrido = duration_cast<duration<double>>(tdespues - tantes);
      cout << transcurrido.count();
      delete[] T;
    }
    return 0;
}