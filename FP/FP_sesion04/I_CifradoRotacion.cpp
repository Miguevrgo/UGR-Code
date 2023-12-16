/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Construya un programa que lea un entero representando la clave y un 
	car�cter (supondremos que se introduce correctamente una letra may�scula
	del alfabeto ingl�s).El programa codificar� el car�cter seg�n la clave 
	introducida y lo mostrar� por pantalla.
	
	Entradas: Valor de la clave y letra(clave,letra)
	Salidas: Valor de la letra tras el cifrado cesar(letra)
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	int clave; //Posiciones a desplazar
	char letra;
	int num_pasados; //Numeros que se pasa con respecto al maximo del intervalo
	int intervalos_pasados; //Intervalos COMPLETOS que se pasa
	const int MIN = 'A';	//Valor minimo del intervalo
	const int MAX = 'Z';	//Valor maximo del intervalo
	const int AMPLITUD = (MAX-MIN)+1; //Amplitud del alfabeto
	
	//Entrada de datos
	
	cout << "Letra: ";
    cin >> letra;
	cout << "Clave: " ;
    cin >> clave;
    
	//C�lculos

	if ((letra + clave) <= MAX){
		
		letra += clave;	
	} 
	else {
		
		num_pasados = letra + clave - MAX; // Numeros que se pasa
		intervalos_pasados = num_pasados / AMPLITUD; // Intervalos que se pasa
		
		//Calculamos la posicion final
		letra = (num_pasados - (intervalos_pasados*AMPLITUD)) + (MIN - 1);
	}
	
	//Salida
	
	cout << "La letra tras el cifrado es: " << letra;

	return 0;
}

