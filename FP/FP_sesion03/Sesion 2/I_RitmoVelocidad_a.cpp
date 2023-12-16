/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez
	En atletismo se expresa la rapidez de un atleta en t�rminos de ritmo 
	(minutos y segundos por kil�metro) m�s que en unidades de velocidad 
	(kil�metros por hora).
	
	Escribid dos programas para convertir entre estas dos medidas:
	a) El primero leer� el ritmo (minutos y segundos, por separado) 
	y mostrar� la velocidad (kil�metros por hora).
	
	
	Entradas: Valores de minutos y segundos (minutos,segundos)
	Salidas: Valor de velocidad (velocidad)
	
	
****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

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
	
	//C�lculos
	
	segundos += minutos*SEG_EN_MIN; //Segundos iniciales mas seg en los min
	horas = segundos/SEG_EN_HORA; // Pasamos los segundos a horas
	
	velocidad = 1/horas; //Calculo de Km por cada hora
	
	//Salida
	
	cout << "La velocidad es de: " << velocidad << " Km/h";


	return 0;
}

