/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Crear un programa que calcule el tiempo minimo en segundos que puede
	emplear un vehiculo en recorrer un tramo controlado por tres radares.
	
	Entradas:
	Salidas: Tiempo umbral de sanción en segundos y en minutos y segundos
	(segundos_umbral,minutos_umbral,segundos_umbral_resto)
	
	
****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> //Inclusión de los recursos matematicos
using namespace std;

int main() //Programa principal
{
	double const KM1 = 5.3;
	double const KM2 = 8.1;
	double const KM3 = 6.4;
	double const VEL1 = 80;
	double const VEL2 = 100;
	double const VEL3 = 80;
	int const HORAS_EN_SEG = 3600; //Conversión horas en segundos
	int const HORAS_EN_MIN = 60; //Conversion horas en segundos
	double segundos_umbral;
	int minutos_umbral;
	int segundos_umbral_resto; //Segundos restantes en el formato min,seg
	
	//Cálculos
	
	segundos_umbral = ((KM1/VEL1)+(KM2/VEL2)+(KM3/VEL3))*HORAS_EN_SEG;
	minutos_umbral = ((KM1/VEL1)+(KM2/VEL2)+(KM3/VEL3))*HORAS_EN_MIN;
	segundos_umbral_resto = fmod(segundos_umbral,HORAS_EN_MIN); 
	
	//Salida
	
	cout << "El tiempo minimo en segundos que se debe emplear "
		 << "para completar el tramo es: " << segundos_umbral << "s" << endl;
		 
	cout << "El tiempo minimo en segundos y minutos que se debe emplear "
		 << "para completar el tramo es: " << minutos_umbral << "min " 
		 << segundos_umbral_resto << "s";
		 
	return 0;
}

