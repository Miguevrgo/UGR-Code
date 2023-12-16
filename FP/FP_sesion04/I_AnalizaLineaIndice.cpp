/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	En este ejercicio se va a procesar el contenido de una cadena de caracteres 
	extrayendo sus componentes. El dato string que se va a procesar tiene un 
	formato fijo y predeterminado.
	Las cadenas a procesar podr�an ser l�neas extraidas del �ndice de un
	documento. En este caso, en concreto, est�n formadas por
	
	� un n�mero que indica la secci�n (ocupa las tres primeras casillas y 
	tiene un m�ximo de tres d�gitos),
	� un n�mero que indica la subsecci�n (ocupa las tres siguientes casillas
	y tiene un m�ximo de tres d�gitos),
	� un n�mero que indica la subsubsecci�n (ocupa las tres siguientes casillas
	y tiene un m�ximo de tres d�gitos),
	� una serie de 40 caracteres que contiene el t�tulo del apartado, y
	� un n�mero que indica la p�gina (ocupa las cuatro siguientes casillas
	y tiene un m�ximo de cuatro d�gitos)

	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
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

