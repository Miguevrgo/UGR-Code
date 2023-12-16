/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Defina la función Redondea para calcular un número real aproximado a un 
	número de cifras decimales dado
	Defina la función Trunca para truncar un número real usando un número de 
	cifras decimales dado.
	En la implementación de estas funciones, necesitará calcular potencias 
	enteras (potencias de 10 en este caso).
	
	Entradas: Numero a redondear, cifras a redondear(numero,cifras)
	Salidas: Numero, Numero redondeado, numero truncado
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <iomanip>
using namespace std;

//Funcion Potencia
double Potencia(double num1, int exponente){
	int resultado = num1;
	for (int i=1;i<exponente;i++){
		resultado = resultado*num1;
	}
	return resultado;
}
//Funcion Redondea
	//Una solucion al problema podria ser usar
	//cout << fixed;
	//cout << setprecision(cifras) << num << endl;
double Redondea(double num, int cifras){
	//Pero vamos a resolverlo usando potencias de 10:
	int aux; 
	//Eliminamos los decimales que no nos interesan(Incluimos el decimal 
	//posterior a la cifra a la que queremos redondear para operarlo).
	aux = num*Potencia(10, cifras+1);  
	/*Le sumamos 5 y pueden ocurrir dos cosas:
	a)La ultima cifra<4(No queremos redondeo) Al sumar y dividir entre 10
	el numero se quedará igual pero sin esa ultima cifra
	b)La ultima cifra>=5(Queremos redondeo) Al sumar 5 la cifra que queremos
	Redondear aumentara a su siguiente valor, y al dividir nos deshacemos del
	valor que no nos interesa*/
	aux = (aux+5)/10;
	//Restauramos el valor inicial del numero una vez redondeado
	num = aux/Potencia(10,cifras);
	return num;
}

//Funcion Trunca
double Trunca(double num, int cifras){
	int aux; //Variable auxiliar que usaremos para Truncar
	aux = num*Potencia(10, cifras); //Eliminamos los decimales que no interesan
	//Restauramos el valor inicial del numero una vez truncado
	num = aux/Potencia(10,cifras);
	return num; 
}


int main() //Programa principal
{
	double numero = 0;
	int cifras;
	bool cifras_incorrecto;
	
	//Entrada de datos
	
	cout << "Introduzca el numero: ";
    cin >> numero;
    do{
    	cout << "Introduzca el numero de cifras a truncar/redondear: ";
    	cin >> cifras;
    	cifras_incorrecto = cifras<0;
	}while(cifras_incorrecto);
	
	//Salida
	
	cout << fixed <<"Numero: " << numero << endl;
	cout << "Numero Redondeado: " << Redondea(numero,cifras) << endl;
	cout << "Numero Truncado: " << Trunca(numero,cifras)<< endl;
	
	return 0;
}

