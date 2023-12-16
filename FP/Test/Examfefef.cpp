/*******************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	
	
	Entradas: 
	Salidas: 
	
	

*******************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

/*******************************************************************************
*                           CONSTANTES GLOBALES								   *
*******************************************************************************/

/*******************************************************************************
*							     FUNCIONES										   *
*******************************************************************************/



string FuncionQuegira(string cad){
	int longitud = cad.length();
	string nueva;
	while (longitud--){
		nueva += cad[longitud];
	}
	return nueva;	
}

int FuncionQuegira(double numero){
	string cad;
	int longitud = 1;
	while (numero/10>1 || numero/10<0){
		longitud++;
		numero /= 10;
	}
	return longitud;
}


/*******************************************************************************
*							      CLASES										   *
*******************************************************************************/

int main() //Programa principal
{
	string cadena = "HOLA ME LLAMO ANTONIO";
	string cadena3 = "HOLA ME LLAMO JOSE";
	double num =456.56;
	cout << cadena << "\n";
	cout << FuncionQuegira(cadena);
	
	cout << "\n______________________________________________\n";
	cout << cadena3 << "\n";
	cout << FuncionQuegira(num);
	//Entrada de datos
	
	
	
	//Cálculos



	//Salida
	


	return 0;
}

