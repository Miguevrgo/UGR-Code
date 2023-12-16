/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	En atletismo se expresa la rapidez de un atleta en términos de ritmo 
	(minutos y segundos por kilómetro) más que en unidades de velocidad 
	(kilómetros por hora).
	
	Escribid dos programas para convertir entre estas dos medidas:
	a) El primero leerá el ritmo (minutos y segundos, por separado) 
	y mostrará la velocidad (kilómetros por hora).
	
	
	Entradas: Valores de minutos y segundos (minutos,segundos)
	Salidas: Valor de velocidad (velocidad)
	
	
****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	int minutos;
	double segundos;
	double horas;
	double velocidad;
	const int SEG_EN_MIN = 60;	//Segundos en 1 minuto
	const int SEG_EN_HORA = 3600;	//Segundos en 1 hora
	
	//Entrada de datos
	
	cout << "Introduce los minutos: ";
	cin >> minutos;
	cout << "Introduce los segundos: ";
	cin >> segundos;
	
	//Cálculos
	
	segundos += minutos*SEG_EN_MIN; //Segundos iniciales mas seg en los min
	horas = segundos/SEG_EN_HORA; // Pasamos los segundos a horas
	
	velocidad = 1/horas; //Calculo de Km por cada hora
	
	//Salida
	
	cout << "La velocidad es de: " << velocidad << " Km/h";


	return 0;
}

