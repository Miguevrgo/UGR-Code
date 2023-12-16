/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Definimos un nuevo criterio de orden entre dos números enteros positivos: 
	Un valor entero a será mayor que otro b si el número de dígitos nueve es 
	mayor en a que en b. Si el número de nueves es igual en los dos, el mayor 
	será el que tiene más ochos.
	
	Si hay empate también con este dígito, se considera el siete. Así hasta 
	llegar al cero, si fuese necesario. Si la frecuencia de todos los dígitos 
	es igual en ambos valores, se les considera iguales.
	Añada cuatro nuevos métodos a la clase SecuenciaEnteros:

	void OrdenaSeleccion_NuevoOrden()
	void OrdenaInsercion_NuevoOrden()
	void OrdenaIntercambio_NuevoOrden()
	void OrdenaIntercambioMejorado_NuevoOrden()

	Escriba un programa que pida el número de elementos de la secuencia 
	(cuántas casillas se van a ocupar), rellene esa secuencia con números 
	aleatorios entre 0 y 999, la ordene con los métodos implementados y muestre 
	el resultado.
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <random>  // para la generación de números pseudoaleatorios
#include <chrono>  // para la semilla

using namespace std;

/*****************************************************************************
*							   CLASES										 *
*****************************************************************************/
class GeneradorAleatorioEnteros
{  
private:
	
	mt19937 generador_mersenne;    // Mersenne twister
	uniform_int_distribution<int>  distribucion_uniforme;
	
	/************************************************************************/
	
	long long Nanosec(){
	return (chrono::high_resolution_clock::now().time_since_epoch().count());
	}
	
	/************************************************************************/ 
	
public:
	
	/************************************************************************/
		
	GeneradorAleatorioEnteros() : GeneradorAleatorioEnteros(0, 1) 
	{ }
	
	/************************************************************************/  
	GeneradorAleatorioEnteros(int min, int max) {
	
		const int A_DESCARTAR = 70000;
		// ACM TOMS Volume 32 Issue 1, March 2006
		
		auto semilla = Nanosec();
		generador_mersenne.seed(semilla);
		generador_mersenne.discard(A_DESCARTAR);
		distribucion_uniforme = uniform_int_distribution<int> (min, max);
	}
	
	/************************************************************************/
	
	int Siguiente(){
	  return (distribucion_uniforme(generador_mersenne));
	}
	
	/************************************************************************/

};


/****************************************************************************
*Clase que permite leer un numero de diferentes maneras
*Parametros: Recibe el texto a mostrar al leer el numero 
*****************************************************************************/
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


class SecuenciaNumeros{
private:

	static const int TAM_MAX = 50; //Tamaño maximo secuencia de numeros
	int vector_privado[TAM_MAX];

	//Pre-condicion: total_utilizados < TAM_MAX
	int total_utilizados; //Total de casillas utilizadas

	// PRE: 0<= pos_izda, pos_dcha < total_utilizados
	void IntercambiaComponentes (int pos_izda, int pos_dcha) {
		char intercambia = vector_privado[pos_izda];
		vector_privado[pos_izda] = vector_privado[pos_dcha];
		vector_privado[pos_dcha] = intercambia;
	}

public:
	//Constructor con argumentos
	SecuenciaNumeros(int utilizados) : total_utilizados (utilizados)
	{
		for (int i=0; i<utilizados; i++){
			GeneradorAleatorioEnteros un_aleatorio(0,999);
			vector_privado[i] = un_aleatorio.Siguiente();
		}
	}
	/*************************************************************************
	*Funcion que devuelve el numero de casillas utilizadas
	*Devuelve: total_utlizados
	**************************************************************************/
	int GetUtilizadas (void){
		return(total_utilizados);
	}

	/*************************************************************************
	*Funcion que devuelve el numero en la casilla indicada
	*Recibe: Posicion del elemento
	*Devuelve: numero en la casilla indicada
	**************************************************************************/
	char GetElemento (int posicion){
		if (posicion < total_utilizados){
			return(vector_privado[posicion]);
		}
	}

	/*************************************************************************
	*Funcion que inserta un elemento en una posicion del array
	*Recibe: Elemento a insertar y posicion
	*Pre-condicion: posicion < total_utilizados && total_utilizados < TAM_MAX
	**************************************************************************/
	void InsertarElemento(int elemento, int posicion){
		if (posicion > 0){
			//Desplazamos los elementos a la derecha de la posicion deseada
			for (int i = total_utilizados; i > posicion; i--){
				vector_privado[i] = vector_privado[i-1];
			}
			vector_privado[posicion] = elemento; //Inserta el nuevo elemento
			total_utilizados++; //Incrementa el total de posiciones utilizadas
		}
	}
	
	/*************************************************************************
	*Funcion que elimina un elemento en una posicion
	*Recibe: Posicion
	*Pre-condicion: posicion < total_utilizados
	**************************************************************************/
	void EliminarElemento(int posicion){
		if (posicion > 0){
			int ultimo_elemento = total_utilizados-1;
			//Desplazamos los elementos a la izquierda de la posicion deseada
			for (int i = posicion; i < ultimo_elemento; i++){
				vector_privado[i] = vector_privado[i+1];
			}
			total_utilizados--; //Disminuye el total de posiciones utilizadas
		}
	}

	/*************************************************************************
	*Funcion que modifica un numero en una posicion
	*Recibe: Numero y posicion
	*Pre-condicion: posicion < total_utilizados
	**************************************************************************/
	void ModificaElemento(int posicion, int numero){
		if (posicion > 0){
			vector_privado[posicion] = numero;
		}
	}

	/*************************************************************************
	*Funcion que añade un numero nuevo al vector(Al final de la cadena)
	*Parametros: Recibe el numero
	*Pre-condicion: Total utilizados < TAM_MAX
	**************************************************************************/
	void AddElemento(int numero){
		if (total_utilizados < TAM_MAX){
			vector_privado[total_utilizados] = numero;
			total_utilizados++;
		}
	}
	//Devuelve la cifra de un numero en una posicion 
	int CifraNumero(int numero,int posicion){
		string cad;
		cad = to_string(numero);
		cad = cad[posicion];
		return (stoi(cad));
	}
	int NumeroCifras(int numero,int cifra){
		int cifras = 0;
		for (int i=0;i<4;i++){
			if (CifraNumero(numero,i)== cifra){
				cifras++;
			}
		}
		return (cifras);
	}
	//Calcula el menor de dos numeros teniendo en cuenta sus cifras
	int MenorDosNumeros(int num1, int num2){
		bool terminar= false;
		int i=9;
		int menor;
		while (!terminar){
			if (NumeroCifras(num1,i)>(NumeroCifras(num2,i))){
				terminar = true;
				menor = num2;
			}
			else if (NumeroCifras(num1,i)<(NumeroCifras(num2,i))){
				terminar = true;
				menor = num1;
			}
			else{
				i--;
			}
		}
		return (menor)
	}
	int PosicionMinimoEntre (int izda, int derecha){
		
		for (int i=izda;i<derecha;i++){
			minimo = MenorDosNumeros(minimo,vector_privado[i]);
		}
		return (minimo);
	}
	void OrdenaSeleccion_NuevoOrden(){
		// Buscar el menor entre las casillas "izda" y "total_utilizados"-1
		// e intercambiar ese valor por el de la posición "izda"
		for (int izda = 0 ; izda < total_utilizados ; izda++){
			int pos_min = PosicionMinimoEntre (izda, total_utilizados-1);
			IntercambiaComponentes (izda, pos_min);
		}
	}

	void OrdenaInsercion_NuevoOrden(){
		for (int izda = 1; izda < total_utilizados; izda++) {
			int a_insertar = vector_privado[izda];
			// Buscar el sitio que le corresponde a "a_insertar"
			// desplazando hacia la derecha los valores mayores
			int i = izda;
			while (i > 0 && 
			(MenorDosNumeros(a_insertar,vector_privado[i-1]))==a_insertar) {
				vector_privado[i] = vector_privado[i-1];
				i--;
			}
			vector_privado[i] = a_insertar; // Colocar en su lugar
		} // for
	}

	void OrdenaIntercambio_NuevoOrden(){

	}

	void OrdenaIntercambioMejorado_NuevoOrden(){

	}

	
	/*************************************************************************
	*Funcion que devuelve un string con el vector
	*Devuelve: Cadena 
	**************************************************************************/
	string ToString(){
		string cad;
		for	(int i=0;i<total_utilizados;i++){
			cad += to_string(vector_privado[i]);
		}
		return(cad);
	}
};



int main() //Programa principal
{
	Lector una_lectura("Introduzca el numero de elementos de la secuencia: ")
	int utilizados;
	//Entrada de datos
	utilizados = una_lectura.LeeEnteroEnRango(0,49);
	SecuenciaNumeros una_secuencia(utilizados);
	
	//Cálculos



	//Salida
	


	return 0;
}

