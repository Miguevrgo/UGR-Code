/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Una secuencia est� determinada �nicamente por una pareja de valores enteros
	(p, q) siendo p < q de manera que si n es un n�mero secuenciable, entonces 
	n = p + (p + 1) + . . . + q
	Para probar esta adici�n, ampl�e la funcionalidad del apartado c de manera 
	que ahora deber� realizar estas tareas:
	Mostrar los n�meros secuenciables (sus valores) cuyo n�mero de 
	descomposiciones coincide con el n�mero de referencia leido.Para cada uno de
	ellos deber� mostrar todas sus descomposiciones.
	Finalmente, mostrar el total de n�meros secuenciables que cumplen esta
	�ltima condici�n.
	Por ejemplo, para n�meros entre 1 y 20 con dos secuencias, el resultado 
	ser�a:
		
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include<iostream>
#include<iomanip>
using namespace std;


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class GestorNumerosSecuenciables 
{
private:
	
	int valor; 	// PRE: 1 <= valor
	
	static const int MAX_SECUENCIAS = 100;
	static const int MAX_ELEMENTOS = 20; //Maximo de elementos de una secuencia
	static const int MAX_VALORES = 200; //Maximo de valores en el intervalo 
	//Guarda las secuencias asociadas a un numero secuenciable
	int secuencias[MAX_SECUENCIAS][MAX_SECUENCIAS][MAX_ELEMENTOS];
	
public:

	/***********************************************************************/
	/***********************************************************************/
	// Constructores
	
	GestorNumerosSecuenciables (void)  : valor (1) { }
		
	GestorNumerosSecuenciables (int n) : valor (n) { }
	
	/***********************************************************************/
	/***********************************************************************/
	// Get/Set triviales
	
	void SetValor (int n) {
		valor = n; 	
	}
	
	int GetValor (void) {
		return (valor); 	
	}
	
	/***********************************************************************/
	/***********************************************************************/
	// Calcula y devuelve si un n�mero es secuenciable o no. 
	
	bool EsSecuenciable (void) 
	{		
		return (NumSecuencias() > 0);
	}

	/***********************************************************************/	
	/***********************************************************************/
	// Calcula y devuelve el n�mero de secuencias de un n�mero secuenciable. 
	// PRE: EsSecuenciable() == true
	
	int NumSecuencias (void) 
	{
		int ultimo_inicio = valor/2;   
		int cont_secuencias = 0; 
				
		for (int inicio = 1; inicio <= ultimo_inicio; inicio++) {
			
			int suma  = inicio;  // suma inicial (primer valor de la sec.)
			int nuevo = inicio+1; 	// segundo valor de la sec. 
			int operaciones = 1; //Numero de operaciones para llegar a valor
			int valor_numero = inicio; //Valor del numero en cada operacion
			
			// Mientras que la suma de la secuencia sea menor que "valor", 
			// seguir a�adiendo t�rminos consecutivos. 
			 
			while (suma < valor) {
				suma += nuevo; // Nueva suma 
				nuevo++; // El nuevo t�rmino a considerar es el siguiente 
				operaciones++; //Incrementa el numero de operaciones
			}
			
			// Si "suma" es igual a "n" hemos encontrado una secuencia. 
			// Si no, la suma es necesariamente mayor.  
			if (suma == valor){
				
				for (int i=0;i<operaciones;i++){
					secuencias[valor][cont_secuencias][i] = valor_numero;
					valor_numero++;
				}
				secuencias[valor][cont_secuencias][operaciones] = -100;
				cont_secuencias++;
			}
		}
		
		return cont_secuencias;
	}
	
	string GetSecuencia(int j){
		string cad = " = ";
			int i = 0;
			if (secuencias[valor][j][i] != 0){
				while (secuencias[valor][j][i] != -100){
					cad += to_string(secuencias[valor][j][i]);
					if (secuencias[valor][j][i+1] != -100){
						cad += " + ";
					}
					i++;
				}	
			}
		return (cad);
	}
	
	/***********************************************************************/
	/***********************************************************************/
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/***************************************************************************/
	
int main (void)
{
	int n1, n2; 
	int n_sec; 
	
	// Entrada (leer los extremos)
	
	do {
	    cout << "Introduzca un numero positivo: ";
    	cin >> n1;    	
	} while (n1<=0);

	do {
	    cout << "Introduzca otro numero positivo: ";
    	cin >> n2;    	
	} while (n2<=0);

	// Entrada (N�mero de secuencias)

	cout << endl; 
	do {
	    cout << "Introduzca numero de secuencias: ";
    	cin >> n_sec;    	
	} while (n_sec<=0);


	// Reajustar los extremos menor y mayor

    int extremo_menor, extremo_mayor;	
	
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


	GestorNumerosSecuenciables g;
	
	// C�lculos y resultado 
	
	// 1. Calcular total de n�meros secuenciables 

	cout << endl; 
	cout << "1. Total de numeros secuenciables." << endl; 	
	cout << endl; 
		 	
	int contador_secuenciables = 0; 
	
	for (int n=extremo_menor; n<=extremo_mayor; n++) {
	
		g.SetValor(n); // Cambiar el valor objeto del c�lculo 
		
		if (g.EsSecuenciable())	contador_secuenciables++;	
	}
	
	cout << "\tSe han encontrado " << setw(3) << contador_secuenciables 
	     << " numeros secuenciables." << endl; 
	cout << endl; 


	// 2. Mostrar numeros secuenciables y el n�mero de secuencias
	
	cout << endl; 
	cout << "2. Los numeros secuenciables y el numero de secuencias." << endl; 	
	cout << endl; 

	for (int n=extremo_menor; n<=extremo_mayor; n++) {
		
		g.SetValor(n); // Cambiar el valor objeto del c�lculo 
		
		if (g.EsSecuenciable())	 {
		   	cout << "\t" << setw(3) << g.GetValor() << " es secuenciable. ";	
	    	cout << "(" << g.NumSecuencias() << " secuencias)" << endl;
		}
	  	else 
		   	cout << "\t" << setw(3) << g.GetValor()  
			     << " NO es secuenciable." << endl;	
	}
	cout << endl; 
	
	// 3. Mostrar numeros secuenciables cuyo n�mero de secuencias 
	// 	  coincida con el valor pedido y el total.  
	
	cout << endl; 
	cout << "3. Numeros secuenciables con " << 
	     setw(2) << n_sec << " secuencias:" << endl; 		
	cout << endl; 
	
	int contador = 0; 
	
	for (int n=extremo_menor; n<=extremo_mayor; n++) {
		
		g.SetValor(n); // Cambiar el valor objeto del c�lculo 
		
		if (g.EsSecuenciable()) {
		
			int num_secuencias_calculadas = g.NumSecuencias();
			
			if (num_secuencias_calculadas == n_sec) {
				
			    contador++;
		
				for (int j=0;j<num_secuencias_calculadas;j++){
					cout << "\t " << setw(3) << g.GetValor() 
						 << g.GetSecuencia(j) << "\n";
				}
				cout << " (" << setw(2) << num_secuencias_calculadas 
					 << " secuencias)" << endl;
			}
		}
	}
	cout << endl; 		
	
	cout << endl; 		
	if (contador > 0) 
		cout << "\tHay " << setw(3) << contador << " numeros con "
		     << n_sec << " secuencias" << endl; 		
	else 
		cout << "\tNo hay ningun numero con " << setw(3) << n_sec 
		     << " secuencias en el rango indicado." << endl; 			
	cout << endl; 		


	return 0;
}

/***************************************************************************/
/***************************************************************************/
