/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Un palíndromo es una secuencia que
	se lee igual de izquierda a derecha que de derecha a izquierda. Se pide que 
	defina un método que calcule y devuelva el palíndromo de mayor longitud 
	contenido en una secuencia. Dicho palíndromo siempre existe y será un objeto
	de la clase SecuenciaCaracteres
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/

/*****************************************************************************
*							   CLASES										 *
*****************************************************************************/
class SecuenciaCaracteres{
private:

	static const int TAM_MAX = 50; //Tamaño maximo secuencia de caracteres
	char vector_privado[TAM_MAX];

	//Pre-condicion: total_utilizados < TAM_MAX
	int total_utilizados; //Total de casillas utilizadas

public:
	//Constructor vacio
	SecuenciaCaracteres() : total_utilizados (0)
	{}
	//Constructor con argumentos
	SecuenciaCaracteres(string cadena) : total_utilizados (0)
	{
		for (int i=0; i<(int)cadena.length(); i++){
			AddElemento(cadena[i]);
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
	*Funcion que devuelve el caracter en la casilla indicada
	*Recibe: Posicion del elemento
	*Devuelve: caracter en la casilla indicada
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
	void InsertarElemento(char elemento, int posicion){
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
	*Funcion que modifica un caracter en una posicion
	*Recibe: Caracter y posicion
	*Pre-condicion: posicion < total_utilizados
	**************************************************************************/
	void ModificaElemento(int posicion, char caracter){
		if (posicion > 0){
			vector_privado[posicion] = caracter;
		}
	}

	/*************************************************************************
	*Funcion que añade un caracter nuevo al vector(Al final de la cadena)
	*Parametros: Recibe el caracter
	*Pre-condicion: Total utilizados < TAM_MAX
	**************************************************************************/
	void AddElemento(char caracter){
		if (total_utilizados < TAM_MAX){
			vector_privado[total_utilizados] = caracter;
			total_utilizados++;
		}
	}

	/*************************************************************************
	*Funcion que elimina todas las apariciones de un caracter a_borrar
	*Parametros: Recibe el caracter a_borrar
	**************************************************************************/
	void EliminaOcurrencias (char a_borrar){
		int puntero_leer = 0;
		int puntero_escribir = 0;
		
		while (puntero_leer < total_utilizados){
			if (vector_privado[puntero_leer] != a_borrar){
				//Si el apuntador de lectura(la posicion) es distinto del
				//caracter a borrar entonces simplemente avanza la posicion
				//Si es igual al caracter a borrar, se aumenta la posicion
				//Para que en la siguiente pasada se elimine automaticamente
				vector_privado[puntero_escribir] = vector_privado[puntero_leer];
				puntero_escribir++;
			}
			puntero_leer++;
		}
		//Si eliminamos posiciones hay que cambiar el total utilizados, en este
		//caso lo igualamos a puntero de escritura ya que este solo cambia
		//aumenta cuando el caracter es distinto del que queremos borrar
		total_utilizados = puntero_escribir;
	}
	
	/*************************************************************************
	*Funcion que elimina el exceso de blancos
	**************************************************************************/
	void EliminaExcesoBlancos(){
		int cont_espacios = 0; //Contador de los espacios
		int posicion; //Posicion en el array
		bool terminar = false;
		int pos_lectura;
		while (posicion < total_utilizados){
			if (vector_privado[posicion] != ' '){
				cont_espacios = 0;
				posicion++;
			}
			else{
				terminar = false;
				pos_lectura = posicion;
				posicion++;
				while (!terminar){
					if (vector_privado[pos_lectura] == ' '){
						cont_espacios++;
						pos_lectura++;
					}
					else{
						terminar = true;
						if(cont_espacios>1){
							for (int i=posicion;i<total_utilizados;i++){
								vector_privado[i] =
								vector_privado[i+cont_espacios-1]; 
							}
							total_utilizados -= (cont_espacios-1);	
						}
					}
				}
			} 
		}
	}
	//Funcion que comprueba si una secuencia de caracteres es un palindromo
	bool EsPalindromo(string cad){
		bool es_palindromo = true;
		if ((int)cad.length()<=1){
		}
		else{
			int j = cad.length();
			for (int i = 0; i<j; i++,j--){
				if (cad[i]!=cad[j-1]){
					es_palindromo = false;
				}
			}
		}
		return (es_palindromo);
	}

	SecuenciaCaracteres MayorPalindromoContenido(void){
		string palabra_mas_larga;
		string palabra;
		for (int i=0;i<total_utilizados;i++){
			palabra.clear();
			for (int j=i;j<total_utilizados;j++){
				palabra += vector_privado[j];
				if (EsPalindromo(palabra) && 
				palabra.length() > palabra_mas_larga.length()){
					palabra_mas_larga = palabra;
				}
			}

		}
		return (SecuenciaCaracteres(palabra_mas_larga));
	}

	/*************************************************************************
	*Funcion que devuelve un string con el vector
	*Devuelve: Cadena 
	**************************************************************************/
	string ToString(){
		string cad;
		for	(int i=0;i<total_utilizados;i++){
			cad += vector_privado[i];
		}
		return(cad);
	}
  
};

int main() //Programa principal
{
	

	//Entrada de datos
	
	SecuenciaCaracteres una_secuencia("gAAtySHHSvvABCCBAfh");
	SecuenciaCaracteres otra_secuencia
	= una_secuencia.MayorPalindromoContenido();
	cout << otra_secuencia.ToString();
	//Cálculos



	//Salida
	


	return 0;
}

