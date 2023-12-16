/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath>
#include <stdlib.h>
using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/
const int MAX_COEF = 500; //Maximos coeficientes de Bezout en Valor abs
/*****************************************************************************
*							  FUNCIONES										 *
*****************************************************************************/
int main() //Programa principal
{
	long int a; //Numero completo
	long int resto; // A * X = resto mod(modulo)
	long int exponente;
	long int base;
	long int modulo;
	const int TERMINADOR = 3;
	int eleccion;
	int k;
	
	
	//Sistemas Congruencias
	long int COEF_A;
	long int COEF_B;
	long int COEF_C;
	
	//Auxiliares
	
	long int COPIA=0; //Copia del modulo
	long int B=1;
	
	
	//Entrada de datos
	
	
	while (eleccion!=TERMINADOR){
		cout << "\nMenu de Opciones" << endl;        
        cout << "[1] Resolver conguencia" << endl; 
        cout << "[2] Resolver ecuacion Diofantica" << endl;
        cout << "[X] Salir" << endl;
        cin >> eleccion;
		system("cls");
		switch(eleccion){
			case 1:
				B=1;
				cout << "Base:";
				cin >> base;
				cout << "Exponente:";
				cin >> exponente;
				cout << "Congruente con:";
				cin >> resto;
				cout << "Modulo:";
				cin >> modulo;
				cout << "\n\n";
				COPIA = modulo - 1; //copia
		
				a = pow(base,exponente);
				
				for (long int c=COPIA;c>=0;c--){
					if (((a*c)%modulo) == resto){
						cout << "Solucion " << B << ": " << c << "   => x = " 
							 << c << " + " << modulo << "k" << "\n";
						B++;
					}
				}
				if (B==1){
						cout << "La congruencia no tiene solucion o soy bobo y " 
							 << "he hecho el programa mal :)";
				}
				break;
			case 2:
				k=1;
				cout << "Ax+By=C\n";
				cout << "Introduzca A:";
				cin >> COEF_A;
				cout << "Introduzca B:";
				cin >> COEF_B;
				cout << "Introduzca C:";
				cin >> COEF_C;
				for (int i=-MAX_COEF;i<MAX_COEF;i++){
					for (int j=-MAX_COEF;j<MAX_COEF;j++){
						if ((COEF_A*i+COEF_B*j)==COEF_C){
							cout << "Solucion" << k << ": " << COEF_A << "(" 
								 << i << ")  +  " << COEF_B << "(" << j 
								 << ")  =  " << COEF_C << "\n"; 
							k++;
						}
					}
				}
			default:
            	cout << "Opcion no valida" << endl;
            	break;			
		}
	}
		
	return 0;
}

