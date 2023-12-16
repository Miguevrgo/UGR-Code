/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Dise�ar un programa para jugar a adivinar un n�mero. El programa generar� 
	un n�mero aleatorio (entre MIN y MAX) y el usuario tendr� que adivinarlo. 
	En cada jugada el jugador introducir� un valor y el el juego indicar� si el
	n�mero introducido por el jugador est� por encima o por debajo del n�mero a 
	adivinar.Como reglas de parada considerad que el usuario: 1) haya acertado, 
	� 2) no quiera seguir jugando, y en este caso usad un valor especial 
	(TERMINADOR) para abandonar.
	
	Entradas: Valor del numero (numero)
	Salidas: Comprobacion numero 
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
#include <ctime>
#include <cstdlib>

using namespace std;

int main() //Programa principal
{
	const int MAX = 100; //Numero maximo
	const int MIN = 0; //Numero minimo
	const int NUM_VALORES = MAX-MIN + 1; //N�mero de valores posibles
	const float TERMINADOR = MIN-1; //Valor para parar de adivinar
	const string mensaje_menor = "El numero introducido es menor que el " 
		   "numero a adivinar (Maximo:" + to_string(MAX) + " Minimo:" 
		  + to_string(MIN) + " Terminar:" + to_string(TERMINADOR) + "):";
	const string mensaje_mayor = "El numero introducido es mayor que el " 
		   "numero a adivinar (Maximo:" + to_string(MAX) + " Minimo:" 
		  + to_string(MIN) + " Terminar:" + to_string(TERMINADOR) + "):";
	int numero;
	time_t t;
	srand(time(&t)); // Inicializa generador de n�ms. aleatorios
					 // con el reloj del sistema (hora actual)
	int incognita;// N�mero aleatorio que se genera
	incognita = (rand() % NUM_VALORES) + MIN;
	
	//C�lculos
	
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

