/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN
	
	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	Escribir un programa en el que se presente un menú principal para que el
	usuario pueda elegir entre las siguientes opciones:
    	A–>Calcular adición. 
        P–>Calcular producto. 
        X–>Salir.
    Si el usuario elige en el menú principal:
    a) Salir, el programa terminará su ejecución.
    b) Calcular adición se presenta un menú (secundario) para que el usuario 
	pueda elegir entre las siguientes opciones:
        S–>Calcular suma. 
        R–>Calcular resta. 
        X–>Salir.
    c) Calcular producto se presenta un menú (secundario) para que el usuario 
	pueda elegir entre las siguientes opciones:
        M–>Calcular multiplicación. 
        D–>Calcular división entera. 
        R–>Calcula resto.
        X–>Salir.
	
	Entradas: Valor de eleccion
	Salidas: Resultado opcion elegida
	
	
****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

int main() //Programa principal
{
    char eleccion;  //Opcion a elegir en el menu
    bool salir_bucle = false; //Condicion salir del programa
    bool salir_menu1 = false; //Condicion salir menu 1
    bool salir_menu2 = false; //Condicion salir menu 2
    double numero1;
    double numero2;
    double resultado;
    int i;
	int j;
	int k;
	int cociente = 0;

	//Entrada de datos

	// Menu de opciones
    do{
        cout << "\nMenu de Opciones" << endl;        
        cout << "[A] Calcular adicion" << endl; 
        cout << "[P] Calcular producto" << endl;
        cout << "[X] Salir" << endl;
        cin >> eleccion;
        switch (eleccion){
            case 'A': //Calcular Adicion
                // Menu de la suma
                do{
                	salir_menu1 = false; //Reseteo salir menu
                    cout << "\nMenu de Adicion" << endl;        
                    cout << "[S] Calcular suma" << endl;
                    cout << "[R] Calcular resta" << endl;
                    cout << "[X] Salir" << endl;
                    cin >> eleccion;
                    switch (eleccion){
                        case 'S': //Suma
                            cout << "Introduzca el numero 1: ";
                            cin >> numero1;
                            cout << "Introduzca el numero 2: ";
                            cin >> numero2;
                            resultado = numero1 + numero2;
                            cout << "Resultado: " << resultado << endl;
                            break;                        
                        case 'R': //Resta
                            cout << "Introduzca el numero 1: ";
                            cin >> numero1;
                            cout << "Introduzca el numero 2: ";
                            cin >>numero2;
                            resultado = numero1 - numero2;
                            cout << "Resultado: " << resultado << endl;
                            break;
                        case 'X': //Salir
                            salir_menu1 = true;
                            break;
                        default:
                            cout << "Opcion no valida" << endl;
                            break;
                    }
                }while(salir_menu1 != true);
                break;
            case 'P': //Calcular Producto       
                //Menu del producto
                do{
                	salir_menu2 = false; //Reseteo salir menu
                    cout << "\nMenu de Producto" << endl;        
                    cout << "[M] Calcular Multiplicacion" << endl;
                    cout << "[D] Calcular Division entera" << endl;
                    cout << "[R] Calcular Resto" << endl;
                    cout << "[X] Salir" << endl;
                    cin >> eleccion;
                    switch(eleccion){
                        case 'M': //Multiplicacion
                        	do{
                        		cout << "Introduzca el numero 1: ";
                            	cin >> numero1;
							}while (numero1<0);
                            do{
                        		cout << "Introduzca el numero 2: ";
                            	cin >> numero2;
							}while (numero2<0);
                            for (i = 1; i <= (int)numero2; i++){
                            	resultado+=(int)numero1;
							}
                            cout << "Resultado: " << resultado << endl;
                            resultado = 0; //Reset valor del resultado
                            break;
                        case 'D': //Division entera
                            do{
                        		cout << "Introduzca el numero 1: ";
                            	cin >> numero1;
							}while (numero1<0);
                            do{
                        		cout << "Introduzca el numero 2: ";
                            	cin >> numero2;
							}while (numero2<0);
                            for (k=(int)numero1;k>=0;k = k-(int)numero2){
                            	cociente++;
							}
							resultado = cociente-1;
                            cout << "Resultado: " << resultado << endl;
                            break;
                        case 'R': //Resto
                            do{
                        		cout << "Introduzca el numero 1: ";
                            	cin >> numero1;
							}while (numero1<0);
                            do{
                        		cout << "Introduzca el numero 2: ";
                            	cin >> numero2;
							}while (numero2<0);
                            for (j=(int)numero1; j>=0 ;j = j-(int)numero2){
                            	resultado = j;
							}
                            cout << "Resultado: " << resultado << endl;
                            break;
                        case 'X':
                            salir_menu2 = true;
                            break;
                        default:
                            cout << "Opcion no valida";
                            break;
                    }
                }while(salir_menu2!=true);
                break;
            case 'X':
                salir_bucle=true;
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    }while(salir_bucle!=true);

	cout << "Has salido del menu";
	
	return 0;
}
