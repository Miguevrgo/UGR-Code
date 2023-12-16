/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Se pide implementar un programa que lea la posición inicial pos (fila y 
	columna, por separado) y la secuencia de órdenes a ejecutar. Le recomendamos
	que use un dato string, p.e. cad_ordenes para la lectura. Si el string es 
	correcto, el array ord se rellenará a partir de cad_ordenes, siendo lon la 
	longitud de cad_ordenes.
	
	Entradas: posicion inicial, longitud de instrucciones e instrucciones
	Salidas: Posiciones tablero
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <vector>

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
	const int MAX_FIL = 10;
	const int MAX_COL = 10;
	int Tablero[MAX_FIL][MAX_COL]; //Tablero 10x10
	int f; //Fila
	int c; //Columna
	const int LON = 5;
	char ord[LON];
	string cad_ordenes;
	int instrucciones = 0; //Numero de instrucciones
	bool error = false;
	//Entrada de datos
	
	do{
		f = LeeEntero("Fila Inicial: ");	
	}while(f<1 || f>10);
	
	do{
		c = LeeEntero("Columna Inicial: ");	
	}while(c<1 || c>10);
	
	cout << "Ordenes(D:derecha|I:izquierda|A:arriba|B:bajo): ";
	cin >> cad_ordenes;
	for (int i=0;i<LON;i++){
		ord[i] = cad_ordenes[i];
		ord[i] = toupper(ord[i]);	
	}
	//Inicializamos el tablero a 0
	for (int i=0;i<MAX_FIL;i++){
		for (int j=0;j<MAX_COL;j++){
			Tablero[i][j] = 0;
		}		
	}
	
	Tablero[f][c] = 1; //Pos inicial
	
	for (int i=0;i<LON;i++){
		bool correcto = false;
		if (ord[i] == 'D'){
			c++; //Derecha
		}
		else if (ord[i] == 'I'){
			c--; //Izquierda
		}
		else if (ord[i == 'A']){
			f--; //Abajo
		}
		else{
			f++; //Arriba
		}
		//Comprobamos que no se pasa de el limite
		correcto = ((f >=1) && (f<=MAX_FIL) && (c>=1) && (c<=MAX_COL));	
		if (correcto){
			instrucciones++; //Incrementa instrucciones
		}
		else{
			error = true;
		}
		Tablero[f][c] += 1; //Pasa una vez por esa posicion
	}	

	
	if (error==true){
		cout << "Serie de ordenes: incorrecta" << endl;
		cout << "Se ejecutaron " << instrucciones << " ordenes";
	}
	else{
		cout << "Serie de ordenes: correcta" << endl;
		cout << "Se ejecutaron " << instrucciones << " ordenes" << endl;
		cout << "Frecuencia de visitas por posicion: " << endl;
		cout << " ";
		for (int i=0;i<MAX_COL;i++){
			cout << " " << i << " "; //Posiciones de columnas
		}
		cout << endl;
		
		for (int i=0;i<MAX_FIL;i++){
			cout << i; //Posiciones de filas
			for (int j=0;j<MAX_COL;j++){
				if (Tablero[i][j] == 0){
					cout << " . ";
				}
				else{
					cout << " " << Tablero[i][j] << " ";//Pinta los valores
				}
			}
			cout << i; //Posiciones de filas
			cout << endl;
		}
		cout << " ";
		for (int i=0;i<MAX_COL;i++){
			cout << " " << i << " "; //Posiciones de columnas
		}
		cout << endl;
	}

	return 0;
}

