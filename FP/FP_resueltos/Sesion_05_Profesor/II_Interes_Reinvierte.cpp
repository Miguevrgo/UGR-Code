/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// RELACIÓN DE PROBLEMAS 2
// 
/*	
   Programa que calcula el dinero que se obtiene al realizar una 
   inversión un número dado de años.

   Entradas: capital a invertir (capital_inicial)
			 interés a aplicar (interes)
			 número de años de la inversión (numero_anios)
   Salidas:  dinero total obtenido por la inversión 
			 (capital + ganancia obtenida) calculado -anualmente- por: 
				total = capital + (capital * interes/100)
			  reinvirtiendo cada año el nuevo total.
			  
	Se comprueba la validez de los valores leídos usando filtros	  
*/
/***************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
	cout.setf(ios::fixed);		// Notación de punto fijo para los reales
	cout.setf(ios::showpoint);	// Mostrar siempre decimales 
	
	
	const int MIN_CAPITAL = 1000;
	const int MIN_ANIOS   =    1;
	const int MAX_ANIOS   =   20;
	const int MIN_INTERES =    0; // En porcentaje 0-100
	const int MAX_INTERES =   10; // En porcentaje 0-100
	
	// Entradas: 
	double interes, capital_inicial;
	int numero_anios;
	   
	// Salidas
	double capital_acumulado;
  
	// Auxiliares 
	int anio;
	
	

	// Lectura y filtrado de datos

	const string mensaje_capital =  "Introduzca capital inicial (capital >= "
	      + to_string(MIN_CAPITAL) + "): ";
	const string mensaje_anios =  "Introduzca numero de anios (" 
	      + to_string(MIN_ANIOS) + "-" +  to_string(MAX_ANIOS) + "): ";
	const string mensaje_interes =  "Introduzca % interes (" 
	      + to_string(MIN_INTERES) + "-" +  to_string(MAX_INTERES) + "]: ";
	      	      
	do {	
		cout << mensaje_capital;
		cin >> capital_inicial;
	} while (capital_inicial < MIN_CAPITAL);

	do {	
		cout << mensaje_anios;
		cin >> numero_anios;
	} while ((numero_anios<MIN_ANIOS) || (numero_anios>MAX_ANIOS));
	
	
	do {	
		cout << mensaje_interes;
		cin >> interes;   
   	} while ((interes<= MIN_INTERES) || (interes>MAX_INTERES));

	cout << endl;

	// En este punto aseguro que 
	//	1)	MIN_CAPITAL <= capital_inicial  
	//	2)	MIN_ANIOS <= numero_anios <= MAX_ANIOS
	// 	3)	MIN_INTERES < interes <= MAX_INTERES


	// Cálculos y presentación de resultados
	
	capital_acumulado = capital_inicial; // Capital inicial
	
	double capital_anterior = capital_inicial; // Capital del año anterior
	double ganancia_acumulada = 0; // Suma de los incrementos de capital, 
									// año a año.
	
	anio  = 1; // contador de años 
   
	while (anio <= numero_anios) {
	
		// Nuevo capital pasado un año
		capital_acumulado = capital_acumulado  +  
		                   (capital_acumulado * (interes / 100.0));   
	
		double ganancia_anio = capital_acumulado - capital_anterior;
		ganancia_acumulada += ganancia_anio; 
		
		capital_anterior = capital_acumulado;
		
		// No es preciso mostrar esta información, pero ayuda a entender
		cout << "Capital obtenido transcurrido el anio numero "
			 << setw(2)  << anio << " = " 
			 << setw(10) << setprecision(2) << capital_acumulado << " ";
		cout << "(" << setw(10) << setprecision(2) << ganancia_anio << ")";
		cout << endl;
	
		anio++; // actualizar el año de inversión 
	}
   
	double incremento_capital =  capital_acumulado-capital_inicial;

	cout << setw(62) << " " << "----------" << endl; 
	cout << setw(62) << " " << setw(10) << setprecision(2) 
	     << incremento_capital << endl; 
	cout << endl;

	bool control_integridad = (incremento_capital == ganancia_acumulada);
	
	if (control_integridad) 		
		cout << "Incremento de capital = " << setw(10) << setprecision(2) 
			 << incremento_capital << endl;
	else 
		cout << "Error en los calculos realizados. ";
	
	cout << endl;
	     
	return 0;
}
