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
	
	Como curiosidad, he ejecutado el codigo con un bucle 1000000 de veces y
	el resultado es aproximadamente 100.

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
	int numero_jugadas = 0; //Numero de jugadasd por partida
	int jugadas_totales = 0; //Numero jugadas totales
	double media_jugadas; //Media jugadas por partida
	int numero;
	time_t t;
	srand(time(&t)); // Inicializa generador de núms. aleatorios
					 // con el reloj del sistema (hora actual)
	int incognita;// Número aleatorio que se genera
	
	//Cálculos
	
	bool parar_jugar;
	while (parar_jugar == false){
		incognita = (rand() % NUM_VALORES) + MIN; //Se genera la incognita
		while(numero != incognita && numero != TERMINADOR){
			numero = (rand() % NUM_VALORES) + MIN; //Se generan numeros
			numero_jugadas++;
			jugadas_totales++;
		}
		
		cout << "El numero se acerto en " << numero_jugadas 
			 << " jugadas" << endl;
		do{
			cout << " ¿Quiere seguir jugando? (S/N): ";
			cin >> seguir_jugando;
		}while ((seguir_jugando != 'S') && (seguir_jugando != 'N'));
		
		if (seguir_jugando == 'N'){
			parar_jugar = true;
		}
		else{
			numero_jugadas = 0; //Reseteo numero de jugadas
		}	
		numero_juegos++;
	}
	
	media_jugadas = (double)jugadas_totales / numero_juegos;
	
	//Salida
	
	cout << "Numero de juegos: " << numero_juegos << endl;
	cout << "Media de jugadas: " << media_jugadas;
	
	return 0;
}
