/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Ahora debera usar la clase Empleado para representar a los empleados. Debera
	diseñar la clase correctamente usando datos privados, constructores, métodos
	Set,métodos Get y otros métodos de gestión si fueran necesarios.
	Use un array de objetos Empleado para almacenar los empleados leidos.
	 
	Muestre su contenido después de leer los datos de los empleados. Calcule los 
	salarios mínimos y máximos, muestre sus valores y los nombres y apellidos de
	los empleados que ganan menos y más. Calcule el salario medio, muestre su 
	valor y después muestre un listado de los empleados cuyo salario es superior
	al salario medio.
	
	Entradas: Empleados
	Salidas: Datos sobre los empleados
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/
const int MAX_EMPLEADOS = 50; //Numero maximo de empleados
const char SEPARADOR = '*'; //Caracter de separacion entre datos
double SALARIO_MIN = 0; //Salario minimo
double SALARIO_MAX = 200000; //Salario Maximo


/*****************************************************************************
*							  FUNCIONES										 *
*****************************************************************************/
/*****************************************************************************
*Funcion pinta una linea con el caracter indicado
*Parametros: caracter a pintar, longitud de la linea
*****************************************************************************/
void Pinta_linea (char caracter, int longitud){
	while(longitud--){
		cout << caracter;
	}
	cout << endl;
}


/*****************************************************************************
*							   STRUCTS										 *
*****************************************************************************/
//Registro que permite expresar una fecha en formato dias/meses/anios
struct Fecha{
	int dia;
	int mes;
	int anio;
};


//Registro que contiene los datos de cada empleado
struct DatosEmpleado{
	string nombre;
	string apellido;
	Fecha fecha; //Fecha de nacimiento
	double salario;
};
/*****************************************************************************
*							   CLASES										 *
*****************************************************************************/
class Empleado{
private:
	DatosEmpleado un_empleado;
public:
	//Constructor
	Empleado(){
	}
	
	void RellenaDatos(string lista_empleados){

		int posicion = 0;
		
		//Extraemos el apellido
		un_empleado.apellido = Extraer_datos(lista_empleados,posicion);
		posicion += un_empleado.apellido.length()+1;
		
		//Extraemos el nombre
		un_empleado.nombre = Extraer_datos(lista_empleados,posicion);
		posicion += un_empleado.nombre.length()+1;
		
		//Extraemos la fecha
		string fecha = Extraer_datos(lista_empleados,posicion);
		un_empleado.fecha = RellenaFecha(fecha);
		posicion += fecha.length()+1;
		
		//Extraemos el sueldo
		string sueldo = Extraer_datos(lista_empleados,posicion);
		un_empleado.salario = stod(sueldo); //Lo pasamos a double
		posicion += sueldo.length()+1;
	
	}
	string Extraer_datos(string linea, int posicion){
		string dato;
		bool terminar = false;
		
		while (!terminar){
			if (linea[posicion]!=SEPARADOR){
				dato += linea[posicion];
				posicion++;
			}
			else{
				terminar = true;
			}
		}
		return dato;
	}
	/*************************************************************************
	*Funcion que rellena el registro que contiene la fecha de cada empleado
	*Parametros: Recibe el string que contiene la fecha de nacimiento del 
	*empleado datos de los empleados y el caracter separador que separa cada 
	*tipo de dato
	*Devuelve: Devuelve la fecha 
	*Pre_Condicion: La longitud de la cadena fecha deber ser 10 y el formato ha
	*de ser dd#mm#aaaa
	*		  ^	 ^
	*		  |	 |
	*	Un caracter de separacion valido distinto de SEPARADOR
	**************************************************************************/
	Fecha RellenaFecha (string cad_fecha)
	{
		Fecha una_fecha; 
		
		una_fecha.dia  = stoi(cad_fecha.substr(0,2));
		una_fecha.mes  = stoi(cad_fecha.substr(3,2));	  	
		una_fecha.anio = stoi(cad_fecha.substr(6,4));	 
		
		return una_fecha; 
	}

	/*************************************************************************
	*Funcion que convierte un dato del struct Fecha en un string
	*Parametros: Recibe la variable fecha
	*Devuelve: string de fecha con el formato deseado: dd mm aaaa
	**************************************************************************/
	string Fecha_a_texto (Fecha fecha)
	{
		const string MESES[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", 
								"Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
								
		string fecha_formato; //Formato: dd mes anio
		
		fecha_formato += to_string(fecha.dia) + " " + MESES[fecha.mes-1] + " " 
					+ to_string(fecha.anio);
		
		return fecha_formato; 
	}

	void SetNombre(string cadena){
		un_empleado.nombre = cadena;
	}
	void SetApellido(string cadena){
		un_empleado.apellido = cadena;
	}
	string GetNombre(void){
		return(un_empleado.nombre);
	}
	string GetApellido(void){
		return(un_empleado.apellido);
	}
	Fecha GetFecha(void){
		return(un_empleado.fecha);
	}
	double GetSalario(void){
		return(un_empleado.salario);
	}
	string ToString(){
		string cad;
		cad = "\n\t Nombre: " + un_empleado.nombre 
		+ "\n\t Apellido: " + un_empleado.apellido
		+ "\n\t Salario: " + to_string(un_empleado.salario)
		+ "\n\t Fecha de Nacimiento: " + Fecha_a_texto(un_empleado.fecha);

		return(cad);
	}
};




int main() //Programa principal
{
	Empleado empleados[MAX_EMPLEADOS];
	double salario_medio = 0; //Salario medio
	double salario_minimo = SALARIO_MAX; //Salario minimo
	double salario_maximo = SALARIO_MIN; //Salario maximo
	string cadena;
	int numero_empleado = 0;
	//Entrada de datos
	
	while (getline(cin,cadena)){ //Mientras se puedan leer lineas
	
		//Rellena los datos Empleado del empleado numero n
		empleados[numero_empleado].RellenaDatos(cadena);
		
		numero_empleado++; //Incrementa el contador de empleado
	}	
	
	//Mostramos los empleados

	for (int i = 0; i<numero_empleado;i++){
		cout << empleados[i].ToString() << endl;
	}
	
	cout << endl;
	Pinta_linea('_',50); //Separamos los datos para mejor legibilidad
	
	//Cálculos

	//Salarios Minimos

	int posicion_minimo; //Guarda la posicion del empleado

	for (int i=0;i<numero_empleado;i++){
		if (empleados[i].GetSalario() < salario_minimo){
			salario_minimo = empleados[i].GetSalario();
			posicion_minimo = i;
		} 
	}

	cout << "\nEl empleado con el minimo salario es: \n" 
		 << empleados[posicion_minimo].ToString() << endl;
		 
	Pinta_linea('_',50); //Separamos los datos para mejor legibilidad
	
	
	
	
	//Salarios Maximo

	int posicion_maximo; //Guarda la posicion del empleado

	for (int i=0;i<numero_empleado;i++){
		if (empleados[i].GetSalario() > salario_maximo){
			salario_maximo = empleados[i].GetSalario();
			posicion_maximo = i;
		} 
	}

	cout << "El empleado con el maximo salario es: \n" 
		 << empleados[posicion_maximo].ToString() << endl;
	
	Pinta_linea('_',50); //Separamos los datos para mejor legibilidad
	
	
	//Calculo del salario medio

	for (int i = 0; i<numero_empleado;i++){
		salario_medio += empleados[i].GetSalario(); //Sumamos todos los salarios
	}

	//Dividimos la suma de los salarios entre el numero total de empleados
	salario_medio /= numero_empleado;
	 
	cout << "El salario medio es: " << salario_medio << endl;

	Pinta_linea('_',50); //Separamos los datos para mejor legibilidad




	//Empleados con salario superior al medio

	cout << "Empleados con salario superior al medio: \n";
	for (int i = 0; i<numero_empleado;i++){
		if (empleados[i].GetSalario() > salario_medio){
			cout << empleados[i].ToString();
		}
	}

	return 0;
}

