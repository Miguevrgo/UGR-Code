/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Cread un programa que lea el valor de la edad (dato de tipo entero) y 
	salario (dato de tipo real) de una persona. Subid el salario un 4 % si es 
	mayor de 65 o menor de 35 años. Si además de cumplir la anterior condición,
	también tiene un salario inferior a	300 euros, se le subirá otro 3 %, 
	mientras que si su salario es mayor o igual que 300 euros pero inferior a 
	900 euros se le subirá un sólo el 1.5 %.Imprimid el resultado por pantalla
	indicando qué subidas se han aplicado
	
	Entradas: Valores de edad y salario(edad,salario)
	Salidas: Valor del nuevo salario (nuevo_salario)
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	int edad;
	double salario;
	double nuevo_salario;
	const int MAYOR_EDAD = 65;
	const int MENOR_EDAD = 35;
	const int SALARIO_INFERIOR = 300;
	const int SALARIO_SUPERIOR = 900;
	const double INCREM_EDAD = 1.04; //Incremento por la edad
	const double INCREM_SALARIO_INF = 0.03; //Incremento en el salario inferior
	const double INCREM_SALARIO_SUP = 0.015; //Incremento en el salario superior

	//Entrada de datos
	
	cout << "Edad: ";
    cin >> edad;
    if (edad<=0){
    	cout <<"Introduce una edad valida: ";
    	cin >> edad;
	}
    cout << "Salario: ";
    cin >> salario;
    if (salario<=0){
    	cout <<"Introduce un salario valido: ";
    	cin >> salario;
	}
	
	//Cálculos
	
	enum class TipoSueldo {subida0,subida1,subida2,subida3};
	
	TipoSueldo incremento;
	
	if ((edad>MAYOR_EDAD) || (edad<MENOR_EDAD)){
		if (salario<SALARIO_INFERIOR){
			incremento = TipoSueldo::subida2;
		}
		else if ((salario>=SALARIO_INFERIOR) && (salario<SALARIO_SUPERIOR)){
			incremento = TipoSueldo::subida3;
		}
		else {
			incremento = TipoSueldo::subida1;
		}
	}
	else{
		incremento = TipoSueldo::subida0;
	}
	
	//Salida
	
	cout << endl;
	
	switch (incremento) {
		case(TipoSueldo::subida0) :
			nuevo_salario = salario;
			break;
		case(TipoSueldo::subida1) :
			nuevo_salario = salario*INCREM_EDAD;
			break;
		case(TipoSueldo::subida2) :
			nuevo_salario = salario*(INCREM_EDAD+INCREM_SALARIO_INF);
			break;
		case(TipoSueldo::subida3) :
			nuevo_salario = salario*(INCREM_EDAD+INCREM_SALARIO_SUP);
			break;
	}
	
	cout << "Nuevo salario: " << nuevo_salario;
	return 0;
}

