/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Escribid un programa calcule CDF(x) para un valor de x dado. El programa 
	debe pedir los parámetros que definen una función gaussiana (µ y s) y el 
	valor de la abscisa, x, para el que se va a calcular CDF(x).
	Para el cálculo práctico de CDF(x) la integral se convierte en una suma, y 
	se requiere concretar cuántas sumas se van a realizar. Bastará con indicar:
	a) un valor inicial para x (tómese µ - 3s).
	b) un “salto” entre dos valores consecutivos de x (use una constante).
	
	Entradas: Valor de x,media y desviacion tipica(x,media,desv_tipica)
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> // Inclusión de los recursos matemáticos

using namespace std;

int main() //Programa principal
{
	double x; //Valor de abscisa
	double media;
	double desv_tipica;
	const double SALTO = 0.000001;
	double x_inicial;
	double rectangulo = 0; //Area de los rectangulos
	double gaussiana;
	double distribucion_acumulada = 0; //CDF de x
	double const PI = 3.14159265358979323846; //Declaración constante PI
	double exponente; //Vamos a declarar la variable exponente que simboliza 
					  //la e incluyendo su exponente para facilitar la lectura

	//Entrada de datos
	
	cout << "Introduce el valor de la abscisa: ";
	cin >> x;
	cout << "Introduce la media: ";
	cin >> media;
	
	//Filtramos el valor de la desviación tipica que tiene que ser mayor que 0
	
	do{
		cout << "Introduce la desviacion tipica: ";
		cin >> desv_tipica;
	}while (desv_tipica <= 0);
	
	//Cálculos
	
	x_inicial = media - (3*desv_tipica); //Calculo valor de abscisa inicial

	for (double i = x_inicial; i <= x; i += SALTO){
		
		exponente = exp(-1/2.0*pow((i-media)/desv_tipica,2));
		gaussiana = 1/(desv_tipica*sqrt(2*PI))*exponente; 
		
		//Calculamos el área del rectangulo bajo la grafica que nos da el valor
		//Aproximado del área real bajo la curva
		
		rectangulo = gaussiana * SALTO;
		
		//Sumamos los rectangulos
		
		distribucion_acumulada += rectangulo;
	}
	
	//Salida
	
	cout << endl;
	cout << "El area aproximada bajo la curva hasta el valor de x=" << x
		 << " Es: " << distribucion_acumulada;

	return 0;
}

