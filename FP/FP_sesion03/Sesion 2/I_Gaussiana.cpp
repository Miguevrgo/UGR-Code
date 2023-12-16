/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez
	Realizar un programa que lea los coeficientes reales � y s de una funci�n 
	gaussiana. A continuaci�n el programa leer� un valor de abscisa x y se 
	imprimir� el valor que toma la funci�n en x.
		
	Entradas: Valores de los coeficientes mu y sigma(media,desv_tipica) y de
	x(x)
	Salidas: Valor de la funci�n en x(gaussiana)
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
#include <cmath> //Inclusi�n de los recursos matem�ticos

using namespace std;

int main() //Programa principal
{
	double media;		//Valor de la media
	double desv_tipica;	//Desviaci�n t�pica
	double x;			//Valor de x
	double gaussiana;	//Valor de la funci�n evaluada en x
	double const pi = 3.14159265; //Declaraci�n constante PI
	double exponente; //Vamos a declarar la variable exponente que simboliza 
					  //la e incluyendo su exponente para facilitar la lectura 
	
	//Entrada de datos
	
	cout << "Introduce la media: ";
	cin >> media;
	cout << "Introduce la desviacion tipica: ";
	cin >> desv_tipica;
	cout << "Introduce el valor de x: ";
	cin >> x;
	
	//C�lculos
	
	exponente = exp(-1/2*pow((x-media)/desv_tipica,2)); //Calculo de la e
	gaussiana = 1/(desv_tipica*sqrt(2*pi))*exponente; //Calculo de la gaussiana
	
	
	//Salida
	cout << exponente;
	cout << "El valor de la gaussiana en x es: " << gaussiana; 

	return 0;
}

