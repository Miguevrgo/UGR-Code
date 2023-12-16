/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACI�N
//
// (C) FRANCISCO JOS� CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACI�N E INTELIGENCIA ARTIFICIAL
//
// RELACI�N DE PROBLEMAS 2
/*	
   Programa que lee un entero y muestra los d�gitos que lo componen 
   individualmente, separ�ndolos por la barra vertical '|' 
   
   En esta versi�n se diferencian las tres etapas: E / C /S
   
   Entradas: un entero
   Salidas:  Los d�gitos del entero leido.
*/
/*********************************************************************/


#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

int main()
{	
	// Entrada
	
	const string mensaje = "Introduce un entero positivo: ";
		
	int numero;

	do {
		cout << mensaje; 
		cin >> numero; 
	} while (numero<=0);
	
	// En este punto aseguro que numero>0
	
	// C�lculos 
	
	int n = numero;  // Copia. Para no perder el valor original
	
	/*	Etapa 1.- Contar cu�ntos d�gitos componen el n�mero
	
		Bastar� con realizar divisones sucesivas de "n" por 10 hasta que 
		no sea posible continuar (cociente nulo). Cada vez que sea posible
		realizar la divisi�n tendremos un d�gito m�s.  
	*/
	
	int num_digitos = 0; // Contador del n�mero de d�gitos

	while (n != 0) {

		n /= 10;		// Actualiza el n�mero 
		num_digitos++;  // Aumenta el contador
	}

	cout << endl;
	cout << "El numero tiene " << num_digitos << " digitos." << endl;
	cout << endl;
		
	
	/*  Etapa 2.- Calcular los d�gitos que conforman el n�mero 
		
		Cada uno de los digitos de "n" se calcula dvividiendo por la potencia 
		de 10 m�s cercana (por defecto) a "n" y tomando el cociente de la 
		divisi�n como el d�gito. Para el siguiente d�gito, "n" ser� el resto 
		y vuelta a empezar. Se termina cuando la potencia de 10 sea 1 (queda 
		un  n�mero de un d�gito). En este caso, "n" es el �ltimo d�gito. 
		
		P.e. 2435 (num_digitos es 3)
			La potencia de 10 m�s cercana es 1000 (10^(num_digitos-1))
			paso 1)	2435/1000 = 2 --> primer d�gito = 2
					2435%1000 = 435 --> continuar con 435
					potencia = 100
			paso 2)	435/100 = 4  --> segundo d�gito = 4
					435%100 = 35 --> continuar con 35
					potencia = 10
			paso 3)	35/10 = 3  --> tercer d�gito = 3
					35%10 = 5 --> continuar con 5
					potencia = 1
			Fin:  	Como potencia == 1 --> cuarto d�gito = 5
	*/
	
	string resultado;  // inicialmente vac�a

	int potencia = (int) pow (10, num_digitos-1); // 10^(num_digitos-1)
		
	n = numero;	
	
	while (potencia > 1) {  // potencia es 1 cuando num_digitos es 1 
							// (10^(1-1) == 10^0 == 1

		int digito = n / potencia;
		n = n % potencia;	
			
		resultado = resultado + "|" + to_string(digito);
		
		potencia /= 10;
	}
	
	resultado = resultado + "|" + to_string(n) + "|";

	
	// 	Resultados		
	
	cout << endl;	
	cout << resultado << endl;
	cout << endl;	
	
	return 0;
}
