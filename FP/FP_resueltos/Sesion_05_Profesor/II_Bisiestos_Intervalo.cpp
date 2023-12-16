/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// RELACIÓN DE PROBLEMAS 2
/*	
	El programa pide los valores de dos años del siglo XXI y muestra todos 
	los años bisiestos comprendidos entre los dos valores dados.

	Entradas: 	Dos años (anio_nicial y anio_final) entre los que se van a
				calcular los años que son bisiestos.
				Ambos años deben ser del siglo XXI.
	Salida:     Mensajes indicando si el año examinado es, o no, bisiesto.
*/
/***************************************************************************/


#include <iostream>
#include <iomanip>
using namespace std;

int main()
{	
	cout.setf(ios::fixed);		// Notación de punto fijo para los reales
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

	// En este punto aseguro que los años están en el rango correcto

	
	// Cálculos - resultado
	
	if (anio_inicial > anio_final) { // Intercambiar los años
		int aux = anio_inicial;
		anio_inicial = anio_final;
		anio_final = aux;
	}
	
	cout << endl;
	cout << "Calculando anios bisiestos entre " << setw(4)
		 << anio_inicial << " y " << setw(4)  << anio_final << endl;
	cout << endl;

	// Variables comunes a las soluciones ofertadas
	
	int anio; // año que se evalúa
	bool es_bisiesto;   // true si "anio" es bisiesto
	
	
	// Solución 1: fuerza bruta
	/*
		Llamada así porque el test "ser bisiesto" se aplica a todos los
		años comprendidos entre los extremos, aunque sabemos que hay
		muchos (un 75%) que nunca serán años bisiestos.
		La solución se escribe rápidamente, pero no es eficiente.
	*/
	
	int cont_1 = 0; // Contador años bisiestos "fuerza bruta"
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


	// Solución 2: Eficiente
	/*
		Una vez localizado el primer año bisiesto desde "anio_inicial"
		tan solo habrá que realizar el test de cuatro en cuatro años.
		La primera parte busca el primer año bisiesto (ciclo while) y la
		segunda evalúa el test "ser bisiesto" cada cuatro años (ciclo for).
	*/

	int cont_2 = 0; // Contador años bisiestos "eficiente"
	int num_tests_2  = 0; // Contador de test "eficiente"


	anio = anio_inicial;
	es_bisiesto = false; // Obligamos a entrar al ciclo while

	// Buscar el primer año bisiesto entre "anio_inicial" y "anio_final"
	while ((anio <= anio_final) && (!es_bisiesto)) {

		es_bisiesto = (((anio%4==0) && (anio%100!=0)) || (anio%400==0));
		num_tests_2++; 

		if (!es_bisiesto)
			anio++;
	}
	
	if (es_bisiesto) { // Se encontró el primer bisiesto

		cout << setw(4) << anio << " es bisiesto (2)." << endl;
		cont_2++;
		
		// El próximo candidato no es el siguiente, sino cuatro más
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
	
	// Si no se encontró un año bisiesto entre "anio_inicial" y "anio_final"
	// el ciclo while acabó porque "anio" > "anio_final", y en ese caso
	// no hay nada que hacer --> no hay años bisiestos en el intervalo dado.
	
	// Estadísticas para medir la bondad de ambas soluciones. La comparrativa
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
