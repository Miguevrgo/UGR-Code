/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// RELACIÓN DE PROBLEMAS 2 
/*	
	Programa que lee un carácter (mayúscula), lo pasa a minúscula y lo imprime.
	La tranformación se realiza considerando la equivalencia char - int
	
	Entradas: caracter en mayúscula
	Salidas:  caracter en minúscula 
   
	Esta versión comprueba la validez del valor leído (que debe ser una 
	letra mayúscula) usando un filtro.
*/
/***************************************************************************/

#include <iostream>
using namespace std;

int main()
{
	char letra; // Entrada
	char letra_minuscula; // Salida


	// Entrada --> Filtro que permite únicamente mayúsculas

	// VERSIÓN 1
	
	do {
		cout << "Introduzca una letra mayuscula  --> ";
		cin >> letra;
	} while ((letra<'A') || (letra>'Z'));

	//  VERSIÓN 2 
	/*
	bool hay_error; 
	
	do {
		cout << "Introduzca una letra mayuscula  --> ";
		cin >> letra;
		
		hay_error = ((letra<'A') || (letra>'Z'));
		
	} while (hay_error);
	*/

	//  VERSIÓN 3 
	/*
	bool es_mayuscula; 
	
	do {
		cout << "Introduzca una letra mayuscula  --> ";
		cin >> letra;
		
		es_mayuscula = ((letra>='A') && (letra<='Z'));
		
	} while (!es_mayuscula);
	*/


	// Sea como sea, aseguro que en este punto la variable "letra"  
	// contiene una letra mayúscula.

	// Cálculos
	
	/*
	Las mayúsculas están antes que las minúsculas en la tabla ASCII.
	Además, sabemos que hay el mismo número de mayúsculas que de
	minúsculas y obviamente se encuentran en el mismo orden. Por
	tanto, sólo necesitamos saber cuantos caracteres hay entre
	'A' y 'a'.

	El número de caracteres que hay entre 'A' y 'a' puede calcularse con 
	la expresión (int) 'a'-'A'
	*/

	const int DISTANCIA_MAY_MIN = 'a'-'A';    // :-)  BIEN HECHO
  
	letra_minuscula = letra + DISTANCIA_MAY_MIN;      // :-)
   
   
	// Salida
	 
	cout << endl;
	cout << "El caracter " << letra
         << " pasado a minuscula es: " << letra_minuscula << endl;
	cout << endl;

	cout << endl;		

	return 0;	
}
