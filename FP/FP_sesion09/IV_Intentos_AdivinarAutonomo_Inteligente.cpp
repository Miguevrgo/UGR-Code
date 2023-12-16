/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N
	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Queremos saber cu�ntos intentos se realizan para localizar cada uno de los 
	valores comprendidos entre MIN y MAX. Para cada valor i (MIN <= i <= MAX) 
	calcule y guarde el n�mero de intentos. A continuaci�n muestre una tabla 
	que indique los valores de i y el n�mero de intentos realizados para 
	localizarlo.
	Deber� separar los procesos de c�lculo y presentaci�n de resultados.
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
	int numero_juegos = 50; //Numero de juegos
	int numero_jugadas = 0; //Numero de jugadas por partida
	int jugadas_totales = 0; //Numero jugadas totales
	double media_jugadas; //Media jugadas por partida
	int numero;
	time_t t;
	srand(time(&t)); // Inicializa generador de n�ms. aleatorios
					 // con el reloj del sistema (hora actual)
	int incognita;// N�mero aleatorio que se genera
	int intervalo_max = MAX;
	int intervalo_min = MIN;
	int intentos[50];
	int valor_i[50];
	//C�lculos
	
	for(int i=0;i<numero_juegos;i++){
		incognita = (rand() % NUM_VALORES) + MIN; //Se genera la incognita
		intervalo_max = MAX;
		intervalo_min = MIN;
		numero = intervalo_max+intervalo_min/2;
		valor_i[i] = incognita;
		//Cuando la incognita sea mayor que NUM_VALORES/2
		while (numero!=incognita){
			numero = intervalo_max+intervalo_min/2;
			if (incognita > numero){
				intervalo_min = numero; 
				numero = (rand() % (intervalo_max-intervalo_min));		
				numero_jugadas++;
				jugadas_totales++;	
			}
			//Cuando la incognita sea menor que NUM_VALORES/2
			else if(incognita < numero){
				intervalo_max = numero;
				numero = (rand() % (intervalo_max-intervalo_min));
				numero_jugadas++;
				jugadas_totales++;			
			}
		}
		intentos[i]=numero_jugadas;
		numero_jugadas = 0;
	}
	
	media_jugadas = (double)jugadas_totales / numero_juegos;
	
	//Salida
	
	cout << "Numero de juegos: " << numero_juegos << endl;
	cout << "Media de jugadas: " << media_jugadas << endl;
	for(int i=0;i<numero_juegos;i++){
		cout << "[i]: " << valor_i[i] << " Intentos: " << intentos[i] << "\t";
	}
	return 0;
}
