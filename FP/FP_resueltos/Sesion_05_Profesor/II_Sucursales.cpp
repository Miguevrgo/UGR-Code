/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACI�N
// 
// (C) FRANCISCO JOS� CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACI�N E INTELIGENCIA ARTIFICIAL
//
// RELACI�N DE PROBLEMAS 2
//
/*	
	Una empresa que tiene tres sucursales decide llevar la contabilidad 
	de las ventas de sus productos a lo largo de una semana. 
	Para ello registra cada venta con tres n�meros, el identificador de 
	la sucursal (1,2 � 3), el c�digo del producto (a, b � c) y el n�mero
	de unidades vendidas. 
	Este programa lee una serie de registros y dice cu�l es la sucursal 
	que m�s productos ha vendido. 

	Entradas: Una serie de tripletas (sucursal, producto, unidades) 
			  La serie de datos termina cuando la sucursal 
			  introducida vale -1. 
	Salidas:  La salida del programa deber� seguir exactamente el 
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
	char producto;	// C�d. de producto
	int  unidades;	// Unidades vendidas
  
	int ventas_sucursal_1 = 0, // Num. de unidades vendidas   
		ventas_sucursal_2 = 0, // en cada una de las tres 
		ventas_sucursal_3 = 0; // sucursales. 

	// La lectura debe interrumpirse cuando el n�mero de sucursal 
	// sea -1, por eso debe leerse de forma anticipada y ser �sta 
	// la condici�n del ciclo while
	
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
		cin >> sucursal;  // Preparando una nueva iteraci�n
	}


	// Calcular el m�ximo entre ventas_sucursal_1, 
	// ventas_sucursal_2 y ventas_sucursal_3
	// El algoritmo puede verse en los apuntes de clase

	int maximo;					// Valor del m�ximo (unidades vendidas)
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
