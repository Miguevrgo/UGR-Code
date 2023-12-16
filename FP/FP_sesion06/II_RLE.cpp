/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Realizar un programa que lea una secuencia de caracteres terminada con el 
	car�cter * y la codifique mediante el m�todo RLE. Leed los datos desde un
	fichero externo
	
	Entradas: Secuencia de caracteres
	Salidas: Secuencia de caracteres codificada mediante RLE
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
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
	
	//C�lculos

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

