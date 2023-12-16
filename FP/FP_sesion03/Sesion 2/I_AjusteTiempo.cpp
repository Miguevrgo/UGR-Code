/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Diseñar un algoritmo que calcule las horas, minutos y segundos dentro
	de su rango correspondiente. Por ejemplo, dadas 10 horas, 119 minutos 
	y 280 segundos, debería dar como resultado 12 horas, 3 minutos y 40 
	segundos.
	
	Entradas: Valores de horas,minutos y segundos(horas,minutos,segundos)
	Salidas: Valores de horas minutos y segundos en el rango correspondiente
	(dias,horas,minutos,segundos)
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

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
	
	//Cálculos
	
	minutos += segundos/MIN_EN_SEG; //Conversión de segundos en minutos
	segundos %= MIN_EN_SEG; 	   //Actualización del valor de segundos
	
	horas += minutos/HORA_EN_MIN; //Conversión de minutos en horas
	minutos %= HORA_EN_MIN; 	 //Actualización del valor de minutos
	
	dias = horas/DIA_EN_HORAS; //Conversión de horas en días
	horas %= DIA_EN_HORAS; 	  //Actualización del valor de horas
	
	//Salida
	
	cout << "El rango correcto de dias,horas,minutos y segundos es: \n";
	cout << dias << " dias\n";
	cout << horas << " horas\n";
	cout << minutos << " minutos\n"; 
	cout << segundos << " segundos\n";

	return 0;
}

