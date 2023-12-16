/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Declarar dos array de datos int con TOPE casillas. Rellenar cada array de
	la siguiente manera: 
	Pedir que se introduzca por teclado una serie indeterminada de números
	enteros (termina cuando se introduce la palabra FIN).
	En primer lugar, el programa mostrará el valor medio de los valores 
	introducidos. Después, indicará si los dos array contienen los mismos 
	valores y en el mismo orden.
	
	Entradas: Numeros del vector 1 y del vector 2
	Salidas: Media de ambos vectores y comparacion
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <string>
using namespace std;

int main() //Programa principal
{
	const int TOPE = 1000;
	int vector1[TOPE];
	int vector2[TOPE];
	string entrada;
	const string FIN = "FIN";
	
	//Entrada de datos
	cout << "Introduzca \"" << FIN << "\" para terminar " << endl;
	int i=0;
	bool terminar1 = false;
	while(!terminar1){
		cout << "Vector1[" << i <<"]: ";
		getline(cin,entrada);
		if (entrada != FIN){
			vector1[i] = stoi(entrada); //Guardamos en el vector el entero
			i++;//Incrementa el contador i
		}
		else{
			terminar1 = true; //Se termina el bucle
			cout << endl;
		}
	}
	
	int j=0;
	bool terminar2 = false;
	while(!terminar2){
		cout << "Vector2[" << j <<"]: ";
		getline(cin,entrada);
		if (entrada != FIN){
			vector2[j] = stoi(entrada); //Guardamos en el vector el entero
			j++; //Incrementa el contador j
		}
		else{
			terminar2 = true; //Se termina el bucle
		}
	}
	
	//Cálculos
	
	//Calculamos la media:

	double media1 = 0;
	if(i>0){ 
		for (int k=0;k<i;k++){
			media1 += vector1[k]; //Sumamos todas las posiciones
		}
		media1 = media1/i; //Dividimos la suma entre la cantidad de elementos
	}

	double media2 = 0;
	if (j>0){
		for (int k=0;k<j;k++){
			media2 += vector2[k]; //Sumamos todas las posiciones
		}
		media2 = media2/j; //Dividimos la suma entre la cantidad de elementos
	}
	cout << "La media del primer vector es: " << media1 << endl; 
	cout << "La media del segundo vector es: " << media2 << endl;
	
	//Comprobamos si son iguales:
	
	bool son_iguales = true;
	if(i==j){ //Primero comprobamos si tienen la misma longitud
		for (int z=0;z<=i;z++){
		//Comprobamos posicion a posicion si son iguales
			if (vector1[z] != vector2[z]){ 
				son_iguales = false;
			}
		}
	}
	else{
		son_iguales = false;
	}

	//Salida
	if (son_iguales){
		cout << "Son iguales" << endl;
	}
	else{
		cout << "No son iguales" << endl;
	}


	return 0;
}

