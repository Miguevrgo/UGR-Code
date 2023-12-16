/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACI�N
//
// (C) FRANCISCO JOS� CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACI�N E INTELIGENCIA ARTIFICIAL
//
// RELACI�N DE PROBLEMAS 2
// 
/* 	Programa que calcula el precio del billete como sigue:
	En primer lugar se fija una tarifa base de 150 euros, la misma para 
	todos los destinos.
	Ahora bien, si el destino est� a menos de 300 kil�metros, el precio final 
	es la tarifa base. Para destinos a m�s de 300 Km, se suman 10 c�ntimos 
	por cada kil�metro de distancia al destino (a partir del Km 300).
	
	El programa lee el n�mero de kil�metros al destino y calcula 
	el precio final del billete. 
	
	--> Hasta aqu�, un ejercicio anterior <--	
	
	Despu�s, aplica descuentos (si procede).
	 
		1)	Un primer descuento vendr� determinado por el n�mero de kil�metros 
			del trayecto. 
			
			Si el trayecto es mayor de 700 km, se aplica un descuento del 2%		
		
		2) 	El segundo descuento depender� del n�mero de puntos de la 
			tarjeta de fidelizaci�n del cliente.
			
			Si el n�mero de puntos es mayor de 100, se aplica un descuento 
			del 3% y si es mayor de 200, se aplica un descuento del 4 %.

	Los dos descuentos anteriores son independientes y acumulables. 
	En cualquier caso, ambos se aplican sobre el precio del billete: en este 
	programa un cliente podr�a beneficiarse de un descuento del 2%, del 3%, 
	del 4%, del 5%, del 6%, o ninguno.
	
	--> Hasta aqu�, otro ejercicio anterior <--	

	NOVEDAD: La lectura de los datos se realiza usando filtros para asegurar  
	que el programa no avanza hasta que los datos sean correctos. 
	
*/
/***************************************************************************/


#include <iostream>   // Inclusi�n de los recursos de E/S
#include <cmath>      // Inclusi�n de los recursos matem�ticos

using namespace std; 


int main() // Programa Principal
{                       
   	const double PRECIO_KM_ADICIONAL = 0.1;	
   	const double PRECIO_BASE = 150.0;	 
   	const double KM_TARIFA_BASE = 300.0;
   	
   	const double KM_DTO_DISTANCIA = 700.0;   	
   	const double DTO_DISTANCIA = 2.0; 

   	const double PUNTOS_DTO_FIDELIDAD_1 = 100.0;   	
   	const double DTO_FIDELIDAD_1 = 3.0;	
   	const double PUNTOS_DTO_FIDELIDAD_2 = 200.0;   	
   	const double DTO_FIDELIDAD_2 = 4.0;	
   	
   	// Datos de entrada
   	double km;      // Distancia al destino
   	double puntos;  // Puntos del cliente
   	
   	// Datos calculados
	double precio_antes_descuentos; // Precio del billete antes de 
									// aplicar los descuentos
	double precio_final; // Precio final del billete
	
	double porc_descuento_total; // Porcentaje acumulado de descuento


	// Entrada de datos

	bool son_km_correctos; 

	do {
		cout << "Introduzca la distancia al destino (>0): " ;
		cin >> km;
		
		son_km_correctos = (km > 0);
		
	} while (!son_km_correctos); // usando variable bool

	
	do {		
		cout << "Introduzca puntos (>=0): " ;
		cin >> puntos;
	
	} while (puntos < 0); // usando una expresi�n bool

	// Al llegar a este punto garantizo: 1) km>0 y 2) puntos>=0
	

	// C�lculos

	// 1. C�lculo del precio antes de aplicar los descuentos	
	
	if (km <= KM_TARIFA_BASE) 
	   	precio_antes_descuentos = PRECIO_BASE;
	else {
		double km_a_tarifar = km-KM_TARIFA_BASE;
		precio_antes_descuentos = PRECIO_BASE 
		                           + (PRECIO_KM_ADICIONAL * km_a_tarifar);	
	}	   

	
	// 2. C�lculo del precio despu�s de aplicar los descuentos	
	
	porc_descuento_total = 0.0;
	
	// 2.1. Descuento por distancia
	if (km >= KM_DTO_DISTANCIA) 
		porc_descuento_total = DTO_DISTANCIA;
	
	// 2.2. Descuento por puntos
	if (puntos >= PUNTOS_DTO_FIDELIDAD_2) 
		porc_descuento_total+=DTO_FIDELIDAD_2;		
	else 
		if (puntos >= PUNTOS_DTO_FIDELIDAD_1) 
			porc_descuento_total+=DTO_FIDELIDAD_1;		
	
	precio_final = 	precio_antes_descuentos * (1-(porc_descuento_total/100.0));

	   	
	// Resultados
	
	cout << endl;
	cout << "Precio antes de descuentos:   " << precio_antes_descuentos 
	     << " Euros" << endl;
	cout << "Precio despues de descuentos: " << precio_final 
	     << " Euros" << endl;
	cout << endl;

	return 0;
}
