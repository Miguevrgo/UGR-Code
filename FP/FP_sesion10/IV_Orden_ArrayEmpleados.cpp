/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Debe escribir un programa para mostrar un listado ordenado (ascendente) de
	los empleados. Use redirección de entrada para la lectura de los datos. 
	Guarde los datos en un (único) array.
	La ordenación deberá poder realizarse por cualquiera de los campos indicados
	(salario, apellidos o fecha de nacimiento) aunque la versión que se 
	compilará, tal cual se entregue, será la que ordena por el salario.
	El programa, no obstante, debe poder modificarse para obtener la ordenación 
	por los otros criterios con el mínimo número de cambios posibles y evitando 
	la repetición de código.
	Realice las pruebas necesarias para asegurar que se realizan correctamente 
	todas las ordenaciones. Cada vez que cambie el criterio de ordenación 
	deberá recompilar el programa, necesariamente. Asegúrese de que los cambios 
	realizados son mínimos y razonables.

	Entradas: Datos de los empleados
	Salidas: Empleados ordenados
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

const char SEPARADOR = '*'; //Caracter de separacion entre datos

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


/****************************************************************************
*Funcion que convierte un dato del struct Fecha en un string
*Parametros: Recibe la variable fecha
*Devuelve: string de fecha con el formato deseado: dd mm aaaa
*****************************************************************************/
string Fecha_a_texto (Fecha fecha)
{
	const string MESES[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", 
							"Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
							
	string fecha_formato; //Formato: dd mes anio
	
	fecha_formato += to_string(fecha.dia) + " " + MESES[fecha.mes-1] + " " 
				  + to_string(fecha.anio);
	
	return fecha_formato; 
}


/****************************************************************************
*Funcion que rellena el registro que contiene la fecha de cada empleado
*Parametros: Recibe el string que contiene la fecha de nacimiento del empleado 
*datos de los empleados y el caracter separador que separa cada tipo de dato
*Devuelve: Devuelve
*Pre_Condicion: La longitud de la cadena fecha deber ser 10 y el formato ha
*de ser dd#mm#aaaa
*		  ^	 ^
*		  |	 |
*	Un caracter de separacion valido distinto de SEPARADOR
*****************************************************************************/
Fecha RellenaFecha (string cad_fecha)
{
	Fecha una_fecha; 
	
	una_fecha.dia  = stoi(cad_fecha.substr(0,2));
	una_fecha.mes  = stoi(cad_fecha.substr(3,2));	  	
	una_fecha.anio = stoi(cad_fecha.substr(6,4));	 
	
	return una_fecha; 
}


/****************************************************************************
*Funcion que extrae datos de una linea que le pasamos sabiendo el delimitador
*que indica el final del dato y la posicion que indica el principio
*Parametros: Recibe el string que contiene las lineas donde se guardan los 
*datos de los empleados, el caracter SEPARADOR y la posicion de inicio
*Devuelve: Devuelve un string con el dato extraido
*****************************************************************************/
string Extraer_datos(string linea, int posicion)
{
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


/****************************************************************************
*Funcion que rellena el registro que contiene los datos de cada empleado
*Parametros: Recibe el string que contiene las lineas donde se guardan los 
*datos de los empleados y el caracter separador que separa cada tipo de dato
*Devuelve: Un dato tipo DatosEmpleado
*****************************************************************************/
DatosEmpleado RellenaDatos(string lista_empleados)
{
	DatosEmpleado un_empleado;
	
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
	un_empleado.salario = stod(sueldo); //Lo pasamos a int
	posicion += sueldo.length()+1;
	
	return un_empleado;
}


/****************************************************************************
*Funcion imprime en pantalla los datos de el empleado N
*Parametros: Recibe la variable struct del empleado a mostrar
*****************************************************************************/
void Pinta_empleados(DatosEmpleado empleado)
{
	cout.fill(' ');
	cout.width(22); //Ancho del campo Apellido
	cout << empleado.apellido << "\t";
	cout.width(20); //Ancho del campo Nombre
	cout << empleado.nombre << "\t";
	cout.width(12); //Ancho del campo fecha
	cout << Fecha_a_texto(empleado.fecha) << "\t";
	cout.width(5); //Ancho del campo salario
	cout << empleado.salario << "\n";
}


int main() //Programa principal
{
	string cadena; //Cadena que se va a leer
	int numero_empleado = 0; //Contador de empleado
	
	const int MAX_EMPLEADOS = 50; //Numero maximo de empleados
	
	//Declaramos un array del struct DatosEmpleado para guardar los datos de
	//Cada empleado
	DatosEmpleado empleado[MAX_EMPLEADOS]; 
	
	//Entrada de datos
	
	while (getline(cin,cadena)){ //Mientras se puedan leer lineas
	
		//Rellena los datos del struct Datos Empleado del empleado numero n
		empleado[numero_empleado] = RellenaDatos(cadena);
		
		numero_empleado++; //Incrementa el contador de empleado
	}	
	
	
	
	//Ordenacion por sueldo bruto (Metodo Burbuja)

	
	for (int i=0;i<numero_empleado;i++){  
		// Comparaciones
		for(int j=0; j<numero_empleado-1; j++){
		// Intercambiamos los elementos
			if(empleado[j].salario > empleado[j+1].salario){
				DatosEmpleado aux;
				aux = empleado[j];
				empleado[j]=empleado[j+1];
				empleado[j+1]=aux;
			}
		}	
	}
	cout << "\nEmpleados Ordenados por salario: \n";
	for (int i=0; i<numero_empleado;i++){
		Pinta_empleados(empleado[i]);	
	}
	
	
	
	//Ordenacion por apellidos
	
	for (int i=0;i<numero_empleado;i++){  
		// Comparaciones
		for(int j=0; j<numero_empleado-1; j++){
			int n=0;
			while(empleado[j].apellido[n] == empleado[j+1].apellido[n]){
				n++; //Si los apellidos sin iguales miramos la letra para la 
				//que son diferentes y las comparamos	
			}
		// Intercambiamos los elementos
			if(empleado[j].apellido[n] > empleado[j+1].apellido[n]){
				DatosEmpleado aux;
				aux = empleado[j];
				empleado[j]=empleado[j+1];
				empleado[j+1]=aux;
			}
		}	
	}
	cout << "\nEmpleados Ordenados por Apellido: \n";
	for (int i=0; i<numero_empleado;i++){
		Pinta_empleados(empleado[i]);	
	}
	
	
	//Ordenacion por fecha de nacimiento
	
	for (int i=0;i<numero_empleado;i++){  
		// Comparaciones
		for(int j=0; j<numero_empleado-1; j++){
			DatosEmpleado aux;
			if(empleado[j].fecha.anio == empleado[j+1].fecha.anio){ //Mismo anio
				if (empleado[j].fecha.mes == empleado[j+1].fecha.mes){ //=Mes
					if(empleado[j].fecha.dia > empleado[j+1].fecha.dia){//Dia
						aux = empleado[j];
						empleado[j]=empleado[j+1];
						empleado[j+1]=aux;
					}
				}
				else if(empleado[j].fecha.mes > empleado[j+1].fecha.mes){//>Mes
					aux = empleado[j];
					empleado[j]=empleado[j+1];
					empleado[j+1]=aux;
				}
			}
			else if(empleado[j].fecha.anio > empleado[j+1].fecha.anio){//>Anio
				aux = empleado[j];
				empleado[j]=empleado[j+1];
				empleado[j+1]=aux;
			}
		}	
	}
	cout << "\nEmpleados Ordenados por Fecha de Nacimiento: \n";
	for (int i=0; i<numero_empleado;i++){
		Pinta_empleados(empleado[i]);	
	}
	
	return 0;
}

