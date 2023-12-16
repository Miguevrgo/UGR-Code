/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Tome como referencia la solución al ejercicio 13 de esta misma relación
	de problemas. Ahora deberá emplear un tipo enumerado que permita guardar 
	el tipo de carácter de letra_original. Considere que ahora podría ser: 
	una letra mayúscula, una letra minúscula, un dígito u otro carácter.
	Importante: las vocales con tilde (mayúsculas y minúsculas) y las letras ú,
	Ü, ñ y Ñ se englobarán en la categoría de otros por simplificar la solución.
	
	Entradas: Valor del caracter leido (letra_original)
	Salidas: Valor del caracter en minuscula o mayuscula(letra_convertida)
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
	char letra_convertida; 
	char letra_original;
	const int MIN_EN_MAY = 'a'-'A'; //Diferencia entre minuscula y mayuscula
	
	//Entrada de datos
	
	cout << "Introduzca una letra  --> ";
	cin >> letra_original;

	//Cálculos
	
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

