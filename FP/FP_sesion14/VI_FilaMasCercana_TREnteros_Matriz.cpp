/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Ampliar la clase TablaRectangularEnteros con un método que busque la fila 
	de la matriz que más se parezca a un vector de enteros (clase 
	SecuenciaEnteros) al que llamaremos referencia. El método devolverá el 
	número de la fila.
	La similitud entre dos vectores x = (x1 · · · xp) e y = (y1 · · · yp) vendrá
	dada por la distancia euclídea entre ambos
	Además, la búsqueda solo se hará sobre un conjunto seleccionado de filas de 
	la tabla, enumeradas en la secuencia de enteros filas_a_comparar (un objeto 
	de la clase SecuenciaEnteros).

	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <iomanip>
#include <cmath>

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/
const int DIST_MINIMA = 9999; //Distancia minima entre dos secuencias

/*****************************************************************************
*							  CLASES										 *
*****************************************************************************/

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




// Tabla rectangular de enteros
class SecuenciaEnteros  
{

private:

	static const int TAMANIO = 40; // Número de casillas disponibles
	int vector_privado[TAMANIO];
	
	//PRE: 0 <= total_utilizados <= TAMANIO
	int total_utilizados;	// Número de casillas ocupadas

public:
	
	/***********************************************************************/
	// Constructor sin argumentos

	SecuenciaEnteros (void) 
	{
		total_utilizados = 0;
	}

	/***********************************************************************/
	// Métodos de lectura (Get) de los datos individuales 

	// Devuelve el número de casillas ocupadas
	int TotalUtilizados (void)
	{
		return (total_utilizados);
	}

	// Devuelve el número de casillas disponibles
	int Capacidad (void)
	{
		return (TAMANIO);
	}

	/***********************************************************************/
	// Añade un elemento al vector.
	// Recibe: nuevo, el elemento que se va a añadir.
	//
	// PRE: total_utilizados < TAMANIO
	// 		La adición se realiza si hay espacio para el nuevo elemento. 
	// 		El nuevo elemento se coloca al final del vector. 
	// 		Si no hay espacio, no se hace nada.	

	void Aniade (int nuevo)
	{
		if (total_utilizados < TAMANIO) {
			vector_privado[total_utilizados] = nuevo;
			total_utilizados++;
		}
	}

	//Reemplaza un elemento de la secuencia
	//Recibe: nuevo, elemento a intercambiar por elemento en la posicion
	//PRE: Total_utilizados <= posicion => 0 
	void Reemplaza (int nuevo, int posicion){
		vector_privado[posicion] = nuevo;
	}
	
	/***********************************************************************/
	// Devuelve el elemento de la casilla "indice" 
	//
	// PRE: 0 <= indice < total_utilizados 

	int Elemento (int indice)
	{
		return vector_privado[indice];
	}

	/***********************************************************************/
	// Devuelve true si la secuencia está vacía

	bool EstaVacia (void)
	{
		return (total_utilizados == 0);
	}

	/***********************************************************************/
	// "Vacía" una secuencia

	void EliminaTodos (void)
	{
		total_utilizados = 0;
	}
	
	/***********************************************************************/
	// Búsqueda de un valor en la secuencia, entre dos posiciones dadas. 
	// Realiza una búsqueda secuencial
	//
	// Recibe: 	buscado, el valor a buscar en la secuencia.
	//			izda y dcha, posiciones entre las que se realiza la búsqueda.
	// Devuelve: la posición del elemento "buscado", si está en la secuencia,
	//			 o -1, si no lo encuentra.
	// PRE: 0 <= izda <= dcha < total_utilizados

	int Posicion (int buscado, int izda, int dcha)
	{
		bool encontrado = false; 
		int pos = izda; 

		while ((pos <= dcha) && (!encontrado)) {

			if (vector_privado[pos] != buscado) // Seguir buscando
				pos++;
			else // Terminar la búsqueda: éxito
				encontrado =  true;
		} 

		if (encontrado)
			return (pos);
		else 
			return (-1);

	}
	
	/***********************************************************************/
	// Devuelve la posición del mínimo valor de la secuencia
	//
	// PRE: 0 <= izda <= dcha < total_utilizados
	
	int PosicionMinimo (int izda, int dcha)
	{
		int posicion_minimo;
		int minimo;
	
		minimo = vector_privado[izda];
		posicion_minimo = izda;
		
		for (int i = izda; i <= dcha ; i++) { 
			
			if (vector_privado[i] < minimo){
				minimo = vector_privado[i];
				posicion_minimo = i;
			}
		}
		
		return (posicion_minimo);		
	}
	
	/***********************************************************************/
	// Devuelve la posición del máximo valor de la secuencia
	//
	// PRE: 0 <= izda <= dcha < total_utilizados
	
	int PosicionMaximo (int izda, int dcha)
	{
		int posicion_maximo;
		int maximo;
	
		maximo = vector_privado[izda];
		posicion_maximo = izda;
		
		for (int i = izda; i <= dcha ; i++) { 
			
			if (vector_privado[i] > maximo){
				maximo = vector_privado[i];
				posicion_maximo = i;
			}
		}
		
		return (posicion_maximo);		
	}
	
	/***********************************************************************/
	// Devuelve el mínimo de la secuencia. 
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	int Minimo (int izda, int dcha)
	{
		return (vector_privado[PosicionMinimo(izda, dcha)]);
	}


	/***********************************************************************/
	// Devuelve el máximo de la secuencia. 
	//
	// PRE: 0 <= izda <= dcha < total_utilizados

	int Maximo (int izda, int dcha)
	{
		return (vector_privado[PosicionMaximo(izda, dcha)]);
	}
	
	/***********************************************************************/
	// Devuelve una secuencia incluida en la secuencia implícita, que empieza 
	// en la posición "pos_init" y tiene "num_datos" valores
	//
	// Recibe: pos_init, posición inicial desde donde empieza la copia a la 
	//					 subsecuencia. 
	//		   num_datos, número de valores que se copian a la subsecuencia. 
	// Devuelve: una subsecuencia de la secuencia implícita. 
	// 
	// Casos: 1) Si 0 <= pos_init < total_utilizados Y 
	//			 pos_init+num_datos<=total_utilizados
	//			 se devuelve una subsecuencia de tamaño "num_datos"
	//		  2) Si 0 <= pos_init < total_utilizados Y 
	//			 pos_init+num_datos>total_utilizados, se devuelve una 
	//			 subsecuencia de tamaño total_utilizados-pos_init
	//		  3) Si pos_init < 0 Ó pos_init >= total_utilizados, 
	//			 se devuelve una subsecuencia vacía.
	//		  4) Si num_datos = 0, se devuelve una subsecuencia vacía.

	SecuenciaEnteros Subsecuencia (int pos_init, int num_datos)
	{
		SecuenciaEnteros a_devolver; // inicialmente vacía
		
		if ((pos_init>=0) && (pos_init<total_utilizados) && (num_datos>0)) {
			
			int pos_end;
			
			if (pos_init+num_datos>total_utilizados) 
				pos_end = total_utilizados;
			else 
				pos_end = pos_init+num_datos;
			
			for (int pos=pos_init; pos<pos_end; pos++)
				a_devolver.Aniade(vector_privado[pos]);
		}
		
		return (a_devolver);
	}
			
	/***********************************************************************/
	// Compara dos secuencias
	
	bool EsIgual (SecuenciaEnteros otra_secuencia) 
	{
		bool son_iguales = true; 
		
		if (total_utilizados != otra_secuencia.total_utilizados)
		
			son_iguales = false;
		
		else {
				
			bool sigo = true;
			int pos = 0;
			
			while (sigo && (pos < total_utilizados)) {
	
				if (vector_privado[pos]!=otra_secuencia.vector_privado[pos]) {
					sigo = false;
					son_iguales = false;
				}
				else
					pos++; 
			} // while (sigo && pos < total_utilizados) 
		}
			
		return (son_iguales);
	}
	

	/***********************************************************************/
	// Calcula la distancia Euclídea entre dos secuencias
	//
	// PRE: total_utiizados = otra_secuencia.TotalUtilizados()

	double DistanciaEuclidea (SecuenciaEnteros otra_secuencia)
	{
		double suma = 0.0;

		for (int pos=0; pos<total_utilizados; pos++) {

			double dif=vector_privado[pos]-otra_secuencia.vector_privado[pos];
			suma += dif*dif;
		}

		return (sqrt(suma));
	}

    /***********************************************************************/
    // Compone un string con todos los valores que están
    // almacenados en la secuencia y lo devuelve.

    string ToString()
    {
        string cadena = "{";

		if (total_utilizados > 0) {

	        for (int i=0; i<total_utilizados-1; i++)
	        	cadena = cadena + to_string(vector_privado[i])+", ";

			// Añadie el último seguido de '}'
	        cadena = cadena + to_string(vector_privado[total_utilizados-1]);
		}

        cadena = cadena + "}";

        return (cadena);
    }
    
   	/***********************************************************************/
   	
};



/////////////////////////////////////////////////////////////////////////////
// El tipo de dato PosicionEnMatriz se emplea para guardar posiciones 	
// dentro de una matriz: se registra la pareja (fila, columna)
	
struct PosicionEnMatriz {
	int fila;
	int columna;
};

/////////////////////////////////////////////////////////////////////////////
// La clase "SecuenciaPosicionEnMatriz" es útil para representar una secuencia
// de  posiciones (coordenadas) en una tabla bidimensional.	
	
class SecuenciaPosicionEnMatriz
{
private:

	static const int TAMANIO = 50; // Número de casillas disponibles
	PosicionEnMatriz vector_privado[TAMANIO];
	
	//PRE: 0 <= total_utilizados <= TAMANIO
	int total_utilizados;	// Número de casillas ocupadas

public: 
	
	/***********************************************************************/
	// Constructor sin argumentos

	SecuenciaPosicionEnMatriz (void) 
	{
		total_utilizados = 0;
	}

	/***********************************************************************/
	// Métodos de lectura (Get) de los datos individuales 

	// Devuelve el número de casillas ocupadas
	int TotalUtilizados (void)
	{
		return (total_utilizados);
	}

	// Devuelve el número de casillas disponibles
	int Capacidad (void)
	{
		return (TAMANIO);
	}

	/***********************************************************************/
	// Añade un elemento al vector.
	// Recibe: nuevo, el elemento que se va a añadir.
	//
	// PRE: total_utilizados < TAMANIO
	// 		La adición se realiza si hay espacio para el nuevo elemento. 
	// 		El nuevo elemento se coloca al final del vector. 
	// 		Si no hay espacio, no se hace nada.	

	void Aniade (PosicionEnMatriz nuevo)
	{
		if (total_utilizados < TAMANIO) {
			vector_privado[total_utilizados] = nuevo;
			total_utilizados++;
		}
	}

	/***********************************************************************/
	// Devuelve el elemento de la casilla "indice" 
	//
	// PRE: 0 <= indice < total_utilizados 

	PosicionEnMatriz Elemento (int indice)
	{
		return vector_privado[indice];
	}
			
	/***********************************************************************/
	// Compone y devuelve un string con el contenido de la secuencia
	
	string ToString ()
	{
	    string cadena = "{";

		if (total_utilizados > 0) {

	        for (int indice=0; indice<total_utilizados-1; indice++) {
	        	PosicionEnMatriz pos = vector_privado[indice];
	    	    cadena = cadena + "(" + to_string(pos.fila) + ", " + 
				                        to_string(pos.columna) + "), ";
			}
	
			// Añadie el último seguido de '}'
			PosicionEnMatriz pos = vector_privado[total_utilizados-1];
	        cadena = cadena + "(" + to_string(pos.fila) + ", " + 
			                        to_string(pos.columna) + ")";
		}
        cadena = cadena + "}";		
		
		return cadena;
	}
	
	/***********************************************************************/
};



class TablaRectangularEnteros
{

private:

    static const int NUM_FILS = 50; // Filas disponibles
    static const int NUM_COLS = 40; // Columnas disponibles
    
    int  matriz_privada[NUM_FILS][NUM_COLS];

    // PRE: 0 <= filas_utilizadas <= NUM_FILS
    // PRE: 0 <= col_utilizadas < NUM_COLS
    
    int filas_utilizadas;
    int cols_utilizadas;

public:

	/***********************************************************************/
	// Constructor sin argumentos--> Crea matriz nula

	TablaRectangularEnteros (void)
		: filas_utilizadas(0), 
		  cols_utilizadas(0)
	{
	}

	/***********************************************************************/
	// Constructor--> Recibe "numero_de_columnas" que indica el número de 
	// columnas que deben tener TODAS las filas. 
	// PRE: numero_de_columnas <= MAX_COL

	TablaRectangularEnteros (int numero_de_columnas)
		: filas_utilizadas(0), 
		  cols_utilizadas(numero_de_columnas)
	{
	}

	/***********************************************************************/
	// Constructor--> Recibe una secuencia de enteros.  El número de 
	// elementos de la secuencia es el valor que se usa como "col_utilizadas"
	// PRE: primera_fila.TotalUtilizados() <= MAX_COL

	TablaRectangularEnteros (SecuenciaEnteros primera_fila)
		: filas_utilizadas(0), 
		  cols_utilizadas (primera_fila.TotalUtilizados())
	{
		Aniade(primera_fila); // Actualiza "filas_utilizadas"
	}


	/***********************************************************************/
	// Método de lectura: número máximo de filas

	int CapacidadFilas (void)
	{
		return (NUM_FILS);
	}

	/***********************************************************************/
	// Método de lectura: número máximo de columnas

	int CapacidadColumnas (void)
	{
		return (NUM_COLS);
	}

	/***********************************************************************/
	// Método de lectura: número real de filas usadas

	int FilasUtilizadas (void)
	{
		return (filas_utilizadas);
	}

	/***********************************************************************/
	// Método de lectura: número real de columnas usadas

	int ColumnasUtilizadas (void)
	{
		return (cols_utilizadas);
	}

	/***********************************************************************/
	// Método de lectura: devuelve el dato que ocupa la casilla 
	// de coordenadas (fila, columna)
	// PRE: 0 <= fila < filas_utilizadas
	// PRE: 0 <= columna < cols_utilizadas	
	
	int Elemento (int fila, int columna)
	{
		return (matriz_privada[fila][columna]);
	}

	/***********************************************************************/
	// Devuelve true si la tabla está vacía

	bool EstaVacia (void)
	{
		return (filas_utilizadas == 0);
	}

	/***********************************************************************/
	// Busca la fila de la matriz que mas se parece a la secuencia referencia
	int FilaMatrizParecida(SecuenciaEnteros referencia, 
	SecuenciaEnteros filas_a_comparar){
		int num_filas = filas_a_comparar.TotalUtilizados();
		int fila;
		int fila_parecida;
		int distancia = DIST_MINIMA; //Distancia euclidea dos secuencias
		for (int i=0;i<num_filas;i++){
			fila = filas_a_comparar.Elemento(i);
			if (referencia.DistanciaEuclidea(Fila(fila)) < distancia){
				distancia = referencia.DistanciaEuclidea(Fila(fila));
				fila_parecida = fila;
			}
		}
		return(fila_parecida);
	}

	/*****************************************************************/
	// Devuelve una fila completa (un objeto "SecuenciaEnteros")
	// PRE: 0 <= indice_fila < filas_utilizadas
	
	SecuenciaEnteros Fila (int indice_fila)
	{
		SecuenciaEnteros fila;

		for (int col=0; col<cols_utilizadas; col++)
			fila.Aniade(matriz_privada[indice_fila][col]);

		return (fila);
	}

	/***********************************************************************/
	// Devuelve una columna completa (un objeto "SecuenciaEnteros")
	// PRE: 0 <= indice_columna < cols_utilizadas
	
	SecuenciaEnteros Columna (int indice_columna)
	{
		SecuenciaEnteros columna;

		for (int fil=0; fil<filas_utilizadas; fil++)
			columna.Aniade (matriz_privada[fil][indice_columna]);

		return (columna);
	}

	/***********************************************************************/
	// Añade una fila completa (un objeto "SecuenciaEnteros")
	// PRE:  fila_nueva.TotalUtilizados() = cols_utilizadas
	// PRE:  filas_utilizadas < MAX_FIL
	
	void Aniade (SecuenciaEnteros fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		if ((filas_utilizadas < NUM_FILS) &&
			(numero_columnas_fila_nueva == cols_utilizadas)) {

			for (int col = 0; col < numero_columnas_fila_nueva; col++)
				matriz_privada[filas_utilizadas][col]=fila_nueva.Elemento(col);

			filas_utilizadas++;
		}
	}

	/***********************************************************************/
	// "Vacía" una tabla

	void EliminaTodos (void)
	{
		filas_utilizadas = 0;
	}
	
	/***********************************************************************/
	// Calcula si dos matrices rectangulares son iguales
	// Compara la tabla implícita con "otra" (tabla explícita) 

	bool EsIgual (TablaRectangularEnteros otra_tabla)
	{
		bool son_iguales = true; 
		
		if ((filas_utilizadas != otra_tabla.FilasUtilizadas()) || 
			 (cols_utilizadas != otra_tabla.ColumnasUtilizadas()))		
			
			son_iguales = false;
		
		else {
			
			int f=0; 
			
			while (f<filas_utilizadas && son_iguales) {
				
				int c=0; 
				
				while (c<cols_utilizadas && son_iguales) {
			
					if (matriz_privada[f][c] != otra_tabla.Elemento(f,c)) 
						son_iguales = false;
						
					c++;
					
				} // while c
	
				f++;
					
			} // while f
					
		} // else 
	
		return (son_iguales);
	}
	

	/***********************************************************************/
	// Devuelve la traspuesta de la matriz (si es posible calcularse)
	// PRE: filas_utilizadas <= MAX_COL
	// PRE: cols_utilizadas  <= MAX_FIL
	// Si no se puede calcular la traspuesta se devuelve una matriz nula. 

	TablaRectangularEnteros Traspuesta (void)
	{		
	    TablaRectangularEnteros traspuesta; // Inicialmente vacía
		
		if ((filas_utilizadas <= NUM_COLS) && (cols_utilizadas  <= NUM_FILS)) {
		
			// La traspuesta tiene tantas filas como columnas tiene la
			// matriz original
	
			TablaRectangularEnteros solucion (filas_utilizadas);
	
	
			SecuenciaEnteros columna; // Las filas de "traspuesta" serán las
										 // columnas de la tabla implícita
	
			for (int col = 0; col < cols_utilizadas; col++){
	
				columna = Columna(col);
				solucion.Aniade(columna);
			}
			
			traspuesta = solucion;
		} 

		return (traspuesta);
	}			
	

	/***********************************************************************/
	// Calcula si una matriz es simétrica.
	// CONDICIÓN NECESARIA: debe ser cuadrada. 
	// Este método comprueba directamente si cada componente es igual a
	// su simétrica, parando el recorrido cuando encuentre una componente
	// que no lo verifique.
	//
	// Evita el cálculo de la traspuesta, y el problema que puede surgir
	// si no se puede calcular la traspuesta de la matriz por problemas de
	// capacidad.

	bool EsSimetrica (void)
	{
		bool es_simetrica = true;

		// Si el número de filas y columnas no coinciden, no hay que seguir
		// porque la matriz no es simétrica.

		es_simetrica = (filas_utilizadas == cols_utilizadas);

		if (es_simetrica) {

			int f=0;

			while (f<filas_utilizadas && es_simetrica) {

				int c=0;

				while (c<cols_utilizadas && es_simetrica) {

					if (matriz_privada[f][c] != matriz_privada[c][f])
						es_simetrica = false;

					c++;

				} // while c

				f++;

			} // while f

		} // if (es_simetrica)

		return (es_simetrica);
	}
					
	/***********************************************************************/
	// Inserta una fila completa en una posición dada. 
	// La fila se porporciona en un objeto "SecuenciaEnteros".
	// 
	// Recibe: num_fila, la posición que ocupará "fila_nueva" cuando se 
	//		 		inserte en la tabla.
	//		   fila_nueva, la secuencia que se va a insertar. Se trata 
	//				de un objeto de la clase "SecuenciaEnteros". 
	//
	// PRE:  fila_nueva.TotalUtilizados() = cols_utilizadas
	// PRE:  filas_utilizadas < MAX_FIL
	// PRE:  0 <= num_fila <= TotalUtilizados()
	//		 Si num_fila = 0, "nueva_fila" será la nueva primera fila. 
	//		 Si num_fila = TotalUtilizados(), "nueva_fila" será la nueva 
	//		 última fila (el resultado será equivalente al de "Aniade()" 
	
	void Inserta (int num_fila, SecuenciaEnteros fila_nueva)
	{
		int numero_columnas_fila_nueva = fila_nueva.TotalUtilizados();
					
		// Comprobar precondiciones
		
		if ((filas_utilizadas < NUM_FILS) &&
			(numero_columnas_fila_nueva == cols_utilizadas) && 
			(0<=num_fila) && (num_fila <=filas_utilizadas)) {

			// "Desplazar" las filas hacia posiciones altas. 
			// La última fila se copia en una NUEVA FILA que ocupa la 
			// posición "filas_utilizadas", la penúltima se copia en 
			// "filas_utilizadas"-1, ... y se queda un "hueco" en 
			// la fila "num_fila ".
			// NOTA: no se modifica (todavía) "filas_utilizadas" 
			
			for (int fil=filas_utilizadas; fil>num_fila; fil--) {
				
				for (int col = 0; col < numero_columnas_fila_nueva; col++)
					matriz_privada[fil][col]=matriz_privada[fil-1][col];
			}
			
			// Copiar en el "hueco" (fila "num_fila") el contenido de 
			// la secuencia "fila_nueva"
			
			for (int col = 0; col < numero_columnas_fila_nueva; col++)
				matriz_privada[num_fila][col]=fila_nueva.Elemento(col);	
			
			filas_utilizadas++; // Actualización del tamaño de la tabla.
		}
	}

	/***********************************************************************/
	// Elimina una fila completa, dada una posición. 
	// 
	// Recibe: num_fila, la posición de la fila a eliminar.
	// PRE:  0 <= num_fila < TotalUtilizados()
	
	void Elimina (int num_fila)
	{		
		// Comprobar precondiciones
		
		if ((0<=num_fila) && (num_fila <=filas_utilizadas)) {

			// "Desplazar" las filas hacia posiciones bajas. 
			// En la posición "num_fila" se copia la que está en la posición
			// siguiente ("num_fila"+1), en su lugar se copia que está en 
			// "num_fila"+2, ... y en la posición "total_utilizados"-2 se 
			// copia la de "total_utilizados"-1. 
			
			for (int fil=num_fila; fil<filas_utilizadas-1; fil++) {
			
				int num_columnas = cols_utilizadas;
					
				for (int c=0; c<num_columnas; c++) 
					matriz_privada[fil][c]=matriz_privada[fil+1][c];
			}
			
			filas_utilizadas--; // Actualización del tamaño de la tabla.
		}
	}	
	
	/***********************************************************************/
	// Devuelve TRUE si la matriz contiene el valor "buscado"
	
	bool Contiene (int buscado)
	{
		bool encontrado = false;

		// Recorrido por columnas 

		int col = 0;

		while (col < cols_utilizadas && !encontrado) {

			int fil=0;

			while (fil < filas_utilizadas && !encontrado) {

				if (matriz_privada[fil][col] == buscado)
					encontrado = true;
				
				fil++;

			} // while fil

			col++; 

		} // while col

		return (encontrado);
	}
		
	/***********************************************************************/
	// Encontrar un dato en la matriz y devolver su posición.
	// El valor devuelto contiene información acerca de la posición 
	// (fila y columna) de "buscado".  
	// 		En el caso de que no esté contendrá {-1,-1}. 
	// La consulta de la fila y la columna se delega en los métodos de 
	// la clase "PosicionEnMatriz" 

	PosicionEnMatriz PrimeraOcurrencia (int buscado)
	{
		PosicionEnMatriz posicion_dato_buscado = {-1,-1};
      
		bool encontrado = false;

		// Recorrido por filas 

		for (int i=0; i < filas_utilizadas && !encontrado ; i++){

			for (int j=0; j < cols_utilizadas && !encontrado; j++){

				if (matriz_privada[i][j] == buscado){
					encontrado = true;
					posicion_dato_buscado.fila = i;
					posicion_dato_buscado.columna = j;
				}

			} // for j

		} // for i
      
		return (posicion_dato_buscado);
	} 
		
	/***********************************************************************/
	// Devuelve las posiciones (f,c) en las que la suma del valor de la 
	// izquierda (f, c-1) y de la derecha (f, c+1) coincide con la del valor 
	// de la casilla (f,c)
	
	SecuenciaPosicionEnMatriz PosicionesSumaLateral (void)
	{
		SecuenciaPosicionEnMatriz secuencia_posiciones;
		
		// Recorrido por filas 

		for (int f=0; f<filas_utilizadas; f++){

			for (int c=1; c<cols_utilizadas-1; c++){

				if (matriz_privada[f][c] == matriz_privada[f][c-1] + 
				                            matriz_privada[f][c+1]){
				    // Version 1. Directa
					// secuencia_posiciones.Aniade(PosicionEnMatriz({f,c}));
					
					// Version 2. Iniciación de todo el struct
					//PosicionEnMatriz pos_encontrada = {f,c};
					//secuencia_posiciones.Aniade(pos_encontrada);					

					// Version 3. Detallada
					PosicionEnMatriz pos_encontrada;
					pos_encontrada.fila = f;
					pos_encontrada.columna = c;
					secuencia_posiciones.Aniade(pos_encontrada);					
				}

			} // for c
			
		} // for f
			
		return secuencia_posiciones;
	}
		
	/***********************************************************************/
	// Compone y devuelve un string con el contenido de la matriz
	
	string ToString ()
	{
		string cad; 
		
		for (int fila=0; fila<filas_utilizadas; fila++) {
			
			for (int col=0; col<cols_utilizadas; col++) {
			
				cad = cad + "\t" + 
				      to_string(matriz_privada[fila][col]);  
			}
			cad = cad + "\n";
		}
		
		return (cad);
	}
	
	/***********************************************************************/
};



int main() //Programa principal
{
		
	
	//Solucion Como TEST del enunciado:
	
	SecuenciaEnteros una_fila; // Secuencia vacía
	una_fila.Aniade (3); una_fila.Aniade (1); 
	una_fila.Aniade (0); una_fila.Aniade (8);
	
	TablaRectangularEnteros una_tabla(una_fila);
	
	una_fila.Reemplaza (4,0); una_fila.Reemplaza (5,1); 
	una_fila.Reemplaza (1,2); una_fila.Reemplaza (5,3);
	una_tabla.Aniade(una_fila);
	
	una_fila.Reemplaza (5,0); una_fila.Reemplaza (7,1); 
	una_fila.Reemplaza (1,2); una_fila.Reemplaza (7,3);
	una_tabla.Aniade(una_fila);
	
	una_fila.Reemplaza (7,0); una_fila.Reemplaza (9,1); 
	una_fila.Reemplaza (6,2); una_fila.Reemplaza (1,3);
	una_tabla.Aniade(una_fila);
	
	una_fila.Reemplaza (4,0); una_fila.Reemplaza (9,1); 
	una_fila.Reemplaza (5,2); una_fila.Reemplaza (5,3);
	una_tabla.Aniade(una_fila);
	
	una_fila.Reemplaza (2,0); una_fila.Reemplaza (8,1); 
	una_fila.Reemplaza (2,2); una_fila.Reemplaza (2,3);
	una_tabla.Aniade(una_fila);
	
	una_fila.Reemplaza (7,0); una_fila.Reemplaza (3,1); 
	una_fila.Reemplaza (2,2); una_fila.Reemplaza (5,3);
	una_tabla.Aniade(una_fila);
	
	//Mostramos la tabla
	cout << una_tabla.ToString();
	
	
	//Secuencia Referencia
	SecuenciaEnteros referencia; // Secuencia vacía
	referencia.Aniade (2); referencia.Aniade (8); 
	referencia.Aniade (1); referencia.Aniade (1);
	
	//Secuencia Referencia
	SecuenciaEnteros filas_a_comparar; // Secuencia vacía
	filas_a_comparar.Aniade (0); filas_a_comparar.Aniade (2); 
	filas_a_comparar.Aniade (4); filas_a_comparar.Aniade (5);

	double fila_mas_par;
	
	fila_mas_par = una_tabla.FilaMatrizParecida(referencia,filas_a_comparar);
	cout << "Fila mas Parecida: " << fila_mas_par;
	
	
	return 0;
}

