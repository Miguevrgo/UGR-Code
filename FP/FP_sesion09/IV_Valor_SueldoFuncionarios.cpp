/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S

using namespace std;


int main() //Programa principal
{	
	double IPC[32];
	IPC[0]=6.5;
	IPC[1]=5.5;
	IPC[2]=5.3;
	IPC[3]=4.9;
	IPC[4]=4.3;
	IPC[5]=4.3;
	IPC[6]=3.2;
	IPC[7]=2.0;
	IPC[8]=1.4;
	IPC[9]=2.9;
	IPC[10]=4.0;
	IPC[11]=2.7;
	IPC[12]=4.0;
	IPC[13]=2.6;
	IPC[14]=3.2;
	IPC[15]=3.7;
	IPC[16]=2.7;
	IPC[17]=4.2;
	IPC[18]=1.4;
	IPC[19]=0.8;
	IPC[20]=3.0;
	IPC[21]=2.4;
	IPC[22]=2.9;
	IPC[23]=0.3;
	IPC[24]=-1.0;
	IPC[25]=0.0;
	IPC[26]=1.6;
	IPC[27]=1.1;
	IPC[28]=1.2;
	IPC[29]=0.8;
	IPC[30]=-0.5;
	IPC[31]=6.5;
	double valor_monetario[50];
	double precio_final;
	double IPC_Acumulado;
	double anio_referencia;
	double anio_inicial;
	double anio_final;
	double diferencia;
	bool terminar = false;
	//Entrada de datos
	int i=0;
	while (!terminar){
		IPC_Acumulado = 0;
		cout << "Precio Inicial: ";
		cin >> valor_monetario[i];
		cout << "Anio inicial: ";
		cin >> anio_inicial;
		cout << "Anio final: "; 
		cin >> anio_final;
		//Teniendo en cuenta que empezamos en la posicion 0 en el array, hay que
		//restar el a�o de inicio de la tabla del ipc = 1990
		anio_inicial -= 1990;
		anio_final -= 1990;
		if (anio_inicial>anio_final){
			for (int j = anio_inicial; j>=anio_final;j--){
				IPC_Acumulado -= IPC[j]; 
			}
		}
		else{ //Anio_inicial<anio_final
			for (int j = anio_inicial; j<=anio_final;j++){
				IPC_Acumulado += IPC[j]; 
			}
		}
		precio_final = valor_monetario[i] *(1+IPC_Acumulado/100);
		cout << "El precio final es: " << precio_final << endl;
		diferencia = (precio_final-valor_monetario[i])*100;
		cout << "La diferencia en porcentaje es: " << diferencia;
		cout << "___________________________________________________" << endl;
		if (valor_monetario[i]<0){
			terminar = true; //Termina el bucle cuando se introduce un valor<0
		}
		else{
			i++;
		}
		
	}
	


	return 0;
}


