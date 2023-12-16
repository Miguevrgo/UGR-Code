/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
// cb@decsai.ugr.es
//
// FELIZ NAVIDAD 2022-2023
//
/***************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <string>

#include <random>  // para la generación de números pseudoaleatorios
#include <chrono>  // para la semilla

using namespace std;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class GeneradorAleatorioEnteros
{  
private:
	
	mt19937 generador_mersenne;    // Mersenne twister
	uniform_int_distribution<int>  distribucion_uniforme;
	
	/************************************************************************/
	
	long long Nanosec(){
	return (chrono::high_resolution_clock::now().time_since_epoch().count());
	}
	
	/************************************************************************/ 
	
public:
	
	/************************************************************************/
		
	GeneradorAleatorioEnteros() : GeneradorAleatorioEnteros(0, 1) 
	{ }
	
	/************************************************************************/  
	GeneradorAleatorioEnteros(int min, int max) {
	
		const int A_DESCARTAR = 70000;
		// ACM TOMS Volume 32 Issue 1, March 2006
		
		auto semilla = Nanosec();
		generador_mersenne.seed(semilla);
		generador_mersenne.discard(A_DESCARTAR);
		distribucion_uniforme = uniform_int_distribution<int> (min, max);
	}
	
	/************************************************************************/
	
	int Siguiente(){
	  return (distribucion_uniforme(generador_mersenne));
	}
	
	/************************************************************************/

};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

const int A = 5;		// 5
const int B = 3;		// 3
const int C = 4;		// 4
const int D = 4*C*B; 	// 4*C*B
const int E = 15; 		// 15
const int F = 64; 		// 64
const int G = 42; 		// 42
const int H = 32; 		// 32
const int I = 76; 		// 76

/***************************************************************************/
/***************************************************************************/

void f (int a1, int a2)
{
	GeneradorAleatorioEnteros g(1,100);
	
	for (int z=a1; z<=a2; z++) {

		for (int b=(D-z); b>0; b--)  cout << (char)H; //Linea **********
		
		for (int c=0; c<(2*z)+1; c++) {
			
			int f = g.Siguiente();		
			cout << ((f<E+1)?(char)F:(char)G);
		}	
		cout << endl; 		
	}
}

/***************************************************************************/
/***************************************************************************/

void g (int z)
{
	int p = (C%2==0)?C+1:C;
	int y = D-(p/2);
	
	for (int a=0; a<z/2; a++) {

		for (int b=y; b>0; b--) cout << (char)H;
		for (int c=0; c<p; c++) cout << (char)I;
		cout << endl; 		
	}
}
/***************************************************************************/
/***************************************************************************/

int main (void)
{
	int p = 0; 
	
	if (C>A) p=1; 
	else {
			 
		f (0, B); 
	 
		int m = 1; 
		int x = B;
		
		for (int k=1; k<C; k++) {
			x *= 2;
			f (pow(2,m), x); 
			m++; 
		}
		g (x); 
	}
	return p; 
}

/***************************************************************************/
/***************************************************************************/

