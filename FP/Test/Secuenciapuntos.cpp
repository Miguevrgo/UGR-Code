/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath>

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/
const int MAX_PUNTOS = 50; //Maximo de puntos
/*****************************************************************************
*							  FUNCIONES										 *
*****************************************************************************/
class Punto2D{
private:

	double abscisa;
	double ordenada;

public:

	//Constructor ( Si no le llegan parametros construye el punto(0,0) )
	Punto2D(double x, double y){
		SetCoordenadas(x,y);
	}
	//Constructor sin parametros
	Punto2D(){
		SetCoordenadas();
	}

	void SetCoordenadas(double x = 0, double y = 0){
		abscisa = x;
		ordenada = y;
	}

	//Metodos para recibir datos privados

	double GetAbscisa(void){
		return (abscisa);
	}

	double GetOrdenada(void){
		return (ordenada);
	}

	//Metodos para modificar datos privados

	void SetAbscisa(double x){
		abscisa = x;
	}

	void SetOrdenada(double y){
		ordenada = y;
	}

	double DistanciaAbscisas(Punto2D otro_punto){
		return (fabs(abscisa-otro_punto.abscisa));
	}

	double DistanciaOrdenada(Punto2D otro_punto){
		return (fabs(ordenada-otro_punto.ordenada));
	}

	double PuntoMedioAbscisa(Punto2D otro_punto){
		return((abscisa+otro_punto.abscisa)/2);
	}

	double PuntoMedioOrdenada(Punto2D otro_punto){
		return((ordenada+otro_punto.ordenada)/2);
	}

	string ToString(void){
		string cad;
		cad = "(" + to_string(abscisa) + "," + to_string(ordenada) + ")";
		return (cad);
	}
};


class ColeccionPuntos{
private:
	
	Punto2D vector_privado[MAX_PUNTOS];
	int total_utilizados = 0; //Puntos utilizados
	
public:
	
	//Constructor
	ColeccionPuntos(Punto2D un_punto = {0,0}){
		vector_privado[total_utilizados] = un_punto;
		total_utilizados++;	
	}
	//Constructor vacio 
	ColeccionPuntos(){}
	
	
	
	//Metodo ToString
	string ToString(){
		string cad;
		for (int i=0;i<total_utilizados;i++){
			cad += vector_privado[i].ToString();
		}
		return cad;
	}
	
	
};

int main() //Programa principal
{
	Punto2D un_punto(3,4);
	cout << un_punto.ToString();
	ColeccionPuntos una_coleccion(un_punto);
	cout << una_coleccion.ToString();

	//Entrada de datos
	
	
	
	//Cálculos



	//Salida
	


	return 0;
}

