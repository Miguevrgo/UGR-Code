/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Las circunferencias en las que estamos interesados se guardarán en un array
	conforme se vayan calculando. Después, se mostrará cuántas circunferencias
	se han guardado y sus propiedades.


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
*							    CLASES										 *
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


class LectorPunto2D{
private:
	string titulo;
public:
	//Constructor
	LectorPunto2D(string cad = "Introduzca: ") : titulo(cad){}

	Punto2D LeerPunto(){
		double x;
		double y;
		Punto2D un_punto;
		cout << titulo;
		
		cout << "\n\tCoordenada x: ";
		cin >> x;
		un_punto.SetAbscisa(x);
		
		cout << "\n\tCoordenada y: ";
		cin >> y;
		un_punto.SetOrdenada(y);
		
		return (un_punto);
	}
};



class Rectangulo{
private:

	Punto2D esquina_sup_izquierda;
	Punto2D esquina_inf_derecha;

public:

	//Constructor
	Rectangulo(Punto2D sup_izq, Punto2D inf_der){
	
		SetCoordenadas(sup_izq,inf_der);

	}
	//Constructor sin argumentos
	Rectangulo() : esquina_sup_izquierda(Punto2D(0,1)), 
	esquina_inf_derecha(Punto2D(1,0)){
	}

	double Area(void){
		double area;
		area = esquina_sup_izquierda.DistanciaAbscisas(esquina_inf_derecha) *
		esquina_sup_izquierda.DistanciaOrdenada(esquina_inf_derecha);
		return(area);
	}

	void SetCoordenadas(Punto2D una_sup_izq, Punto2D una_inf_der){

		//Operador de asignacion
		esquina_sup_izquierda = una_sup_izq;
		esquina_inf_derecha = una_inf_der;
	}

	Punto2D GetSup_Izq(void){
		return (esquina_sup_izquierda);
	}

	Punto2D GetInf_Der(void){
		return (esquina_inf_derecha);
	}

	string ToString(void){
		string cad;
		cad = "\nRectangulo: \n\tEsquina superior izquierda: " 
		+ esquina_sup_izquierda.ToString() + "\n\tEsquina inferior derecha: "
		+ esquina_inf_derecha.ToString() + "\n\tArea: " + to_string(Area());
		return (cad);
	}

};


class Circunferencia{
private:

	Punto2D centro;
	double radio;

public:
	//Constructor 
	Circunferencia(double a_c,double o_c, double r_c){
		//a_c --> Abscisa Centro
		//o_c --> Ordenada Centro
		//r_c --> Radio Centro
		SetCircunferencia(a_c,o_c,r_c);
	}
	//Constructor sin parametros
	Circunferencia(){
		SetCircunferencia();
	}

	/*************************************************************************
	*Funcion que calcula el Area de la circunferencia
	*Devuelve: Area de la circunferencia
	**************************************************************************/
	double Area(void){
		return (PI*pow(radio,2));
	}

	//Metodos Set

	void SetRadio(double rad){
		radio = rad;
	}

	void SetCentro(double x, double y){
		Punto2D un_centro(x,y);
		centro = un_centro;
	}

	void SetCircunferencia(double abs_centro = 0, double ord_centro = 0,
		double rad = 1){
			Punto2D un_centro(abs_centro,ord_centro);
			centro = un_centro;
			radio = rad;
		}

	//Metodos Get

	Punto2D GetCentro(void){
		return (centro);
	}
	double GetOrdenadaCentro(void){
		return (centro.GetOrdenada());
	}

	double GetAbscisaCentro(void){
		return (centro.GetAbscisa());
	}

	double GetRadio(void){
		return (radio);
	}

	void IncrementaRadio(double incremento = INCREMENTO){
		radio += incremento;
	}

	string ToString(void){
		string cad;
		cad = "\n\tCoordenada centro: " + centro.ToString() + "\n\tRadio: " +
		to_string(radio) + "\n\tArea: " + to_string(Area());
		return (cad);
	} 
};



int main() //Programa principal
{
	bool radio_menor = true;
	Punto2D sup_izq;
	Punto2D inf_der;
	int cir_gen = 0; //Circunferencias generadas
	bool esta_inscrita; //Circunferencia inscrita

	Circunferencia una_circunferencia[MAX];
	LectorPunto2D sup_izquierda("Coordenadas esquina superior izquierda: ");
	LectorPunto2D inf_derecha("Coordenadas esquina inferior derecha: ");
	//Entrada de datos
	
	//Leemos las coordenadas de la esquina superior izquierda
	sup_izq 
	= sup_izquierda.LeerPunto();
	inf_der
	= inf_derecha.LeerPunto();
	
	//Cálculos
	
	Rectangulo un_rectangulo(sup_izq,inf_der);
	una_circunferencia[cir_gen].SetCircunferencia
	(sup_izq.PuntoMedioAbscisa(inf_der),sup_izq.PuntoMedioOrdenada(inf_der),
	RADIO_INICIAL);

	cir_gen++;

	while (radio_menor){
		una_circunferencia[cir_gen] = 
		una_circunferencia[cir_gen-1];
		una_circunferencia[cir_gen].IncrementaRadio();

		esta_inscrita = ((una_circunferencia[cir_gen].GetOrdenadaCentro() 
		+ una_circunferencia[cir_gen].GetRadio() 
		<= un_rectangulo.GetSup_Izq().GetOrdenada()) 
		&& (una_circunferencia[cir_gen].GetAbscisaCentro() 
		+ una_circunferencia[cir_gen].GetRadio() 
		< un_rectangulo.GetInf_Der().GetAbscisa()));
		
		
		if (esta_inscrita){
			cir_gen++;
		}
		else{
			radio_menor = false;
		}
	}

	//Salida
	
	cout << un_rectangulo.ToString() << endl << endl;
	Pinta_linea('_',30);
	
	for (int i=0;i<cir_gen;i++){
		cout << "Circunferencia " << i+1 << ":\n";
		cout << una_circunferencia[i].ToString() << "\n";
		Pinta_linea('_',30);
	}

	return 0;
}

