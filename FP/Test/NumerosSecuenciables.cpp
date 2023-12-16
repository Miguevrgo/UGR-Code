/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// EXAMEN PRÁCTICO 1
//
// Números secuenciables
//
// 	Diremos que un número entero positivo es secuenciable si se puede generar 
// 	como suma de números consecutivos. Por ejemplo, 6 = 1 + 2 + 3, 15 = 7 + 8. 
//	Esta descomposición no tiene por qué ser única. 
//		Por ejemplo, 15 = 7 + 8 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5.
// 
// Curiosidad: los únicos números sin descomposiciones son las potencias de 2.
//
/* 	Este programa lee dos valores enteros positivos (n1 y n2) y considerará 
	los valores entre ellos (los dos extremos incluidos). También leerá un 
	numero de secuencias/descomposiciones (n_sec). 
	Después calcula y muestra:
		(1) Cuántos números secuenciables hay entre n1 y n2. 
		(2) Los números secuenciables entre n1 y n2 (sus valores) 
			y cuántas descomposiciones tienen.
		(3) Los numeros secuenciables entre n1 y n2 cuyo número de 
			descomposiciones coincide con n_sec, y finalmente cuántas 
			descomposiciones de n_sec sumandos hay entre n1 y n2.	
*/
/***************************************************************************/

#include<iostream>
#include<iomanip>
using namespace std;

/***************************************************************************/
// Calcula si un número es secuenciable o no. 
//
// Parámetros: n, número entero del que queremos conocer su "secuenciabilidad"
// Devuelve: true, si "n" es secuenciable.
//
// PRE: n >= 0

bool EsSecuenciable (int n) 
{
	bool es_secuenciable = false; 
	
	int inicio = 1; 			
	int ultimo_inicio = n/2;   
	
	// Exploramos hasta encontrar una secuencia
	
	while (inicio <= ultimo_inicio && !es_secuenciable) {
		
		int suma = inicio;		// suma inicial (primer valor de la secuencia)
		int valor = inicio+1; 	// segundo valor de la secuencia 

		// Mientras que la suma de la secuencia sea menor que n, seguir
		// añadiendo términos a la secuencia, consecutivos al anterior. 
		 
		while (suma < n) {
			
			suma += valor; // Nueva suma 
			valor++; // El nuevo término a considerar es el siguiente 
		}
		
		// Si "suma" es igual a "n" hemos encontrado una secuencia. 
		// Si no, la suma es necesariamente mayor.  
		
		if (suma == n) es_secuenciable = true; 
		else inicio++;
	}
	
	return es_secuenciable;
}

/***************************************************************************/
// Calcula el número de secuencias de un número secuenciable. 
//
// Parámetros: n, número secuenciable. 
// Devuelve: el número de secuencias de "n"
//
// PRE: n >= 0
// PRE: EsSecuenciable(n) == true

int NumSecuencias (int n) 
{
	int inicio = 1; 			
	int ultimo_inicio = n/2;   
	
	int cont_secuencias = 0; 
	
	// Exploramos hasta encontrar una secuencia
	
	while (inicio <= ultimo_inicio) {
		
		int suma = inicio;		// suma inicial (primer valor de la secuencia)
		int valor = inicio+1; 	// segundo valor de la secuencia 

		//cout << setw(3) << inicio; 
		
		// Mientras que la suma de la secuencia sea menor que n, seguir
		// añadiendo términos a la secuencia, consecutivos al anterior. 
		 
		while (suma < n) {
			suma += valor; // Nueva suma 
			valor++; // El nuevo término a considerar es el siguiente 
		}
		
		// Si "suma" es igual a "n" hemos encontrado una secuencia. 
		// Si no, la suma es necesariamente mayor.  
		if (suma == n) cont_secuencias++;

		// Probemos si existe otra.		
		inicio++;
	}
	
	return cont_secuencias;
}

/***************************************************************************/
	
int main (void)
{
	int n1, n2; 
    int extremo_menor, extremo_mayor;	
	int num_secuencias; 
	
	// Entrada (leer los extremos)
	
	do {
	    cout << "Introduzca un numero positivo: ";
    	cin >> n1;    	
	} while (n1<=0);

	do {
	    cout << "Introduzca otro numero positivo: ";
    	cin >> n2;    	
	} while (n2<=0);

	// Entrada (Número de secuencias)

	cout << endl; 
	do {
	    cout << "Introduzca numero de secuencias: ";
    	cin >> num_secuencias;    	
	} while (num_secuencias<=0);


	// Reajustar los extremos menor y mayor
	if (n1<n2) {
		extremo_menor = n1;
		extremo_mayor = n2;	
	}
	else {
		extremo_menor = n2;
		extremo_mayor = n1;			
	}

	cout << endl; 
	cout << "Calculando numeros secuenciables entre " << setw(3) 
	     << extremo_menor << " y " << setw(3) << extremo_mayor << endl; 
	cout << endl; 
	
	cout << "................................................" << endl; 
	cout << endl; 

	
	// Cálculos y resultado 
	
	// 1. Calcular total de números secuenciables 

	cout << endl; 
	cout << "1. Total de numeros secuenciables." << endl; 	
	cout << endl; 
		 	
	int contador_secuenciables = 0; 
	for (int n=extremo_menor; n<=extremo_mayor; n++) 
		if (EsSecuenciable(n)) contador_secuenciables++;	
	
	cout << "\tSe han encontrado " << setw(3) << contador_secuenciables 
	     << " numeros secuenciables." << endl; 
	cout << endl; 

	// 2. Mostrar numeros secuenciables y el número de secuencias
	
	cout << endl; 
	cout << "2. Los numeros secuenciables y el numero de secuencias." << endl; 	
	cout << endl; 

	for (int n=extremo_menor; n<=extremo_mayor; n++) {
		if (EsSecuenciable(n)) {
		   	cout << "\t" << setw(3) << n << " es secuenciable. ";	
	    	cout << "(" << NumSecuencias(n) << " secuencias)" << endl;
		}
	  	else 
		   	cout << "\t" << setw(3) << n << " NO es secuenciable." << endl;	
	}
	cout << endl; 
	
	// 3. Mostrar numeros secuenciables cuyo número de secuencias 
	// 	  coincida con el valor pedido y el total.  
	
	cout << endl; 
	cout << "3. Numeros secuenciables con " << 
	     setw(2) << num_secuencias << " secuencias:" << endl; 		
	cout << endl; 
	
	int cont_num_secuencias = 0; 
	
	for (int n=extremo_menor; n<=extremo_mayor; n++) 
		
		if (EsSecuenciable(n)) 
		
			if (NumSecuencias(n) == num_secuencias) {
				
			   	cout << "\t" << setw(3) << n << " --> " 
				     << NumSecuencias(n) << " secuencias" << endl;
		    	
		    	cont_num_secuencias++;
		}
	cout << endl; 		
	
	cout << endl; 		
	if (cont_num_secuencias > 0) 
		cout << "\tHay " << setw(3) << cont_num_secuencias << " numeros con "
		     << num_secuencias << " secuencias" << endl; 		
	else 
		cout << "\tNo hay ningun numero con " << setw(3) << num_secuencias 
		     << " secuencias en el rango indicado." << endl; 			
	cout << endl; 		
	
	return 0;
}

/***************************************************************************/
/***************************************************************************/
