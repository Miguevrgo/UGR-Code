/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Crear un programa que lea el número de kilometros a un destino 
	y calcule el precio final del billete con descuento.
	
	a) Un primer descuento está determinado por el número de kilómetros del 
	trayecto.
	Si el trayecto es mayor de 700 km, se aplica un descuento del 2 %
	
	b) El segundo descuento dependerá del número de puntos de la tarjeta de 
	fidelización del cliente.Si el número de puntos es mayor de 100, se aplica
	un descuento del 3 % y si es mayor de 200, se aplica un descuento del 4 %.
	
	Entradas: El valor de kilometros hasta el destino 
	y los puntos en la tarjeta(kilometros,puntos_tarjeta)
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
	double puntos_tarjeta;	//Puntos en la tarjeta
	double descuento;
	const int NUMERO_KM_DESCUENTO = 700;
	const int NUMERO_PUNTOS_DESCUENTO2 = 100;
	const int NUMERO_PUNTOS_DESCUENTO3 = 200;
	const float DESCUENTO1 = 0.02;	//Descuento numero de kilometros
	const float DESCUENTO2 = 0.03;	//Descuento puntos > 100
	const float DESCUENTO3 = 0.04;	//Descuento puntos > 200
	double precio_descuento;	//Precio total con descuento
	
	//Entrada de datos
	
	cout << "Numero de kilometros hasta el destino: " << endl;
	cin >> kilometros;
	cout << "Puntos tarjeta fidelizacion: " << endl;
	cin >> puntos_tarjeta;
	
	//Calculos
	
	precio = PRECIO_BASE + kilometros * PRECIO_KM;
	
	//Salida de datos
	
	cout << "El precio del viaje es: " << precio << endl;
	
	//Calculos descuento

	if (kilometros > NUMERO_KM_DESCUENTO){
		
		descuento += DESCUENTO1;
	}
	
	if (puntos_tarjeta > NUMERO_PUNTOS_DESCUENTO3){
		
		descuento += DESCUENTO3;
	}
	else if (puntos_tarjeta > NUMERO_PUNTOS_DESCUENTO2){
		
		descuento += DESCUENTO2;
	}
	
	precio_descuento = precio*(1-descuento);

	//Salida de datos descuento
	
	cout << "El precio del viaje tras el descuento es: " << precio_descuento;
	
	return 0;
}

