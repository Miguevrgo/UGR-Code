/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACI�N
//
// (C) FRANCISCO JOS� CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACI�N E INTELIGENCIA ARTIFICIAL
//
// RELACI�N DE PROBLEMAS 2
/*	
	El programa pide los valores de dos a�os del siglo XXI y muestra todos 
	los a�os bisiestos comprendidos entre los dos valores dados.

	Entradas: 	Dos a�os (anio_nicial y anio_final) entre los que se van a
				calcular los a�os que son bisiestos.
				Ambos a�os deben ser del siglo XXI.
	Salida:     Mensajes indicando si el a�o examinado es, o no, bisiesto.
*/
/***************************************************************************/


#include <iostream>
#include <iomanip>
using namespace std;

int main()
{	
	cout.setf(ios::fixed);		// Notaci�n de punto fijo para los reales
	cout.setf(ios::showpoint);	// Mostrar siempre decimales

	const int PRIMER_ANIO_VALIDO = 2001;
	const int ULTIMO_ANIO_VALIDO = 2100;
	
   	int	 anio_inicial, anio_final;
	bool es_anio_valido; 

	// Entrada
	
	do {
		cout << "Introduzca un anio entre " << PRIMER_ANIO_VALIDO 
		     << " y " << ULTIMO_ANIO_VALIDO << ": ";
		cin >> anio_inicial;
		
		es_anio_valido = ((PRIMER_ANIO_VALIDO <= anio_inicial) && 
		                  (anio_inicial <= ULTIMO_ANIO_VALIDO));
		                  
	} while (!es_anio_valido);
	
	cout << endl;
	 
	do {
		cout << "Introduzca otro anio entre " << PRIMER_ANIO_VALIDO 
		     << " y " << ULTIMO_ANIO_VALIDO << ": ";
		cin >> anio_final;

		es_anio_valido = ((PRIMER_ANIO_VALIDO <= anio_final) && 
		                  (anio_final <= ULTIMO_ANIO_VALIDO));
		                  
	} while (!es_anio_valido);

	cout << endl;

	// En este punto aseguro que los a�os est�n en el rango correcto

	
	// C�lculos - resultado
	
	if (anio_inicial > anio_final) { // Intercambiar los a�os
		int aux = anio_inicial;
		anio_inicial = anio_final;
		anio_final = aux;
	}
	
	cout << endl;
	cout << "Calculando anios bisiestos entre " << setw(4)
		 << anio_inicial << " y " << setw(4)  << anio_final << endl;
	cout << endl;

	// Variables comunes a las soluciones ofertadas
	
	int anio; // a�o que se eval�a
	bool es_bisiesto;   // true si "anio" es bisiesto
	
	
	// Soluci�n 1: fuerza bruta
	/*
		Llamada as� porque el test "ser bisiesto" se aplica a todos los
		a�os comprendidos entre los extremos, aunque sabemos que hay
		muchos (un 75%) que nunca ser�n a�os bisiestos.
		La soluci�n se escribe r�pidamente, pero no es eficiente.
	*/
	
	int cont_1 = 0; // Contador a�os bisiestos "fuerza bruta"
	int num_tests_1  = 0; // Contador de test "fuerza bruta"
	
	anio = anio_inicial; 
	
	while (anio <= anio_final) {

		es_bisiesto = (((anio%4==0) && (anio%100!=0)) || (anio%400==0));
		num_tests_1++;
		
		if (es_bisiesto) {
			cout << setw(4) << anio << " es bisiesto." << endl;
			cont_1++;
		}
		
		anio++;

	} // while
	
	cout << endl << endl;


	// Soluci�n 2: Eficiente
	/*
		Una vez localizado el primer a�o bisiesto desde "anio_inicial"
		tan solo habr� que realizar el test de cuatro en cuatro a�os.
		La primera parte busca el primer a�o bisiesto (ciclo while) y la
		segunda eval�a el test "ser bisiesto" cada cuatro a�os (ciclo for).
	*/

	int cont_2 = 0; // Contador a�os bisiestos "eficiente"
	int num_tests_2  = 0; // Contador de test "eficiente"


	anio = anio_inicial;
	es_bisiesto = false; // Obligamos a entrar al ciclo while

	// Buscar el primer a�o bisiesto entre "anio_inicial" y "anio_final"
	while ((anio <= anio_final) && (!es_bisiesto)) {

		es_bisiesto = (((anio%4==0) && (anio%100!=0)) || (anio%400==0));
		num_tests_2++; 

		if (!es_bisiesto)
			anio++;
	}
	
	if (es_bisiesto) { // Se encontr� el primer bisiesto

		cout << setw(4) << anio << " es bisiesto (2)." << endl;
		cont_2++;
		
		// El pr�ximo candidato no es el siguiente, sino cuatro m�s
		anio += 4;
	
		while (anio <= anio_final) {
			
			bool es_bisiesto = (((anio%4==0)&&(anio%100!=0))||(anio%400==0));
   			num_tests_2++;
   			
			if (es_bisiesto) {
				cout << setw(4) << anio << " es bisiesto (2)." << endl;
				cont_2++;
			}
			
			anio=anio+4; // anio +=4;

		} // while
		
		cout << endl << endl;
	}
	
	// Si no se encontr� un a�o bisiesto entre "anio_inicial" y "anio_final"
	// el ciclo while acab� porque "anio" > "anio_final", y en ese caso
	// no hay nada que hacer --> no hay a�os bisiestos en el intervalo dado.
	
	// Estad�sticas para medir la bondad de ambas soluciones. La comparrativa
	// se establece en el numero de test "ser bisiesto" efectuados
	
	cout << endl;
	cout << "ESTADISTICAS" << endl;
	cout << endl;
	cout << "Num. bisiestos version 1: " << setw(3) << cont_1 << endl;
	cout << "Num. bisiestos version 2: " << setw(3) << cont_2 << endl;
	cout << endl;
	cout << "Num. test. version 1: " << setw(5) << num_tests_1 << "   "
		 << setw(6) << setprecision(2)
		 << ((double)num_tests_1/(anio_final-anio_inicial+1))*100.0
		 << " % " << endl;
	cout << "Num. test. version 2: " << setw(5) << num_tests_2 << "   "
		 << setw(6) << setprecision(2)
		 << ((double)num_tests_2/(anio_final-anio_inicial+1))*100.0
		 << " % " << endl;
	cout << endl;
	
	return 0;
}
