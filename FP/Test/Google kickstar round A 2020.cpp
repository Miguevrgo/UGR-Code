/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
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













