/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Dise�ar un programa para jugar a adivinar un n�mero. El programa generar� 
	un n�mero aleatorio (entre MIN y MAX) y el usuario tendr� que adivinarlo. 
	En cada jugada el jugador introducir� un valor y el el juego indicar� si 
	el n�mero introducido por el jugador est� por encima o por debajo del 
	n�mero a adivinar.
	Como reglas de parada considerad que el usuario: 1) haya acertado, � 2) 
	no quiera seguir jugando, y en este caso usad un valor especial (TERMINADOR)
	para abandonar
	Al terminar (no se quiere jugar m�s) el programa mostrar� cu�ntos juegos 
	se han realizado (en caso de abandono tambi�n se contabiliza ese juego).

	Entradas: Valor del numero (numero) 
	Salidas: Comprobacion numero y numero de juegos
	
	

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
	srand(time(&t)); // Inicializa generador de n�ms. aleatorios
					 // con el reloj del sistema (hora actual)
	int incognita;// N�mero aleatorio que se genera
	
	//C�lculos
	
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
			cout << " �Quiere seguir jugando? (S/N): ";
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
