/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Diseñar un programa para jugar a adivinar un número. El programa generará 
	un número aleatorio (entre MIN y MAX) y el usuario tendrá que adivinarlo. 
	En cada jugada el jugador introducirá un valor y el el juego indicará si 
	el número introducido por el jugador está por encima o por debajo del 
	número a adivinar.
	Como reglas de parada considerad que el usuario: 1) haya acertado, ó 2) 
	no quiera seguir jugando, y en este caso usad un valor especial (TERMINADOR)
	para abandonar
	Al terminar (no se quiere jugar más) el programa mostrará cuántos juegos 
	se han realizado (en caso de abandono también se contabiliza ese juego).

	Entradas: Valor del numero (numero) 
	Salidas: Comprobacion numero y numero de juegos
	
	

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
	char seguir_jugando; //Comprobar si quiere volver a jugar
	int numero_juegos = 0; //Numero de juegos
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
	
	//Cálculos
	
	bool en_rango;
	bool parar_jugar;
	while (parar_jugar == false){
		incognita = (rand() % NUM_VALORES) + MIN; //Se genera la incognita
		do {
		    cout << "Introduzca un numero entre " 
				 << MIN << " y " << MAX << ": ";
	    	cin >> numero;
	    	
	    	en_rango = ((numero>=MIN) && (numero<=MAX));
		} while ( !en_rango && (numero != TERMINADOR));
		
		while(numero != incognita && numero != TERMINADOR){
		
		    if (numero < incognita){
		    	cout << mensaje_menor << endl; 
			}
			else{
				cout << mensaje_mayor << endl;
			}
			
			do {
			    cout << "Introduzca un numero entre " 
					 << MIN << " y " << MAX << ": ";
		    	cin >> numero;
		    	
		    	en_rango = ((numero>=MIN) && (numero<=MAX));	
			}while ( !en_rango && (numero != TERMINADOR));
		}
		
		if (numero == TERMINADOR) 
		    cout << "Has abandonado el juego";	
		else {
		    cout << "Felicidades, has acertado el numero!" << endl;
		}
		
		do{
			cout << " ¿Quiere seguir jugando? (S/N): ";
			cin >> seguir_jugando;
		}while ((seguir_jugando != 'S') && (seguir_jugando != 'N'));
		
		if (seguir_jugando == 'N'){
			parar_jugar = true;
		}	
		numero_juegos++;
	}
	
	cout << "Has jugado: " << numero_juegos << " veces";
	return 0;
}
