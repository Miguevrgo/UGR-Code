/**
   @file Ordenaci�n por mezcla
*/

   
#include <chrono>
using namespace std::chrono;   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>






/* ************************************************************ */ 
/*  M�todo de ordenaci�n por mezcla  */

/**
   @brief Ordena un vector por el m�todo de mezcla.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de mezcla.
*/
template<typename P>
inline static void mergesort(P T[], int num_elem);



/**
   @brief Ordena parte de un vector por el m�todo de mezcla.

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
   Aplica el algoritmo de la mezcla.
*/
template<typename P>
static void mergesort_lims(P T[], int inicial, int final);


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
   Aplica el algoritmo de la inserci�n.
*/
template<typename P>
static void insercion_lims(P T[], int inicial, int final);


/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a escribir.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a escribir
		   inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El n�mero de elementos de U y V sumados debe coincidir
             con final - inicial.

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los
   elementos de los vectores U y V.
*/
template<typename P>
static void fusion(P T[], int inicial, int final, P U[], P V[]);



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
    while ((T[j] < T[j-1]) && (j > inicial)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


const int UMBRAL_MS = 100;

template<typename P>
void mergesort(P T[], int num_elem)
{
  mergesort_lims(T, 0, num_elem);
}


template<typename P>
static void mergesort_lims(P T[], int inicial, int final)
{
  if (final - inicial < UMBRAL_MS)
    {
      insercion_lims(T, inicial, final);
    } else {
      int k = (final - inicial)/2;

      P * U = new P [k - inicial + 1];
      assert(U);
      int l, l2;
      for (l = 0, l2 = inicial; l < k - inicial; l++, l2++)
	    U[l] = T[l2];
      U[l] = INT_MAX;

      P * V = new P [final - k + 1];
      assert(V);
      for (l = 0, l2 = k; l < final - k; l++, l2++)
	    V[l] = T[l2];
      V[l] = INT_MAX;

      mergesort_lims(U, 0, k - inicial);
      mergesort_lims(V, 0, final - k);
      fusion(T, inicial, final, U, V);
      delete [] U;
      delete [] V;
    };
}
  
template<typename P>
static void fusion(P T[], int inicial, int final, P U[], P V[])
{
  int j = 0;
  int k = 0;
  for (int i = inicial; i < final; i++)
    {
      if (U[j] < V[k]) {
	T[i] = U[j];
	j++;
      } else{
	T[i] = V[k];
	k++;
      };
    };
}





int main(int argc, char *argv[]) {

    int size = atoi(argv[1]);

    high_resolution_clock::time_point tantes, tdespues;
    duration<double> transcurrido;

    int tipo = atoi(argv[2]); // 1: int, 2: float, 3: double

    // Crear el array según el tipo especificado
    if (tipo == 1) { // int
        int *T = new int[size];
        assert(T);
        for (int i = 0; i < size; ++i) {
            T[i] = static_cast<int>(random());
        }
        tantes = high_resolution_clock::now();
        mergesort(T, size);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues - tantes);
        cout << transcurrido.count();
        delete[] T;
    } else if (tipo == 2) { // float
        float *T = new float[size];
        assert(T);
        for (int i = 0; i < size; ++i) {
            T[i] = static_cast<float>(random());
        }
        tantes = high_resolution_clock::now();
        mergesort(T, size);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues - tantes);
        cout << transcurrido.count();
        delete[] T;
    } else { // double
        double *T = new double[size];
        assert(T);
        for (int i = 0; i < size; ++i) {
            T[i] = static_cast<double>(random());
        }
        tantes = high_resolution_clock::now();
        mergesort(T, size);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues - tantes);
        cout << transcurrido.count();
        delete[] T;
    }

    return 0;
}
