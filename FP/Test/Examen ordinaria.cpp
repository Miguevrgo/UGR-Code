/****************************************************************************
	FUNDAMENTOS DE PROGRAMACIÓN

	Miguel Ángel De La Vega Rodríguez    |	Grupo A1
	
	
	Entradas: 
	Salidas: 
	
	

****************************************************************************/

#include <iostream> //Inclusión de los recursos de E/S

using namespace std;

/*****************************************************************************
*                        CONSTANTES GLOBALES								 *
*****************************************************************************/
const int MAX_JUGADORES = 100; //Máximo de jugadores por partida de Bingo
const int TACHADO = 0; //Numero con el que se tacha por defecto
/*****************************************************************************
*							  FUNCIONES										 *
*****************************************************************************/

/*****************************************************************************
*							    CLASES										 *
*****************************************************************************/
class Carton{
private:

public:

    //_______________________Constructores____________________________________

    Carton(string ID) : identificador(ID)
    {
        RellenaCarton();
    }

    Carton(void) : identificador(""){}

    //Calcula si un numero x esta en el carton del jugador
    //PRE(OPCIONAL): MIN_NUMERO<numero<MAX_NUMERO

    bool ContieneNumero(int el_numero){
        bool encontrado = falso;
        int fil=0;
        while ((!encontrado) && (fil<FILAS_CARTON)){
            col=0; //Para cada fila reiniciamos el valor de col
            while ((!encontrado) && (col<COLUMNAS_CARTON)){
                if (matriz[fil][col]==el_numero){ //Si elemento = numero buscado
                    encontrado = true;
                }
                else{
                    col++; //Incrementa la columna para la siguiente iteracion
                }  
            }
            if (!encontrado){
                fil++; //Incrementa la fila para la siguiente iteracion
            }  
        }
        return (encontrado);
    }

    //Tacha un numero X del carton usando la constante TACHADO
    //(u otro numero si es preciso)
    //PRE:(OPCIONAL) el_numero € Matriz
    void TacharNumero(int el_numero,int tachado = TACHADO){
        bool encontrado = falso;
        int fil=0;
        while ((!encontrado) && (fil<FILAS_CARTON)){
            col=0; //Para cada fila reiniciamos el valor de col
            while ((!encontrado) && (col<COLUMNAS_CARTON)){
                if (matriz[fil][col]==el_numero){ //Si elemento = numero buscado
                    encontrado = true;
                    matriz[fil][col] = tachado;
                }
                else{
                    col++; //Incrementa la columna para la siguiente iteracion
                }  
            }
            if (!encontrado){
                fil++; //Incrementa la fila para la siguiente iteracion
            }  
        }  
    }

    //Comprueba si la fila fil esta tachada
    //Recibe: numero de fila a comprobar, numero de tachado en caso de cambio
    bool FilaTachada(int fil, int tachado = TACHADO){
        bool fila_tachada = true;
        for (int col=0;col<COLUMNAS_CARTON;col++){
            if (matriz[fil][col] != TACHADO){
                fila_tachada = false; //Se ha encontrado un numero no tachado
            }
        }
        return fila_tachada;
    }

    //Comprueba si hay bingo en un tablero
    bool HayBingo(void){
        bool ganador=true;
        int fil=0

        while(ganador && fil<FILAS_CARTON){
            if (!FilaTachada(fil)){ganador = false}
            else{fil++;}
        }

        return ganador;
    }

    // Devuelve el número de casillas tachadas
	
	int NumCasillasTachadas (void)
	{
		int cont = 0; 
		
		for (int f=0; f<FILS; f++)
			for (int c=0; c<COLS; c++)
				if (matriz[f][c] == TACHADO) cont++;
		
		return cont; 
	}

private:

};

class SecuenciaCartones{
private:

public:

    //___________________________Constructores________________________________

    //Ordena la secuencia de cartones en una SecuenciaCopia que es la que 
    //devuelve
    SecuenciaCartones Ordenar(){
        SecuenciaCartones copia;

        for (int i=0;i<total_utilizados;i++){
            copia.vector_privado[i] = vector_privado[i];
        }
        copia.total_utilizados = total_utilizados;


        for (int j=0;j<copia.total_utilizados;j++){
            for (int i=0;i<copia.total_utilizados-j;i++){
                if (copia.vector_privado[j].EsMayor(copia.vector_privado[j+1])){
                    Carton aux = copia.vector_privado[j+1];
                    copia.vector_privado[j+1] = copia.vector_privado[j];
                    copia.vector_privado[j] = aux;
                }
            }
        }

        return copia;
    }

};

int main() //Programa principal
{
    const string FIN = "FIN";
    SecuenciaCartones Bingo;
    string identificador;

    cout << "Identificador tablero " << Bingo.Utilizados()+1 << ":";
    cin >> identificador;

	while (identificador != FIN && Bingo.Utilizados()<MAX_JUGADORES){

        Bingo.Aniade(Carton(identificador));

        cout << "Identificador tablero " << Bingo.Utilizados()+1 << ":";
        cin >> identificador;
        
    }

    SecuenciaEnteros Bombo(90,1,90); //Bombo de numeros sacados "aleatorios"

    bool ganador = false;
    bool linea_permitida = true; //Si hay linea se vuelve false

    int turno = 1;
    int numero_a_tachar;

    while (!ganador && turno<=90){
        numero_a_tachar = Bombo.GetElemento(turno);



    }

	//Entrada de datos
	
	
	
	//Cálculos



	//Salida
	


	return 0;
}

