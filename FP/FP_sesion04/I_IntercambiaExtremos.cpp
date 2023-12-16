/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Escriba un programa que lea un n�mero entero (original) y construya otro a 
	partirde �l (nuevo) intercambiando la primera y la �ltima cifra. Despu�s 
	indicar� si la primera cifra de original es igual, mayor o menor que que la
	�ltima del mismo valor (h�galo comparando original y nuevo).
	
	Entradas: Valor del numero original(original)
	Salidas: Valor del numero intercambiado(nuevo)
	
	EXPLICACION_1: Se calculan el numero de digitos del numero original,
	restando 1 ya que nos interesa que al dividir por 10^longitud se obtenga
	el primer digito y no 0.XXX que seria lo que se obtendria si dividiesemos
	por 10^numero de digitos totales.
	
	EXPLICACION_2: Para obtener el ultimo digito podemos dividir entre 10
	y "quedarnos" con la parte decimal o equivalentemente hacer el modulo
	y "quedarnos" con el resto.
	
	EXPLICACION_3: Tras las operaciones obtenemos y guardamos los digitos  
	tras el primer digito y eliminamos el ultimo digito que ya hemos 
	calculado previamente dividiendo por 10 al final.
	
	EXPLICACION_4: Aqui se coloca el numero con las posiciones invertidas
	correctamente, concretamente lo que se esta haciendo es sumar el 
	cada numero de tal manera que esten en su posicion correspondiente. 
	
****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
#include <cmath> //Inclusi�n de los recurso matem�ticos
using namespace std;

int main() //Programa principal
{
	int original;
	int original_a; //Valor de original que se va a mantener constante
	int nuevo;
	int primer_digito;
	int ultimo_digito;
	int longitud;
	int auxiliar;
	bool menor;
	bool mayor;
	bool igual;

	//Entrada de datos
	
	cout << "Numero original: ";
    cin >> original;
	
	//C�lculos
	
	original_a = original; //Guarda el valor de la variable nuevo
	
	longitud = log10(original); // Calculo numero de digitos-->EXPLICACION_1
	
	primer_digito = original / (pow(10, longitud)); // Primer digito
	ultimo_digito = original % 10; //Ultimo digito-->EXPLICACION_2
	
	auxiliar = (primer_digito * pow(10, longitud));
	original = (original % auxiliar)/10; //EXPLICACION_3
	
	nuevo = ultimo_digito*pow(10,longitud) + original*10 + primer_digito; 
	//EXPLICACION_4
	
	
	menor = original_a < nuevo; //Devuelve true si es menor
	mayor = original_a > nuevo;	//Devuelve true si es mayor
	igual = original_a == nuevo;//Devuelve true si es igual
	
	//Salida
	
	cout << "Numero nuevo: " << nuevo; 
	cout << boolalpha << "\nNumero original menor que nuevo: " << menor;
	cout << "\nNumero original mayor que nuevo: " << mayor;
	cout << "\nNumero original igual que nuevo: " << igual;

	return 0;
}

