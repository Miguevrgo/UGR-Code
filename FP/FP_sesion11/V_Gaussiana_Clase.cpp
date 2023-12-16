/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Debe diseñar la clase teniendo en cuenta que la función matemática gaussiana
	viene determinada unívocamente por el valor de la esperanza y la desviación,
	es decir, son estos dos parámetros lo que distinguen a una función gaussiana
	de otra.
	Recuerde añadir un método ToString para la clase. Sugerimos el siguiente 
	formato:
	si g es N(0, 1) y el objeto g representa a esa función, la ejecución de 
	g.ToString() devolverá la cadena N (0.000000, 1.000000).

	Entradas: valor de la media y de la desviacion tipica
	Salidas: Gaussiana, CDF y CDF_2
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> // Inclusión de los recursos matemáticos

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/
const double PI = 3.1415926535; //Valor de PI
const double SALTO = 0.25; //Diferencia valores consecutivos
/*****************************************************************************
*							  FUNCIONES										 *
*****************************************************************************/





/*****************************************************************************
*Funcion que lee un numero real
*Parametros: string que indica el texto a mostrar para leer el numero
*Devuelve: Numero real leido
*****************************************************************************/
double LeeReal (string titulo){
	string entero;
	bool es_entero = true;
	do{
		cout << titulo; //Imprime el mensaje 
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
		int k=0;
		int p = entero.length();
		while ((p--) && (es_entero==true)){
			//Para cada posicion del string comprobamos si es un numero
			if (isdigit(entero[p]) == false){
				if(entero[p]=='.'){
					k++;
				}
				if(k>1){
					es_entero = false;
				}
			}
		}	
	}while(!es_entero);
	return stod(entero);
}
//Funcion que devuelve el valor de la gaussiana en funcion de valores x,m,s
double Gauss (double x, double m, double s)
{
	return (exp (-0.5 * pow ((x - m)/s, 2)) /  (s * sqrt(2*PI)));
}


class Gaussiana{
private:
	double media; // Esperanza
	double desviacion; // Desviacion tipica
public:
	//Constructor
	Gaussiana(double x, double y){
		media = x;
		desviacion = y;
	}
	double Valor(double x){
		double exponente,gaussiana;
		exponente = exp((-1.0/2)*pow((x-media)/desviacion,2));
		gaussiana = 1/(desviacion*sqrt(2*PI))*exponente; 
		return (gaussiana);
	}

	double CDF_1(double inicio, double fin){ 
		double suma_gaussiana = 0;
		const double SALTO_CDF = 0.01;
		for (double j=inicio;j<=fin;j += SALTO_CDF){ 
			suma_gaussiana += Valor(j);	
		}
		return (suma_gaussiana*SALTO_CDF);
	}

	double CDF_2(double x){

		const double B0 =  0.2316419;
		const double B1 =  0.319381530;
		const double B2 = -0.356563782;
		const double B3 =  1.781477937;
		const double B4 = -1.821255978;
		const double B5 =  1.330274429;
		double z = (x-media)/desviacion;
		double w;
		double t;
		t = 1.0 / (1+(B0*fabs(z)));
		const double T2 = t*t;
		const double T3 = T2*t;
		const double T4 = T3*t;
		const double T5 = T4*t;

		w = 1.0 - (Gauss(fabs(z),0,1)) * (B1*t + B2*T2 + B3*T3 + B4*T4 + B5*T5);

		if (x>=0){
			return w;
		}
		else{
			return (1-w);
		}
	}
	
	//Metodos de acceso para la lectura de datos:
	double GetMedia(){
		return(media);
	}

	double GetDesviacion(){
		return(desviacion);
	}

};




int main() //Programa principal
{
	double media;
	double desv_tipica;

	//Entrada de datos
	
	media = LeeReal("Introduce la media: ");
	
	do{
		desv_tipica = LeeReal("Introduce la desviacion tipica: ");
	}while (desv_tipica <= 0);
	
	
	//Cálculos

	Gaussiana una_gaussiana(media,desv_tipica);

	double x_inicial = media - (3*desv_tipica); //Calculo abscisa inicial
	double x_final = media + (3*desv_tipica); //Calculo abscisa final

	for (double i = x_inicial; i <= x_final; i += SALTO){
		 
		cout << fixed << "Gaussiana(" << i << "): " 
			 << una_gaussiana.Valor(i) << "\t";
		cout << "CDF(" << x_inicial << "," << i 
			 <<"): " << una_gaussiana.CDF_1(x_inicial,i) << "\t";
		cout << "CDF_2 " << "hasta " << i 
			 <<": " << una_gaussiana.CDF_2(i) << endl; 
	}

	return 0;
}





