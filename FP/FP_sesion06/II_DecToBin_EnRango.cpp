/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	El programa pedir� en primer lugar el n�mero de bits (llam�mosle n) que 
	tendr�n los valores binarios con los que se va a trabajar. Dado n los 
	n�meros enteros que se admitir�n estar�n comprendidos entre 0 y 2
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
	int n_decimal; 		// N�mero del que calculamos la representaci�n binaria
	string n_binario; 	// Resultado (string formado por '0'�y '1') 
	int n; 				// N�mero de bits
		
	// Entrada
	
	do {
		cout << "Introduzca el numero de bits: "; 
		cin >> n;
		cout << "Introduzca un numero entero positivo: "; 
		cin >> n_decimal; 
	} while ( (n_decimal < 0) || (n_decimal > (pow(2,n)-1)) );
	
	
	// C�lculos 
	
	int n_copia = n_decimal; // Se trabaja con una copia de "n_decimal" 
	
	while (n_copia != 0) { // while (n)

		// Comparar el bit menos significativo con 1  
		
		if (n_copia & 1) 
			n_binario = "1" + n_binario;  	// Es 1
		else 
			n_binario = "0" + n_binario;	// No es 1 (es 0)
		
		n_copia >>= 1; // Desplazar a la derecha n (n /= 2)
	}
	
	
	// Presentaci�n de resultados

	cout << endl;
	cout << n_decimal << " (dec)" << " = ";
	cout.fill('0'); //Rellena con 0 los valores que falten hasta el ancho
	cout.width(n);  //El ancho ser� n que es el numero de bits
	cout << n_binario << " (bin)"<< endl; 
	cout << endl; 
	
	return 0;
}
