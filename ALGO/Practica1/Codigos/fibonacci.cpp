/**
   @file C�lculo de la sucesi�n de Fibonacci
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <chrono> 
using namespace std::chrono;


/**
   @brief Calcula el t�rmino n-�simo de la sucesi�n de Fibonacci.

   @param n: n�mero de orden del t�rmino buscado. n >= 1.

   @return: t�rmino n-�simo de la sucesi�n de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(int argc, char *argv[])
{
    int size = atoi(argv[1]);

    high_resolution_clock::time_point tantes, tdespues;
    duration<double> transcurrido;
    int f;

    tantes = high_resolution_clock::now();	
    f = fibo(size);
    tdespues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    cout << transcurrido.count();

  return 0;
}

