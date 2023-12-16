/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	En este ejercicio queremos determinar la sanción a aplicar en una autovía, 
	cuyo límite de velocidad es 120 Km/h. En la siguiente tabla se muestra la 
	velocidad del vehículo y la sanción correspondiente (número de puntos del 
	carnet de conducir que se restan y la multa en euros)

	Entradas: Valor de la velocidad(velocidad)
	Salidas: Sanciones correspondientes(puntos_carnet,multa)
	
	(120,150] -> 0, 100€
	(150,170] -> 2, 300€
	(170,180] -> 4, 400€
	(180,190] -> 6, 500€
	(190,oo)  -> 6, 600€

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	double velocidad;
	int multa;
	int puntos_carnet;
	const int MULTA_120_150 = 100;
	const int MULTA_150_170 = 300;
	const int MULTA_170_180 = 400;
	const int MULTA_180_190 = 500;
	const int MULTA_MAS_190 = 600;
	const int PUNTOS_120_150 = 0;
	const int PUNTOS_150_170 = 2;
	const int PUNTOS_170_180 = 4;
	const int PUNTOS_180_190 = 6;
	const int PUNTOS_MAS_190 = 6;

	//Entrada de datos
	
	cout << "Velocidad: ";
    cin >> velocidad;
	
	//Cálculos

	if (velocidad <= 120){
		multa = 0;
		puntos_carnet = 0;
	} 
	else if ((velocidad > 120) && (velocidad <= 150)){
		multa = MULTA_120_150;
		puntos_carnet = PUNTOS_120_150;
	}
	else if ((velocidad > 150) && (velocidad <= 170)){
		multa = MULTA_150_170;
		puntos_carnet = PUNTOS_150_170;
	}
	else if ((velocidad > 170) && (velocidad <= 180)){
		multa = MULTA_170_180;
		puntos_carnet = PUNTOS_170_180;
	}
	else if ((velocidad > 180) && (velocidad <= 190)){
		multa = MULTA_180_190;
		puntos_carnet = PUNTOS_180_190;
	}
	else if (velocidad > 190){
		multa = MULTA_MAS_190;
		puntos_carnet = PUNTOS_MAS_190;
	}
	
	

	//Salida
	cout << "Multa: " << multa << endl;
	cout << "Puntos perdidos carnet: " << puntos_carnet;
	
	return 0;
}

