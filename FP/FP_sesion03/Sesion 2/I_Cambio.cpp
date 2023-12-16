/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Crear un programa para una caja de supermercado que lea el total a pagar
	y la cantidad pagada e indique el numero de monedas de 2€, 1€, 50cnts,
	20cnts, 10cnts, 5cnts, 2cnts, 1cnts que se deben dar de cambio, se 
	indicará el mínimo numero de monedas de cada clase.
	
	Entradas: Valores del total a pagar y la cantidad pagada
	(pagado, a_pagar).
	Salidas: Numero de monedas de 2€, 1€, 50cnts,20cnts, 10cnts,
	5cnts, 2cnts, 1cnts que se deben dar (MON200,MON100,MON50,MON20,MON10,
	MON5,MON2,MON1)
	
****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> //Inclusión de los recursos matemáticos

using namespace std;

int main() //Programa principal
{
	int MON200,MON100,MON50,MON20,MON10,MON5,MON2,MON1;
	double pagado, a_pagar, cambio;
	double const valor_MON200 = 2;
	double const valor_MON100 = 1;
	double const valor_MON50 = 0.5;
	double const valor_MON20 = 0.2;
	double const valor_MON10 = 0.1;
	double const valor_MON5 = 0.05;
	double const valor_MON2 = 0.02;
	double const valor_MON1 = 0.01;
	
	
	//Entrada de datos
	
	cout << "Introduce la cantidad a pagar: ";
	cin >> a_pagar;
	cout << "Introduce la cantidad pagada: ";
	cin >> pagado;
	
	//Cálculos
	
	cambio = (pagado-a_pagar); //Calculamos el cambio
	
	MON200 = cambio/valor_MON200;		 //Calculo de cuantas monedas de cada 
	cambio = fmod (cambio,valor_MON200); //tipo hacen falta
	
	MON100 = cambio/valor_MON100;
	cambio = fmod (cambio,valor_MON100);
	
	MON50 = cambio/valor_MON50;
	cambio = fmod (cambio,valor_MON50);
	
	MON20 = cambio/valor_MON20;
	cambio = fmod (cambio,valor_MON20);
	
	MON10 = cambio/valor_MON10;
	cambio = fmod (cambio,valor_MON10);
	
	MON5 = cambio/valor_MON5;
	cambio = fmod (cambio,valor_MON5);
	
	MON2 = cambio/valor_MON2;
	cambio = fmod (cambio,valor_MON2);
	
	MON1 = cambio/valor_MON1;
	
	//Salida
	
	cout << "El cambio es: \n"; //Imprime en pantalla el numero de monedas
	cout << MON200 << " Monedas de 2euros\n";
	cout << MON100 << " Monedas de 1euros\n";
	cout << MON50 << " Monedas de 50cnts\n";
	cout << MON20 << " Monedas de 20cnts\n";
	cout << MON10 << " Monedas de 10cnts\n";
	cout << MON5 << " Monedas de 5cnts\n";
	cout << MON2 << " Monedas de 2cnts\n";
	cout << MON1 << " Monedas de 1cnts\n";

	return 0;
}

