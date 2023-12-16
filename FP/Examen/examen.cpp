
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;



string ToStringInt (int entero, int num_casillas, char relleno=' ')
{
	// Inicialmente nos quedamos con el resultado de to_string
	
	string cadena = to_string(entero);
	int long_cadena = (int) cadena.length(); 
	
	// Si es preciso se completa (por la izquierda) con relleno
	
	if (long_cadena < num_casillas) {
		int num_casillas_faltan = num_casillas-long_cadena; 
		for (int i=0; i<num_casillas_faltan; i++) 
			cadena = relleno + cadena; 
	}
	return (cadena);
}




class SecuenciaEnteros
{
private:
	static const int TAMANIO = 100; // Número de casillas reservadas 
	static const int UMBRAL_PEQUENIA = 5; 	 									 
	int vector_privado[TAMANIO];
	//PRE: 0 <= total_utilizados <= TAMANIO
	int total_utilizados;	// Numero de casillas ocupadas

public:

	/***********************************************************************/
	// Constructor sin argumentos

	SecuenciaEnteros (void) : total_utilizados (0) {}

	/***********************************************************************/
	// Devuelve el numero de casillas ocupadas
	
	int TotalUtilizados (void)
	{
		return (total_utilizados);
	}

	/***********************************************************************/
	// Devuelve el numero de casillas disponibles
	
	int Capacidad (void)
	{
		return (TAMANIO);
	}

	
	void Aniade (int nuevo)
	{
		if (total_utilizados < TAMANIO) {
			vector_privado[total_utilizados] = nuevo;
			total_utilizados++;
		}
	}


	int Elemento (int indice)
	{
		return vector_privado[indice];
	}

	/***********************************************************************/
	// "Limpia" una secuencia

	void EliminaTodos (void)
	{
		total_utilizados = 0;
	}

	int PrimeraOcurrenciaEntre (int buscado, int izda, int dcha)
	{
		// Por defecto, el valor NO esta 
		bool encontrado = false;	// ¿Se encontro "buscado"?	
		int pos_buscado = -1;		// Posicion de "buscado"
				
		int pos = izda; 		
		 
		while  (pos <= dcha && !encontrado) 
	
			if (vector_privado[pos] != buscado)
				pos++;
			else {
				encontrado = true; 
				pos_buscado = pos;
			}
	
		return pos_buscado;
	}
	
	/***********************************************************************/
	// Busqueda de un valor en la secuencia, entre dos posiciones dadas.
	
	int BusquedaInterpolacion(int buscado, int izda, int dcha)
	{
	    int pos = -1;
	    int pos_buscado = -1;
	    if(EsPequenia(izda-dcha+1))
	    {
	        pos_buscado = PrimeraOcurrenciaEntre(buscado, izda, dcha);
	    }
	    else
	    {
			if(vector_privado[dcha] == vector_privado[izda]){
    			pos = izda;
			} else {
    			pos = izda + (dcha - izda)/(vector_privado[dcha] - vector_privado[izda]) * (buscado - vector_privado[izda]);
			}
	        if(vector_privado[pos] != buscado){
	        	if(vector_privado[pos] < buscado)
	            	pos_buscado = BusquedaInterpolacion(buscado, pos+1, dcha);
	        	else{
	        		pos_buscado = BusquedaInterpolacion(buscado, izda, pos-1);
				}     	
			}
	    }
	    return pos_buscado; //si no encuentra el valor buscado -->-1
	}
	
	
	/***********************************************************************/
	// Devuelve un string con la representacion textual de la secuencia.

	string ToString (void)
	{
        string cadena = "{";

		if (total_utilizados > 0) {

	        for (int i=0; i<total_utilizados-1; i++)
	        	cadena = cadena + ToStringInt(vector_privado[i], 3) + ",";

			// Añadie el último seguido de '}'
	        cadena = cadena+ToStringInt(vector_privado[total_utilizados-1], 3);
		}
		cadena = cadena + "}";
		
        return (cadena);
	}
	
	/***********************************************************************/			
			
private: 

		

	bool EsPequenia (int num_valores)
	{
		return (num_valores <= UMBRAL_PEQUENIA);
	}

	/***********************************************************************/

};

////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Tabla rectangular de enteros
// Representacion: matriz clasica

class TablaRectangularEnteros
{

private:

    static const int NUM_FILS = 40; // Filas disponibles
    static const int NUM_COLS = 50; // Columnas disponibles
    
    int  matriz_privada[NUM_FILS][NUM_COLS];

    // PRE: 0 <= filas_utilizadas <= NUM_FILS
    // PRE: 0 <= col_utilizadas < NUM_COLS
    
    int filas_utilizadas;
    int cols_utilizadas;

public:

	/***********************************************************************/
	// Constructor sin argumentos--> Crea matriz nula

	TablaRectangularEnteros(void): filas_utilizadas(0), cols_utilizadas(0) {}

	/***********************************************************************/
	// Constructor--> Recibe "numero_de_columnas" que indica el numero de 
	// columnas que deben tener TODAS las filas. 
	// PRE: numero_de_columnas <= CapacidadColumnas()

	TablaRectangularEnteros (int numero_de_columnas)
		: filas_utilizadas(0), cols_utilizadas(numero_de_columnas) {}

	/***********************************************************************/
	// Constructor--> Recibe una secuencia de enteros.  El numero de 
	// elementos de la secuencia es el valor que se usa como "col_utilizadas"
	// PRE: primera_fila.TotalUtilizados() <= CapacidadColumnas()

	TablaRectangularEnteros (SecuenciaEnteros primera_fila)
		: filas_utilizadas(0), cols_utilizadas(primera_fila.TotalUtilizados())
	{
		Aniade(primera_fila); // Actualiza "filas_utilizadas"
	}

	/***********************************************************************/
	// Metodo de lectura: numero maximo de filas

	int CapacidadFilas (void)
	{
		return (NUM_FILS);
	}

	/***********************************************************************/
	// Metodo de lectura: numero maximo de columnas

	int CapacidadColumnas (void)
	{
		return (NUM_COLS);
	}

	/***********************************************************************/
	// Metodo de lectura: numero real de filas usadas

	int FilasUtilizadas (void)
	{
		return (filas_utilizadas);
	}

	/***********************************************************************/
	// Metodo de lectura: número real de columnas usadas

	int ColumnasUtilizadas (void)
	{
		return (cols_utilizadas);
	}

	/***********************************************************************/
	// Metodo de lectura: devuelve el dato que ocupa la casilla 
	// de coordenadas (fila, columna)
	// PRE: 0 <= fila < FilasUtilizadas()
	// PRE: 0 <= columna < ColumnasUtilizadas()	
	
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
	
	/*****************************************************************/
	// Devuelve una fila completa (un objeto "SecuenciaEnteros")
	// PRE: 0 <= indice_fila < FilasUtilizadas()
	
	SecuenciaEnteros Fila (int indice_fila)
	{
		SecuenciaEnteros fila;

		for (int col=0; col<cols_utilizadas; col++)
			fila.Aniade(matriz_privada[indice_fila][col]);

		return (fila);
	}

	/***********************************************************************/
	// Devuelve una columna completa (un objeto "SecuenciaEnteros")
	// PRE: 0 <= indice_columna < ColumnasUtilizadas()	
	
	SecuenciaEnteros Columna (int indice_columna)
	{
		SecuenciaEnteros columna;

		for (int fil=0; fil<filas_utilizadas; fil++)
			columna.Aniade (matriz_privada[fil][indice_columna]);

		return (columna);
	}

	/***********************************************************************/
	// Añade una fila completa (un objeto "SecuenciaEnteros")
	// PRE:  fila_nueva.TotalUtilizados() = ColumnasUtilizadas()	
	// PRE:  filas_utilizadas < CapacidadFilas()
	
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
	// Devuelve un string con la representacion textual de la tabla.

	string ToString ()
	{
		string cad = "Dimensiones = " + to_string(filas_utilizadas) + 
			          " x " + to_string(cols_utilizadas) + "\n\n"; 
		
		for (int num_fila=0; num_fila<filas_utilizadas; num_fila++) 			
			cad = cad + Fila(num_fila).ToString() + "\n";
		
		return cad; 
	}	
	
	/***********************************************************************/
	
};

/////////////////////////////////////////////////////////////////////////////


/***************************************************************************/
/***************************************************************************/

int main (void)
{
	cout.setf(ios::fixed);		// Notacion de punto fijo para los reales
	cout.setf(ios::showpoint);	// Mostrar siempre decimales

	const int MIN_VALOR = 1;
	const int MAX_VALOR = 67;	
	
	/************************************************************************/
	// ENTRADA: Lectura de los valores de la tabla.
	// PRE: Todos los valores, n, verifican que MIN_VALOR <= n <= MAX_VALOR
    
    int num_fil; // Numero de filas de la tabla 
    int num_col; // Numero de columnas de la tabla
    
	do{
	    cout << "Introduzca el numero de filas de la tabla: ";
	    cin >> num_fil;
	    
	}while(num_fil > MAX_VALOR || num_fil < MIN_VALOR);
	
	do{
	    cout << "Introduzca el numero de columnas de la tabla: ";
	    cin >> num_col;
	    
	}while(num_col > MAX_VALOR || num_col < MIN_VALOR);
	
	
    //Secuencia de enteros que se usara para rellenar cada fila de la tabla
    SecuenciaEnteros la_secuencia;
    
    //TablaRectangularEnteros que recibe como constructor el numero de columnas
    //Que tendra cada fila
    TablaRectangularEnteros tabla(num_col); 
	
    int elemento; //Elemento a añadir por posicion (el numero al leer)
	
	
	//Para cada fila de la matriz, creamos una secuencia de enteros que se 
    //construira leyendo los numeros de la fila en cada posicion hasta num_col
    
	for (int i=0;i<num_fil;i++){ 
	
	    for (int j=0;j<num_col;j++){
	        cin >> elemento;
	        la_secuencia.Aniade(elemento);
	    }
	    
	    //Se Aniade la secuencia que representa una fila
	    tabla.Aniade(la_secuencia);
	    
	    //Vaciamos la secuencia para rellenar la siguiente fila
	    la_secuencia.EliminaTodos(); 
	    
	}
	
    
    
    // Mostrar tabla de datos en la que se realizarán las búsquedas
	
	cout << endl; 
	cout << tabla.ToString() << endl;  
	cout << endl; 


	/************************************************************************/
	// CALCULO: Crear y rellenar la secuencia "ausentes"
	//
	// Un valor "buscado" (MIN_VALOR <= buscado <= MAX_VALOR) se aniade a 
	// "ausentes" si no aparece en ninguna de las  filas de la tabla. 
	// La busqueda por fila se debe hacer, obligatoriamente, con el algoritmo 
	// de busqueda por interpolacion.
		
	SecuenciaEnteros ausentes; // Secuencia resultado
	
	bool encontrado; //¿Se ha encontrado en alguna fila el numero?
	int fil; //Contador para ir fila a fila
	
	//Se busca cada posible numero en la tabla para ver si esta ausente
	for (int buscado=MIN_VALOR;buscado<=MAX_VALOR;buscado++){
	    
        //Para cada numero, suponemos que no se encuentra en la tabla
        encontrado = false;
        //Para cada numero, comenzamos a buscar desde la fila 0
        fil = 0;
        
        while(!encontrado && fil<num_fil){
            
            //Si en alguna fila se encuentra el numero, acaba la busqueda
           if(tabla.Fila(fil).BusquedaInterpolacion(buscado,0,num_col)!= -1){
	           encontrado = true;
	       }
           else{
               fil++;
           } 
        }
        
        //Cuando se recorrando todas las filas de la tabla y no se haya 
        //encontrado
        if (!encontrado){
            ausentes.Aniade(buscado);
        }
	    
	}
	
	
	
	
	/************************************************************************/
	// SALIDA: Mostrar el contenido de la secuencia "ausentes"
		
	cout << endl; 
	cout << "Valores que NO aparecen en ninguna fila: " << endl; 
	cout << endl; 	
	cout << ausentes.ToString() << endl; 	
	cout << endl; 

	/************************************************************************/

	return 0;
}

/***************************************************************************/
/***************************************************************************/













