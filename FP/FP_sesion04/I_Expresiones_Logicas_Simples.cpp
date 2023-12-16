/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Escribid una expresi�n l�gica que sea verdadera si una variable de tipo 
	car�cter llamada letra es una letra may�scula y falso en otro caso.
	
	Escribid una expresi�n l�gica que sea verdadera si una variable de tipo 
	entero llamada edad es mayor o igual que 18 y menor que 67.
	
	Escribid una expresi�n l�gica que nos informe cuando un a�o es bisiesto. 
	Los a�os bisiestos son aquellos que o bien son divisibles por 4 pero no 
	por 100, o bien son divisibles por 400.
	
	Escribid una expresi�n l�gica que nos informe si el valor de una variable
	double llamada distancia es menor que la constante LIMITE.
	
	Usad una variable l�gica que registre si el valor de una variable int es
	menor que otra, otra que informe si son iguales y otra que informe si es
	mayor. 
	Aseg�rese que s�lo una, y s�lo una de las tres trendr� el valor true.
	
	
	Entradas: Valores de variables (letra,edad,year,distancia,num1,num2)
	Salidas: Valor de las expresiones logicas(exp_log_1, exp_log_2, exp_log_3,
	exp_log_4, exp_log_5a, exp_log_5b, exp_log_5c)
	
	Voy a usar year en vez de a�o por compatibilidad con la �

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	//Declaracion expresi�n logica 1
	
	char letra;
	bool exp_log_1;
	const int MAYOR_MAYUS = 'Z';
	const int MENOR_MAYUS = 'A';
	
	//Declaracion expresi�n logica 2
	
	int edad;
	bool exp_log_2;
	const int MAYOR_IGUAL_EDAD = 18;
	const int MENOR_EDAD = 67;
	
	//Declaracion expresi�n logica 3
	
	int year;
	bool exp_log_3;
	const int DIVIS_1 = 400;
	const int DIVIS_2 = 100;
	const int DIVIS_3 = 4;
	
	//Declaracion expresi�n logica 4
	
	double distancia;
	bool exp_log_4;
	const double LIMITE = 100;
	
	//Declaracion expresi�n logica 5
	
	int num1,num2;
	bool menor;
	bool mayor;
	bool igual;

	//Entrada de datos expresi�n logica 1
	
	cout << "Letra: ";
    cin >> letra;
    
    //Entrada de datos expresi�n logica 2
	
	cout << "Edad: ";
    cin >> edad;
    
    //Entrada de datos expresi�n logica 3
	
	cout << "Anio: ";
    cin >> year;
    
    //Entrada de datos expresi�n logica 4
	
	cout << "Distancia: ";
    cin >> distancia;
    
    //Entrada de datos expresi�n logica 5
	
	cout << "Numero 1: ";
    cin >> num1;
    cout << "Numero 2: ";
	cin >> num2;
	
	//C�lculos

	exp_log_1 = (letra >= MENOR_MAYUS) && (letra <= MAYOR_MAYUS);
	
	exp_log_2 = (edad >= MAYOR_IGUAL_EDAD) && (edad < MENOR_EDAD);
	cout << exp_log_2;
	
	exp_log_3 = (year % DIVIS_1 == 0) 
	|| ((year % DIVIS_3 == 0) && (year % DIVIS_2 !=0));
	
	exp_log_4 = distancia < LIMITE;
	
	menor = num1 < num2;	//Devuelve true si es menor
	mayor = num1 > num2;	//Devuelve true si es mayor
	igual = num1 == num2;	//Devuelve true si es igual
	
	//Salida
	
	cout << boolalpha << "\nLa primera expresion logica es: " << exp_log_1;
	cout << "\nLa segunda expresion logica es: " << exp_log_2;
	cout << "\nLa tercera expresion logica es: " << exp_log_3;
	cout << "\nLa cuarta expresion logica es: " << exp_log_4;
	cout << "\nNumero 1 menor que Numero 2: " << menor;
	cout << "\nNumero 1 mayor que Numero 2: " << mayor;
	cout << "\nNumero 1 igual que Numero 2: " << igual;
	
	return 0;
}

