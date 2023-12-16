/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez
	En atletismo se expresa la rapidez de un atleta en t�rminos de ritmo 
	(minutos y segundos por kil�metro) m�s que en unidades de velocidad 
	(kil�metros por hora).
	
	Escribid dos programas para convertir entre estas dos medidas:
	b) El segundo leer� la velocidad (kil�metros por hora) y mostrar� el 
	ritmo (minutos y segundos).
	
	
	Entradas: Valor de velocidad (velocidad)
	Salidas: Valor de minutos y segundos (minutos, segundos)
	
	
****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	int minutos;
	int segundos;
	double horas;
	double velocidad;
	const int SEG_EN_MIN = 60;	//Segundos en 1 minuto
	const int SEG_EN_HORA = 3600;	//Segundos en 1 hora
	
	//Entrada de datos
	
	cout << "Introduce la velocidad: ";
	cin >> velocidad;
	
	//C�lculos
	
	horas = 1/velocidad; //Calculo de cuantas horas pasan por cada km
	segundos = horas*SEG_EN_HORA; // Pasamos las horas a segundos
	
	minutos = segundos/SEG_EN_MIN; //Calculamos los minutos
	segundos = segundos%SEG_EN_MIN; //Calculamos los segundos restantes
	
	//Salida
	
	cout << "El ritmo es de: " << minutos << "min " << segundos << "s";


	return 0;
}

