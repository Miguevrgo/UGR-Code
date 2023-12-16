/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Reescriba la solución del ejercicio 47 de la Relación de Problemas II usando
	funciones. En dicho ejercicio se pedía leer un número entero positivo y 
	calcular y mostrar su descomposición en factores primos de dos maneras 
	diferentes. Escriba ahora dos funciones void para calcular y mostrar la 
	descomposición en factores primos de n, con las cabeceras:
	
	void CalculaMuestra_DescFactPrimos_1 (int n);
	void CalculaMuestra_DescFactPrimos_2 (int n);
	
	y otras dos para calcular la descomposición en factores primos de n 
	devolviendo la expresión textual en un string. Las cabeceras serán:
	
	string Calcula_DescFactPrimos_1 (int n);
	string Calcula_DescFactPrimos_2 (int n);
	
	Entradas: Valor del numero(numero)
	Salidas: Descomposicion en factores primos de 4 maneras
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <string>

using namespace std;

void CalculaMuestra_DescFactPrimos_1 (int n){
	bool terminar_bucle = false;
	cout << endl << n << " Factorizado manera a) : ";
	if (n==1){
		cout << 1;
	}
	else{
	    for (int i=2;terminar_bucle != true; i++){
	        while (n%i == 0){ //Se puede dividir por el factor
	        	n = n/i; //Actualiza el valor de n una vez dividido
	        	if (n != 1){
		            cout << i << " * ";
	            }
	            else if (n ==1){
	            	cout << i;	
				}
	        }
	        if (n == 1){ //El numero es 1 por lo que no hay mas factores
	            terminar_bucle = true; //Terminamos el bucle
	        }
	    }
    }
}

void CalculaMuestra_DescFactPrimos_2 (int n){
	bool terminar_bucle = false;
	int potencia;
	cout << endl << n << " Factorizado manera b) : ";
	if (n==1){
		cout << 1;
	}
	else{
	    for (int j=2;terminar_bucle != true; j++){
	    	potencia = 0;
	        while (n%j == 0){
	            potencia++;
	            n = n/j;
	        }
	        if (n !=1){
		        if (potencia > 1){
		        	cout << j << "^" << potencia << " * ";	
				}
				else if (potencia == 1){
					cout << j << " * ";
				}
	        }
	        else if (n ==1){
	        	if (potencia > 1){
		        	cout << j << "^" << potencia;	
				}
				else if (potencia == 1){
					cout << j;
				}
		        if (n == 1){
		            terminar_bucle = true; //Terminamos el bucle
	        	}	
			}
	    }
    }
	
}

string Calcula_DescFactPrimos_1 (int n){
	string cadena;
	bool terminar_bucle = false;
	if (n==1){
		cadena = "1";
	}
	else{
		for (int i=2;terminar_bucle != true; i++){
	    	while (n%i == 0){ //si n%i == 0 --> i es un factor
	        	n = n/i; //Actualiza el valor de n
	        	if (n != 1){ //Si n puede ser factorizado mas veces(n!=1)
		            cadena += to_string(i);
		            cadena += " * ";
	            }
	            else if (n ==1){
	            	cadena += to_string(i);
					terminar_bucle = true; //Terminamos el bucle	
				}
	        }
	    }
    }
	return cadena;
}

string Calcula_DescFactPrimos_2 (int n){
	bool terminar_bucle = false;
	int potencia;
	string cadena;
	if (n==1){
		cadena = "1";
	}
	else{
	    for (int j=2;terminar_bucle != true; j++){
	    	potencia = 0;
	        while (n%j == 0){
	            potencia++;
	            n = n/j;
	        }
	        if (n !=1){ //Quedan mas factores (n != 1) (Se añade * al final)
		        if (potencia > 1){
		        	cadena += to_string(j) + "^" + to_string(potencia) + " * "; 
				}
				else if (potencia == 1){
					cadena += to_string(j) + " * ";
				}
	        }
	        else if (n == 1){ //Ultimo factor (n==1)
	        	if (potencia > 1){
		        	cadena += to_string(j) + "^" + to_string(potencia);	
				}
				else if (potencia == 1){
					cadena += to_string(j);
				}
		        if (n == 1){
		            terminar_bucle = true; //Terminamos el bucle
	        	}	
			}
	    }
	}
	return cadena;
}
int main() //Programa principal
{
	int numero;
	bool es_correcto;
	
	//Entrada de datos
	
	do{
		cout << "Introduzca el numero: ";
    	cin >> numero;
    	es_correcto = numero>0;
	}while(!es_correcto);
	
	//Salida
	
	CalculaMuestra_DescFactPrimos_1 (numero);
	CalculaMuestra_DescFactPrimos_2 (numero);
	cout << endl << "Descomposicion metodo 1(string): " 
		 << Calcula_DescFactPrimos_1 (numero);
		 cout << endl << "Descomposicion metodo 2(string): " 
		 << Calcula_DescFactPrimos_2 (numero);

	return 0;
}

