/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez
	Crear un programa que pida la longitud del radio, calcule el �rea 
	del circulo y la longitud de la circunferencia e imprima los resultados.
	
	Entradas: El valor del radio(radio).
	Salidas: Longitud circunferencia y �rea del circulo(lon_cir,area).
	
	Lon_cir = 2*pi*r	area=pi*r^2

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
#include <math.h> //Inclusi�n de los recursos matem�ticos

using namespace std;

int main(int argc, char** argv) //Programa principal
{
	double radio;	//Declaraci�n de variables para guardar
	double lon_cir;	//El radio,la longitud,pi y el �rea
	double area;
	double pi=3.1415927;
	
	//Entrada de datos
	
	cout << "Introduzca el valor del Radio: ";
	cin >> radio;
	
	//C�lculos
	
	lon_cir = 2*pi*radio;
	area = pi*pow(radio, 2);
	
	//Salida
	
	cout << endl;
	cout << "El valor de la longitud es: " << lon_cir << endl;
	cout << endl;
	cout << "El valor del area es: " << area << endl;
	
	return 0;
}

