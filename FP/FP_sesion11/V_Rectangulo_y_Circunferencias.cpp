/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Este ejercicio consiste en reescribir la solución al problema planteado en 
	el ejercicio 4 de la Relación de Problemas IV. Ahora se utilizarán clases 
	para entidades tipo rectangulo y circunferencia. En cualquier caso, la 
	solución no será la definitiva ya que necesitamos profundizar en la materia 
	para poder diseñar una correcta estructura de clases: en este momento no 
	sabemos cómo trabajar con una clase que tiene datos miembro de otra clase 
	(p.e. la clase Circunferencia se caracteriza a partir de un dato Punto2D 
	-el centro- además del radio). 
	
	Entradas: Coordenadas del rectangulo
	Salidas: Circunferencia de radio superior al rectangulo
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> //Inclusion recursos matemáticos

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/
const double PI = 3.1415926535; //Valor de PI
const double INCREMENTO = 0.25; //Incremento del radio en cada iteracion
const double RADIO_INICIAL = 0.5; //Valor inicial del radio	
/*****************************************************************************
*							  FUNCIONES										 *
*****************************************************************************/

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



/****************************************************************************
*Lee un dato tipo double (Una coordenada) y calcula el punto medio de esa
*coordenada
*Parametros: coordenada, punto sobre el que va a trabajar
*Devuelve: Punto medio de esa coordenada
*****************************************************************************/
double Punto_medio(double coordenada){
	double punto_medio;
	punto_medio = coordenada/2;
	return punto_medio;
}





struct Punto2D{ //Coordenadas del punto
	double abscisa; //Valor de x del punto
	double ordenada; //Valor de y del punto
};


class Rectangulo{
private:

	double area;
	Punto2D un_punto;

public: //Metodos

	//Constructor
	Rectangulo (double x,double y)
	{
		un_punto.abscisa = x;
		un_punto.ordenada = y;
	}
	//Calcula el area del rectangulo y lo guarda en la variable Area
	void Area_rectangulo(){
		area = un_punto.abscisa*un_punto.ordenada;
	}
	//Metodo de acceso para la lectura
	double GetArea (void){
		return (area);
	}
	
};


class Circunferencia{ //Circunferencia
private:

	Punto2D centro;
	double radio;
	double area;

public:
	//Constructor
	Circunferencia(double valor_radio) :
		radio (valor_radio)
	{}	
	//Calcula el area de la circunferencia y lo guarda en area
	void Area_circunferencia(){
		area = PI*pow(radio,2);
	}
	//Incrementa el radio
	void Incrementa_radio(){
		radio += INCREMENTO;
	}
	void Centro_circunferencia(double abscisa, double ordenada){
		centro.abscisa = Punto_medio(abscisa);
		centro.ordenada = Punto_medio(ordenada);
	}

	//Metodos de acceso a la lectura:
	double GetArea (){
		return (area);
	}

	double GetRadio (){
		return (radio);
	}

	double GetAbscisaCentro (){
		return(centro.abscisa);
	}

	double GetOrdenadaCentro (){
		return(centro.abscisa);
	}

};



int main() //Programa principal
{
	bool radio_menor = true;
	double x,y; //Ordenada y abscisa
	

	//Leemos las coordenadas de los puntos
	x = LeeEntero("Introduzca la coordenada x: ");
	y = LeeEntero("Introduzca la coordenada y: ");

	Rectangulo un_rectangulo(x,y);
	Circunferencia una_circunferencia(RADIO_INICIAL);
	
	//Cálculos
	
	//Calcula coordenadas centro de la circunferencia
	una_circunferencia.Centro_circunferencia(x,y);

	while(radio_menor){
		//Area de la circunferencia 
		una_circunferencia.Area_circunferencia();
		un_rectangulo.Area_rectangulo();

		if (una_circunferencia.GetArea() < un_rectangulo.GetArea()){
			una_circunferencia.Incrementa_radio(); //Incrementamos el radio	
		}
		else{
			radio_menor = false; //Salimos del bucle
		}
	}
	
	//Salida
	
	cout << "\nCircunferencia:\n";
	Pinta_linea('_',30);
	cout << "\n\tCoordenada centro: ( " << una_circunferencia.GetAbscisaCentro() 
		 << " , " << una_circunferencia.GetOrdenadaCentro() << " )\n";
	cout << "\tRadio: " << una_circunferencia.GetRadio() << endl;
	cout << "\tArea: " << una_circunferencia.GetArea() << endl << endl;
	Pinta_linea('_',30);
	cout << "\nRectangulo: \n"; 
	cout << "\n\tArea: " << un_rectangulo.GetArea();

	return 0;
}

