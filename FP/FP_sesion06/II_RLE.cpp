/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Realizar un programa que lea una secuencia de caracteres terminada con el 
	carácter * y la codifique mediante el método RLE. Leed los datos desde un
	fichero externo
	
	Entradas: Secuencia de caracteres
	Salidas: Secuencia de caracteres codificada mediante RLE
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <string>

using namespace std;

int main() //Programa principal
{
	const char TERMINADOR = '*';
	string cadena;
	string cadena_codificada;
	int contador = 1;
	int posicion = 0;
	
	//Entrada de datos
	
    cin >> cadena[posicion];
	
	//Cálculos

	while (cadena[posicion] != TERMINADOR){
		cin >> cadena[posicion+1];
		if (cadena[posicion] == cadena[posicion+1]) {
			contador++;
		}
		else {
			cadena_codificada += to_string(contador); //Cantidad de caracteres
			cadena_codificada += cadena[posicion]; //Caracter repetido
			contador = 1; //Reseteamos el valor de contador
		}
		posicion++;
	}


	//Salida
	
	cout << "Cadena codificada: " << cadena_codificada << endl;

	return 0;
}

