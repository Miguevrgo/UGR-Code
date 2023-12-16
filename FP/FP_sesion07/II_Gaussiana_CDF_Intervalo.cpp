/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Escribid un programa que pida los par�metros que definen una funci�n 
	gaussiana (� y s), los extremos del intervalo de valores de la abscisa y 
	la diferencia (salto) entre dos valores consecutivos de x. A continuaci�n 
	mostrar�, para cada valor de x los valores de g(x) y de CDF(x)
	
	Entradas: Valor de x,media y desviacion tipica(x,media,desv_tipica),salto
	Salidas: valores de g(x) y de CDF(x)
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
#include <cmath> // Inclusi�n de los recursos matem�ticos

using namespace std;

int main() //Programa principal
{
	double x; //Valor de abscisa
	double media;
	double desv_tipica;
	double salto;
	double x_inicial;
	double rectangulo = 0; //Area de los rectangulos
	double gaussiana;
	double distribucion_acumulada = 0; //CDF de x
	double const PI = 3.14159265358979323846; //Declaraci�n constante PI
	double exponente; //Vamos a declarar la variable exponente que simboliza 
					  //la e incluyendo su exponente para facilitar la lectura

	//Entrada de datos
	
	cout << "Introduce el valor de la abscisa: ";
	cin >> x;
	cout << "Introduce la media: ";
	cin >> media;
	
	//Filtramos el valor de la desviaci�n tipica que tiene que ser mayor que 0
	
	do{
		cout << "Introduce la desviacion tipica: ";
		cin >> desv_tipica;
	}while (desv_tipica <= 0);
	
	do{	
		cout << "Introduce el salto: ";
		cin >> salto;
	}while (salto <= 0);
	
	//C�lculos
	
	x_inicial = media - (3*desv_tipica); //Calculo valor de abscisa inicial

	for (double i = x_inicial; i <= x; i += salto){
		
		exponente = exp((-1.0/2)*pow((i-media)/desv_tipica,2));
		gaussiana = 1/(desv_tipica*sqrt(2*PI))*exponente; 
		
		cout << "El valor de la gaussiana en " << i << " es: " << gaussiana;
		
		//Calculamos el �rea del rectangulo bajo la grafica que nos da el valor
		//Aproximado del �rea real bajo la curva
		
		rectangulo = gaussiana * salto;
		
		//Sumamos los rectangulos
		
		distribucion_acumulada += rectangulo;	
		cout << endl;
		cout << "El area aproximada bajo la curva hasta el valor de x=" << i
		 << " Es: " << distribucion_acumulada << endl; 
	}
		 
	return 0;
}

