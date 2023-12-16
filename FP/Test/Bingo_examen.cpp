/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
/*	
	Bingo
	
	Versión aceptable para el examen.
	
	Incluye para la clase SecuenciaEnteros:   
	
	1) Constructor de una secuencia aleatoria (sin valores repetidos). 
	
		SecuenciaEnteros (int n_casillas, int min, int max); 
	
			donde "n_casillas" es número de casillas que se van a ocupar y 
			"min" y "max" son los valores mínimo y máximo de los num. 
			aleatorios que se generan. 
	
	2) Método que devuelve una secuencia aleatoria (sin valores repetidos).  
	
		void SecuenciaAleatoria (int min, int max);  
	
			donde "min" y "max" son los valores mínimo y máximo de los num. 
			aleatorios que se generan. 
			La secuencia tendrá el mismo tamaño que la secuencia inmplícita. 
*/
/***************************************************************************/

//#define DEBUG

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>

#include <random>  // para la generación de números pseudoaleatorios
#include <chrono>  // para la semilla

using namespace std;

/***************************************************************************/
// Convierte el dato int "entero" a un string con "num_casillas" casillas 
// que contiene el valor textual de "entero".
// 
// Recibe: 	entero, el valor a transformar.
//			num_casillas, número total de casillas que tendrá el resultado.
//			relleno, el carácter que se emplea para rellenar los huecos. 
//
// Devuelve: el string compuesto.  
//
// NOTAS: Si el número de casillas solicitado es mayor que el que se necesita, 
//	  	se completa al principio con "relleno" hasta alcanzar un tamaño de 
//	  	"num_casillas". Si el valor tuviera "per se" más de "num_casillas" 
//		se devuelve tal cual.  

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

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class SecuenciaEnteros {

private:

    static const int TAMANIO = 100; // Núm.casillas disponibles
    int vector_privado[TAMANIO];

    // PRE: 0<=total_utilizados<=TAMANIO

    int total_utilizados; // Núm.casillas ocupadas

public:

    /***********************************************************************/
    // Constructor sin argumentos

    SecuenciaEnteros (void) : total_utilizados (0)
    {}
    
    /***********************************************************************/
    // Constructor de una secuencia aleatoria (sin valores repetidos). 
	// Recibe:
	//		n_casillas, número de casillas que se van a ocupar.
	//		min, mínimo valor posible \ 
	//		max, mánimo valor posible / de los num. aleatorios que se generan
	
	SecuenciaEnteros (int n_casillas, int min, int max) : total_utilizados (0)
	{
		// Rellenar el vector con valores aleatorios entre "min" y "max"
	 
		GeneradorAleatorioEnteros generador	(min, max);
			
		while (total_utilizados < n_casillas) {
	    	int valor = generador.Siguiente();
	    	if (!Contiene(valor)) Aniade(valor);
		}
	}	

    /***********************************************************************/
    // Devuelve el número de casillas ocupadas

    int TotalUtilizados (void)
    {
        return (total_utilizados);
    }

    /***********************************************************************/
    // Devuelve el número de casillas disponibles

    int Capacidad (void)
    {
        return (TAMANIO);
    }

    /***********************************************************************/
    // Añade un elemento ("nuevo") al vector.
    // PRE: total_utilizados < TAMANIO
    // 		La adición se realiza si hay alguna casilla disponible.
    // 		El nuevo elemento se coloca al final del vector.
    // 		Si no hay espacio, no se hace nada.

    void Aniade (int nuevo)
    {
        if (total_utilizados < TAMANIO) {
            vector_privado[total_utilizados] = nuevo;
            total_utilizados++;
        }
    }

    /***********************************************************************/
    // Devuelve el elemento de la casilla "indice"
    // PRE: 0 <= indice < total_utilizados

    int Elemento (int indice)
    {
        return (vector_privado[indice]);
    }

    /***********************************************************************/
    // Eliminar el Jugador de la posición dada por "indice".
    // Realiza un borrado físico (desplazamiento y sustitución).
    // PRE: 0 <= indice < total_utilizados

    void Elimina (int indice)
    {
        if ((indice >= 0) && (indice < total_utilizados)) {

            int tope = total_utilizados-1; // posic. del último

            for (int i = indice ; i < tope ; i++)
                vector_privado[i] = vector_privado[i+1];

            total_utilizados--;
        }
    }
 
    /***********************************************************************/
    // Sustituye el entero de la posición dada por "indice" por "nuevo".
    // PRE: 0 <= indice < total_utilizados

    void Sustituye (int indice, int nuevo)
    {
        if ((indice >= 0) && (indice < total_utilizados)) {
			vector_privado[indice] = nuevo;
        }
    }
 
    /***********************************************************************/
    // Indica si el dato "buscado" pertenece a la secuencia.
    
    bool Contiene (int buscado) 
	{
    	int pos = 0; 
		bool encontrado = false; 
		
		while (pos<total_utilizados && !encontrado)	
			if (vector_privado[pos] == buscado) encontrado = true; 
			else pos++;
			
		return encontrado; 
	}

    /***********************************************************************/
    // Devuelve una secuencia aleatoria (sin valores repetidos). 
	// Recibe:
	//		min, mínimo valor posible \ 
	//		max, mánimo valor posible / de los num. aleatorios que se generan
	
	void SecuenciaAleatoria (int min, int max) 
	{
		SecuenciaEnteros nueva (total_utilizados, min, max);
	
        for (int i = 0 ; i < total_utilizados ; i++)
            vector_privado[i] = nueva.vector_privado[i];
	}	
	
    /***********************************************************************/
    // Compone un string con todos los caracteres que están
    // almacenados en la secuencia y lo devuelve.

    string ToString (int datos_linea=10)
    {    	
        string cadena;
		string separador; 
	
        for (int i=0; i<total_utilizados; i++) {
			separador = (((i+1)%datos_linea == 0) ? "\n": "");
            cadena = cadena + ToStringInt(vector_privado[i],4) + separador;
		}

        return (cadena);
    }
 
	/***********************************************************************/
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class Carton 
{
private:

	static const int MENOR =  1; 
	static const int MAYOR = 90; 
	
	static const int FILS = 3; // Filas y columnas del cartón
	static const int COLS = 9; 
	
	static const int TACHADO = 0; // La casilla ha sido tachada
	
	string id_carton;		// Matrícula o identificador único del cartón
	 
	int matriz[FILS][COLS];	// Valores del cartón 
	
	// PRE: MENOR <= matriz[f][c] <= MAYOR 
	//		para f=0,1,...,FILS-1   c=0,1,...,COLS-1
	// PRE: No hay valores repetidos en "matriz"
	
public: 

	/***********************************************************************/
	// Constructores
	 
	Carton (void) : id_carton ("") { }
		 
	Carton (string identificador) : id_carton (identificador)	
	{
		RellenaCarton (); 
	}
	
	/***********************************************************************/
	// Métodos Get
	
	string GetIdentificador (void) { return id_carton; } 

	int NumFilas    (void) { return FILS; }
	int NumColumnas (void) { return COLS; }
	
	/***********************************************************************/
	// Calcula si el cartón contiene un número dado. 
	
	bool Contiene (int numero) 
	{
		bool encontrado = false; 
	
		int f = 0; 
		while (f<FILS && !encontrado) {
			int c = 0;
			while (c<COLS && !encontrado) 		
				if (matriz[f][c]==numero) encontrado = true; 			
				else c++;
			if (!encontrado) f++; 
		}
		return encontrado; 
	}

	/***********************************************************************/
	// Tacha un número del cartón 
	// PRE: Contiene(numero)==true ("numero" está en el carton) 
	
	void Tacha (int numero) 
	{
		bool encontrado = false; 
	
		int f,c; 
		
		f = 0; 
		while (f<FILS && !encontrado) {
			c = 0;
			while (c<COLS && !encontrado) 		
				if (matriz[f][c]==numero) encontrado = true; 			
				else c++;
			if (!encontrado) f++; 
		}
		
		matriz[f][c]=TACHADO;  
	}
	
	/***********************************************************************/
	// Calcula si toda la fila "fila" está tachada
	
	bool FilaTachada (int fila) 
	{
		bool todos_tachados = true;
		
		int c = 0; 
		while (c<COLS && todos_tachados) 	
			if (matriz[fila][c] != TACHADO) todos_tachados = false; 			
			else c++;				
		
		return todos_tachados;
	}
	
	/***********************************************************************/
	// Calcula si hay alguna linea
	
	bool HayLinea (void) 
	{
		bool hay_linea = false; 
		
		int f = 0; 
		while (f<FILS && !hay_linea) 
			if (FilaTachada(f)) hay_linea = true; 	
			else f++; 
		
		return hay_linea;
	}
	
	/***********************************************************************/
	// Calcula si hay bingo 
	
	bool HayBingo (void) 
	{
		bool hay_bingo = true; 
		
		int f = 0; 
		while (f<FILS && hay_bingo) {
			if (!FilaTachada(f)) hay_bingo = false; 
			else f++; 				
		}
		
		return hay_bingo;
	}

	/***********************************************************************/
	// Devuelve el número de casillas pendientes de ser tachadas
	
	int NumCasillasSinTachar (void)
	{
		int cont = 0; 
		
		for (int f=0; f<FILS; f++)
			for (int c=0; c<COLS; c++)
				if (matriz[f][c] != TACHADO) cont++;
		
		return cont; 
	}

	/***********************************************************************/
	// Devuelve el número de casillas tachadas
	
	int NumCasillasTachadas (void)
	{
		int cont = 0; 
		
		for (int f=0; f<FILS; f++)
			for (int c=0; c<COLS; c++)
				if (matriz[f][c] == TACHADO) cont++;
		
		return cont; 
	}
	
	/***********************************************************************/
	// Calcula si el objeto "Carton" implícito es menor que "otro".
	// Criterio: Numero de casillas sin tachar.

	bool EsMenor (Carton otro)
	{
		return (NumCasillasSinTachar() < otro.NumCasillasSinTachar()); 
	}

	/***********************************************************************/
	// Calcula si el objeto "Carton" implícito es mayor que "otro".
	// Criterio: Numero de casillas tachadas.

	bool EsMayor (Carton otro)
	{
		return (NumCasillasTachadas() > otro.NumCasillasTachadas()); 
	}
	
	/***********************************************************************/
	// Serializa un dato "Carton"
	
	string ToString (void)
	{
		string cad = "Id = " + id_carton + "\n"; 
		
		for (int fila=0; fila<FILS; fila++) {
			
			for (int col=0; col<COLS; col++) {
	
				string valor; 
			
				if (matriz[fila][col] == TACHADO) valor = "  -  ";
				else valor = ToStringInt(matriz[fila][col], 5);
		
				cad = cad + valor;  
			}
			cad = cad + "\n";
		}
		return cad; 
	}
	
private: 

	/***********************************************************************/
	// Rellena el campo "id_carton"

	void SetIdentificador (string el_id_carton) { id_carton = id_carton; } 
	
	/***********************************************************************/
	// Rellena el cartón con números aleatorios
	
	void RellenaCarton (void)
	{
		SecuenciaEnteros numeros_carton (FILS*COLS, MENOR, MAYOR);		
		
		int pos = 0; 
		
		for (int f=0; f<FILS; f++) {
			
			for (int c=0; c<COLS; c++) {
	
				matriz[f][c] = numeros_carton.Elemento(pos); 
				pos++;
				
			} // for c	
				
		} // for f
	}

	/***********************************************************************/	
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class SecuenciaCartones {

private:

    static const int TAMANIO = 100; // Núm.casillas disponibles
    Carton vector_privado[TAMANIO];

    // PRE: 0<=total_utilizados<=TAMANIO

    int total_utilizados; // Núm.casillas ocupadas

public:

    /***********************************************************************/
    // Constructor sin argumentos

    SecuenciaCartones (void) : total_utilizados (0) {}

    /***********************************************************************/
    // Devuelve el número de casillas ocupadas

    int TotalUtilizados (void)
    {
        return (total_utilizados);
    }

    /***********************************************************************/
    // Devuelve el número de casillas disponibles

    int Capacidad (void)
    {
        return (TAMANIO);
    }

    /***********************************************************************/
    // Añade un elemento ("nuevo") al vector.
    // PRE: total_utilizados < TAMANIO
    // 		La adición se realiza si hay alguna casilla disponible.
    // 		El nuevo elemento se coloca al final del vector.
    // 		Si no hay espacio, no se hace nada.

    void Aniade (Carton nuevo)
    {
        if (total_utilizados < TAMANIO){
            vector_privado[total_utilizados] = nuevo;
            total_utilizados++;
        }
    }

    /***********************************************************************/
    // Devuelve el elemento de la casilla "indice"
    // PRE: 0 <= indice < total_utilizados

    Carton Elemento (int indice)
    {
        return (vector_privado[indice]);
    }

    /***********************************************************************/
    // Eliminar el Jugador de la posición dada por "indice".
    // Realiza un borrado físico (desplazamiento y sustitución).
    // PRE: 0 <= indice < total_utilizados

    void Elimina (int indice)
    {
        if ((indice >= 0) && (indice < total_utilizados)) {

            int tope = total_utilizados-1; // posic. del último

            for (int i = indice ; i < tope ; i++)
                vector_privado[i] = vector_privado[i+1];

            total_utilizados--;
        }
    }
 
    /***********************************************************************/
    // Sustituye el Jugador de la posición dada por "indice" por "nuevo".
    // PRE: 0 <= indice < total_utilizados

    void Modifica (int indice, Carton nuevo)
    {
        if ((indice >= 0) && (indice < total_utilizados)) {
			vector_privado[indice] = nuevo;
        }
    }
 
    /***********************************************************************/
 	// Devuelve una copia ordenada creciente de la secuencia.
	  
 	SecuenciaCartones Ordena (void) 
 	{
 		// Copiar la secuencia implícita en "copia", que será la secuencia 
 		// que se va a ordenar. 
 		// En Metodología se resumirá este proceso con: 
		// 		SecuenciaCartones copia = *this;
 		
		SecuenciaCartones copia; 
		
		for (int i=0; i<total_utilizados; i++)
			copia.vector_privado[i] = vector_privado[i];
		copia.total_utilizados = total_utilizados; 
	
		// Ordenar (burbuja)  
			
		for (int izda = 0; izda < copia.total_utilizados; izda++)
		
			for (int i = copia.total_utilizados-1 ; i > izda ; i--) {
			
				if (copia.vector_privado[i].EsMenor(copia.vector_privado[i-1])) 
				{  
			        Carton tmp = copia.vector_privado[i-1];
					copia.vector_privado[i-1] = copia.vector_privado[i];
			        copia.vector_privado[i] = tmp;
				}

			} // for i
		
		return copia; 
	}
	
    /***********************************************************************/
 	// Devuelve una copia orenada decreciente de la secuencia.
	  
 	SecuenciaCartones OrdenaDecreciente (void) 
 	{
 		// Copiar la secuencia implícita en "copia", que será la secuencia 
 		// que se va a ordenar. 
 		// En Metodología se resumirá este proceso con: 
		// 		SecuenciaCartones copia = *this;
 		
		SecuenciaCartones copia; 
		
		for (int i=0; i<total_utilizados; i++)
			copia.vector_privado[i] = vector_privado[i];
		copia.total_utilizados = total_utilizados; 
	
		// Ordenar (burbuja)  
			
		for (int izda = 0; izda < copia.total_utilizados; izda++)
		
			for (int i = copia.total_utilizados-1 ; i > izda ; i--) {

				if (copia.vector_privado[i].EsMayor(copia.vector_privado[i-1])) 
				{  
			        Carton tmp = copia.vector_privado[i-1];
					copia.vector_privado[i-1] = copia.vector_privado[i];
			        copia.vector_privado[i] = tmp;
				}

			} // for i
		
		return copia; 
	}
	
    /***********************************************************************/
    // Compone un string con todos los datos que están almacenados en la 
	// secuencia y lo devuelve.

    string ToString()
    {
        string cadena;

        for (int i=0; i<total_utilizados; i++)
            cadena = cadena + vector_privado[i].ToString() + "\n";

        return (cadena);
    }
 
	/***********************************************************************/
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/***************************************************************************/
/***************************************************************************/

int main (void) 
{		 
	// Crear y rellenar la secuencia de cartones que participan en el juego.
	
	SecuenciaCartones cartones; 
	
	// Solución rápida: creación de cartones y adición directa. //
	/*	
	cartones.Aniade(Carton("001"));
	cartones.Aniade(Carton("002"));
	cartones.Aniade(Carton("003"));
	cartones.Aniade(Carton("004"));
	cartones.Aniade(Carton("005"));
	cartones.Aniade(Carton("006"));
	*/
	
	// Solución pedida en el enunciado. 
	
	const string FINALIZADOR = "FIN";
	string id_carton_leido; 
		
	cout << "Introzduzca id. carton num. " 
	     << setw(3) << cartones.TotalUtilizados()+1 << ": ";
	cin >> id_carton_leido; 
	
	while (id_carton_leido != FINALIZADOR && 
	       cartones.TotalUtilizados() < cartones.Capacidad()) {
		
		cartones.Aniade(Carton(id_carton_leido));

		cout << "Introzduzca id. carton num. " 
		     << setw(3) << cartones.TotalUtilizados()+1 << ": ";
		cin >> id_carton_leido; 
	}
	
	if (cartones.TotalUtilizados() == cartones.Capacidad()) {
		cout << endl; 
		cout << "Se ha completado el numero maximo de cartones." << endl; 
		cout << endl; 			
	}
	
	cout << endl; 
	cout << "Se han leido " 
	     << setw(3) << cartones.TotalUtilizados() << " cartones." << endl; 
	cout << endl; 	
	cout << cartones.ToString();
	cout << endl; 
	
	
	// Como puede haber más de una línea y bingo en la misma jugada, 
	// se guardan los cartones agraciados en sendas secuencias. 
	
	SecuenciaCartones cartones_bingo; 
	SecuenciaCartones cartones_linea; 
	

	// Crear y rellenar "bombo", la lista de bolas en el orden que que 
	// saldrían del bombo.
	// IMPORTANTE: No se repiten los números. 

	const int MENOR =  1; 
	const int MAYOR = 90; 
	const int NUM_MAX_BOLAS = MAYOR-MENOR+1; // 90

	/*
		Si no dispusiéramos del constructor indicado: 
		
		SecuenciaEnteros (int n_casillas, int min, int max);
		  
		podría usarse una lista de bolas extraidas (vacía inicialmente) 
		y generarse números aleatorios uno a uno, y si no está en la lista,  
		guardarlo para no volver a procesarlo si saliera posteriormente.				
	 	
	GeneradorAleatorioEnteros generador (MENOR,MAYOR);
	
	SecuenciaEnteros bombo; 
	
	while (bombo.TotalUtilizados() < NUM_MAX_BOLAS) {
	
		int numero = generador.Siguiente();
		if (!bombo.Contiene(numero)) bombo.Aniade(numero);
	}
	*/

	SecuenciaEnteros bombo (NUM_MAX_BOLAS, MENOR, MAYOR);	
	int tamanio_bombo = bombo.TotalUtilizados(); 
	
	
	// Comprobación de integridad sobre el contenido del bombo
	// (Nunca debería ser cierta la condición)
	
	if (tamanio_bombo != NUM_MAX_BOLAS) {
		cerr << "ERROR DE INTEGRIDAD: "; 
		cerr << "Numero incorrecto de bolas en el bombo." << endl; 
		cerr << "Debia contener " << setw(3) << NUM_MAX_BOLAS; 
		cerr << " y contiene " << setw(3) << tamanio_bombo << endl; 
		cerr << endl; 
		exit(1);
	}
	
	cout << endl; 
	cout << "Secuencia de numeros en el bombo (" 
		 << setw(4) << bombo.TotalUtilizados() << " bolas) = " << endl; 
	cout << bombo.ToString(15) << endl; 
	
	
	/*......................................................................*/
	// Juego	
	
	bool cantado_bingo   = false; // true: terminar el juego.
	bool linea_permitida = true;  // false: no se permite cantar más líneas.
	
	int num_jugada = 0; // Jugada en curso 
	
	while (!cantado_bingo && num_jugada < tamanio_bombo) {
		
		num_jugada++; 
		
		// "Extraer" el número con el que se juega en esta iteración
		
		int numero = bombo.Elemento(num_jugada-1); 
		
		cout << endl; 
		cout << "........................................" << endl; 		
		cout << "Extraccion " << setw(3) << num_jugada << ". ";
		cout << "Numero = " << setw(3) << numero << endl; 
		cout << endl; 


		bool hay_linea = false; 

		// Se exploran, por orden, todos los cartones
		
		for (int pos=0; pos<cartones.TotalUtilizados(); pos++) {
			
			Carton carton_actual =  cartones.Elemento(pos);
			string id_carton_actual = carton_actual.GetIdentificador();
			
			cout << "CARTON: " << setw(10) << id_carton_actual;
		
			// Si el número está en el cartón, tacharlo y después 
			// comprobar si hay línea y bingo. 
				
			if (carton_actual.Contiene(numero)) {
				
				cout << " --> EXITO" << endl;

				carton_actual.Tacha(numero);
				cartones.Modifica (pos, carton_actual);
				
				
				#ifdef DEBUG
				cout << endl;
				cout << "TACHADO " + ToStringInt(numero, 3) << endl;
				cout << carton_actual.ToString() << endl; 
				#endif
				
				if (carton_actual.HayLinea() && linea_permitida) {

					hay_linea = true; 
					cartones_linea.Aniade(carton_actual);

					cout << endl;
					cout << "===> LINEA EN " << id_carton_actual 
					     << " <==="<< endl;
					cout << endl;					
				}
				
				if (carton_actual.HayBingo()) {

					cantado_bingo = true; // La iteracion actual será la última 
					
					// Carton premiado: añadir a lista de premiados con bingo 
					// y quitarlo de la lista de los no premiados.
					cartones_bingo.Aniade(carton_actual); 
										
					cout << endl;
					cout << "===> BINGO EN " << id_carton_actual 
					     << " <===" << endl;
					cout << endl;
				}
				
			} // if (carton_actual.Contiene(numero))
			
			else  cout << " --> NADA" << endl;
			
		} // for pos
		
		if (hay_linea) linea_permitida = false; 
		
	} // while (!cantado_bingo && num_jugada < tamanio_bombo)
	

	cout << endl; 
	cout << "........................................" << endl; 		
	cout << endl; 

	cout << "Se extrajeron " << setw(3) << num_jugada << " bolas." << endl; 
	cout << endl; 

	if (!cantado_bingo) {
		cout << "ERROR DE INTEGRIDAD: NADIE HA CANTADO BINGO" << endl; 
		exit(2); 
	}
	
	
	/*......................................................................*/
	// Resumen del estado de los cartones
	
	cout << endl; 
	cout << "........................................" << endl; 		
	cout << endl; 
	cout << "Estado final: " << endl;  
	cout << endl; 
   	
	for (int pos=0; pos<cartones.TotalUtilizados(); pos++) {
	
		Carton carton_actual =  cartones.Elemento(pos);
		
		cout << setw(10) << carton_actual.GetIdentificador() 
			 << " --> casillas pendientes = " << setw(3) 
			 << carton_actual.NumCasillasSinTachar() << endl; 			
		
	} // for 
	
	cout << endl; 
	for (int pos=0; pos<cartones.TotalUtilizados(); pos++) 
		cout << cartones.Elemento(pos).ToString() << endl; 
	cout << endl; 


	// Cartones no premiados con bingo. Inicialmente, todos.
	
	SecuenciaCartones cartones_sin_bingo = cartones; 

	for (int pos=0; pos<cartones_sin_bingo.TotalUtilizados(); pos++) 

		// Si tiene bingo, eliminarlo.
		
		if (cartones_sin_bingo.Elemento(pos).NumCasillasSinTachar() == 0) 
			cartones_sin_bingo.Elimina(pos); 


	/*......................................................................*/
	// Informe de pagos

	cout << endl; 
	cout << "........................................" << endl; 		
	cout << endl; 
	cout << "Informe de pagos. " << endl;  
	cout << endl; 
		
	cout << "Lineas cantadas = " << setw(2) 
		 << cartones_linea.TotalUtilizados() << endl; 
	
	cout << "Pagar linea a los cartones:" << endl; 
	for (int i=0; i<cartones_linea.TotalUtilizados(); i++) 
		cout << "\t" << cartones_linea.Elemento(i).GetIdentificador() << endl; 
	cout << endl; 

	cout << endl; 
	cout << "Cartones sin bingo = " << setw(2) 
		 << cartones_sin_bingo.TotalUtilizados() << endl; 
	cout << "Bingos cantados    = " << setw(2) 
		 << cartones_bingo.TotalUtilizados() << endl; 
	
	cout << "Pagar bingo a los cartones:" << endl; 
	for (int i=0; i<cartones_bingo.TotalUtilizados(); i++) 
		cout << "\t" << cartones_bingo.Elemento(i).GetIdentificador() << endl; 
	cout << endl; 

   	
	/*......................................................................*/
   	// Ranking de jugadores no premiados (1)
   	
   	cout << endl; 
	cout << "........................................" << endl; 		
	cout << endl; 
	cout << "Ranking de los cartones que no han cantado bingo: " << endl;  
	cout << endl; 
	
	cout << "Orden creciente por numeros pendientes. " << endl; 
	cout << endl; 

	SecuenciaCartones ordenados = cartones.Ordena(); 

	for (int pos=0; pos<ordenados.TotalUtilizados(); pos++) {
	
		Carton carton_actual = ordenados.Elemento(pos);
		
		if (carton_actual.NumCasillasSinTachar() > 0) {
		// if (!carton_actual.HayBingo()) {
			
			cout << setw(10) << carton_actual.GetIdentificador() 
			     << " --> casillas pendientes = " << setw(3) 
				 << carton_actual.NumCasillasSinTachar() << endl; 			
		}
		
	} // for 
		
	cout << endl; 

	cout << "Orden decreciente por numeros tachados. " << endl; 
	cout << endl; 
	
	SecuenciaCartones ordenados_tachados_dec = cartones.OrdenaDecreciente(); 
	int num_casillas = Carton().NumFilas()*Carton().NumColumnas();  

	for (int pos=0; pos<ordenados_tachados_dec.TotalUtilizados(); pos++) {
	
		Carton carton_actual = ordenados_tachados_dec.Elemento(pos);
		
		if (carton_actual.NumCasillasTachadas() != num_casillas) {
			
			cout << setw(10) << carton_actual.GetIdentificador() 
			     << " --> casillas tachadas = " << setw(3) 
				 << carton_actual.NumCasillasTachadas() << endl; 			
		}
		
	} // for 
	
	cout << endl; 
	
	cout << "........................................" << endl; 		
	cout << endl; 


	/*......................................................................*/
   	// Ranking de jugadores no premiados (2)
   	
   	cout << endl; 
	cout << "........................................" << endl; 		
	cout << endl; 
	cout << "Ranking de los cartones que no han cantado bingo: " << endl;  
	cout << endl; 
	
	cout << "Orden decreciente por numeros tachados. " << endl; 
	cout << endl; 
	
	SecuenciaCartones ordenados_sin_premio = 
					  cartones_sin_bingo.OrdenaDecreciente(); 

	for (int pos=0; pos<ordenados_sin_premio.TotalUtilizados(); pos++) {
	
		Carton carton_actual = ordenados_sin_premio.Elemento(pos);
					
		cout << setw(10) << carton_actual.GetIdentificador() 
			 << " --> casillas tachadas = " << setw(3) 
			 << carton_actual.NumCasillasTachadas() << endl; 			
		
	} // for 
	
	cout << endl; 
	
	cout << "........................................" << endl; 		
	cout << endl; 
	
	return 0;	
}

/***************************************************************************/
/***************************************************************************/

