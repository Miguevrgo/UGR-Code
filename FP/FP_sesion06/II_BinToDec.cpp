/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Escribir un programa que muestre el valor decimal de un valor dado en el 
	sistema de numeración binario.
	El programa pedirá el valor binario, que se leerá sobre un dato string, 
	se calculará su valor decimal que se guardará a un entero y se mostrará 
	el resultado. Comprobar y controlar adecuadamente toda las situaciones 
	de error.
	
	Entradas: Valor en binario(binario)
	Salidas: Valor en base decimal(entero)
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <string>
#include <cmath>

using namespace std;

int main() //Programa principal
{
	string binario;
	int entero = 0;
	int longitud;
	bool cadena_valida;
	//Entrada de datos
	
	do{
		cout << "Introduzca el numero en binario: ";
    	getline(cin,binario);
    	longitud = binario.length();
    	
    	//Se comprueba que la cadena es valida:
    	
    	for (int j=1;j < longitud;j++){
			if ((binario[j]=='1') || (binario[j]=='0')){
				cadena_valida = true;
			}
			else{
				cadena_valida = false;
			}
		} 
    }while(cadena_valida == false);
	
    
    
	
	//Cálculos
	
	for (int i=0;i <= longitud-1;i++){
		if (binario[i] == '1'){	//Si el numero en la posicion vale 1:
			
			//Sumamos a entero 2 elevado a la posicion en la que esta el 1,
			//Teniendo en cuenta que la izquierda representa los valores mas
			//Altos, y restamos 1 para tener en cuenta que la cadena empieza 
			//Con posicion 0
			
			entero += pow(2,longitud-i-1); 
		}
	}

	//Salida
	
	cout << "Numero entero: " << entero;

	return 0;
}

