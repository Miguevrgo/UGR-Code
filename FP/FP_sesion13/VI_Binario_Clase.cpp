/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Queremos disponer de una clase que nos permita trabajar con datos binarios 
	(la clase Bin) y realizar las operaciones básicas típicas sobre éstos.
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath>
#include <string>

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/
/*****************************************************************************
*							   CLASES										 *
*****************************************************************************/

class Bin{
private:

	unsigned int valor_bin; //PRE: 0 <= valor_bin < 2^{32}-1

public:

	//Constructor vacio
	Bin(void) : valor_bin(0){}

	//Constructor que recibe un unsigned int
	Bin(unsigned int el_valor_inicial) : valor_bin(el_valor_inicial){}

	//Constructor que recibe un string
	Bin(string el_valor_inicial)
	{
		SetValor(el_valor_inicial);
	}

	void SetValor (unsigned int el_valor){
		valor_bin = el_valor;
	}

 	void SetValor (string el_valor){
		valor_bin = BinToDec(el_valor);
	}

 	int MinNumBits (void){
		int n=0; //Representa el exponente del 2
		bool esta_contenido = false;
		while (!esta_contenido){
			if (valor_bin <= pow(2,n)){
				esta_contenido = true;
			}
			else{
				n++; //Si no esta contyenido en 2^n, incrementamos n
			}
		}
		return (n); //El exponente es el numero de bits necesarios
	}

	unsigned int GetValorDecimal (void){
		return valor_bin;
	}

	string ToString (int num_casillas){
		string cad;
		cad = "[" + DecToBin(valor_bin,num_casillas) + "]";
		return (cad);
	}

	//Metodos Binarios
	//Pre: otro+este <= 2^32 -1
	Bin Suma (Bin otro){
		unsigned int sum = otro.GetValorDecimal() + GetValorDecimal();
		Bin suma(sum);
		return (suma);
	}
	//Pre: este-otro > 0
	Bin Resta (Bin otro){
		unsigned int res = GetValorDecimal() - otro.GetValorDecimal();
		Bin resta(res);
		return (resta);
	}

	Bin AND (Bin otro){
		Bin nuevo(otro.GetValorDecimal()&valor_bin);
		return(nuevo);
	}

	Bin OR (Bin otro){
		Bin nuevo(otro.GetValorDecimal()|valor_bin);
		return(nuevo);
	}

	Bin DespDcha (int veces){
		unsigned int aux = valor_bin;
		aux = aux >> veces;
		Bin auxiliar(aux);
		return(auxiliar);
	}

	Bin DespIzda (int veces){
		unsigned int aux = valor_bin;
		aux = aux << veces;
		Bin auxiliar(aux);
		return(auxiliar);
	}

private:
	unsigned int BinToDec(string cad){
		unsigned int entero;
		for (int i=0;i <= (int)cad.length()-1;i++){
			if (cad[i] == '1'){	//Si el numero en la posicion vale 1:
				
				//Sumamos a entero 2 elevado a la posicion en la que esta el 1,
				//Teniendo en cuenta que la izquierda representa los valores mas
				//Altos, y restamos 1 para tener en cuenta que la cadena empieza 
				//Con posicion 0
				
				entero += pow(2,(int)cad.length()-i-1); 
			}
		}
		return(entero);
	}
	string DecToBin(unsigned int num_decimal,int num_casillas = 32){
		string n_binario;
		while (num_decimal != 0) { // while (n)

			// Comparar el bit menos significativo con 1  
			
			if (num_decimal & 1) 
				n_binario = "1" + n_binario;  	// Es 1
			else 
				n_binario = "0" + n_binario;	// No es 1 (es 0)
			
			num_decimal >>= 1; // Desplazar a la derecha n (n /= 2)
		}
		if (n_binario.length()<num_casillas){
			int diferencia = num_casillas-n_binario.length();
			while (diferencia--){
				n_binario.append("0",n_binario.length()+1);
			}
		}
		else{
			int diferencia = n_binario.length()-num_casillas;
			while (diferencia--){
				n_binario.erase(n_binario.begin());
			}
		}
		return (n_binario);
	}

};


int main() //Programa principal
{
	


	
	//Cálculos
	
	//300 en binario equivale a 100101100
	Bin otro_binario(300);
	cout << otro_binario.ToString(otro_binario.MinNumBits());
	Bin un_binario = otro_binario.DespDcha(1);
	cout << otro_binario.ToString(un_binario.MinNumBits());
	


	//Salida
	


	return 0;
}

