/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Crear un programa que lea el número de kilometros a un destino 
	y calcule el precio final del billete.
	
	Entradas: El valor de kilometros hasta el destino (kilometros)
	Salidas: Valor del precio correspondiente a dicho viaje(precio)
	
	La tarifa base es de 150€ y se suman 10 centimos por cada kilómetro.

****************************************************************************/
#include <iostream> // Inclusión de los recursos de E/S

using namespace std; 

int main() //Programa principal
{
	const double PRECIO_BASE = 150.0;	//Precio base
	const double PRECIO_KM = 0.1;	//Precio por kilometro
	double kilometros;
	double precio;
	
	//Entrada de datos
	
	cout << "Introduzca el numero de kilometros hasta el destino: " << endl;
	cin >> kilometros;
	
	//Calculos
	
	precio = PRECIO_BASE + kilometros * PRECIO_KM;
	
	//Salida de datos
	
	cout << "El precio del viaje es: " << precio;
	
	return 0;
}

