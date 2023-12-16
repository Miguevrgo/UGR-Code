/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Se quiere construir un programa que lea un número real r y un número 
	entero n y trunque r a tantas cifras decimales como indique n. El resultado
	debe guardarse en una variable diferente. La única función que puede usar
	de cmath es pow. Comprobando que el numero es r	
	
	Entradas: Valor numero real y entero (r,n)
	Salidas: Valor numero real truncado (r_tras_n)
	
	Vamos a declarar una variable int (num_sin_decimal) para que se eliminen
	los decimales que no nos interesan al truncar. Es decir:
	
	Si por ejemplo el valor(r) es 3.1415 y le truncamiento(n) es 2:
	
	3.1415 ----> 314.15 -----> 314 ----> 3.14
	valor r		r*(10^n)	 r->int		r/(10^n)
	
****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> //Inclusión de los recursos matemáticos

using namespace std;

int main() //Programa principal
{
	double r;
	int n;
	double r_tras_n;
	int num_sin_decimal;

	//Entrada de datos
	
	cout << "Valor de r:" ;
    cin >> r;
    cout << "Valor de n: ";
	cin >> n;
	
	//Cálculos

	r = r * pow(10,n); //Obtenemos parte entera hasta el valor del truncamiento
	
	num_sin_decimal = r; //Se eliminan los decimales que no interesan
	
	r_tras_n = num_sin_decimal / pow(10,n);	//Se vuelve a expresar el numero en
											//Decimal
	
	//Salida
	
	cout << "El valor de r tras truncarlo es: " << r_tras_n;

	return 0;
}

