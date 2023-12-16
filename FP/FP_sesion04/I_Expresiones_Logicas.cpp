/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Escriba expresiones lógicas para reflejar las situaciones que se describen 
	a continuación. Para cada caso, el resultado debe guardarse en una variable 
	lógica (escoja un nombre adecuado).
	a) El número de votos emitidos totales es mayor que el número de votantes.
	b) El número de votos válidos no es igual a la suma de los votos recibidos 
	por las tres opciones.
	c) El número de votos registrados es igual a la suma de los votos válidos y 
	nulos.
	d) Gana la opción A.
	e) Gana la opción B.
	f) Gana la opción C.
	g) Empatan dos opciones.
	h) Hay un empate técnico entre las opciones A y B. Definimos que ocurre un 
	empate técnico cuando la diferencia entre los dos valores es menor que el 
	5 % de su suma.
	i) La opción A obtiene mayoría absoluta.
	j) La coalición A-C obtiene mayoría absoluta.
	k) Hay una coalición de dos opciones que obtiene mayoría absoluta.
	l) La opción B obtiene menos de 3 % de los votos válidos registrados.
	m) La participación es mayor que el 75 % del censo de votantes.
	n) Queremos saber si la opción A puede gobernar "sólo o en compañía 
	de otros".
	ñ) El número de abstenciones es mayor que el número de votos válidos.
	o) El número de abstenciones es mayor que el número de votos válidos, 
	pero las abstenciones no son mayores que los votos nulos.
	p) El número de votos por correo es mayor que el 20 % de los votos 
	presenciales o el número de abstenciones.
	q) El número de votos nulos por correo es mayor que el número de votos 
	nulos presenciales.
	r) El número de votos nulos por correo es mayor que el número de votos 
	válidos por correo.
	
	Salidas: a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S
#include <cmath> //Inclusion recursos matematicos

using namespace std;

int main() //Programa principal
{
	const int VOTANTES = 1000;			// Número de votantes totales
    
    int votos_emitidos = 700;			// Número total de de votos registrados
    int votos_presenciales = 500;		// Número total de de votos presenciales
    int votos_correo = 200;        		// Número total de de votos por correo
    
    int votos_validos = 600;			// Votos registrados válidos
    int votos_nulos = 100;				// Votos registrados nulos
    
    int votos_validos_correo = 50;		// Votos válidos por correo
    int votos_validos_presenciales = 550; // Votos válidos presenciales
    
    int votos_A = 400;
    int votos_B = 300;
    int votos_C = 150;
	
	//Cálculos

	// a) El núm. de votos emitidos totales es mayor que el núm. de votantes.

    bool fraude_num_votos =  (votos_emitidos > VOTANTES);

    cout << endl;
    cout << "a) Fraude num.votos = " << fraude_num_votos;

    // b) El número de votos válidos no es igual a la suma de los votos
    // recibidos por las tres opciones.
    
    int  recuento_votos = votos_A + votos_B + votos_C;
    bool error_recuento_votos = (recuento_votos != votos_validos);
    
    cout << endl;
    cout << "b) Error recuento votos = " << error_recuento_votos;
    
    // c) El número de votos registrados es igual a la suma de los votos válidos 
	// y nulos.
	
	int recuento_votos_registrados = votos_validos + votos_nulos;
	bool error_votos_registrados 
	= (recuento_votos_registrados != votos_emitidos);
	
	cout << endl;
	cout << "c) Error votos registrados =  " << error_votos_registrados;
	
	// d) Gana la opción A.
	
	bool gana_a = (votos_A > votos_B) && (votos_A > votos_C);
	
	cout << endl;
	cout << "d) Gana la opcion A = " << gana_a;
	
	// e) Gana la opción B.
	
	bool gana_b = (votos_B > votos_A) && (votos_B > votos_C);
	
	cout << endl;
	cout << "e) Gana la opcion B = " << gana_b;
	
	// f) Gana la opción C.
	
	bool gana_c = (votos_C > votos_A) && (votos_C > votos_B);
	
	cout << endl;
	cout << "f) Gana la opcion C = " << gana_c;
	
	// g) Empatan dos opciones.
	
	bool empate = (votos_B == votos_A) || (votos_B == votos_C)
	||(votos_C == votos_A);
	
	cout << endl;
	cout << "g) Hay empate = " << empate;
	
	// h) Hay un empate técnico entre las opciones A y B. Definimos que ocurre 
	// un empate técnico cuando la diferencia entre los dos valores es menor 	 
	// que el 5 % de su suma.
	
	const double PORCENTAJE = 0.05;
	const int DIF_RESTA = abs(votos_A - votos_B);
	const int SUMA_A_B = votos_A + votos_B;
	bool empate_tecnico = DIF_RESTA < (SUMA_A_B*PORCENTAJE);
	
	cout << endl;
	cout << "h) Hay empate tecnico = " << empate_tecnico;
	
	// i) La opción A obtiene mayoría absoluta.
	
	const double mayoria_absoluta = 0.5;
	bool mayoria_absoluta_a = votos_A > (recuento_votos * mayoria_absoluta);
	
	cout << endl;
	cout << "i) La opcion A gana por mayoria absoluta = " << mayoria_absoluta_a;
	
	// j) La coalición A-C obtiene mayoría absoluta.
	
	const int SUMA_A_C = votos_A + votos_C;
	const int VOTOS_MAYORIA_ABSOLUTA = (recuento_votos*mayoria_absoluta);
	bool mayoria_absoluta_a_c = SUMA_A_C > VOTOS_MAYORIA_ABSOLUTA;
	
	cout << endl;
	cout << "j) La coalicion A-C gana por mayoria absoluta = "  
		 << mayoria_absoluta_a_c;
		 
	// k) Hay una coalición de dos opciones que obtiene mayoría absoluta.
	
	const int SUMA_B_C = votos_B + votos_C;
	bool mayoria_absoluta_coalicion = (SUMA_B_C > VOTOS_MAYORIA_ABSOLUTA)
	|| (SUMA_A_C > VOTOS_MAYORIA_ABSOLUTA) 
	|| (SUMA_A_B > VOTOS_MAYORIA_ABSOLUTA);
	
	cout << endl;
	cout << "k) Una coalicion gana por mayoria absouluta = "
		 << mayoria_absoluta_coalicion;
	
	// l) La opción B obtiene menos de 3 % de los votos válidos registrados.
	
	const int porcentaje_votos_validos = votos_validos * 0.03;
	bool opcion_B_menor_porcentaje = votos_B < porcentaje_votos_validos;
	
	cout << endl;
	cout << "l) Opcion B obtiene menos de 3% = " << opcion_B_menor_porcentaje;
	
	// m) La participación es mayor que el 75 % del censo de votantes.
	
	const double porcentaje_participacion = 0.75;
	bool participacion_mayor = votos_emitidos 
	> VOTANTES * porcentaje_participacion;
	
	cout << endl;
	cout << "m) Participacion es mayor que el 75% = " << participacion_mayor;
	
	// n) Queremos saber si la opción A puede gobernar "sólo o en compañía 
	// de otros".
	
	bool a_gobierna_solo = mayoria_absoluta_a;
	bool a_gobierna_en_comp = (SUMA_A_C > VOTOS_MAYORIA_ABSOLUTA) 
	|| (SUMA_A_B > VOTOS_MAYORIA_ABSOLUTA);
	
	cout << endl;
	cout << "n) A gobierna solo = " << a_gobierna_solo << endl;
	cout << "n) A gobierna en compania = " << a_gobierna_en_comp;
	
	// ñ) El número de abstenciones es mayor que el número de votos válidos.
	const int ABSTENCIONES = recuento_votos- votos_emitidos;
	bool abstenciones_mayor_validos = ABSTENCIONES > votos_validos;
	
	cout << endl;
	cout << "N) Numero de abstenciones mayor que votos validos = " 
		 << abstenciones_mayor_validos; 
		 
	// o) El número de abstenciones es mayor que el número de votos válidos, 
	// pero las abstenciones no son mayores que los votos nulos.
	
	bool abstenciones_mayor_validos_menor_nulos = (ABSTENCIONES > votos_validos)
	&& (votos_nulos > ABSTENCIONES);
	
	cout << endl;
	cout << "o) Numero de abstenciones mayor que votos validos pero " 
		 << "abstenciones menor que nulos = " 
		 << abstenciones_mayor_validos_menor_nulos;
		 
	// p) El número de votos por correo es mayor que el 20 % de los votos 
	// presenciales o el número de abstenciones.
	
	const double PORCENTAJE_PRESENCIALES = 0.2;
	bool votos_correo_mayor_presenciales_o_abstenciones = (votos_correo 
	> votos_presenciales * PORCENTAJE_PRESENCIALES) 
	|| (votos_correo > ABSTENCIONES);
	
	cout << endl;
	cout << "El numero de votos por correo es mayor que el 20 % de los votos " 
		 << "presenciales o el numero de abstenciones = "
		 << votos_correo_mayor_presenciales_o_abstenciones;
		 
	// q) El número de votos nulos por correo es mayor que el número de votos 
	// nulos presenciales.
	const int VOTOS_NULOS_CORREO = votos_correo - votos_validos_correo;
	const int VOTOS_NULOS_PRESENCIAL = votos_correo - votos_validos_presenciales;
	bool votos_nulos_correo_mayor_nulos_presenciales = VOTOS_NULOS_CORREO
	> VOTOS_NULOS_PRESENCIAL;
	
	cout << endl;
	cout << "q) Numero de votos nulos por correo mayor que el numero de votos "
		 << "nulos presenciales = " 
		 << votos_nulos_correo_mayor_nulos_presenciales;
		 
	//r) El número de votos nulos por correo es mayor que el número de votos 
	//válidos por correo.
	
	bool votos_nulos_correo_mayor_votos_validos_correo = VOTOS_NULOS_CORREO 
	> votos_validos_correo;
	
	cout << endl;
	cout << "El numero de votos nulos por correo es mayor que el numero "
		 <<"de votos validos por correo = " 
		 << votos_nulos_correo_mayor_votos_validos_correo;
	
	return 0;
}

