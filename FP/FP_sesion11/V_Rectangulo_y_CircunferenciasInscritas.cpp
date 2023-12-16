/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Escribir un programa que lea las coordenadas que definen un rectángulo y 
	calcule y muestre una serie de datos de tipo Circunferencia, todas centrada 
	en en el punto de corte de las diagonales del rectángulo.
	Las circunferencias en las que estamos interesadas serán todas las 
	circunferencias inscritas en el rectángulo. Para ello comience con una 
	circunferencia de radio radio=0.5 y vaya incrementando su valor 0.25 
	en cada iteración. 
	
	Entradas: Coordenadas del rectangulo
	Salidas: Circunferencias cuyo area es menor que la del rectangulo
	
	

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
const int MAX = 100; //Maximo de circunferencias generadas	
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
	double GetAbscisa(){
		return(un_punto.abscisa);
	}
	double GetOrdenada(){
		return(un_punto.ordenada);
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
	int circunferencias_generadas = 0;
	double area_circunferencias[MAX];
	double radio_circunferencias[MAX];
	bool esta_inscrita; //Circunferencia inscrita

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
		
		una_circunferencia.Incrementa_radio(); //Incrementamos el radio
		
		
		esta_inscrita = ((una_circunferencia.GetAbscisaCentro() 
		+ una_circunferencia.GetRadio()) <= un_rectangulo.GetAbscisa() 
		&& ((una_circunferencia.GetOrdenadaCentro() + 
		una_circunferencia.GetRadio()) <= un_rectangulo.GetOrdenada()));
		
		
		if (esta_inscrita){
			
			//Guardamos el area de la circunferencia en el array
			area_circunferencias[circunferencias_generadas] = 
			una_circunferencia.GetArea();

			//Guardamos el radio de la circunferencia en el aray
			radio_circunferencias[circunferencias_generadas] = 
			una_circunferencia.GetRadio();

			circunferencias_generadas++; //Aumentamos el contador	
		}
		else{
			radio_menor = false; //Salimos del bucle
		}
	}
	
	//Salida

	cout << "\nRectangulo: \n"; 
	cout << "\n\tArea: " << un_rectangulo.GetArea() << endl;
	Pinta_linea('_',30);

	for (int i = 0;i < circunferencias_generadas;i++){
		cout << "Circunferencia " << i+1 << ":\n";
		cout << "\n\tCoordenada centro: ( " 
			 << una_circunferencia.GetAbscisaCentro() 
			 << " , " << una_circunferencia.GetOrdenadaCentro() << " )\n";
		cout << "\tRadio: " << radio_circunferencias[i] << endl;
		cout << "\tArea: " << area_circunferencias[i] << endl << endl;
		Pinta_linea('_',30);
		
	}
	
	return 0;
}
