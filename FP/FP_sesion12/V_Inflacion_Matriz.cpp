/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Reescriba la solución del ejercicio 47 de la Relación de Problemas IV usando
	una clase, GestorIPC, que proporcione los valores del IPC y métodos para su 
	gestión. La estructura de la clase que proponemos es la indicada en la 
	figura 41. Los valores de las constantes estáticas, del array PAISES y de la
	matriz IPC puede consultarlos en la figura 27 en la que se mostraba el IPC 
	de varios paises entre 2001 y 2021.
	
	Entradas: Numero de anios 
	Salidas: Maximo y Minimo valor del IPC
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/
const int VALOR_MINIMO_IPC_MEDIO = -500; //Algun IPC medio tiene que ser mayor
const int VALOR_MAXIMO_IPC_MEDIO = 500; //Algun IPC medio tiene que ser menor
const int TERMINADOR = -1;
/*****************************************************************************
*							   STRUCTS										 *
*****************************************************************************/
struct InfoIPC {
	int indice_pais; // 0 <= indice_pais <= NUM_PAISES
	double valor_medio_IPC; // Maximo o minimo IPC medio (valor)
	int anio_inicio; // Primer año del periodo
	int num_anios; // Número de años del periodo
};
/*****************************************************************************
*							   CLASES										 *
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
		titulo = titulo + "(El numero debe ser mayor que " 
		+ to_string(menor) + " y menor que " + to_string(mayor) + "):";
		do{
			entero = LeeEntero();
			//Repetir mientras este fuera del intervalo
		}while ((entero > mayor || entero < menor) && entero != TERMINADOR); 
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



class GestorIPC{
private:

	static const int PRIMER_ANIO = 2001;
	static const int ULTIMO_ANIO = 2021;
	static const int NUM_ANIOS = ULTIMO_ANIO - PRIMER_ANIO + 1;
	static const int NUM_PAISES = 4;
	static const string PAISES[NUM_PAISES];
	static const double IPC[NUM_ANIOS][NUM_PAISES];
	

public:
	//Metodos de acceso para la lectura:

	int PrimerAnio(void){
		return (PRIMER_ANIO);
	}
	int UltimoAnio(void){
		return(ULTIMO_ANIO);
	}
	int NumAnios(void){
		return(NUM_ANIOS);
	}
	int NumPaises(void){
		return(NUM_PAISES);
	}

	/*************************************************************************
	*Funcion que devuelve el nombre de un pais
	*Parametros: Recibe la posicion en el array del pais(int)
	*Devuelve: Nombre del pais en la posicion indicada
	*Pre-condiciones: NUM_PAISES  >= pais >= 0 
	**************************************************************************/
	string NombrePais(int pais){
		
		return(PAISES[pais]);
	}

	/*************************************************************************
	*Funcion que devuelve el valor del IPC de un pais en un anio
	*Parametros: Anio y pais cuyo valor de IPC se quiere consultar
	*Devuelve: Valor del IPC del pais en el anio
	*Pre-condiciones: NUM_PAISES  >= pais >= 0 
	*				  PRIMER_ANIO <= anio <= ULTIMO_ANIO
	**************************************************************************/
	double ValorIPC(int anio, int pais){
		
		//Para mayor comodidad, la funcion recibe el anio exacto que queremos
		//y se ocupa de ajustar el dato para poder leerlo en el array
		//Por ejemplo: Si el usuario quiere saber el IPC en 2001, escribira 
		//2001 y la funcion devolvera el IPC[pais][0] que sera el valor en 2001
		
		anio -= PRIMER_ANIO;
		return(IPC[anio][pais]);
	}

	/*************************************************************************
	*Funcion que calcula el IPC medio de un pais en un periodo de anios
	*Parametros: Pais, anio de inicio y periodo sobre el que se va a calcular
	*Devuelve: IPC Medio del pais en el periodo
	*Pre-condiciones: el_primer_anio + los anios <= ULTIMO_ANIO
	**************************************************************************/
	double IPC_Medio_PaisPeriodo(int el_pais,int el_primer_anio,int los_anios){
		double suma_ipc=0; 
		int ultimo_anio = el_primer_anio + los_anios;
		for (int i=el_primer_anio;i<ultimo_anio ;i++){
			suma_ipc += ValorIPC(i,el_pais); //Sumatorio de los valores del IPC
		}
		return (suma_ipc/los_anios);
	}

	/*************************************************************************
	*Funcion que calcula el IPC medio maximo en un intervalo 
	*Parametros: Numero de anios del periodo
	*Devuelve: Struct con datos del pais con Mayor IPC medio en el periodo 
	*Pre-condiciones: num_anios <= NUM_ANIOS
	**************************************************************************/
	InfoIPC Info_IPC_MaxMedio_Periodo (int num_anios){
		InfoIPC max_periodo;
		max_periodo.valor_medio_IPC = VALOR_MINIMO_IPC_MEDIO;
		double ipc_periodo;

		for (int i=0;i<NUM_PAISES;i++){  //Bucle para recorrer cada pais
			//Queremos llamar a IPC_Medio_PaisPeriodo con la precondicion
			// de que el anio inicial + num_anios sea <= que el ULTIMO_ANIO
			for(int j=PRIMER_ANIO;j+num_anios<=ULTIMO_ANIO+1;j++){//Recorre anios
				ipc_periodo = IPC_Medio_PaisPeriodo(i,j,num_anios);
				if (ipc_periodo > max_periodo.valor_medio_IPC){
					max_periodo.indice_pais = i;
					max_periodo.valor_medio_IPC = ipc_periodo;
					max_periodo.anio_inicio = j;
					max_periodo.num_anios = num_anios;
				}
			} 
		}
		return (max_periodo);
	}

	/*************************************************************************
	*Funcion que calcula el IPC medio minimo en un intervalo 
	*Parametros: Numero de anios del periodo
	*Devuelve: Struct con datos del pais con Menor IPC medio en el periodo 
	*Pre-condiciones: num_anios <= NUM_ANIOS
	**************************************************************************/
	InfoIPC Info_IPC_MinMedio_Periodo (int num_anios){
		InfoIPC min_periodo;
		min_periodo.valor_medio_IPC = VALOR_MAXIMO_IPC_MEDIO;
		double ipc_periodo;

		for (int i=0;i<NUM_PAISES;i++){  //Bucle para recorrer cada pais
			//Queremos llamar a IPC_Medio_PaisPeriodo con la precondicion
			// de que el anio inicial + num_anios sea <= que el ULTIMO_ANIO
			for(int j=PRIMER_ANIO;j+num_anios<=ULTIMO_ANIO+1;j++){//Recorre anios
				ipc_periodo = IPC_Medio_PaisPeriodo(i,j,num_anios);
				if (ipc_periodo < min_periodo.valor_medio_IPC){
					min_periodo.indice_pais = i;
					min_periodo.valor_medio_IPC = ipc_periodo;
					min_periodo.anio_inicio = j;
					min_periodo.num_anios = num_anios;
				}
			} 
		}
		return(min_periodo);
	}
	
	/*************************************************************************
	*Funcion que devuelve los datos del IPC medido en el periodo 
	*Parametros: Struct InfoIPC
	*Devuelve: Cadena con datos del struct
	**************************************************************************/
	string Tostring(InfoIPC periodo){
		string cad;
		cad = "\tPais: " + NombrePais(periodo.indice_pais) 
		+ "\n\tValor IPC: " + to_string(periodo.valor_medio_IPC) 
		+ "\n\tAnio Inicio: " + to_string(periodo.anio_inicio) 
		+ "\n\tNumero de Anios: " + to_string(periodo.num_anios);

		return (cad);
	}
};
const string GestorIPC::PAISES[NUM_PAISES]={"Espania","Inglaterra","USA","Zona Euro"};
const double GestorIPC::IPC[NUM_ANIOS][NUM_PAISES]={
	/* ESP  ING   USA  ZEUR
	 ___  ___   ___  ____ */	
	{2.7, 1.07, 1.6, 22.1},{4, 1.69, 2.4, 2.3},{2.6, 1.25, 1.9, 2}, //01-03
	{3.2, 1.64, 3.3, 2.4},{3.7, 1.92, 3.4, 2.2},{2.7, 2.97, 2.5, 1.9},//04-06
	{4.2, 2.12, 4.1, 3.1},{1.4, 3.11, 0.1, 1.6},{0.8, 2.83, 2.7, 0.9},//07-09
	{3, 3.73, 1.5, 2.2},{2.4, 4.2, 3, 2.8},{2.9, 2.71, 1.7, 2.2},//10-12
	{0.3, 2, 1.5, 0.8},{-1, 0.55, 0.8, -0.2},{0, 0.23, 0.7, 0.2},//13-15
	{1.6, 1.6, 2.1, 1.1},{1.1, 2.9, 2.1, 1.3},{1.2, 2.1, 1.9, 1.5},//16-18
	{0.8, 1.3, 2.3, 1.3},{-0.5, 0.6, 1.4, -0.3},{6.5, 5.4, 7, -25}//19-21
	};


int main() //Programa principal
{
	int anios;
	bool terminar;

	//Entrada de datos
	while (!terminar){
		GestorIPC un_ipc;
		Lector una_lectura("");
		una_lectura.SetTitulo("Introduzca el anio (-1 para terminar): ");
		anios = una_lectura.LeeEnteroEnRango(2,5);

		terminar = (anios == TERMINADOR); //Si lee el terminador finaliza
		if (anios != TERMINADOR){
			
			cout << "\nMayor IPC medio: \n\n"
			 	 << un_ipc.Tostring(un_ipc.Info_IPC_MaxMedio_Periodo(anios))
				 << endl;
				 
			cout << "\nMenor IPC medio: \n\n"
			 	 << un_ipc.Tostring(un_ipc.Info_IPC_MinMedio_Periodo(anios))
				 << "\n\n";
		}	 
	}

	
	//Cálculos



	//Salida
	


	return 0;
}

