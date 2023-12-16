/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez
	Crear un programa que pida un valor de intensidad 
	y resistencia e imprima el voltaje correspondiente.
	
	Entradas: Los valores de intensidad y resistencia(intensidad,resistencia).
	Salidas: Valor de voltaje correspondiente(voltaje).
	
	voltaje=intensidad*resistencia

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

using namespace std;

int main(int argc, char** argv) //Programa principal
{
	double intensidad;	//Declaraci�n de variables para guardar
	double resistencia;	//La intensidad,resistencia e hipotenusa
	double voltaje;
	
	//Entrada de datos
	
	cout << "Introduzca el valor de la Intensidad: ";
	cin >> intensidad;
	cout << "Introduzca el valor de la Resistencia: ";
	cin >> resistencia;
	
	//C�lculo
	
	voltaje = intensidad*resistencia;
	
	//Salida
	
	cout << endl;
	cout << "El valor del voltaje es: " << voltaje << endl;
	
	return 0;
}
