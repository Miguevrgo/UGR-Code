/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	El programa pedirá en primer lugar el número de bits (llamémosle n) que 
	tendrán los valores binarios con los que se va a trabajar. Dado n los 
	números enteros que se admitirán estarán comprendidos entre 0 y 2
	n - 1 (todos ellos pueden representarse estrictamente con n bits o menos).
	
	Entradas: Numero en decimal y bits (n_decimal,n)
	Salidas: 
	
	

****************************************************************************/

#include <iostream> // Recursos de E/S
#include <string>   // Recursos para gestionar string
#include <cmath>

using namespace std; 

int main() // Programa Principal
{             
	int n_decimal; 		// Número del que calculamos la representación binaria
	string n_binario; 	// Resultado (string formado por '0'´y '1') 
	int n; 				// Número de bits
		
	// Entrada
	
	do {
		cout << "Introduzca el numero de bits: "; 
		cin >> n;
		cout << "Introduzca un numero entero positivo: "; 
		cin >> n_decimal; 
	} while ( (n_decimal < 0) || (n_decimal > (pow(2,n)-1)) );
	
	
	// Cálculos 
	
	int n_copia = n_decimal; // Se trabaja con una copia de "n_decimal" 
	
	while (n_copia != 0) { // while (n)

		// Comparar el bit menos significativo con 1  
		
		if (n_copia & 1) 
			n_binario = "1" + n_binario;  	// Es 1
		else 
			n_binario = "0" + n_binario;	// No es 1 (es 0)
		
		n_copia >>= 1; // Desplazar a la derecha n (n /= 2)
	}
	
	
	// Presentación de resultados

	cout << endl;
	cout << n_decimal << " (dec)" << " = ";
	cout.fill('0'); //Rellena con 0 los valores que falten hasta el ancho
	cout.width(n);  //El ancho será n que es el numero de bits
	cout << n_binario << " (bin)"<< endl; 
	cout << endl; 
	
	return 0;
}
