/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

Indice FUNCIONES:
1-Calcular letra NIF || Linea 40
2-Comprobar si NIF es correcto || Linea 52
3-Leer entero || Linea 85
4-Pinta_linea ||Linea 120
5-Leer Real || Line 134
6-
7-
8-Cabecera para funciones y metodos(Hacer)
9-
10-
11-






















______________________________________________________________________________*/

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
________________________________________________________________________________

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

________________________________________________________________________________

/*****************************************************************************
*Funcion que lee un numero entero
*Parametros: string que indica el texto a mostrar para leer el numero
*Devuelve: Numero entero leido
*****************************************************************************/
int LeeEntero (string titulo){
	string entero;
	bool es_entero = true;
	do{
		cout << titulo; //Imprime el mensaje 
		cin >> entero;
		es_entero = true;
		//Comprobamos que el primer digito sea un numero entero o el signo -/+
		if ( !( isdigit(entero[0]) || entero[0] == 45 || entero[0] == 43) ){
			es_entero = false;
		}
		//Si el numero es: -/+
		else if ((entero[0] == 45 || entero[0] == 43 ) && entero.length() == 1){ 
			es_entero = false;
		}
		int i = 1;
		while(i<(int)entero.length() && es_entero){
			//Para cada posicion del string comprobamos si es un numero
			if (!isdigit(entero[i])){
				es_entero = false;
			}
			i++;
		}	
	}while(!es_entero);
	return stoi(entero);
}

________________________________________________________________________________


/*****************************************************************************
*Funcion pinta una linea con el caracter indicado
*Parametros: caracter a pintar, longitud de la linea
*****************************************************************************/
void Pinta_linea (char caracter, int longitud){
	while(longitud--){
		cout << caracter;
	}
	cout << endl;
}

________________________________________________________________________________


double LeeReal (string titulo){
	string real;
	bool es_real = true;
	do{
		cout << titulo; //Imprime el mensaje 
		cin >> real;
		es_real = true;
		//Comprobamos que el primer digito sea un numero entero o el signo -/+
		if ( !( isdigit(real[0]) || real[0] == 45 || real[0] == 43) ){
			es_real = false;
		}
		//Si el numero es: -/+
		else if ((real[0] == 45 || real[0] == 43 ) && real.length() == 1){ 
			es_real = false;
		}
		int k=0;
		int p = real.length();
		while ((p--) && (es_real)){
			//Para cada posicion del string comprobamos si es un numero
			if (!isdigit(real[p])){
				if(real[p]=='.'){
					k++;
				}
				if(k>1){
					es_real = false;
				}
			}
		}	
	}while(!es_real);
	return stod(real);
}

________________________________________________________________________________

















































































































