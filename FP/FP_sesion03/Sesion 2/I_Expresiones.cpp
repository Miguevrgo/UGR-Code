/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Declarar las variables necesarias y traducir las siguientes fórmulas a 
	expresiones válidas del lenguaje C++
	
	Entradas: Variables x,y,h(x,y,h)
	Salidas: Resultado de a,b,c(a,b,c)

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> //Inclusión de los recursos matemáticos

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
	
	//Cálculos
	
	a = (1+(pow(x,2)/y))/(pow(x,3)/(1+y));	//Expresión función a
	
	b = (1+(1/3)*sin(h)-(1/7)*cos(h))/(2*h);	//Expresión función b
	
	c = sqrt(1+pow(exp(x)/pow(x,2),2));		//Expresión función c
	
	//Salida
	
	cout << "El valor de a es: " << a << endl;
	cout << "El valor de b es: " << b << endl;
	cout << "El valor de c es: " << c;

	return 0;
}

