/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// RELACIÓN DE PROBLEMAS 2
/*	
	Programa que calcula el número de segundos que han transcurrido entre dos
	instantes. Cada instante se caracteriza por la hora, minuto y segundo.
	los dos instantes pueden pertenecer a dos días consecutivos.
	
	Entradas: hora, minuto y segundo inicial, y hora, minuto y segundo final.
	Salidas:  número de segundos entre los dos instantes dados
	
	NOTA: No transcuren más de 24 h. entre los dos instantes
	
	Esta versión comprueba la validez de los valores leídos usando filtros.
*/
/***************************************************************************/

#include <iostream>
using namespace std;

int main()
{
	const int SEGS_MIN   = 60;  // Segundos en un minuto
	const int MINS_HORA  = 60;	// Minutos en una hora
	const int HORAS_DIAS = 24;	// Horas en un día
	
	const int SEGS_HORA = MINS_HORA * SEGS_MIN; // Segundos en una hora
	const int SEGS_DIA  = HORAS_DIAS*SEGS_HORA;	// Segundos en un día
			
	// Datos de entrada
	int hora_inic, minuto_inic, segundo_inic;
	int hora_fin,  minuto_fin,  segundo_fin;
	
	int num_segs_entre_instantes;  // Resultado



	// Entrada de datos (con filtros)
	
	cout << "Introduzca hora inicial:" << endl;

	do {
		cout << "\tHora:    ";
		cin >> hora_inic;
	} while ((hora_inic<0) || (hora_inic>=HORAS_DIAS)); 
	
	do {
		cout << "\tMinuto:  ";
		cin >> minuto_inic;
	} while ((minuto_inic<0) || (minuto_inic>=MINS_HORA)); 
	
	do {
		cout << "\tSegundo: ";
		cin >> segundo_inic;
	} while ((segundo_inic<0) || (segundo_inic>=SEGS_MIN)); 
	
           
    cout << "Introduzca hora final:" << endl;
    
	do {
		cout << "\tHora:    ";
		cin >> hora_fin;
	} while ((hora_fin<0) || (hora_fin>=HORAS_DIAS)); 
	
	do {
		cout << "\tMinuto:  ";
		cin >> minuto_fin;
	} while ((minuto_fin<0) || (minuto_fin>=MINS_HORA)); 
	
	do {
		cout << "\tSegundo: ";
		cin >> segundo_fin;
	} while ((segundo_fin<0) || (segundo_fin>=SEGS_MIN)); 
	
	// Puedo asegurar es este punto que los datos leídos son correctos.
	
	
	// Cálculos 
	
	/* 	
		En primer lugar se calcula si los dos instantes pertenecen al mismo 
		día o no. Después, se calculan los segundos transcurridos en base 
		al primer resultado.  
	*/
	
	bool mismo_dia;
	
	if (hora_inic < hora_fin) mismo_dia = true;
	else 	
		if (hora_inic > hora_fin) mismo_dia = false;
		else  // hora_inic == hora_fin --> Minutos
			if (minuto_inic < minuto_fin) mismo_dia = true;
			else 
				if (minuto_inic > minuto_fin) mismo_dia = false;
				else // (hora_inic == hora_fin && 
					 //  minuto_inic == minuto_fin) --> Segundos
					if (segundo_inic < segundo_fin) mismo_dia = true;
					else 
						if (segundo_inic > segundo_fin) mismo_dia = false;
						else // (hora_inic == hora_fin && 
					 		 //  minuto_inic == minuto_fin && 
					 		 //  segundo_inic == segundo_fin) --> 0 segundos
							mismo_dia = true;
			
			
	int segs_hora_inic, segs_hora_fin;
	segs_hora_inic = (hora_inic*SEGS_HORA)+(minuto_inic*SEGS_MIN)+segundo_inic;
	segs_hora_fin  = (hora_fin*SEGS_HORA) +(minuto_fin*SEGS_MIN) +segundo_fin;
	
	num_segs_entre_instantes = segs_hora_fin - segs_hora_inic;

	if (!mismo_dia)  
		num_segs_entre_instantes += SEGS_DIA;
	
	
	// Resultado 
	
	cout << endl;
	cout << "Entre las " << hora_inic << ":" << minuto_inic
		 << ":" << segundo_inic << " y las " << hora_fin << ":"
		 << minuto_fin << ":" << segundo_fin << " hay "
		 << num_segs_entre_instantes << " segundos." << endl;
	cout << endl;
	
	if (mismo_dia) 
		cout << "Los dos instantes son del mismo dia." << endl;	
	else 
		cout << "Ha habido cambio de dia." << endl;	
	
	
	return 0;
}
