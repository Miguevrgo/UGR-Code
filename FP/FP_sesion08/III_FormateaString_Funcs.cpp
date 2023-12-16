/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Escriba una funci�n para dar formato a un string, obteniendo como resultado 
	un nuevo string de acuerdo al formato indicado en su llamada. La funci�n 
	tendr� el prototipo:

	string FormateaString (string cad, int num_casillas,
	TipoAjuste ajuste, char relleno=� �);
	
	Transforma el contenido del dato cad a un nuevo string de acuerdo al
	formato indicado. La funci�n devuelve un nuevo string.
	El nuevo string tendr� un m�nimo de num_casillas casillas. Si el n�mero
	de casillas solicitado (num_casillas) es mayor que el tama�o de cad se
	completan las casillas necesarias con el car�cter relleno. Si la longitud 
	de cad fuera mayor simplemente se devuelve una copia de cad.
	Respecto al ajuste se usa un valor del tipo TipoAjuste para indicar la
	alineaci�n de la cadena resultado. Use la siguiente definici�n de tipo 
	enumerado TipoAjuste:
	enum class TipoAjuste {izquierda, centro, derecha};

	Entradas: String original
	Salidas: String tras la transformacion
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
#include <string>
using namespace std;

enum class TipoAjuste {izquierda, centro, derecha};

string FormateaString (string cad, int num_casillas,
TipoAjuste ajuste, char relleno){
	string cadena = cad;
	if (num_casillas > cad.length()){
		switch(ajuste){
			case (TipoAjuste::izquierda):
				//A�adimos a la izquierda de la cadena(posicion 0)
				//Tantos caracteres como para que los caracteres + la longitud
				//de la cadena sean iguales al numero de casillas
				cadena.insert(0,num_casillas-cad.length(),relleno); 
				break;
			case (TipoAjuste::centro):
				//A�adimos a la izquierda de la cadena(posicion 0)
				//Caracteres hasta rellenar la primera mitad de la cadena
				//(sin incluir la cadena original) y caracteres tras la cadena
				//original hasta que el total de caracteres sea el deseado
				cadena.insert(0,((num_casillas-cad.length())/2),relleno);
				cadena.insert(((num_casillas - cad.length()) / 2) + cad.length()
				,(num_casillas-cad.length())/2, relleno);
				break;
			case (TipoAjuste::derecha):
				//A�adimos a la derecha de la cadena(cadena.append)
				//Tantos caracteres como para que los caracteres + la longitud
				//de la cadena sean iguales al numero de casillas
				cadena.append(num_casillas-cad.length(),relleno);
				break;	
		}	
	}
	else{
		//En caso de que num_casillas < la longitud de la cadena
		cadena = cad;
	}
	return cadena; //Devuelve la cadena una vez modificada	
	}
	
int main() //Programa principal
{
	int num_casillas; //Numero de casillas deseadas
	int min_casillas = 2; //Minimo de casillas
	string cad; //Cadena original
	char relleno; //Caracter para rellenar
	
	//Entrada de datos
	
	cout << "Introduzca su linea: ";
    getline(cin,cad);
    
    do{
	    cout << "Introduzca el numero de casillas de su nueva cadena: ";
	    cin >> num_casillas;
	}while (num_casillas < min_casillas);
	
	cout << "Introduzca el caracter de relleno: ";
	cin >> relleno;
	
	//C�lculos
	
	bool tipo_ajuste_correcto;
	char posicion;
	do{
		cout << "Posicion deseada(I,C,D): ";
		cin >> posicion;
		posicion = toupper(posicion);
		tipo_ajuste_correcto = (posicion == 'I' 
		|| posicion == 'C' || posicion == 'D');
	}while(!tipo_ajuste_correcto);
	
	TipoAjuste ajuste;
	
	switch(posicion){
		case 'I':
			ajuste = TipoAjuste::izquierda;
			break;
		case 'C':
			ajuste = TipoAjuste::centro;
			break;
		case 'D':
			ajuste = TipoAjuste::derecha;
			break;
	}
	
	cad = FormateaString (cad,num_casillas,ajuste,relleno);
	cout << cad;

	return 0;
}

