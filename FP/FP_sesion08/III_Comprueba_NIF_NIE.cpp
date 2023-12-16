/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Escriba una función que verifique la validez de un NIF (de españoles 
	residentes mayores de edad) y del NIE (de extranjeros residentes en España).
	Escriba un programa que lea un número indefinido de NIFs/NIEs (finaliza 
	cuando se introduzca FIN) y verifique su validez.
	Modularice el programa adecuadamente, usando funciones.
	
	Entradas: NIF o NIE
	Salidas: NIF correcto o NIF incorrecto
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <string>

using namespace std;

char LetraNIF(int numero){
	string letra = "TRWAGMYFPDXBNJZSQVHLCKE";
	return letra[numero%23];
}
bool Escorrecta(string cadena,int numero){
	if (cadena.length() != 9){ 
		return 0; //El NIF es incorrecto
	}
	else{
		//Para ver si es correcto comparamos la ultima letra del NIF dado
		//Con la letra que deberia de tener de acuerdo con la funcion LetraNIF
		return (LetraNIF(numero) == toupper(cadena[8]));
	}
}

int main() //Programa principal
{
	string nif;
	string nie;
	bool termina = false;
	const double FIN = -1;
	
	//Entrada de datos
	
	while (!termina){
		cout << "Introduzca su NIF(-1 para TERMINAR): ";
		getline(cin,nif);
		int numero_nif = stoi(nif); 
		
		if (Escorrecta(nif,numero_nif)){
			cout << "El NIF es correcto\n";
		}
		   else{
			cout << "El NIF es incorrecto\n";
		}
	
		cout << "Introduzca su NIE(-1 para TERMINAR): ";
		getline(cin,nie);
			    
		if (nie[0] == toupper('x')){ //Si la primera letra es X
			nie[0] = '0';
		}
		else if (nie[0] == toupper('y')){ // Si la primera letra es Y
			nie[0] = '1';
		}
		else{ //Si la primera letra es Z o diferente(incorrecta)
			nie[0] = '2';
		}	
		int numero_nie = stoi(nie); 

		if (Escorrecta(nie,numero_nie)){
			cout << "El NIE es correcto\n";
		}
		else{
			cout << "El NIE es incorrecto\n";
		}
		termina = (stoi(nie) == FIN) || (stoi(nif) == FIN);		
	}
	cout << endl <<"Ha finalizado el programa";
	return 0;
}

