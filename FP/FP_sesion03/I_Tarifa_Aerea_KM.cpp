/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Crear un programa que lea el número de kilometros a un destino 
	y calcule el precio final del billete con descuento.
	
	Entradas: El valor de kilometros hasta el destino 
	y el descuento(kilometros,descuento)
	Salidas: Valor del precio correspondiente a dicho viaje
	sin descuento y tras el descuento(precio,precio_descuento)
	
	La tarifa base es de 150€ y se suman 10 centimos por cada kilómetro.

****************************************************************************/
#include <iostream> // Inclusión de los recursos de E/S

using namespace std; 

int main() //Programa principal
{
	const double PRECIO_BASE = 150.0;	//Precio base
	const double PRECIO_KM = 0.1;	//Precio por kilometro
	double kilometros;
	double precio;	//Precio total sin descuento
	double descuento;
	double precio_descuento;	//Precio total con descuento
	
	//Entrada de datos
	
	cout << "Introduzca el numero de kilometros hasta el destino: " << endl;
	cin >> kilometros;
	
	//Calculos
	
	precio = PRECIO_BASE + kilometros * PRECIO_KM;
	
	//Salida de datos
	
	cout << "El precio del viaje es: " << precio << endl;
	
	//Entrada de datos descuento
	
	cout << "Introduzca el porcentaje de descuento: ";
	cin >> descuento;
	
	//Calculos descuento
	
	precio_descuento = precio - precio * (descuento/100);
	
	/*Solucion alternativa: 
	precio_descuento = precio*((100-descuento));
	*/
	
	//Salida de datos descuento
	
	cout << "El precio del viaje tras el descuento es: " << precio_descuento;
	
	return 0;
}

