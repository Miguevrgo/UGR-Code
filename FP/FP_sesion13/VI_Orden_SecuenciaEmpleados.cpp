/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Reescriba el ejercicio 24 de esta Relaci�n de Problemas para ordenar una
	colecci�n de datos de clase Empleado que contienen un dato de clase Fecha.
	Organice ahora los datos Empleado en una secuencia. Deber� crear la clase
	SecuenciaEmpleados y realizar las ordenaciones propuestas sobre la secuencia
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

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
*							   CLASES										 *
*****************************************************************************/


class Fecha{
private:
	int dia;
	int mes;
	int anio;
public:
	//Constructor
	Fecha(string cadena){
		RellenaFecha(cadena);
	}
	//Constructor vacio
	Fecha(){
		dia = 1;
		mes = 1;
		anio = 2000;
	}
	/*************************************************************************
	*Funcion que establece una fecha
	*Recibe: Dia, mes y anio
	**************************************************************************/
	void SetFecha(int un_dia = 1,int un_mes = 1,int un_anio = 2000){
		dia = un_dia;
		mes = un_mes;
		anio = un_anio;
	}

	/*************************************************************************
	*Funcion que rellena el registro que contiene la fecha de cada empleado
	*Parametros: Recibe el string que contiene la fecha de nacimiento del 
	*empleado
	*Pre_Condicion: La longitud de la cadena fecha deber ser 10 y el formato ha
	*de ser dd#mm#aaaa
	*		  ^	 ^
	*		  |	 |
	*	Un caracter de separacion valido distinto de SEPARADOR
	**************************************************************************/
	void RellenaFecha (string cad_fecha){

		dia  = stoi(cad_fecha.substr(0,2));
		mes  = stoi(cad_fecha.substr(3,2));	  	
		anio = stoi(cad_fecha.substr(6,4));	  
	}

	//Metodos Get

	int GetDia(void){
		return (dia);
	}

	int GetMes(void){
		return (mes);
	}

	int GetAnio(void){
		return (anio);
	}


	//Metodos Set

	void SetDia(int un_dia){
		dia = un_dia;
	}

	void SetMes(int un_mes){
		mes = un_mes;
	}

	void SetAnio(int un_anio){
		anio = un_anio;
	}
	
	/*************************************************************************
	*Funcion que convierte un dato Fecha en un string
	*Devuelve: string de fecha con el formato deseado: dd/mm/aaaa
	**************************************************************************/
	string ToString (void)
	{
		const string MESES[] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", 
								"Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};
								
		string fecha_formato; //Formato: dd/mes/anio
		
		fecha_formato += to_string(dia) + "/" + MESES[mes-1] + "/" 
					+ to_string(anio);
		
		return fecha_formato; 
	}

};



struct DatosEmpleado{

	string nombre;
	string apellido;
	Fecha fecha; //Fecha de nacimiento
	double salario;
	
};



class Empleado{
private:
	
	DatosEmpleado un_empleado;
	
public:
	
	//Constructor vacio necesario para crear un array con los empleados. No se
	//debe usar para nada mas
	Empleado(){}
	
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
		Fecha una_fecha(fecha);
		un_empleado.fecha = una_fecha;
		posicion += fecha.length()+1;
		
		//Extraemos el sueldo
		string sueldo = Extraer_datos(lista_empleados,posicion);
		un_empleado.salario = stod(sueldo); //Lo pasamos a double
		posicion += sueldo.length()+1;
		
	}

	/*************************************************************************
	*Funcion que extrae datos de un string en funcion de la posicion
	*Recibe: Posicion del elemento, string con el dato y separador
	*Devuelve: String con dato extraido
	**************************************************************************/
	string Extraer_datos(string linea, int posicion, char sep = SEPARADOR){
		string dato;
		bool terminar = false;
		 
		while (!terminar){
			if (linea[posicion]!=sep){
				dato += linea[posicion];
				posicion++;
			}
			else{
				terminar = true;
			}
		}
		return dato;
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
		+ "\n\t Fecha de Nacimiento: " + un_empleado.fecha.ToString();

		return(cad);
	}
};



class SecuenciaEmpleados{
private:
	Empleado empleados[MAX_EMPLEADOS];
	int numero_empleado = 0;
public:
	//Constructor sin parametros
	SecuenciaEmpleados(){
		RellenaDatos();
	}
	//Rellena Datos
	void RellenaDatos(void){
		string cadena;
		while (getline(cin,cadena)){ //Mientras se puedan leer lineas
		
			//Rellena los datos Empleado del empleado numero n
			empleados[numero_empleado].RellenaDatos(cadena);
			
			numero_empleado++; //Incrementa el contador de empleado
		}	
	}
	
	void OrdenaApellido(){
		for (int i=0;i<numero_empleado;i++){  
			// Comparaciones
			for(int j=0; j<numero_empleado-1; j++){
				int n=0;
				while(empleados[j].GetApellido()[n] == 
				empleados[j+1].GetApellido()[n]){
					n++; //Si los apellidos sin iguales miramos la letra para la 
					//que son diferentes y las comparamos	
				}
			// Intercambiamos los elementos
				if(empleados[j].GetApellido()[n] >
				 empleados[j+1].GetApellido()[n]){
					Empleado aux;
					aux = empleados[j];
					empleados[j]=empleados[j+1];
					empleados[j+1]=aux;
				}
			}	
		}
	}
	void OrdenaFecha(){
		for (int i=0;i<numero_empleado;i++){  
			// Comparaciones
			for(int j=0; j<numero_empleado-1; j++){
				Empleado aux;
				if(empleados[j].GetFecha().GetAnio() ==
				 empleados[j+1].GetFecha().GetAnio()){ 
					if (empleados[j].GetFecha().GetMes() == 
					empleados[j+1].GetFecha().GetMes()){ //=Mes
						if(empleados[j].GetFecha().GetDia() > 
						empleados[j+1].GetFecha().GetDia()){//Dia
							aux = empleados[j];
							empleados[j]=empleados[j+1];
							empleados[j+1]=aux;
						}
					}
					else if(empleados[j].GetFecha().GetMes() > 
					empleados[j+1].GetFecha().GetMes()){//>Mes
						aux = empleados[j];
						empleados[j]=empleados[j+1];
						empleados[j+1]=aux;
					}
				}
				else if(empleados[j].GetFecha().GetAnio() > 
				empleados[j+1].GetFecha().GetAnio()){//>Anio
					aux = empleados[j];
					empleados[j]=empleados[j+1];
					empleados[j+1]=aux;
				}
			}	
		}
	}
	void OrdenaSalario(){
		for (int i=0;i<numero_empleado;i++){  
			// Comparaciones
			for(int j=0; j<numero_empleado-1; j++){
			// Intercambiamos los elementos
				if(empleados[j].GetSalario() > empleados[j+1].GetSalario()){
					Empleado aux;
					aux = empleados[j];
					empleados[j] = empleados[j+1];
					empleados[j+1] = aux;
				}
			}	
		}
	}
	string ToString(void){
		string cad;
		for (int i=0;i<numero_empleado;i++){
			cad += 	empleados[i].ToString() + "\n\n";
		}
		return cad;
	}
};





int main() //Programa principal
{
	SecuenciaEmpleados una_secuencia;
	cout << una_secuencia.ToString();
	Pinta_linea('_',50); //Separamos los datos para mejor legibilidad
	
	
	una_secuencia.OrdenaApellido();
	cout << "\n\n" << una_secuencia.ToString();
	Pinta_linea('_',50); //Separamos los datos para mejor legibilidad
	
	
	una_secuencia.OrdenaSalario();
	cout << "\n\n" << una_secuencia.ToString();
	Pinta_linea('_',50); //Separamos los datos para mejor legibilidad
	
	
	una_secuencia.OrdenaFecha();
	cout << "\n\n" << una_secuencia.ToString();
	
	//C�lculos


	return 0;
}
