/****************************************************************************

	Miguel Ángel De La Vega Rodríguez
	
	Aplicacion para cifrar y descifrar un mensaje
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/

/*****************************************************************************
*							    CLASES										 *
*****************************************************************************/
class Mensaje{
private:

	string cadena_cifrada; //Cadena de texto cifrada
	string cadena_descifrada; //Cadena de texto descifrada
	int modo; //Mensaje cifrado (1), Mensaje Descrifrado (2)

public:

	//Constructor sin argumentos
	Mensaje(){
		cadena_cifrada = "Cadena vacia entregada"
		cadena_descifrada = "Cadena vacia entregada"
	}

	//Constructor
	Mensaje(string cad,int opcion = 1){ //El modo por defecto es cifrado (1)
		if (opcion == 1){ //Recibe mensaje cifrado
			cadena_cifrada = cad;
		}
		else if (opcion == 2){ //Recibe mensaje descifrado
			cadena_descifrada = cad;
		}
		else{
			cout << "Error, los modos son Cifrado (1), Descifrado (2)";
		}
	}

	//Metodos Set

	void SetCifrada(string cad_cifrada){
		cadena_cifrada = cad_cifrada;
	}

	void SetDescifrada(string cad_descifrada){
		cadena_descifrada = cad_descifrada;
	}

	//Metodos Get

	string GetCifrada(void){return (cadena_cifrada)}

	string GetDescifrada(void){ return (cadena_descifrada)}

	int GetModo(void){return (modo)}

	//Metodo ToString
	string ToString(){
		string cad;
		cad = "Cadena Cifrada: " + cadena_cifrada +
		"\n Cadena Descifrada: " + cad_descifrada;
		return (cad);
	}


};

int main() //Programa principal
{
	

	//Entrada de datos
	
	
	
	//Cálculos



	//Salida
	


	return 0;
}

