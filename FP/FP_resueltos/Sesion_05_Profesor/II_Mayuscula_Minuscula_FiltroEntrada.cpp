/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACI�N
//
// (C) FRANCISCO JOS� CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACI�N E INTELIGENCIA ARTIFICIAL
//
// RELACI�N DE PROBLEMAS 2 
/*	
	Programa que lee un car�cter (may�scula), lo pasa a min�scula y lo imprime.
	La tranformaci�n se realiza considerando la equivalencia char - int
	
	Entradas: caracter en may�scula
	Salidas:  caracter en min�scula 
   
	Esta versi�n comprueba la validez del valor le�do (que debe ser una 
	letra may�scula) usando un filtro.
*/
/***************************************************************************/

#include <iostream>
using namespace std;

int main()
{
	char letra; // Entrada
	char letra_minuscula; // Salida


	// Entrada --> Filtro que permite �nicamente may�sculas

	// VERSI�N 1
	
	do {
		cout << "Introduzca una letra mayuscula  --> ";
		cin >> letra;
	} while ((letra<'A') || (letra>'Z'));

	//  VERSI�N 2 
	/*
	bool hay_error; 
	
	do {
		cout << "Introduzca una letra mayuscula  --> ";
		cin >> letra;
		
		hay_error = ((letra<'A') || (letra>'Z'));
		
	} while (hay_error);
	*/

	//  VERSI�N 3 
	/*
	bool es_mayuscula; 
	
	do {
		cout << "Introduzca una letra mayuscula  --> ";
		cin >> letra;
		
		es_mayuscula = ((letra>='A') && (letra<='Z'));
		
	} while (!es_mayuscula);
	*/


	// Sea como sea, aseguro que en este punto la variable "letra"  
	// contiene una letra may�scula.

	// C�lculos
	
	/*
	Las may�sculas est�n antes que las min�sculas en la tabla ASCII.
	Adem�s, sabemos que hay el mismo n�mero de may�sculas que de
	min�sculas y obviamente se encuentran en el mismo orden. Por
	tanto, s�lo necesitamos saber cuantos caracteres hay entre
	'A' y 'a'.

	El n�mero de caracteres que hay entre 'A' y 'a' puede calcularse con 
	la expresi�n (int) 'a'-'A'
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
