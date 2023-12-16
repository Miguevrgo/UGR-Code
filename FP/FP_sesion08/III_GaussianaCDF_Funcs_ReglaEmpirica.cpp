/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Escribir un programa que lea los parámetros de una distribución gaussiana 
	y a continuación muestre los valores de:
	a) g(x) con la función escrita en el ejercicio 8,
	b) CDF(x) con la función escrita en el ejercicio 28, y
	c) CDF(x) con la función escrita en el ejercicio 29
	
	Para valores de x comprendidos entre µ - 3s y µ + 3s. Use 0.25 como la 
	diferencia entre dos valores consecutivos de x.
	
	Entradas: Valores de la media y la desviacion tipica
	Salidas: valores de la gaussiana g(x), CDF funcion ejer 28, CDF funcion
	ejer 29
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> // Inclusión de los recursos matemáticos
#include <iomanip>

using namespace std;

double Gaussiana(double x, double media, double desv_tipica, double PI){
	double exponente,gaussiana;
	exponente = exp((-1.0/2)*pow((x-media)/desv_tipica,2));
	gaussiana = 1/(desv_tipica*sqrt(2*PI))*exponente; 
	return gaussiana;
}

double CDF_1(double inicio, double fin, double media, double desv, double s,
 double PI){ 
	double rectangulo;
	double distribucion_acumulada;
	for (double j=inicio;j<=fin;j +=s){ //s es el salto entre dos valores
		rectangulo = Gaussiana(j,media,desv,PI) * s;
		//Sumamos los rectangulos
		distribucion_acumulada += rectangulo;	
	}
	return distribucion_acumulada;
}

double CDF_2(double x, double media, double desv, double PI){
	const double b0 = 0.2316419;
	const double b1 = 0.319381530;
	const double b2 = -0.356563782;
	const double b3 = 1.781477937;
	const double b4 = -1.821255978;
	const double b5 = 1.330274429;
	double w;
	double t;
	t = 1 / (1+(b0*abs(x)));
	w = 1-(Gaussiana(abs(x),media,desv,PI))
	 	* (b1*t + b2*pow(t,2) + b3*pow(t,3) + b4*pow(t,4) + b5*pow(t,5));
	if (x>=0){
		return w;
	}
	else{
		return (1-w);
	}
}

int main() //Programa principal
{
	const double SALTO = 0.25; //Diferencia valores consecutivos
	double media;
	double desv_tipica;
	double const PI = 3.14159265358979323846;
	//Entrada de datos
	
	cout << "Introduce la media: ";
	cin >> media;
	do{
		cout << "Introduce la desviacion tipica: ";
		cin >> desv_tipica;
	}while (desv_tipica <= 0);
	
	
	//Cálculos
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	double x_inicial = media - (3*desv_tipica); //Calculo abscisa inicial
	double x_final = media + (3*desv_tipica); //Calculo abscisa final
	for (double i = x_inicial; i <= x_final; i += SALTO){
		 
		cout << right << setw(25) << setprecision(3) << "Gaussiana(" <<setw(5)<< i << "): " 
			 << setprecision(7)<< Gaussiana(i,media,desv_tipica,PI);
		cout << setw(25) << setprecision(3) << "CDF(" << x_inicial << "," << i 
			 <<"): "<< setprecision(7) << CDF_1(x_inicial,i,media,desv_tipica,SALTO,PI) << setw(20);
		cout << setw(25) << setprecision(3) << "CDF_2 " << "hasta " << i 
			 <<": " << setprecision(7)<< CDF_2(i,media,desv_tipica,PI) << endl; 
	}

	return 0;
}

