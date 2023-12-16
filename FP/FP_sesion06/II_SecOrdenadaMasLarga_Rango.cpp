/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIï¿½N

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Construya un programa que calcule cuando se produjo la mayor secuencia de 
	días consecutivos con temperaturas crecientes. El programa leerá una 
	secuencia de reales representando temperaturas, hasta llegar al -1 y debe 
	calcular la subsecuencia de números ordenada, de menor a mayor, de mayor 
	longitud. El programa nos debe decir la posición donde comienza la 
	subsecuencia y su longitud.
	
	Modifique el ejercicio para que la lectura de datos finalice cuando se 
	introduce un valor fuera de un rango establecido entre los valores 
	MIN_TEMP_VALIDA y MAX_TEMP_VALIDA.
	
	Entradas: Valor de temperatura(temperatura)
	Salidas: Posicion de la subsecuencia y longitud
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	const int MIN_TEMP_VALIDA = 0;
	const int MAX_TEMP_VALIDA = 40;
	const int MIN_LONG_VALIDA = 2;
	const double TERMINADOR = -1;
	double temperatura;
	double prev_temperatura; //Temperatura anterior
	int contador = 0;
	int contador_max = 0; //Secuencia ordenada de mayor longitud
	int posicion = 0; //Posicion dentro de la cadena
	int posicion_ini = 0; //Posicion inicial de la subcadena 
	int posicion_ini_max =0;//Posicion inicial de la subcadena de mayor longitud
	

	//Entrada de datos
	
	cout << "Introduzca las temperaturas(" << TERMINADOR << " para terminar): ";
    cin >> temperatura;
	
	//Cálculos
	
	bool temperatura_valida = (temperatura != TERMINADOR)
		 && (temperatura > MIN_TEMP_VALIDA) && (temperatura < MAX_TEMP_VALIDA);;
	
	while (temperatura_valida){	
		posicion++; //Incremento de la posicion
		if (temperatura > prev_temperatura){
			contador++; //Incremento de longitud
			if (contador == 2){
				posicion_ini = posicion-1;
			}
			if ((contador > contador_max) && (contador >= MIN_LONG_VALIDA)){
				contador_max = contador; //Subcadena mas larga
				posicion_ini_max = posicion_ini; 
			}
		}
		else{
			contador = 1; //Reseteo de contador 
		}
		prev_temperatura = temperatura; 
		cout << "Temperaturas(" << TERMINADOR << " para terminar): ";
		cin >> temperatura;
		
		temperatura_valida = (temperatura != TERMINADOR)
		 && (temperatura > MIN_TEMP_VALIDA) && (temperatura < MAX_TEMP_VALIDA);
	}


	//Salida
	
	cout << "La subcadena mas larga empieza en la posicion: " 
		 << posicion_ini_max << " Y su longitud es de: " << contador_max;

	return 0;
}


