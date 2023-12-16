/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Escribir un programa que lea las coordenadas que definen un rectángulo y 
	calcule la circunferencia centrada en el punto de corte de las diagonales 
	del rectángulo tal que su superficie sea la menor entre todas las 
	circunferencias de área mayor que la del rectángulo.
	
	Use datos de tipo Rectangulo, Circunferencia y Punto2D para la resolución 
	de este problema.
	
	Entradas: Valor abscisa x, ordenada y
	Salidas: Coordenadas centro circunferencia, radio, area circunferencia y
	rectangulo
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> //Inclusion recursos matemáticos

using namespace std;

struct Circunferencia{ //Circunferencia
	double area;
	double centro_abscisa;
	double centro_ordenada;		
	double radio;
};
	
struct Rectangulo{ //Rectangulo
	double area; //Valor del area del rectangulo;
	};
	
struct Punto2D{ //Coordenadas del punto
	double abscisa; //Valor de x del punto
	double ordenada; //Valor de y del punto
	};

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

int main() //Programa principal
{
	const double INCREMENTO = 0.25; //Incremento del radio en cada iteracion
	const double PI = 3.14159265359; //Valor de pi
	bool radio_menor = true;
	
	Punto2D un_punto; //Coordenadas de las esquinas del rectangulo
	cout << "Introduzca la coordenada x: ";
	cin >> un_punto.abscisa; //Abscisa esquina inferior derecha
	cout << "Introduzca la coordenada y: ";
	cin >> un_punto.ordenada; //Ordenada esquina superior izquierda
	
	Rectangulo un_rectangulo; //Rectangulo de referencia
	un_rectangulo.area = un_punto.abscisa * un_punto.ordenada; //Area rectangulo
	
	Circunferencia una_circunferencia; //Variable una_circunferencia
	//Coordenadas del centro de la circunferencia
	una_circunferencia.centro_abscisa = Punto_medio(un_punto.abscisa);
	una_circunferencia.centro_ordenada = Punto_medio(un_punto.ordenada);
	//Valor inicial del radio
	una_circunferencia.radio = 0.5;
	
	//Cálculos

	while(radio_menor){
		//Area de la circunferencia 
		una_circunferencia.area = PI*pow(una_circunferencia.radio,2);
		if (una_circunferencia.area < un_rectangulo.area){
			una_circunferencia.radio += INCREMENTO; //Incrementamos el radio	
		}
		else{
			radio_menor = false; //Salimos del bucle
		}
	}
	
	//Salida
	
	cout << "Circunferencia:\n";
	cout << "\tCoordenada centro: (" << una_circunferencia.centro_abscisa << "," 
		 << una_circunferencia.centro_ordenada << ")\n";
	cout << "\tRadio: " << una_circunferencia.radio << endl;
	cout << "\tArea: " << una_circunferencia.area << endl << endl;
	cout << "Rectangulo: \n"; 
	cout << "\tArea: " << un_rectangulo.area;

	return 0;
}

