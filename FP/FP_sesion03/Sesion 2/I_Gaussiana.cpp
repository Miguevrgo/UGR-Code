/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Realizar un programa que lea los coeficientes reales µ y s de una función 
	gaussiana. A continuación el programa leerá un valor de abscisa x y se 
	imprimirá el valor que toma la función en x.
		
	Entradas: Valores de los coeficientes mu y sigma(media,desv_tipica) y de
	x(x)
	Salidas: Valor de la función en x(gaussiana)
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> //Inclusión de los recursos matemáticos

using namespace std;

int main() //Programa principal
{
	double media;		//Valor de la media
	double desv_tipica;	//Desviación típica
	double x;			//Valor de x
	double gaussiana;	//Valor de la función evaluada en x
	double const pi = 3.14159265; //Declaración constante PI
	double exponente; //Vamos a declarar la variable exponente que simboliza 
					  //la e incluyendo su exponente para facilitar la lectura 
	
	//Entrada de datos
	
	cout << "Introduce la media: ";
	cin >> media;
	cout << "Introduce la desviacion tipica: ";
	cin >> desv_tipica;
	cout << "Introduce el valor de x: ";
	cin >> x;
	
	//Cálculos
	
	exponente = exp(-1/2*pow((x-media)/desv_tipica,2)); //Calculo de la e
	gaussiana = 1/(desv_tipica*sqrt(2*pi))*exponente; //Calculo de la gaussiana
	
	
	//Salida
	cout << exponente;
	cout << "El valor de la gaussiana en x es: " << gaussiana; 

	return 0;
}

