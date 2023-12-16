/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN
	
	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Ahora deberá realizar un programa que lea un número indeterminado de enteros
	positivos (finalizar cuando se introduce un cero) y exprese cada uno de 
	ellos en base al producto de sus factores primos. Exprese el resultado como 
	el producto de potencias
	(apartado b del ejercicio antes mencionado). Por ejemplo:

	Entradas: Valor del numero entero
	Salidas: Descomposicion en factores primos con dos notaciones
	
	
	
****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	const int MAX_DATOS = 40; //Tamaño del array numero
	const int TAM = 500; //Tamaño arrays es_primo y numero_primo
    int numero[MAX_DATOS]; //Array numeros a descomponer
    int numero_primo[TAM]; //Array numeros primos
    bool es_primo[TAM];
	int potencia;
	
	//Entrada de datos
	
	bool terminar = false;
	int i=0;
	while (!terminar){
		cout << "Introduzca el numero[" << i <<"]: ";
		cin >> numero[i];
		if(numero[i]>=0){
			i++;
		}
		else{
			terminar = true; //Termina el bucle si el numero es menor que 0
		}
	}
	//Numeros primos
	
	for (int j=0;j<TAM;j++){
		es_primo[j]=true; //"Pintamos" todos los numeros
	}
	int k=0;
	for (int j=2;j<=TAM;j++){
		if (es_primo[j]){
			numero_primo[k] = j;
			k++; //Incrementa el contador
			for (int p=2;p*j <= TAM;p++){
				es_primo[j*p] = false; //"Borramos" los numeros no primos
			}
		}
	}
	//Cálculos
    for (int n=0;n<i;n++){
    	cout << "Factorizacion de " << numero[n] << ": ";
    	if (numero[n]==1){
		cout << 1;
		}
		else{
			bool terminar_bucle = false;
			int j=0;
	    	while(!terminar_bucle){
	    		potencia = 0;
	        	while (numero[n]%numero_primo[j] == 0){ //Si es un factor
	            	potencia++; //Incrementa la potencia
	            	numero[n] = numero[n]/numero_primo[j]; //Divide por factor
	        	}
	        	if (numero[n] != 1){ //Se puede dividir por mas factores
		        	if (potencia > 1){
		        		cout << numero_primo[j] << "^" << potencia << " * ";	
					}
					else if (potencia == 1){
						cout << numero_primo[j] << " * ";
					}
	        	}
	        	else {
	        		if (potencia > 1){
		        		cout << numero_primo[j] << "^" << potencia;	
					}
					else if (potencia == 1){
						cout << numero_primo[j];
					}
		        	terminar_bucle = true; //Terminamos el bucle	
				}
				j++; //Incrementa j
	    	}
    	}
    	cout << endl;
	}
	
	return 0;
}

