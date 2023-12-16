/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez
	Declarar las variables necesarias y traducir las siguientes f�rmulas a 
	expresiones v�lidas del lenguaje C++
	
	Entradas: Variables x,y,h(x,y,h)
	Salidas: Resultado de a,b,c(a,b,c)

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
#include <cmath> //Inclusi�n de los recursos matem�ticos

using namespace std;

int main() //Programa principal
{
	double x,y,h;
	double a,b,c;
	
	//Entrada de datos
	
	cout << "Introduce el valor de x: ";
	cin >> x;
	cout << "Introduce el valor de y: ";
	cin >> y;
	cout << "Introduce el valor de h: ";
	cin >> h;
	
	//C�lculos
	
	a = (1+(pow(x,2)/y))/(pow(x,3)/(1+y));	//Expresi�n funci�n a
	
	b = (1+(1/3)*sin(h)-(1/7)*cos(h))/(2*h);	//Expresi�n funci�n b
	
	c = sqrt(1+pow(exp(x)/pow(x,2),2));		//Expresi�n funci�n c
	
	//Salida
	
	cout << "El valor de a es: " << a << endl;
	cout << "El valor de b es: " << b << endl;
	cout << "El valor de c es: " << c;

	return 0;
}

