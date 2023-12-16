/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez
	Dise�ar un algoritmo que calcule las horas, minutos y segundos dentro
	de su rango correspondiente. Por ejemplo, dadas 10 horas, 119 minutos 
	y 280 segundos, deber�a dar como resultado 12 horas, 3 minutos y 40 
	segundos.
	
	Entradas: Valores de horas,minutos y segundos(horas,minutos,segundos)
	Salidas: Valores de horas minutos y segundos en el rango correspondiente
	(dias,horas,minutos,segundos)
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	int dias;
	int horas;
	int minutos;
	int segundos;
	const int MIN_EN_SEG = 60;
	const int HORA_EN_MIN = 60;
	const int DIA_EN_HORAS = 24;
	
	//Entrada de datos
	
	cout << "Introduzca el numero de horas: ";
    cin >> horas;
    cout << "Introduzca el numero de minutos: ";
    cin >> minutos;
    cout << "Introduzca el numero de segundos: ";
    cin >> segundos;
	
	//C�lculos
	
	minutos += segundos/MIN_EN_SEG; //Conversi�n de segundos en minutos
	segundos %= MIN_EN_SEG; 	   //Actualizaci�n del valor de segundos
	
	horas += minutos/HORA_EN_MIN; //Conversi�n de minutos en horas
	minutos %= HORA_EN_MIN; 	 //Actualizaci�n del valor de minutos
	
	dias = horas/DIA_EN_HORAS; //Conversi�n de horas en d�as
	horas %= DIA_EN_HORAS; 	  //Actualizaci�n del valor de horas
	
	//Salida
	
	cout << "El rango correcto de dias,horas,minutos y segundos es: \n";
	cout << dias << " dias\n";
	cout << horas << " horas\n";
	cout << minutos << " minutos\n"; 
	cout << segundos << " segundos\n";

	return 0;
}

