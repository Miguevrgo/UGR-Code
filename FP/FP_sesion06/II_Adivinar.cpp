/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Diseñar un programa para jugar a adivinar un número. El programa generará 
	un número aleatorio (entre MIN y MAX) y el usuario tendrá que adivinarlo. 
	En cada jugada el jugador introducirá un valor y el el juego indicará si el
	número introducido por el jugador está por encima o por debajo del número a 
	adivinar.Como reglas de parada considerad que el usuario: 1) haya acertado, 
	ó 2) no quiera seguir jugando, y en este caso usad un valor especial 
	(TERMINADOR) para abandonar.
	
	Entradas: Valor del numero (numero)
	Salidas: Comprobacion numero 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <ctime>
#include <cstdlib>

using namespace std;

int main() //Programa principal
{
	const int MAX = 100; //Numero maximo
	const int MIN = 0; //Numero minimo
	const int NUM_VALORES = MAX-MIN + 1; //Número de valores posibles
	const float TERMINADOR = MIN-1; //Valor para parar de adivinar
	const string mensaje_menor = "El numero introducido es menor que el " 
		   "numero a adivinar (Maximo:" + to_string(MAX) + " Minimo:" 
		  + to_string(MIN) + " Terminar:" + to_string(TERMINADOR) + "):";
	const string mensaje_mayor = "El numero introducido es mayor que el " 
		   "numero a adivinar (Maximo:" + to_string(MAX) + " Minimo:" 
		  + to_string(MIN) + " Terminar:" + to_string(TERMINADOR) + "):";
	int numero;
	time_t t;
	srand(time(&t)); // Inicializa generador de núms. aleatorios
					 // con el reloj del sistema (hora actual)
	int incognita;// Número aleatorio que se genera
	incognita = (rand() % NUM_VALORES) + MIN;
	
	//Cálculos
	
	cout << "Intente adivinar el numero: ";
	cin >> numero;
	
	while(numero != incognita && numero != TERMINADOR){
	
	    if (numero < incognita){
	    	cout << mensaje_menor << endl; 
		}
		else if (numero > incognita){
			cout << mensaje_mayor << endl;
		}
		else{
			cout << "Felicidades, has acertado el numero!";
		}
		cout << "Intente adivinar el numero: ";
	    cin >> numero;
	}

	return 0;
}

