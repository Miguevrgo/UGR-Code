/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Realizar un programa que nos pida una longitud cualquiera dada en metros. 
	El programa deberá calcular el equivalente de dicha longitud en pulgadas,
	pies, yardas y millas, y mostrarnos los resultados en pantalla.
	
	Entradas: Valor de la longitud en metros(longitud)
	Salidas: Valores de la longitud en pulgadas, pies, yardas y millas
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	double longitud;
	double const MIL_EN_CM = 10; 	//Relación Milimetros/Centímetros
	double const CM_EN_M = 100;		//Relación Centímetros/Metros
	double const M_EN_KM = 1000;	//Relación Metros/Kilometros
	double pulgadas,pies,yardas,millas;
	double const PUL_EN_MIL = 25.4;
	double const PIE_EN_CM = 30.48;
	double const YAR_EN_M = 0.9144;
	double const MILLA_EN_KM = 1.609344;
	
	//Entrada de datos
	
	cout << "Introduzca la longitud en metros: ";
	cin >> longitud;
	
	//Cálculos
	
	pulgadas = (longitud * CM_EN_M * MIL_EN_CM)/PUL_EN_MIL; //Conversiones
	pies = (longitud * CM_EN_M)/PIE_EN_CM;
	yardas = longitud/YAR_EN_M;
	millas = (longitud / M_EN_KM)/MILLA_EN_KM;
	
	//Salida
	
	cout << longitud << "m es equivalente a: " << endl;
	cout << pulgadas << " pulgadas\n";
	cout << pies << " pies\n";
	cout << yardas << " yardas\n";
	cout << millas << " millas";

	return 0;
}

