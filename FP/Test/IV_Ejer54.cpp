/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Unifique en un único programa las tareas realizadas en los ejercicios 35 y 
	36 de esta misma relación de problemas, pero guardando los NIFs/NIEs 
	localizados en matrices de datos char en lugar de usar arrays de string.
	Deberá usar dos matrices, una para los NIFs/NIEs correctos y otra para los 
	NIFs/NIEs incorrectos. Cada fila tendrá, en consecuencia, 9 columnas.
	
	Entradas: NIF/NIEs
	Salidas: NIF/NIEs validos o invalidos
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <string>

using namespace std;


/****************************************************************************
*Funcion que devuelve el ultimo caracter que tiene que tener un NIF
*Parametros: Recibe el numero del NIF 
*Devuelve: El caracter que debe tener el NIF para el numero dado
*****************************************************************************/
char LetraNIF(int numero)
{
	string letra = "TRWAGMYFPDXBNJZSQVHLCKE";
	return letra[numero%23];
}


/****************************************************************************
*Funcion que calcula si un NIF podria ser valido sin tener en cuenta la letra
*Parametros: Recibe el string que contiene el NIF 
*Devuelve: Si podria ser valido sin tener en cuenta la letra
*****************************************************************************/
bool Podria_ser_valido(string cadena)
{
	int longitud = cadena.length(); //Longitud de la cadena
	if (longitud >= 8){
		if (longitud == 10){
			bool va_seguido_de_caracter = (cadena[9]=='.'|| cadena[9]=='.' 
								   		|| cadena[9] == ';');
			return va_seguido_de_caracter;
		}
		else if (longitud == 9 || longitud == 8){
			bool numero_valido = true;
			//Para comprobar si los 8 primeros caracteres son digitos si hubiese
			//tambien caracter de letra hay que ignorarlo
			if (longitud == 9){ 
				longitud--;
			}
			while (longitud--){
				if (!isdigit(cadena[longitud])){
					numero_valido = false;
				}
			}
			return numero_valido;
		}
		else{
			return 0; //Si es mayor que 10
		}
	}
	else{
		return 0; //Si la longitud es menor que 8 entonces no es valido
	}
	
}


/****************************************************************************
*Funcion que comprueba si un NIF es correcto
*Parametros: Recibe el string que contiene el NIF y el numero del mismo
*Devuelve: Si el NIF es correcto
*****************************************************************************/
bool Escorrecta(string cadena,int numero)
{
	int longitud = cadena.length(); //Longitud de la cadena
	bool va_seguido_de_caracter = false;
	if (longitud < 9){ 
		return 0; //El NIF es incorrecto
	}
	else if (longitud == 9){
		//Para ver si es correcto comparamos la ultima letra del NIF dado
		//Con la letra que deberia de tener de acuerdo con la funcion LetraNIF
		return (LetraNIF(numero) == toupper(cadena[8]));
	}
	else{
		//Si la longitud es mayor de 9 hay que comprobar si el caracter tras la
		//Letra es un punto,coma o punto-coma:
		va_seguido_de_caracter = (cadena[9]=='.'|| cadena[9]=='.' 
							   || cadena[9] == ';');
		if (va_seguido_de_caracter){
			return (LetraNIF(numero) == toupper(cadena[8]));
		}
		else{
			return 0; //Si longitud > 9 y no va seguido de . , ; es incorrecto
		}
	}
}



int main() //Programa principal
{
	const int MAX_NIF_NIE = 100;
	string nif;
	string nie;
	bool termina = false;
	const double FIN = -1;
	char NIF_NIE_correctos[MAX_NIF_NIE][9]; // 9 columnas
	char NIF_NIE_incorrectos[MAX_NIF_NIE][9]; // 9 columnas
	int contador_correctos = 0;
	int contador_incorrectos = 0;
	//Entrada de datos
	
	while (!termina){
		cout << "Introduzca su NIF(-1 para TERMINAR): ";
		getline(cin,nif);
		int numero_nif = stoi(nif); 
		if (numero_nif != FIN){ //Si NIF es -1 no comprueba si es correcto
			if (Escorrecta(nif,numero_nif)){
				cout << "El NIF es correcto\n";
				for (int i = 0;i<9;i++){
					NIF_NIE_correctos[contador_correctos][i] = nif[i];
				}
				contador_correctos++;
			}
			else{
				for (int i = 0;i<9;i++){
					NIF_NIE_incorrectos[contador_incorrectos][i] = nif[i];
				}
				contador_incorrectos++;
				if (Podria_ser_valido(nif)){
					cout << "Error ultimo caracter o en letra\n";	
				}
				else{
					cout << "El NIF es incorrecto\n";	
				}	
			}
		}
		
		if (numero_nif != FIN){ //Si NIF es -1 termina programa
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
				for (int i = 0;i<9;i++){
					NIF_NIE_correctos[contador_correctos][i] = nie[i];
				}
				contador_correctos++;
			}
			else{
				for (int i = 0;i<9;i++){
					NIF_NIE_incorrectos[contador_incorrectos][i] = nie[i];
				}
				contador_incorrectos++;
				if (Podria_ser_valido(nie)){
					cout << "Error ultimo caracter o en letra\n";	
				}
				else{
					cout << "El NIE es incorrecto\n";
				}
			}	
		}	    	
		
		termina = (stoi(nie) == FIN) || (stoi(nif) == FIN);
				
	}
	
	cout << endl <<"Ha finalizado el programa" << endl;
	cout << "NIF/NIEs Correctos: \n";
	for (int i=0; i<contador_correctos;i++){
		for (int j=0;j<9;j++){
			cout << NIF_NIE_correctos[i][j];
		}
		cout << endl;
	}
	
	cout << "NIF/NIEs Incorrectos: \n";
	for (int i=0; i<contador_incorrectos;i++){
		for (int j=0;j<9;j++){
			cout << NIF_NIE_incorrectos[i][j];
		}
		cout << endl;
	}
	return 0;
}

