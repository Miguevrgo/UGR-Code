/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Tome como referencia la soluci�n al ejercicio 13 de esta misma relaci�n
	de problemas. Ahora deber� emplear un tipo enumerado que permita guardar 
	el tipo de car�cter de letra_original. Considere que ahora podr�a ser: 
	una letra may�scula, una letra min�scula, un d�gito u otro car�cter.
	Importante: las vocales con tilde (may�sculas y min�sculas) y las letras �,
	�, � y � se englobar�n en la categor�a de otros por simplificar la soluci�n.
	
	Entradas: Valor del caracter leido (letra_original)
	Salidas: Valor del caracter en minuscula o mayuscula(letra_convertida)
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	char letra_convertida; 
	char letra_original;
	const int MIN_EN_MAY = 'a'-'A'; //Diferencia entre minuscula y mayuscula
	
	//Entrada de datos
	
	cout << "Introduzca una letra  --> ";
	cin >> letra_original;

	//C�lculos
	
	enum class TipoCaracter {Mayuscula, Minuscula, Digito, Otros};

	TipoCaracter tipo;
	
	if ((letra_original >= 'A') && (letra_original <= 'Z')){
		tipo = TipoCaracter::Mayuscula;
	}
	else{
	
		if ((letra_original >= 'a') && (letra_original <= 'z')){
			tipo = TipoCaracter::Minuscula;
		}	
		else{
		
			if ((letra_original >= '0')&&(letra_original <= '9')){
				tipo = TipoCaracter::Digito;
			}
			else{
				tipo = TipoCaracter::Otros;
			}				
		}
	}
	
	switch (tipo) {
		
		case (TipoCaracter::Mayuscula) : 
			letra_convertida = letra_original + MIN_EN_MAY;
			break;	
		case (TipoCaracter::Minuscula) : 
			letra_convertida = letra_original - MIN_EN_MAY;
			break;	
		default: 
			letra_convertida = letra_original;
			break;
	}

	//Salida
	
	cout << endl;
	cout << "Letra original : " << letra_original << endl;

	
	switch (tipo) {
		
		case (TipoCaracter::Mayuscula) : 		
			cout << "La letra era una mayuscula. Una vez convertida es: "
			     << letra_convertida;
			break;	
		case (TipoCaracter::Minuscula) : 
			cout << "La letra era una minuscula. Una vez convertida es: "
				 << letra_convertida;
			break;	
		default: 
			cout << "El caracter no era una letra.";
			break;
	}

   return 0;
}

