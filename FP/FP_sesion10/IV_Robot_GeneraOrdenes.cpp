/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Se pide implementar un programa (directamente en la funci�n main) para que, 
	dada una posici�n inicial pos y una lista de �rdenes ord de longitud lon, 
	haga lo siguiente:
	� Si la serie de �rdenes es correcta, muestre cu�ntas veces se visit� 
	cada posici�n.
	� Si la serie de �rdenes NO es correcta, el programa terminar� indicando 
	cu�ntas �rdenes se pudieron ejecutar.
	
	Entradas: posicion inicial, longitud de instrucciones e instrucciones
	Salidas: Posiciones tablero
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

using namespace std;

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


int main() //Programa principal
{
	int Tablero[100]; //100 Posiciones que guardan el numero de veces pasadas
	int pos;
	int lon;
	string ord;
	int instrucciones = 0; //Numero de instrucciones
	bool error = false;
	//Entrada de datos
	
	do{
		pos = LeeEntero("Posicion Inicial: ");	
	}while(pos<1 || pos>100);
	
	do{
		lon = LeeEntero("Longitud: ");	
	}while(lon<0);
	
	cout << "Ordenes(D:derecha|I:izquierda): ";
	cin >> ord;
	for (int i=0;i<lon;i++){
		ord[i] = toupper(ord[i]);	
	}
	for (int i=0;i<100;i++){
		Tablero[i] = 0;	
	}
	Tablero[pos] = 1;
	
	for (int i=0;i<lon;i++){
		if (ord[i] == 'D'){
			pos++;
		}
		else{
			pos--;
		}
			
		if (pos<=100 && pos>=1){
			instrucciones++; //Incrementa instrucciones
		}
		else{
			error = true;
		}
		Tablero[pos] += 1; //Pasa una vez por esa posicion
	}	

	
	if (error==true){
		cout << "Serie de ordenes: incorrecta" << endl;
		cout << "Se ejecutaron " << instrucciones << " ordenes";
	}
	else{
		cout << "Serie de ordenes: correcta" << endl;
		cout << "Frecuencia de visitas por posicion: " << endl;
		for (int i=0;i<100;i++){
			if (Tablero[i] > 0){
				cout << "(" << i << "," << Tablero[i] <<")  ";
			}
		}
	}

	return 0;
}

