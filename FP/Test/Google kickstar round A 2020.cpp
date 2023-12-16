/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <algorithm>
using namespace std;

int main() //Programa principal
{
	
	int a[1000];
	for (int i=0;i<10;i++){
		cin >> a[i];
	}
	sort (a,a+10);
	for (int i =0;i<10;i++)
	cout << a[i] << " ";
}













