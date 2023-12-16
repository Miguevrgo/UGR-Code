/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Realizar un programa que realice la conversión entre dos unidades de 
	distancia del SI. Las unidades contempladas serán: mm (milímetros), cm
	(centímetros), m (metros) y km (kilómetros).
	El programa mostrará el prompt > y el usuario escribirá cuatro tokens:
	valor unidad_inicial a unidad_final
	y el programa mostrará el resultado de la transformación. Por ejemplo, 
	si quisiéramos transformar 7 centímetros a metros escribiremos:

	
	Entradas: Valores de los tokens
	Salidas: Valor tras la conversion de unidades
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main()
{
	cout.setf(ios::fixed); //Establecemos la precision al imprimir los valores
	int valor;
	string unidad_inicial;
	string a;
	string unidad_final;
	const double MM_A_KM = 0.000001;
	const double MM_A_M = 0.001;
	const double MM_A_CM = 0.1;
	const double CM_A_KM = 0.00001;
	const double CM_A_M = 0.01;
	const double CM_A_MM = 10;
	const double M_A_KM = 0.001;
	const double M_A_CM = 100;
	const double M_A_MM = 1000;
	const double KM_A_M = 1000;
	const double KM_A_CM = 100000;
	const double KM_A_MM = 1000000;
	bool datos_correctos;
	int unidad;
	
	//Entrada de datos
	
	cout << "Conversion: ";
	cin >> valor;
	cin >> unidad_inicial;
	cin >> a;
	cin >> unidad_final;
	
	//Comprobacion datos introducidos correctos
	
	datos_correctos = ((valor>=0) && (a == "a") 
	&&((unidad_inicial == "km") || (unidad_inicial == "m") 
	|| (unidad_inicial == "cm") || (unidad_inicial == "mm"))
	&&((unidad_final == "km") || (unidad_final == "m")
	|| (unidad_final == "cm") || (unidad_final == "mm")));
	
	//Cálculos
	
	if (datos_correctos){
	
	//Asignamos al valor de unidad inicial un numero para poder dividir las
	//distintas estructuras condicionales segun el tipo de magnitud
	
	if (unidad_inicial == "cm"){
	  unidad = 1;		
	}

	if (unidad_inicial == "mm"){
	  unidad = 2;		
	}

	if (unidad_inicial == "m"){
	  unidad = 3;		
	}

	if (unidad_inicial == "km"){
	  unidad = 4;		
	}
	
	//Declaramos la clase TipoMagnitud
	
	enum class TipoMagnitud { km, m, cm, mm };
	
	TipoMagnitud magnitud;
	
	if (unidad_final == "km"){
		magnitud = TipoMagnitud::km;
	}
	else if (unidad_final == "m"){
		magnitud = TipoMagnitud::m;
	}
	else if (unidad_final == "cm"){
		magnitud = TipoMagnitud::cm;
	}
	else if (unidad_final == "mm"){
		magnitud = TipoMagnitud::mm;
	}
	
	if (unidad_inicial == unidad_final){
		cout << valor << unidad_inicial << " = " << valor << unidad_final;
	}
	else if (unidad == 1) {
		switch(magnitud){
			case (TipoMagnitud::cm):
			cout << valor << unidad_inicial << " = " << valor * MM_A_CM 
				 << unidad_final;
			break;
			case (TipoMagnitud::m):
			cout << valor << unidad_inicial << " = " << valor * MM_A_M 
				 << unidad_final;
			break;
			case (TipoMagnitud::km):
			cout << valor << unidad_inicial << " = " << valor * MM_A_KM 
				 << unidad_final;
			break;
		}
	}
	else if (unidad == 2) {
		switch(magnitud){
			case (TipoMagnitud::km):
			cout << valor << unidad_inicial << " = " << valor * CM_A_KM 
				 << unidad_final;
			break;
			case (TipoMagnitud::m):
			cout << valor << unidad_inicial << " = " << valor * CM_A_M 
				 << unidad_final;
			break;
			case (TipoMagnitud::mm):
			cout << valor << unidad_inicial << " = " << valor * CM_A_MM 
				 << unidad_final;
			break;
		}
	}
	else if (unidad == 3) {
		switch(magnitud){
			case (TipoMagnitud::km):
			cout << valor << unidad_inicial << " = " << valor * M_A_KM 
				 << unidad_final;
			break;
			case (TipoMagnitud::cm):
			cout << valor << unidad_inicial << " = " << valor * M_A_CM 
				 << unidad_final;
			break;
			case (TipoMagnitud::mm):
			cout << valor << unidad_inicial << " = " << valor * M_A_MM 
				 << unidad_final;
			break;
		}
	}
	else if (unidad == 4) {
		switch(magnitud){
			case (TipoMagnitud::m):
			cout << valor << unidad_inicial << " = " << valor * KM_A_M 
				 << unidad_final;
			break;
			case (TipoMagnitud::cm):
			cout << valor << unidad_inicial << " = " << valor * KM_A_CM 
				 << unidad_final;
			break;
			case (TipoMagnitud::mm):
			cout << valor << unidad_inicial << " = " << valor * KM_A_MM 
				 << unidad_final;
			break;
		}
	}
	
	}
	else{
		cout << "Los datos introducidos son incorrectos.";
	}
   return 0;
}
