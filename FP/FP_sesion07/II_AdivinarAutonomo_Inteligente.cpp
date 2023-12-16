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
	Mejoraremos la solución autónoma al problema de la adivinación planteado 
	en el ejercicio 86 introduciendo una sencilla heurística para dirigir la 
	solución. Evitaremos generar números aleatorios independientes para 
	encontrar el valor buscado. Utilizaremos un valor inicial tentativo y a 
	partir de él, mediante comparaciones con el valor buscado iremos reduciendo 
	el ámbito de la búsqueda. Se tratará de una versión autónoma del problema 
	planteado originalmente en el ejercicio 49 en el que el programa nos daba 
	pistas para encontrar el valor buscado.
	Heurística: Se parte del valor medio entre MIN y MAX. Si es el valor 
	buscado, terminamos. Si no, el valor buscado estará en la mitad izquierda 
	(si el valor buscado es menor que el valor medio) o en la mitad derecha 
	(si el valor buscado es mayor que el valor medio). Sabiendo en qué mitad 
	hay que buscar, se vuelve a repetir el proceso en la mitad donde 
	corresponde.


	Entradas: Valor del numero (numero) 
	Salidas: Comprobacion numero y numero de juegos
	
	Como curiosidad, he ejecutado el codigo con un bucle 1000000 de veces y
	el resultado es aproximadamente 75 en este caso. 25 menos que en la
	anterior version del programa.

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
		numero = NUM_VALORES/2;
		
		//Cuando la incognita sea mayor que NUM_VALORES/2
		if (incognita > numero){ 
			while (numero!=incognita){
				numero = (rand() % NUM_VALORES) + (NUM_VALORES/2);
				numero_jugadas++;
				jugadas_totales++;
			}	
		}
		//Cuando la incognita sea menor que NUM_VALORES/2
		else if(incognita < numero){
			while (numero!=incognita){
				numero = (rand() % NUM_VALORES/2) + MIN;
				numero_jugadas++;
				jugadas_totales++;
			}	
		}
		else {
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
