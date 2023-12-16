/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACI�N
//
// (C) FRANCISCO JOS� CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACI�N E INTELIGENCIA ARTIFICIAL
//
// RELACI�N DE PROBLEMAS 2 
//
/* 	Programa que muestra la representaci�n binaria de un n�mero entero 
	decimal. El resultado que se muestra lo guarda en un dato string, que 
	contiene, evidentemente, una serie de ceros y unos.  

	Entradas: 	n_decimal, n�mero entero positivo (int)
	Salida: 	n_binario, string que contiene ceros ('0') y unos ('1')
*/
/***************************************************************************/

#include <iostream> // Recursos de E/S
#include <string>   // Recursos para gestionar string

using namespace std; 

int main() // Programa Principal
{             
	int n_decimal; 		// N�mero del que calculamos la representaci�n binaria
	string n_binario; 	// Resultado (string formado por '0'�y '1') 

		
	// Entrada
	
	do {
		cout << "Introduzca un numero entero positivo: "; 
		cin >> n_decimal; 
	} while (n_decimal < 0);
	
	
	// C�lculos 
	
	int n = n_decimal; // Se trabaja con una copia de "n_decimal" 
	
	while (n != 0) { // while (n)

		// Comparar el bit menos significativo con 1  
		
		if (n & 1) 
			n_binario = "1" + n_binario;  	// Es 1
		else 
			n_binario = "0" + n_binario;	// No es 1 (es 0)
		
		n >>= 1; // Desplazar a la derecha n (n /= 2)
	}
	
	
	// Presentaci�n de resultados

	cout << endl; 
	cout << n_decimal << " (dec)" << " = " << n_binario << " (bin)"<< endl; 
	cout << endl; 
	
	return 0;
}
