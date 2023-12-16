/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Encapsule en la clase Lector las funciones escritas en los ejercicios 17 y 
	18 de la Relación de Problemas III. El objetivo es disponer de una clase 
	(Lector) que ofrezca un conjunto de métodos seguros de lectura etiquetada 
	de datos int y double.

	Entradas: Lectura de numero
	Salidas: Se devuelve el numero leido con el filtro
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;



class Lector{	
private:
	string titulo;
public:
	
	//Constructor
	Lector(string cad=" "){
		titulo = cad;
	}
	
	/**************************************************************************
	*Funcion que lee un numero entero
	*Parametros: string que indica el texto a mostrar para leer el numero
	*Devuelve: Numero entero leido
	**************************************************************************/
	int LeeEntero (){
		string entero;
		bool es_entero = true;
		do{
			cout << titulo; //Imprime el mensaje 
			cin >> entero;
			es_entero = true;
			//Comprobamos que el primer digito sea un numero entero o  -/+
			if ( !( isdigit(entero[0]) || entero[0] == 45 || entero[0] == 43) ){
				es_entero = false;
			}
			//Si el numero es: -/+
			else if ((entero[0] == 45 || entero[0] == 43 ) 
			&& entero.length() == 1){ 
				es_entero = false;
			}
			int i = 1;
			while(i<(int)entero.length() && es_entero){
				//Para cada posicion del string comprobamos si es un numero
				if (!isdigit(entero[i])){
					es_entero = false;
				}
				i++;
			}	
		}while(!es_entero);
		return stoi(entero);
	}
	
	/*************************************************************************
	*Funcion que lee un numero real
	*Parametros: string que indica el texto a mostrar para leer el numero
	*Devuelve: Numero real leido
	**************************************************************************/
	double LeeReal (){
		string entero;
		bool es_entero = true;
		do{
			cout << titulo; //Imprime el mensaje 
			cin >> entero;
			es_entero = true;
			//Comprobamos que el primer digito sea un numero entero o -/+
			if ( ( isdigit(entero[0]) || entero[0] == 45 || entero[0] == 43) 
			== false){
				es_entero = false;
			}
			//Si el numero es: -/+
			else if ((entero[0] == 45 || entero[0] == 43 ) && 
			entero.length() == 1){ 
				es_entero = false;
			}
			int k=0;
			int p = entero.length();
			while ((p--) && (es_entero==true)){
				//Para cada posicion del string comprobamos si es un numero
				if (isdigit(entero[p]) == false){
					if(entero[p]=='.' || entero[p]==','){
						entero[p] = '.';
						k++;
					}
					if(k>1){
						es_entero = false;
					}
				}
			}	
		}while(!es_entero);
		return stod(entero);
	}

	/**************************************************************************
	*Funcion que lee un numero entero en un rango determinado
	*Parametros: string que indica el texto a mostrar para leer el numero,
	*numeros inferior y superior del rango
	*Devuelve: Numero entero leido en rango
	**************************************************************************/
	int LeeEnteroEnRango (int menor, int mayor){
		int entero;
		//Mensaje para pasarle a la funcion LeeEntero
		titulo = titulo + "(La hora debe ser mayor que " 
		+ to_string(menor) + " y menor que " + to_string(mayor) + "):";
		do{
			entero = LeeEntero();
			//Repetir mientras este fuera del intervalo
		}while (entero > mayor || entero < menor); 
		return entero;
	}


	/**************************************************************************
	*Funcion que lee un numero entero mayor o igual a otro numero
	*Parametros: string que indica el texto a mostrar para leer el numero,
	*numero de referencia para ser mayor o igual
	*Devuelve: Numero entero leido
	**************************************************************************/
	int LeeEnteroMayorOIgual (int referencia){
		int entero;
		//Mensaje para pasarle a la funcion LeeEntero
		titulo = titulo + "(El numero debe ser mayor o igual que " 
		+ to_string(referencia) + "):";
		do{
			entero = LeeEntero();
			//Repetir mientras sea menor que referencia
		}while (entero < referencia); 
		return entero;
	}
	void SetTitulo(string cad){
		titulo = cad;
	}
};





int main() //Programa principal
{

	// Lectura de un entero
	Lector un_lector("Numero: ");
	double numero = un_lector.LeeReal();
	cout << numero;
	


	return 0;
}

