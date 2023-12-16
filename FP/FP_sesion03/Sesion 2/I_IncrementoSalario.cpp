/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Construya un programa para leer el valor de una variable salario_base de
	tipo double, la incremente un 2 % e imprima el resultado en pantalla. 
	Para realizar este cálculo, multiplique por 1.02 el valor original.
	
	Entradas: Valor de salario base(salario_base)
	Salidas: Valor del salario tras el incremento
	
	En este caso he preferido usar la opcion a) por que es la mas simple y
	la que menos espacio en memoria ocupa. En caso de que el incremento fuese
	variable optaria por la b) ya que tener una constante con el porcentaje 
	de incremento sería la opción mas cómoda.

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	double salario_base;
	
	//Entrada de datos
	
	cout << "Introduzca el salario base: ";
	cin >> salario_base;
	
	//Salida
	
	cout << "El salario final es: " << salario_base*1.02;

	return 0;
}

