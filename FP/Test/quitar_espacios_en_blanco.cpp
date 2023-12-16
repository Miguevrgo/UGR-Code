/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <string>
using namespace std;
string Quitaespacios(string cadena){
	bool terminar1 = false;
	bool terminar2 = false;
	while(!terminar1){
		if (cadena[0]== ' '){
			cadena.erase(0,1);
		}
		else{
			terminar1 = true;
		}
	}
	while(!terminar2){
		int longitud = cadena.end();
		if (cadena[longitud]== ' '){
			cadena.erase(longitud-1,longitud);
		}
		else{
			terminar2 = true;
		}
	}
	return cadena;
}


int main() //Programa principal
{
	string cadena;

	//Entrada de datos
	cout << "Cadena :";
	getline(cin,cadena);
	cout << cadena << endl;
	cout << Quitaespacios(cadena);

	return 0;
}

