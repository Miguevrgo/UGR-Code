/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Reescriba el programa modificando únicamente la clase TablaDentadaEmpleados
	para que se base en una secuencia de secuencias de datos Empleado.


	
	

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
*Funcion que pinta una linea con el caracter indicado
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




class Empleado{
private:
	//Aquí use un struct dentro de la clase para los datos, interpretar las sucesivas funciones sin considerar el struct y considerando los 
	//datos miembro como datos privados separados ya que usar un struct
	// Es inadecuado
	string nombre;
	string apellido;
	Fecha fecha; //Fecha de nacimiento
	double salario;
	
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
		cad = "\t" + un_empleado.nombre + "\t" + un_empleado.apellido
		+ "\t " + to_string(un_empleado.salario) + "\t" 
		+ un_empleado.fecha.ToString();

		return(cad);
	}
};



class SecuenciaEmpleados{
private:
	Empleado empleados[MAX_EMPLEADOS]; 
	int numero_empleado = 0; //PRE: numero_empleado < 50 (MAX_EMPLEADOS)
public:
	//Constructor vacio
	SecuenciaEmpleados(){}
	//Constructor
	SecuenciaEmpleados(int num_empleados_fila){
		RellenaDato(num_empleados_fila);
	}

	//Rellena Datos
	//Recibe el numero de empleados en la secuencia
	void RellenaDato(int num_empleados_fila){
		string cadena;
		for (int i=0; i<num_empleados_fila;i++){
			getline(cin,cadena);
			//Rellena los datos Empleado del empleado numero n
			empleados[numero_empleado].RellenaDatos(cadena);
			
			numero_empleado++; //Incrementa el contador de empleado
		}
	}
	void Aniade_Elementos(Empleado un_empleado){
		empleados[numero_empleado] = un_empleado;
		numero_empleado++;	
	}
	
	Empleado Elemento(int posicion){
		return (empleados[posicion]);
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

	int TotalUtilizados(void){
		return numero_empleado;
	}

	string ToString(void){
		string cad;
		for (int i=0;i<numero_empleado;i++){
			cad += 	empleados[i].ToString() + "\n\n";
		}
		return cad;
	}
};

//Clase Pareja enteros, nos permite gestionar una pareja de numeros enteros
class ParejaEnteros{
private:

	int primero;
	int segundo;

public:

	//Constructor que recibe dos enteros
	ParejaEnteros(int a, int b) : primero(a),segundo(b){}

	void SetPrimero(int el_primero){ primero = el_primero; }
	void SetSegundo(int el_segundo){ segundo = el_segundo; }

	int GetPrimero(void){ return primero; }
	int GetSegundo(void){ return segundo; }

	string ToString(void){
		return ("{"+ to_string(primero) + "," + to_string(segundo) + "}");
	}

};

class TablaDentadaEmpleados {
private:

	static const int TAMANIO = 50; // "Filas" disponibles
	
	SecuenciaEmpleados vector_privado[TAMANIO];
	
	//PRE: 0 <= total_utilizados <= TAMANIO
	int total_utilizados; // Número de casillas ocupadas

public:
	// Constructor sin argumentos--> Crea matriz nula

	TablaDentadaEmpleados (void) : total_utilizados(0) { }

	/***********************************************************************/
	// Constructor--> Recibe una secuencia de empleados.  
	// PRE: total_utilizados < TAMANIO

	TablaDentadaEmpleados (SecuenciaEmpleados primera_fila)
		: total_utilizados(0)
	{
		Aniade(primera_fila); // Actualiza "filas_utilizadas"
	}

	void Aniade (SecuenciaEmpleados fila_nueva)
	{
		vector_privado[total_utilizados] = fila_nueva;
	}
	
	Empleado GetEmpleado(ParejaEnteros la_pareja){
		return vector_privado[la_pareja.GetPrimero()].
		Elemento(la_pareja.GetSegundo());
	}
	
	int TotalEmpleados(void){
		int total_empleados;
		for (int departamento = 0;departamento<total_utilizados;departamento++){
			total_empleados += vector_privado[departamento].TotalUtilizados();
		}
		return (total_empleados);
	}

	/*************************************************************************
	*Funcion que Localiza el menor salario de la lista de empleados
	*Devuelve: Posicion en la matriz del empleado (departamento y numero)
	**************************************************************************/
	ParejaEnteros LocalizacionSalarioMenor (void){
		double salario_menor = SALARIO_MAX; //Salario_menor < SALARIO_MAX
		double dpto_menor;
		double emp_menor;
		//Recorre todos los empleados de cada departamento en busca del empleado
		//Con menor salario
		for (int dpto=0; dpto < total_utilizados; dpto++ ){
			for (int emp=0; emp<vector_privado[dpto].TotalUtilizados();emp++){
				if (vector_privado[dpto].Elemento(emp).GetSalario() < salario_menor){
					salario_menor 
					= vector_privado[dpto].Elemento(emp).GetSalario();
					dpto_menor = dpto;
					emp_menor = emp;
				}
			}
		}
		return (ParejaEnteros(dpto_menor,emp_menor));
	}

	/*************************************************************************
	*Funcion que Localiza el mayor salario de la lista de empleados
	*Devuelve: Posicion en la matriz del empleado (departamento y numero)
	**************************************************************************/
	ParejaEnteros LocalizacionSalarioMayor (void){
		double salario_mayor = SALARIO_MIN; //Salario_mayor > SALARIO_MIN
		double dpto_mayor;
		double emp_mayor;
		//Recorre todos los empleados de cada departamento en busca del empleado
		//Con mayor salario
		for (int dpto=0; dpto < total_utilizados; dpto++ ){
			for (int emp=0; emp<vector_privado[dpto].TotalUtilizados();emp++){
				if (vector_privado[dpto].Elemento(emp).GetSalario() > 
				salario_mayor){
					salario_mayor = 
					vector_privado[dpto].Elemento(emp).GetSalario();
					dpto_mayor = dpto;
					emp_mayor = emp;
				}
			}
		}
		return (ParejaEnteros(dpto_mayor,emp_mayor));
	}

	double SalarioMedio (void){
		double salario_medio = 0;
		double total_empleados = TotalEmpleados();
		for (int dpto=0; dpto < total_utilizados; dpto++ ){
			for (int emp=0; emp<vector_privado[dpto].TotalUtilizados();emp++){
				salario_medio += 
				vector_privado[dpto].Elemento(emp).GetSalario();
			}
		}
		double sueldo = salario_medio/total_empleados;
		return (sueldo);
	}

	SecuenciaEmpleados EmpleadosSalarioMenor (double valor){
		SecuenciaEmpleados la_secuencia;
		for (int dpto=0; dpto < total_utilizados; dpto++ ){
			for (int emp=0; emp<vector_privado[dpto].TotalUtilizados();emp++){
				if (vector_privado[dpto].Elemento(emp).GetSalario()<valor){
					la_secuencia.Aniade_Elementos
					(vector_privado[dpto].Elemento(emp));
				}
			}
		}
		return (la_secuencia);
	}
	
	SecuenciaEmpleados EmpleadosSalarioMayor (double valor){
		SecuenciaEmpleados la_secuencia;
		for (int dpto=0; dpto < total_utilizados; dpto++ ){
			for (int emp=0; emp<vector_privado[dpto].TotalUtilizados();emp++){
				if (vector_privado[dpto].Elemento(emp).GetSalario() > valor){
					la_secuencia.Aniade_Elementos
					(vector_privado[dpto].Elemento(emp));
				}
			}
		}
		return (la_secuencia);
	}
	
	string ToString_Departamentos(int departamento){
		string cad = "Departamento: " + to_string(departamento+1) + "\n\n";
		for (int j=0;j<vector_privado[departamento].TotalUtilizados();j++){
			cad += vector_privado[departamento].Elemento(j).ToString() + "\n";
		}
		return(cad); 
	}
	string ToString(){
		string cad;

		for (int i=0;i<total_utilizados;i++){
			for (int j=0;j<vector_privado[i].TotalUtilizados();j++){
				cad += vector_privado[i].Elemento(j).ToString() + "\n";
			} 
		}
		return cad;
	}

};

int main() //Programa principal
{	
	string departamentos; //Numero de departamentos
	string num_empleados_dpto;  //Numero de empleados por departamento

	TablaDentadaEmpleados una_tabla;
	getline(cin,departamentos);

	for (int i=0;i<stoi(departamentos);i++){
		getline(cin,num_empleados_dpto);
		una_tabla.Aniade(SecuenciaEmpleados(stoi(num_empleados_dpto)));
	}
	cout << "Hasta aqui";
	cout << "LISTADO DE EMPLEADOS: \n";
	cout << "\nNumero de empleados: "<< una_tabla.TotalEmpleados() << "\n";
	cout << una_tabla.ToString() << "\n";
	Pinta_linea('_',50); //Separamos los datos para mejor legibilidad
	
	cout << "LISTADO DE EMPLEADOS POR DEPARTAMENTO: \n";
	for (int i=0;i<stoi(departamentos);i++){
		cout << una_tabla.ToString_Departamentos(i);
	}
	Pinta_linea('_',50); //Separamos los datos para mejor legibilidad
	
	cout << "\nEmpleado salario mayor: \n";
	cout 
	<< una_tabla.GetEmpleado(una_tabla.LocalizacionSalarioMayor()).ToString()
	<< "\n"; 
	
	Pinta_linea('_',50); //Separamos los datos para mejor legibilidad
	cout << "\n\nEmpleado salario menor: \n";
	cout 
	<< una_tabla.GetEmpleado(una_tabla.LocalizacionSalarioMenor()).ToString();
	
	cout << "\nSueldo medio:" << una_tabla.SalarioMedio() << "\n";
	cout << "\nEmpleados con salario mayor: \n" 
	<< una_tabla.EmpleadosSalarioMayor(una_tabla.SalarioMedio()).ToString();
	
	cout << "\nEmpleados con salario menor: \n" 
	<< una_tabla.EmpleadosSalarioMenor(una_tabla.SalarioMedio()).ToString();
	
	


	return 0;
}
