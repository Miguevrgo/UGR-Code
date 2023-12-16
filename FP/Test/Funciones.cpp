

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;




double Gauss (double x, double m, double s)
{
	const double PI = 6 * asin(0.5);
	return (exp (-0.5 * pow ((x - m)/s, 2)) /  (s * sqrt(2*PI)));
}
 


double CDF_1 (double x, double m, double s)
{
	const double SALTO_CDF = 0.001;	


	
	double abscisa_inic = m-(3*s); 
	double abscisa_fin  = x; 

	
	double suma_g_abs = 0.0; 

	
	
	for (double abs=abscisa_inic; abs<=abscisa_fin; abs+=SALTO_CDF) {
	
		double g_abs = Gauss(abs, m, s);  
		suma_g_abs += g_abs; 
	}

	return (suma_g_abs * SALTO_CDF); 

}

double CDF_2 (double x, double m, double s)
{
	const double B0 =  0.231641900;
	const double B1 =  0.319381530;
	const double B2 = -0.356563782;
	const double B3 =  1.781477937;
	const double B4 = -1.821255978;
	const double B5 =  1.330274429;

	// Estandarizar la distribución gaussiana  
	// Si x -> N(m,s) y z = (x-m)/s entonces z -> N(0,1)    
	
	double z = (x-m)/s; // variable aleatoria N(0,1)  
	
	double t = 1.0 / (1 + B0*fabs(z));
	double t2 = t*t;
	double t3 = t2*t; // t*t*t
	double t4 = t3*t; // t*t*t*t
	double t5 = t4*t; // t*t*t*t*t

	double g_std_x = Gauss(fabs(z), 0, 1); 
	double w = 1.0 - g_std_x * (B1*t + B2*t2 + B3*t3 + B4*t4 + B5*t5);

	return (x>=0.0 ? w : 1.0-w);
}

/***************************************************************************/
/***************************************************************************/

int main (void)
{
	const double NUM_STDV = 3.0;
	const double SALTO_X  = 0.25;

	cout.setf(ios::fixed);	
	cout.setf(ios::showpoint);	

	double esperanza, desviacion;


   


	cout << "Parametros de la gaussiana." << endl;
	cout << endl; 
		
	cout << "\tEsperanza = ";
	cin >> esperanza;
	
	do {
		cout << "\tDesviacion tipica = ";
		cin >> desviacion;
	} while (desviacion <= 0);

	cout << endl << endl; 
	
	


	
	double min_x = esperanza - NUM_STDV*desviacion;
	double max_x = esperanza + NUM_STDV*desviacion;
	
	for (double x=min_x; x<=max_x; x+=SALTO_X) {

		double g_x;	    
		double cdf_1_x; 
		double cdf_2_x;
		
		
		g_x     = Gauss (x, esperanza, desviacion);
		cdf_1_x = CDF_1 (x, esperanza, desviacion);
		cdf_2_x = CDF_2 (x, esperanza, desviacion);

	
	
		cout << "G(" << setw(11) << setprecision(7) << x << ") = " 
			 << setw(10) << setprecision(7) << g_x << " ----- ";
		cout << "CDF_1 (" << setw(11) << setprecision(7) << x << ") = " 
			 << setw(10) << setprecision(7) << cdf_1_x << " ----- ";
		cout << "CDF_2 (" << setw(11) << setprecision(7) << x << ") = " 
			 << setw(10) << setprecision(7) << cdf_2_x;			
		cout << endl;
	
	} // for x
	
	return 0;
}

/***************************************************************************/
/***************************************************************************/
