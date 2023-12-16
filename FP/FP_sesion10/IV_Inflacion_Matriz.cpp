/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Escriba un programa que solicite un número n de años (2 = n = 5) y muestre 
	qué pais (España, Inglaterra, USA ó Zona Euro) es el que 1) tiene el mayor 
	IPC medio en n años y 2) tiene el menor IPC medio en n años. Muestre además,
	sus valores y los años entre los que se han calculado los resultados.
	Repita hasta introducir un valor de n negativo.
	
	Entradas: valor de n(intervalo media anios)
	Salidas: IPC mayor,menor de cada pais, anios entre los que se ha realizado
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

const double IPC[][4]={
	/*
	 ESP  ING   USA  ZEUR
	 ___  ___   ___  ____ */	
	{2.7, 1.07, 1.6, 2.1},{4, 1.69, 2.4, 2.3},{2.6, 1.25, 1.9, 2}, //01-03
	{3.2, 1.64, 3.3, 2.4},{3.7, 1.92, 3.4, 2.2},{2.7, 2.97, 2.5, 1.9},//04-06
	{4.2, 2.12, 4.1, 3.1},{1.4, 3.11, 0.1, 1.6},{0.8, 2.83, 2.7, 0.9},//07-09
	{3, 3.73, 1.5, 2.2},{2.4, 4.2, 3, 2.8},{2.9, 2.71, 1.7, 2.2},//10-12
	{0.3, 2, 1.5, 0.8},{-1, 0.55, 0.8, -0.2},{0, 0.23, 0.7, 0.2},//13-15
	{1.6, 1.6, 2.1, 1.1},{1.1, 2.9, 2.1, 1.3},{1.2, 2.1, 1.9, 1.5},//16-18
	{0.8, 1.3, 2.3, 1.3},{-0.5, 0.6, 1.4, -0.3},{6.5, 5.4, 7, 5}//19-21
	
	};
	
	
/*****************************************************************************
*Funcion que lee un numero entero
*Parametros: string que indica el texto a mostrar para leer el numero
*Devuelve: Numero entero leido
*****************************************************************************/
int LeeEntero (string titulo){
	string entero;
	bool es_entero = true;
	do{
		cout << titulo; //Imprime el mensaje Introduzca la coordenada x
		cin >> entero;
		es_entero = true;
		//Comprobamos que el primer digito sea un numero entero o el signo -/+
		if ( ( isdigit(entero[0]) || entero[0] == 45 || entero[0] == 43) 
		== false){
			es_entero = false;
		}
		//Si el numero es: -/+
		else if ((entero[0] == 45 || entero[0] == 43 ) && entero.length() == 1){ 
			es_entero = false;
		}
		
		for (int i = 1; i < (int)entero.length(); i++){
			//Para cada posicion del string comprobamos si es un numero
			if (isdigit(entero[i]) == false){
				es_entero = false;
			}
		}	
	}while(!es_entero);
	return stoi(entero);
}


/*****************************************************************************
*Funcion que devuelve el IPC_Medio_Mayor de un pais en intervalos de n anios
*Parametros: valor del intervalo n y pais
*Devuelve: Valor medio del IPC mas grande del pais
*****************************************************************************/
double IPC_Medio_Mayor(int n, int pais){
	double IPC_aux;
	double IPC_mayor = 0;
	int anio = 0;
	bool terminar = false;
	while(!terminar){
		for (int i=0;i<n;i++){
			IPC_aux += IPC[anio][pais]; //Sumatorio de IPC
			if(anio<=20){ //Cuando el anio sea 20 ya no hay mas valores
				anio++; //Incrementa el anio
			}	
		}
		//Ajustamos el valor de anio para que pase por todos los anios
		anio = (anio-n+1);
		IPC_aux = IPC_aux/n; //Calculamos el IPC medio
		if (IPC_aux>IPC_mayor){
			IPC_mayor = IPC_aux; //IPC_mayor es la mayor media
		}
		IPC_aux = 0; //Reseteamos IPC_aux
		if (anio+n>21){
			terminar = true;
		}
	}
	return IPC_mayor;
}


/*****************************************************************************
*Funcion que devuelve el IPC_Medio_Menor de un pais en intervalos de n anios
*Parametros: valor del intervalo n y pais
*Devuelve: Valor medio del IPC mas pequenio del pais
*****************************************************************************/
double IPC_Medio_Menor(int n, int pais){
	double IPC_aux;
	double IPC_menor = 100000; //Valor basura para que IPC_aux sea menor 
	int anio = 0;
	bool terminar = false;
	while(!terminar){
		for (int i=0;i<n;i++){
			IPC_aux += IPC[anio][pais]; //Sumatorio de IPC
			if(anio<=20){ //Cuando el anio sea 20 ya no hay mas valores
				anio++; //Incrementa el anio
			}	
		}
		//Ajustamos el valor de anio para que pase por todos los anios
		anio = (anio-n+1); 
		IPC_aux = IPC_aux/n; //Calculamos el IPC medio
		if (IPC_aux<IPC_menor){
			IPC_menor = IPC_aux; //IPC_mayor es la mayor media
		}
		IPC_aux = 0; //Reseteamos IPC_aux
		if (anio+n>21){
			terminar = true;
		}
	}
	return IPC_menor;
}


int main() //Programa principal
{
	int n; //Numero de años
	bool n_correcto = false;
	bool terminar =false;
	double IPC_Mayor_Pais[4];
	double IPC_Menor_Pais[4];
	string Paises[]={"Espania","Inglaterra","USA","Zona Euro"};
	double IPC_Mayor_Absoluto; //Mayor IPC de todos los paises
	double IPC_Menor_Absoluto; //Menor IPC de todos los paises
	
	//Entrada de datos
	
	while (!terminar){
		IPC_Mayor_Absoluto = 0; //Reset valores
		IPC_Menor_Absoluto = 9000; //Reset valores
		do{
			n = 
			LeeEntero("Introduzca un numero(entre 2 y 5)(-1 para terminar)");
			n_correcto = (((n>=2) && (n<=5)) || (n<0));	
		}while(!n_correcto);
	
		terminar = n<0; //Si el numero leido es TERMINADOR termina
		if (n>0){
				for (int i=0;i<4;i++){
				IPC_Mayor_Pais[i]=IPC_Medio_Mayor(n,i);
				cout << "Mayor IPC " << Paises[i] << ": " << IPC_Mayor_Pais[i]
					 << "%\n";
				if (IPC_Mayor_Pais[i]>IPC_Mayor_Absoluto){
					IPC_Mayor_Absoluto = IPC_Mayor_Pais[i];
				}
			}
			
			cout << "Mayor IPC medio: " << IPC_Mayor_Absoluto << "%" << endl;
			
			cout << endl;
			
			for (int i=0;i<4;i++){
				IPC_Menor_Pais[i]=IPC_Medio_Menor(n,i);
				cout << "Menor IPC " << Paises[i] << ": " << IPC_Menor_Pais[i]
					 << "%\n";
				if (IPC_Menor_Pais[i]<IPC_Menor_Absoluto){
					IPC_Menor_Absoluto = IPC_Menor_Pais[i];
				}
			}
	
			cout << "Menor IPC medio: " << IPC_Menor_Absoluto << "%" << endl;
			
			cout << "\nEl IPC se ha calculado entre: " << endl;
			int anio = 2001; //Primer anio
			while (anio<=2021){
				if ((anio+n)<=2022){
					cout << anio << "-";
				}
				anio += n-1; //Restamos 1 por que el anio inicial se incluye 
				if ((anio)<=2021){
					cout << anio << " | ";	
				}	 
			}
			cout << endl;
		}
		cout << endl;		
	}


	return 0;
}

