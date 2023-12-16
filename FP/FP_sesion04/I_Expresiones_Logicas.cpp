/****************************************************************************
	FUNDAMENTOS DE PROGRAMACI�N

	Miguel �ngel De La Vega Rodr�guez    |	Grupo A1
	Escriba expresiones l�gicas para reflejar las situaciones que se describen 
	a continuaci�n. Para cada caso, el resultado debe guardarse en una variable 
	l�gica (escoja un nombre adecuado).
	a) El n�mero de votos emitidos totales es mayor que el n�mero de votantes.
	b) El n�mero de votos v�lidos no es igual a la suma de los votos recibidos 
	por las tres opciones.
	c) El n�mero de votos registrados es igual a la suma de los votos v�lidos y 
	nulos.
	d) Gana la opci�n A.
	e) Gana la opci�n B.
	f) Gana la opci�n C.
	g) Empatan dos opciones.
	h) Hay un empate t�cnico entre las opciones A y B. Definimos que ocurre un 
	empate t�cnico cuando la diferencia entre los dos valores es menor que el 
	5 % de su suma.
	i) La opci�n A obtiene mayor�a absoluta.
	j) La coalici�n A-C obtiene mayor�a absoluta.
	k) Hay una coalici�n de dos opciones que obtiene mayor�a absoluta.
	l) La opci�n B obtiene menos de 3 % de los votos v�lidos registrados.
	m) La participaci�n es mayor que el 75 % del censo de votantes.
	n) Queremos saber si la opci�n A puede gobernar "s�lo o en compa��a 
	de otros".
	�) El n�mero de abstenciones es mayor que el n�mero de votos v�lidos.
	o) El n�mero de abstenciones es mayor que el n�mero de votos v�lidos, 
	pero las abstenciones no son mayores que los votos nulos.
	p) El n�mero de votos por correo es mayor que el 20 % de los votos 
	presenciales o el n�mero de abstenciones.
	q) El n�mero de votos nulos por correo es mayor que el n�mero de votos 
	nulos presenciales.
	r) El n�mero de votos nulos por correo es mayor que el n�mero de votos 
	v�lidos por correo.
	
	Salidas: a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r

****************************************************************************/

#include <iostream> //Inclusi�n de los recursos de E/S
#include <cmath> //Inclusion recursos matematicos

using namespace std;

int main() //Programa principal
{
	const int VOTANTES = 1000;			// N�mero de votantes totales
    
    int votos_emitidos = 700;			// N�mero total de de votos registrados
    int votos_presenciales = 500;		// N�mero total de de votos presenciales
    int votos_correo = 200;        		// N�mero total de de votos por correo
    
    int votos_validos = 600;			// Votos registrados v�lidos
    int votos_nulos = 100;				// Votos registrados nulos
    
    int votos_validos_correo = 50;		// Votos v�lidos por correo
    int votos_validos_presenciales = 550; // Votos v�lidos presenciales
    
    int votos_A = 400;
    int votos_B = 300;
    int votos_C = 150;
	
	//C�lculos

	// a) El n�m. de votos emitidos totales es mayor que el n�m. de votantes.

    bool fraude_num_votos =  (votos_emitidos > VOTANTES);

    cout << endl;
    cout << "a) Fraude num.votos = " << fraude_num_votos;

    // b) El n�mero de votos v�lidos no es igual a la suma de los votos
    // recibidos por las tres opciones.
    
    int  recuento_votos = votos_A + votos_B + votos_C;
    bool error_recuento_votos = (recuento_votos != votos_validos);
    
    cout << endl;
    cout << "b) Error recuento votos = " << error_recuento_votos;
    
    // c) El n�mero de votos registrados es igual a la suma de los votos v�lidos 
	// y nulos.
	
	int recuento_votos_registrados = votos_validos + votos_nulos;
	bool error_votos_registrados 
	= (recuento_votos_registrados != votos_emitidos);
	
	cout << endl;
	cout << "c) Error votos registrados =  " << error_votos_registrados;
	
	// d) Gana la opci�n A.
	
	bool gana_a = (votos_A > votos_B) && (votos_A > votos_C);
	
	cout << endl;
	cout << "d) Gana la opcion A = " << gana_a;
	
	// e) Gana la opci�n B.
	
	bool gana_b = (votos_B > votos_A) && (votos_B > votos_C);
	
	cout << endl;
	cout << "e) Gana la opcion B = " << gana_b;
	
	// f) Gana la opci�n C.
	
	bool gana_c = (votos_C > votos_A) && (votos_C > votos_B);
	
	cout << endl;
	cout << "f) Gana la opcion C = " << gana_c;
	
	// g) Empatan dos opciones.
	
	bool empate = (votos_B == votos_A) || (votos_B == votos_C)
	||(votos_C == votos_A);
	
	cout << endl;
	cout << "g) Hay empate = " << empate;
	
	// h) Hay un empate t�cnico entre las opciones A y B. Definimos que ocurre 
	// un empate t�cnico cuando la diferencia entre los dos valores es menor 	 
	// que el 5 % de su suma.
	
	const double PORCENTAJE = 0.05;
	const int DIF_RESTA = abs(votos_A - votos_B);
	const int SUMA_A_B = votos_A + votos_B;
	bool empate_tecnico = DIF_RESTA < (SUMA_A_B*PORCENTAJE);
	
	cout << endl;
	cout << "h) Hay empate tecnico = " << empate_tecnico;
	
	// i) La opci�n A obtiene mayor�a absoluta.
	
	const double mayoria_absoluta = 0.5;
	bool mayoria_absoluta_a = votos_A > (recuento_votos * mayoria_absoluta);
	
	cout << endl;
	cout << "i) La opcion A gana por mayoria absoluta = " << mayoria_absoluta_a;
	
	// j) La coalici�n A-C obtiene mayor�a absoluta.
	
	const int SUMA_A_C = votos_A + votos_C;
	const int VOTOS_MAYORIA_ABSOLUTA = (recuento_votos*mayoria_absoluta);
	bool mayoria_absoluta_a_c = SUMA_A_C > VOTOS_MAYORIA_ABSOLUTA;
	
	cout << endl;
	cout << "j) La coalicion A-C gana por mayoria absoluta = "  
		 << mayoria_absoluta_a_c;
		 
	// k) Hay una coalici�n de dos opciones que obtiene mayor�a absoluta.
	
	const int SUMA_B_C = votos_B + votos_C;
	bool mayoria_absoluta_coalicion = (SUMA_B_C > VOTOS_MAYORIA_ABSOLUTA)
	|| (SUMA_A_C > VOTOS_MAYORIA_ABSOLUTA) 
	|| (SUMA_A_B > VOTOS_MAYORIA_ABSOLUTA);
	
	cout << endl;
	cout << "k) Una coalicion gana por mayoria absouluta = "
		 << mayoria_absoluta_coalicion;
	
	// l) La opci�n B obtiene menos de 3 % de los votos v�lidos registrados.
	
	const int porcentaje_votos_validos = votos_validos * 0.03;
	bool opcion_B_menor_porcentaje = votos_B < porcentaje_votos_validos;
	
	cout << endl;
	cout << "l) Opcion B obtiene menos de 3% = " << opcion_B_menor_porcentaje;
	
	// m) La participaci�n es mayor que el 75 % del censo de votantes.
	
	const double porcentaje_participacion = 0.75;
	bool participacion_mayor = votos_emitidos 
	> VOTANTES * porcentaje_participacion;
	
	cout << endl;
	cout << "m) Participacion es mayor que el 75% = " << participacion_mayor;
	
	// n) Queremos saber si la opci�n A puede gobernar "s�lo o en compa��a 
	// de otros".
	
	bool a_gobierna_solo = mayoria_absoluta_a;
	bool a_gobierna_en_comp = (SUMA_A_C > VOTOS_MAYORIA_ABSOLUTA) 
	|| (SUMA_A_B > VOTOS_MAYORIA_ABSOLUTA);
	
	cout << endl;
	cout << "n) A gobierna solo = " << a_gobierna_solo << endl;
	cout << "n) A gobierna en compania = " << a_gobierna_en_comp;
	
	// �) El n�mero de abstenciones es mayor que el n�mero de votos v�lidos.
	const int ABSTENCIONES = recuento_votos- votos_emitidos;
	bool abstenciones_mayor_validos = ABSTENCIONES > votos_validos;
	
	cout << endl;
	cout << "N) Numero de abstenciones mayor que votos validos = " 
		 << abstenciones_mayor_validos; 
		 
	// o) El n�mero de abstenciones es mayor que el n�mero de votos v�lidos, 
	// pero las abstenciones no son mayores que los votos nulos.
	
	bool abstenciones_mayor_validos_menor_nulos = (ABSTENCIONES > votos_validos)
	&& (votos_nulos > ABSTENCIONES);
	
	cout << endl;
	cout << "o) Numero de abstenciones mayor que votos validos pero " 
		 << "abstenciones menor que nulos = " 
		 << abstenciones_mayor_validos_menor_nulos;
		 
	// p) El n�mero de votos por correo es mayor que el 20 % de los votos 
	// presenciales o el n�mero de abstenciones.
	
	const double PORCENTAJE_PRESENCIALES = 0.2;
	bool votos_correo_mayor_presenciales_o_abstenciones = (votos_correo 
	> votos_presenciales * PORCENTAJE_PRESENCIALES) 
	|| (votos_correo > ABSTENCIONES);
	
	cout << endl;
	cout << "El numero de votos por correo es mayor que el 20 % de los votos " 
		 << "presenciales o el numero de abstenciones = "
		 << votos_correo_mayor_presenciales_o_abstenciones;
		 
	// q) El n�mero de votos nulos por correo es mayor que el n�mero de votos 
	// nulos presenciales.
	const int VOTOS_NULOS_CORREO = votos_correo - votos_validos_correo;
	const int VOTOS_NULOS_PRESENCIAL = votos_correo - votos_validos_presenciales;
	bool votos_nulos_correo_mayor_nulos_presenciales = VOTOS_NULOS_CORREO
	> VOTOS_NULOS_PRESENCIAL;
	
	cout << endl;
	cout << "q) Numero de votos nulos por correo mayor que el numero de votos "
		 << "nulos presenciales = " 
		 << votos_nulos_correo_mayor_nulos_presenciales;
		 
	//r) El n�mero de votos nulos por correo es mayor que el n�mero de votos 
	//v�lidos por correo.
	
	bool votos_nulos_correo_mayor_votos_validos_correo = VOTOS_NULOS_CORREO 
	> votos_validos_correo;
	
	cout << endl;
	cout << "El numero de votos nulos por correo es mayor que el numero "
		 <<"de votos validos por correo = " 
		 << votos_nulos_correo_mayor_votos_validos_correo;
	
	return 0;
}

