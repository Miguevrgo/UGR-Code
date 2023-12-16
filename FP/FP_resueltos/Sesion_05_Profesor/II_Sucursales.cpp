/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
// 
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// RELACIÓN DE PROBLEMAS 2
//
/*	
	Una empresa que tiene tres sucursales decide llevar la contabilidad 
	de las ventas de sus productos a lo largo de una semana. 
	Para ello registra cada venta con tres números, el identificador de 
	la sucursal (1,2 ó 3), el código del producto (a, b ó c) y el número
	de unidades vendidas. 
	Este programa lee una serie de registros y dice cuál es la sucursal 
	que más productos ha vendido. 

	Entradas: Una serie de tripletas (sucursal, producto, unidades) 
			  La serie de datos termina cuando la sucursal 
			  introducida vale -1. 
	Salidas:  La salida del programa deberá seguir exactamente el 
			  siguiente formato:
				SUCURSAL: ...
				VENTAS: ...
*/
/***************************************************************************/
 
#include <iostream>
using namespace std;

int main()
{
	const int TERMINADOR = -1;
	
	int  sucursal;	// Num. de sucursal
	char producto;	// Cód. de producto
	int  unidades;	// Unidades vendidas
  
	int ventas_sucursal_1 = 0, // Num. de unidades vendidas   
		ventas_sucursal_2 = 0, // en cada una de las tres 
		ventas_sucursal_3 = 0; // sucursales. 

	// La lectura debe interrumpirse cuando el número de sucursal 
	// sea -1, por eso debe leerse de forma anticipada y ser ésta 
	// la condición del ciclo while
	
	cout << "Sucursal : "; 
	cin >> sucursal;         

	while (sucursal != TERMINADOR) {

		// Si se ha entrado al ciclo, procesar esta venta

		cout << "Producto : "; 
		cin >> producto; 
	
		cout << "Unidades : "; 
		cin >> unidades; 

		switch (sucursal) {
			case (1) :	ventas_sucursal_1 += unidades;
						break;
			case (2) :	ventas_sucursal_2 += unidades;
						break;
			case (3) :	ventas_sucursal_3 += unidades;
						break;
		};

		cout << endl; 

		cout << "Sucursal : "; 
		cin >> sucursal;  // Preparando una nueva iteración
	}


	// Calcular el máximo entre ventas_sucursal_1, 
	// ventas_sucursal_2 y ventas_sucursal_3
	// El algoritmo puede verse en los apuntes de clase

	int maximo;					// Valor del máximo (unidades vendidas)
	int sucursal_maximo = 0;	// Sucursal asociada al maximo

	if (ventas_sucursal_1 > ventas_sucursal_2) {
		maximo = ventas_sucursal_1;
		sucursal_maximo = 1;
	}
	else {
		maximo = ventas_sucursal_2;
		sucursal_maximo = 2;
	}
	if (ventas_sucursal_3 > maximo) {
		maximo = ventas_sucursal_3;
		sucursal_maximo = 3;
	}

	// Salida

	cout << endl;
	if (maximo > 0) {
		cout << "SUCURSAL: " << sucursal_maximo << endl;
		cout << "VENTAS: " << maximo << endl;
	}
	cout << endl << endl;

	return 0;
}
