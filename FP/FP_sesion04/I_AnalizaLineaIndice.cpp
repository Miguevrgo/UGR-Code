/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	En este ejercicio se va a procesar el contenido de una cadena de caracteres 
	extrayendo sus componentes. El dato string que se va a procesar tiene un 
	formato fijo y predeterminado.
	Las cadenas a procesar podrían ser líneas extraidas del índice de un
	documento. En este caso, en concreto, están formadas por
	
	• un número que indica la sección (ocupa las tres primeras casillas y 
	tiene un máximo de tres dígitos),
	• un número que indica la subsección (ocupa las tres siguientes casillas
	y tiene un máximo de tres dígitos),
	• un número que indica la subsubsección (ocupa las tres siguientes casillas
	y tiene un máximo de tres dígitos),
	• una serie de 40 caracteres que contiene el título del apartado, y
	• un número que indica la página (ocupa las cuatro siguientes casillas
	y tiene un máximo de cuatro dígitos)

	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <string> 

using namespace std;

int main() //Programa principal
{
	string cadena;

	//Entrada de datos
	
	cout << "Introduce 53 caracteres: ";
    getline (cin,cadena);
	
	string seccion = cadena.substr (0,3);
	string subseccion = cadena.substr (3,3);
	string subsubseccion = cadena.substr (6,3);
	string titulo = cadena.substr(9,40);
	string pagina = cadena.substr(49,4);
	
	//Salida
	
	cout << "Componentes:\t\t" << endl;
	cout << "\tSeccion:\t\t" << seccion <<endl;
	cout << "\tSubseccion:\t\t" << subseccion << endl;
	cout << "\tSubsubseccion:\t\t" << subsubseccion << endl;
	cout << "\tPagina:\t\t\t" << pagina << endl;
	cout << "\tTitulo:\t\t\t" << titulo << endl;
	
	cout << endl << seccion << "." << subseccion << "." 
	<< subsubseccion << "." << titulo << pagina;
	
	return 0;
}

