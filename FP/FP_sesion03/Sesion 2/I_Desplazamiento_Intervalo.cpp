/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez
	Se pide construir un programa que lea dos enteros minimo y maximo que
	determinarán el intervalo [minimo, maximo] (supondremos que el usuario 
	introduce como maximo un valor mayor o igual que minimo). A continuación 
	el programa leerá un valor entero desplazamiento (supondremos que el
	usuario introduce un valor entre 0 y maximo - minimo). Finalmente, el 
	programa leerá un entero a_desplazar
	
	Entradas:Valores minimo y maximo del intervalo, el número a desplazar 
	y el numero de posiciones que se desplaza(min)(max)(a_desplazar)
	(desplazamiento)
	Salidas: El valor de la posición final(posicion_final)
	
	Para solucionar este programa, he decidido calcular la amplitud del 
	intervalo, y la diferencia entre el valor desplzado y el minimo, esto
	nos sirve para saber cuantas unidades se desplaza respecto del minimo
	y si estas unidades son superiores al valor maximo del intervalo,
	entonces el resto de estas unidades respecto del valor de la amplitud
	se sumará al valor inicial, realizando un ciclo.
	
	Se podria haber hecho de otra manera utilizando los condicionales if
	pero este metodo es el mas adecuado al contexto de curso actual.

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	int min;
	int max;
	int a_desplazar;
	int desplazamiento;
	int desplazado;
	int posicion_final;
	int amplitud;
	
	// Entrada de datos
	
	cout << "Introduzca el minimo del intervalo: ";
	cin >> min;
	cout << "Introduzca el maximo del intervalo: ";
	cin >> max;
	cout << "Introduzca el numero que desea desplazar: ";
	cin >> a_desplazar;
	cout << "Introduzca el numero de desplazamientos: ";
	cin >> desplazamiento;
	
	//Cálculos
	
	desplazado = a_desplazar + desplazamiento;
	amplitud = (max-min)+1; //Sumamos 1 para contar el valor del minimo
	posicion_final = min + ((desplazado-min)%amplitud);
	
	//Salida
	
	cout << "La posicion final del numero es: " << posicion_final;

	return 0;
}

