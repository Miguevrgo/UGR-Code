/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Dise�ar un programa que lea un car�cter (supondremos que el usuario 
	introduce una min�scula), lo pase a may�scula y lo imprima en pantalla.
	Con comprobacion
	
	Entradas: Valor del caracter en minuscula(caracter).
	Salidas: Valor del caracter en mayuscula(caracter).
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	char caracter; //Caracter en min�scula
	const int MIN_EN_MAY = 'a'-'A'; //Diferencia entre minuscula y mayuscula
	
	//Entrada de datos
	
	cout << "Caracter en minuscula: ";
    cin >> caracter;
    
    //Usaremos una estructura condicional para comprobar que el caracter es una
    //Letra en minuscula
    
    if ((caracter < 'a') || (caracter > 'z')){
    	cout << "Introduce un caracter valido: ";
    	cin >> caracter;
	}
	
	//C�lculos
	
	caracter = caracter - MIN_EN_MAY; //Pasamos a Mayuscula el caracter

	//Salida
	
	cout << "Caracter en mayuscula: " << caracter;

	return 0;
}

