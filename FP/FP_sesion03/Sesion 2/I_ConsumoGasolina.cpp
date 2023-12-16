/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez
	Crear un programa que calcule el consumo de gasolina y cuantos km le 
	quedan con ese nivel de consumo dandole la distancia recorrida, 
	los litro de gasolina consumidos y los litros que quedan en el dep�sito.
	
	Entradas:Valores de distancia recorrida, litros consumidos y litros en 
	dep�sito(dist_recorrida,litros_cons,litros_depos)
	Salidas:Consumo de gasolina en Km/l y litros/100Km y km restantes
	(consumoKML,consumoLKM,dist_restante)
	
		Consumo(Km/L)	|	(litros/100Km)	|	Km restantes

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	double dist_recorrida,dist_restante;
	double litros_cons,litros_depos;
	double consumoKML,consumoLKM;
	
	//Entrada de datos
	
	cout << "Introduce la distancia recorrida: ";
	cin >> dist_recorrida;
	cout << endl << "Introduce los litros consumidos: ";
	cin >> litros_cons;
	cout << endl << "Introduce los litros en deposito: ";
	cin >> litros_depos;
	
	//C�lculos
	
	consumoKML = dist_recorrida/litros_cons; // Consumo en Km/L
	consumoLKM = (100*litros_cons)/dist_recorrida; // Consumo en L/100Km
	dist_restante = litros_depos*consumoKML; // Km restantes
	
	//Salida
	
	cout << "El consumo en Km/L es de: " << consumoKML << endl;
	cout << "El consumo en L/100Km es de: " << consumoLKM << endl;
	cout << "Quedan " << dist_restante << " Kilometros.";

	return 0;
}

