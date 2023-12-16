/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Definid una clase Dinero para trabajar de forma precisa con datos 
	monetarios. La clase tendrá dos datos miembro: euros y centimos.
	La clase deberá permitir que se introduzca un número de céntimos arbitrario 
	(siempre que sea positivo o cero) y se encargará de ajustar las cantidades 
	debidamente. Por ejemplo, si asignamos 20 euros y 115 céntimos, el objeto 
	deberá almacenar el valor 21 en euros y 15 en centimos. No olvide añadir un 
	método ToString() para reperesentar de forma textual el contenido de un 
	objeto Dinero.
	Hacer un programa que calcule el precio final de un producto a partir de su 
	precio inicial, de un incremento fijo mensual y de un número de meses. 
	El programa irá mostrando, mes a mes, el precio del producto.
	
	Entradas: precio inicial, incremento y numero de meses
	Salidas: precio por mes
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

/*****************************************************************************
*							  FUNCIONES										 *
*****************************************************************************/
/*****************************************************************************
*Funcion que lee un numero entero
*Parametros: string que indica el texto a mostrar para leer el numero
*Devuelve: Numero entero leido
*****************************************************************************/
int LeeEntero (string titulo){
	string entero;
	bool es_entero = true;
	do{
		cout << titulo; //Imprime el mensaje Introduzca la coordenada x
		cin >> entero;
		es_entero = true;
		//Comprobamos que el primer digito sea un numero entero o el signo -/+
		if ( ( isdigit(entero[0]) || entero[0] == 45 || entero[0] == 43) 
		== false){
			es_entero = false;
		}
		//Si el numero es: -/+
		else if ((entero[0] == 45 || entero[0] == 43 ) && entero.length() == 1){ 
			es_entero = false;
		}
		
		for (int i = 1; i < (int)entero.length(); i++){
			//Para cada posicion del string comprobamos si es un numero
			if (isdigit(entero[i]) == false){
				es_entero = false;
			}
		}	
	}while(!es_entero);
	return stoi(entero);
}




class Dinero{
private:
	int euros;
	int centimos;
public:
	//Constructor
	Dinero(int cent)
	{
		IngresoDinero(cent);
	}
	//Funcion que ingresa dinero
	//Precondiciones: eur y cent >=0
	void IngresoDinero(int cent){
		centimos += cent;
		while ((centimos-100)>=0){
			euros++; //Incrementa euros
			centimos = centimos-100;
		}
	}
	//Devuelve un string que contiene el precio del producto
	string ToString(){
		string cad;
		cad = "Precio: " + to_string(euros) + "eur " + to_string(centimos)
			+ "cents"; 
		return (cad);	
	}
	//Metodos de acceso para la lectura
	int GetEuros(){
		return (euros);
	}
	
	int GetCentimos(){
		return (centimos);
	}
};




int main() //Programa principal
{
	int precio_inicial; //Precio inciial del producto
	int incremento; //Incremento
	int num_meses; //Numero de meses
	string cad; //Cadena que contiene el precio

	//Entrada de datos

	//Filtramos y leemos los datos
	do{
		precio_inicial = LeeEntero("Introduzca el precio inicial: ");
	}while (precio_inicial<0);

	do{
		incremento = LeeEntero("Introduzca el incremento: ");
	}while (incremento<0);

	do{
		num_meses = LeeEntero("Introduzca el numero de meses: ");
	}while (num_meses<0);
	
	//Cálculos
	Dinero precio(precio_inicial);
	
	for (int i=0;i<=num_meses;i++){
		cout << "Mes " << i+1 << ": \n";
		precio.IngresoDinero(incremento);
		cad = precio.ToString();
		cout << cad << endl;
	}

	return 0;
}

