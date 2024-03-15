/**
   @file Resoluci�n del problema de las Torres de Hanoi
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <chrono> 
using namespace std::chrono;

/**
   @brief Resuelve el problema de las Torres de Hanoi
   @param M: n�mero de discos. M > 1.
   @param i: n�mero de columna en que est�n los discos.
             i es un valor de {1, 2, 3}. i != j.
   @param j: n�mero de columna a que se llevan los discos.
             j es un valor de {1, 2, 3}. j != i.

   Esta funci�n imprime en la salida est�ndar la secuencia de 
   movimientos necesarios para desplazar los M discos de la
   columna i a la j, observando la restricci�n de que ning�n
   disco se puede situar sobre otro de tama�o menor. Utiliza
   una �nica columna auxiliar.
*/
void hanoi (int M, int i, int j);


/* Vamos a desglosar esta función para entender lo que hace.
En primer lugar destacar que M es el número de discos que se quieren mover, i es la columna de origen 
y j es la columna de destino. Además, la columna primera en la que pueden estar los discos sera la 1, 
la segunda la 2 y la tercera la 3.
De modo que cada vez que se llama a la función se mueven M discos de la columna i a la columna j.
Para ello, se llama a la función hanoi con M-1 discos de la columna i a la columna 6-i-j, es decir,
a la columna que no es ni la de origen ni la de destino, la auxiliar (que intuitivamente podemos
pensar que suele ser la 2, de ahí que 6-i-j=6-1-3=2). Después se llama a la función hanoi con M-1 discos
de la columna 6-i-j a la columna j (de la axuliar a la de destino).
Aqui tenemos un enlace visual para poder entender mejor el algoritmo: https://www.youtube.com/watch?v=YstLjLCGmgg
*/

void hanoi (int M, int i, int j)
{
  if (M > 0)
    {
      hanoi(M-1, i, 6-i-j);
      hanoi (M-1, 6-i-j, j);
  }
}
/**
 * @brief En este código sólo tiene sentido contemplar el algoritmo con int ya que no se pueden tener un numero racional de discos para ver cuanto tardaría en finalizar el algortimo
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]) {
    int size = atoi(argv[1]);

    high_resolution_clock::time_point tantes, tdespues;
    duration<double> transcurrido;

    //int tipo = atoi(argv[2]); // 1: int
        tantes = high_resolution_clock::now();
        hanoi(size, 1, 3);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues - tantes);
        cout << transcurrido.count();
    

    return 0;

}
