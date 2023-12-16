/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Finalmente muestre una tabla comparativa en la que se muestren los valores
	estimados por los dos métodos y por la función sqrt para valores de x 
	desde 0 a 16, con saltos de 0.5. ¿Puede extraer alguna conclusión de esta 
	tabla? ¿Puede proponer un método de estimación mejor -más ajustado al 
	verdadero valor- que los dos implementados?

	
	Entradas: 
	Salidas: valores de las aproximaciones de la raiz
	
	
	Podemos ver que el primer metodo es mucho mas certero que el segundo,
	sin embargo, ambos metodos proporcionan una buen aproximacion
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath>
#include <iomanip>

using namespace std;

int main() //Programa principal
{
	double numero;	//Numero al que le vamos a calcular la raiz cuadrada
	double auxiliar;
	double auxiliar2;
	double metodo1; //Resultado de aproximar por el primer metodo
	double metodo2;	//Resultado de aproximar por el segundo metodo
	double valor_real;	//Resultado de la raiz cuadrada
	const double SALTO = 0.5;
	const double MAX = 16;
	const double MIN = 0;
	bool terminar = false;
	bool terminar2 = false;
	int raiz_exacta_inferior; //Raiz exacta que se encuentra por encima del num.
	int raiz_exacta_superior; //Raiz exacta que se encuentra por debajo del num.
	
	//Entrada de datos
	
	cout << "Introduzca el numero cuya raiz quiere calcular: ";
    cin >> numero;
	
	
		

	
	//Cálculos

	/*___________________________Metodo 1___________________________________*/
	
	metodo1=0;
	while (terminar == false && numero!=0){
		if (abs(numero-pow(auxiliar,2))<(abs(numero-pow(auxiliar+1,2)))){
			metodo1 = auxiliar + ((numero-pow(auxiliar,2))/(auxiliar*2));
			terminar = true; 
		}
		else{
			auxiliar++;
		}
	}
	terminar = false; //Reset de terminar para la tabla posterior
	auxiliar = 0; //Reset de auxiliar para la tabla posterior
	cout << "Aproximacion por metodo 1: " << metodo1 << endl;

	/*___________________________Metodo 2___________________________________*/

	while (pow(raiz_exacta_superior,2) <= numero){
		//Asignamos a la raiz exacta inferior el numero mas grande que al
		//elevarlo al cuadrado no se pase, y el siguiente numero a ese, será
		//La raiz exacta superior
		raiz_exacta_inferior = raiz_exacta_superior;
		raiz_exacta_superior++;
	}
	//Vamos a usar la semejanza de triangulos por la que el cateto opuesto 
	//del triangulo grande/cateto opuesto del triangulo pequeño es proporcional
	//a el cateto contiguo del grande/cateto contiguo del pequeño:
	
	if (pow(raiz_exacta_superior,2) == numero){
		metodo2 = raiz_exacta_superior;
	}
	else{
		metodo2 = ((raiz_exacta_superior-raiz_exacta_inferior)
		*(numero-pow(raiz_exacta_inferior,2))
		/(pow(raiz_exacta_superior,2)-pow(raiz_exacta_inferior,2)))
		+raiz_exacta_inferior;
	}
	cout << "Aproximacion por metodo 2: " << metodo2 << endl;
	metodo2 = 0;
	raiz_exacta_inferior = 0;
	raiz_exacta_superior = 0;
	
	//Salida
	
	std::cout.precision(5);
	for (double i=MIN;i<=MAX;i+=SALTO){
		//Valor real
		
		valor_real = sqrt (i);
		
		//Metodo 1
		metodo1=0;
		while ((terminar == false) && (i != 0)){
			if (abs(i-pow(auxiliar,2))<(abs(i-pow(auxiliar+1,2)))){
				metodo1 = auxiliar + ((i-pow(auxiliar,2))/(auxiliar*2));
				terminar = true; 
			}
			else{
				auxiliar++;
			}
		}
		auxiliar = 0;
		terminar = false;
		
		//Metodo 2
		
		while (pow(raiz_exacta_superior,2) <= i){
		raiz_exacta_inferior = raiz_exacta_superior;
		raiz_exacta_superior++;
		}
		if (pow(raiz_exacta_superior,2) == i){
			metodo2 = raiz_exacta_superior;
		}
		else{
			metodo2 = ((raiz_exacta_superior-raiz_exacta_inferior)
			*(i-pow(raiz_exacta_inferior,2))
			/(pow(raiz_exacta_superior,2)-pow(raiz_exacta_inferior,2)))
			+raiz_exacta_inferior;
		}
		raiz_exacta_inferior = 0;
		raiz_exacta_superior = 0;
		
		cout << std::fixed << "Valor Real: " << valor_real << "\tMetodo 1: "
			 << metodo1 << "\tMetodo2: " << metodo2 << endl; 
	}
	
	return 0;
}

