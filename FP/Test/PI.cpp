/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <iomanip>
#include <cmath>
using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/

/*****************************************************************************
*							  FUNCIONES										 *
*****************************************************************************/
double calcularPi(double iteraciones) {
  double numerador = 4;
  double denominador = 1; // A este lo vamos a ir aumentando de 2 en 2
  double pi = 0;
  int x = 0;
  // Recuerda que es alternar entre negativo y positivo; por eso la bandera.
  // Comenzamos en positivo
  int operador = 1;
  for (x; x < iteraciones; x++) {
    pi += operador * (numerador / denominador);
    denominador += 2; // El denominador aumenta de 2 en 2
    operador *= -1;   // Alternamos operador
  }
  return pi;
}
int main() //Programa principal
{
	cout.setf(ios::fixed);		// Notación de punto fijo para los reales
	cout.setf(ios::showpoint);
	double numero;
	numero = calcularPi(5000000);
	cout << setprecision(400) << numero;
	long long pi = pi = 4.0 * atan(1.0);
	cout << pi;
	//Cálculos


	return 0;
}

