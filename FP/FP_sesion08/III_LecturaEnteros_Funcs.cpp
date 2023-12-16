/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Escribir las siguientes funciones para leer números enteros:
	
	int LeeEntero (string titulo)
	Lee y devuelve un dato int. Si el valor leido no fuera un int (p.e. 94.5,
	dos, 77 88, 0xA2, 55.0) la función volvería a pedirlo hasta que se 
	proporcione un valor correcto. La lectura se etiqueta con titulo.
	Por ejemplo, si x es int, la ejecución de la instrucción
	x = LeeEntero("Introduzca la coordenada x: "); muestra Introduzca la 
	coordenada x: _ y espera a la introducción de un valor int. Si el valor 
	introducido no fuera int vuelve a pedirlo.
	
	int LeeEnteroEnRango (string titulo, int menor, int mayor)
	Lee y devuelve un dato int en un rango dado. Si el valor leido no fuera int
	ó éste fuera menor que menor o mayor que mayor la función volvería a
	pedirlo hasta que se proporcionara un valor correcto. La lectura se etiqueta
	con titulo.
	
	int LeeEnteroMayorOIgual (string titulo, int referencia)
	Lee y devuelve un dato int que debe ser mayor o igual que referencia.
	Si el valor leido no fuera int ó éste fuera menor que referencia la función
	volvería a pedirlo hasta que se proporcionara un valor correcto. La lectura 
	se etiqueta con titulo.
	
	Entradas: Entero con las distintas restricciones
	Salidas: Entero una vez ledio
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int LeeEntero (string titulo){
	string entero;
	const int CERO = '0';
	const int NUEVE = '9';
	bool es_entero = true;
	do{
		cout << titulo; //Imprime el mensaje Introduzca la coordenada x
		cin >> entero;
		es_entero = true;
		//Comprobamos que el primer digito sea un numero entero o el signo -
		if (( (entero[0] < NUEVE) && (entero[0] > CERO) || (entero[0] == 45) ) 
		== false){
			es_entero = false;
		}
		else if (entero[0] == 45 && entero.length() == 1){ //Si el numero es: -
			es_entero = false;
		}
		
		for (int i = 1; i < entero.length(); i++){
			//Para cada posicion del string comprobamos si es un numero
			if ((entero[i]< NUEVE && entero[i]> CERO) == false){
				es_entero = false;
			}
		}	
	}while(!es_entero);
	return stoi(entero);
}
int LeeEnteroEnRango (string titulo1, int menor, int mayor){
	int entero;
	//Mensaje para pasarle a la funcion LeeEntero
	string titulo = titulo1 + "(El numero debe ser mayor que " 
	+ to_string(menor) + " y menor que " + to_string(mayor) + "):";
	do{
		entero = LeeEntero(titulo);
		//Repetir mientras este fuera del intervalo
	}while (entero > mayor || entero < menor); 
	return entero;
}
int LeeEnteroMayorOIgual (string titulo1, int referencia){
	int entero;
	//Mensaje para pasarle a la funcion LeeEntero
	string titulo = titulo1 + "(El numero debe ser mayor o igual que " 
	+ to_string(referencia) + "):";
	do{
		entero = LeeEntero(titulo);
		//Repetir mientras sea menor que referencia
	}while (entero < referencia); 
	return entero;
}

int main() //Programa principal
{
	string titulo = "Introduzca la coordenada x: ";
	int entero;
	int menor = 1; //Valores de ejemplo
	int mayor = 4000;
	int referencia = 10;
	
	//Entrada de datos
	
	entero = LeeEntero(titulo);
	cout << entero << endl;
	entero = LeeEnteroEnRango(titulo, menor, mayor);
	cout << entero << endl;
	entero = LeeEnteroMayorOIgual(titulo, referencia);
	cout << entero << endl;

	return 0;
}

