/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
#include <iomanip>

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/

/*****************************************************************************
*							  FUNCIONES										 *
*****************************************************************************/
int main() //Programa principal
{
	double numero = 2.0;
	double numero2 = 2.23;
	double numero3 = 2.328;
	
	cout.setf (ios::fixed);
	cout.setf (ios::showpoint);
	//Entrada de datos
	
	cout << setw(6) << setprecision(2) << numero << endl;
	cout << setw(6) << setprecision(3) << numero2 << endl;
	cout << setw(6) << setprecision(2) << numero3 << endl;
	
	
	//C�lculos



	//Salida
	


	return 0;
}

