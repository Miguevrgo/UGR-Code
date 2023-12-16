/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// RELACIÓN DE PROBLEMAS 2 
//
/* 	Programa que muestra la representación binaria de un número entero 
	decimal. El resultado que se muestra lo guarda en un dato string, que 
	contiene, evidentemente, una serie de ceros y unos.  

	Entradas: 	n_decimal, número entero positivo (int)
	Salida: 	n_binario, string que contiene ceros ('0') y unos ('1')
*/
/***************************************************************************/

#include <iostream> // Recursos de E/S
#include <string>   // Recursos para gestionar string

using namespace std; 

int main() // Programa Principal
{             
	int n_decimal; 		// Número del que calculamos la representación binaria
	string n_binario; 	// Resultado (string formado por '0'´y '1') 

		
	// Entrada
	
	do {
		cout << "Introduzca un numero entero positivo: "; 
		cin >> n_decimal; 
	} while (n_decimal < 0);
	
	
	// Cálculos 
	
	int n = n_decimal; // Se trabaja con una copia de "n_decimal" 
	
	while (n != 0) { // while (n)

		// Comparar el bit menos significativo con 1  
		
		if (n & 1) 
			n_binario = "1" + n_binario;  	// Es 1
		else 
			n_binario = "0" + n_binario;	// No es 1 (es 0)
		
		n >>= 1; // Desplazar a la derecha n (n /= 2)
	}
	
	
	// Presentación de resultados

	cout << endl; 
	cout << n_decimal << " (dec)" << " = " << n_binario << " (bin)"<< endl; 
	cout << endl; 
	
	return 0;
}
