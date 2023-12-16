/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Diseñar un programa que lea un carácter (supondremos que el usuario 
	introduce una minúscula), lo pase a mayúscula y lo imprima en pantalla.
	
	Entradas: Valor del caracter en minuscula(caracter).
	Salidas: Valor del caracter en mayuscula(caracter).
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	char caracter; //Caracter en minúscula
	const int MIN_EN_MAY = 'a'-'A'; //Diferencia entre minuscula y mayuscula
	
	//Entrada de datos
	
	cout << "Caracter en minuscula: ";
    cin >> caracter;
	
	//Cálculos
	
	caracter = caracter - MIN_EN_MAY; //Pasamos a Mayuscula el caracter

	//Salida
	
	cout << "Caracter en mayuscula: " << caracter;

	return 0;
}

