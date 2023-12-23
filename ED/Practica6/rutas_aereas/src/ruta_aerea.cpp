/**
* @file ruta_aerea.cpp
* @brief Obtiene un mapa del mundo sobre el que se pinta una ruta aerea
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstring>
#include "imagenES.h"
#include "imagen.h"
#include "paises.h"
#include "almacen.h"
#include "ruta.h"

using namespace std;

Imagen Rota(const Imagen & Io,double angulo){
    double rads=angulo;
    double coseno = cos(angulo);
    double seno = sin(angulo);
    //Para obtener las dimensiones de la imagen
    int rcorners[4],ccorners[4];
    int newimgrows,newimgcols;
    double new_row_min,new_col_min,new_row_max,new_col_max;
    double inter,inter1;
    rcorners[0] = rcorners[1] = ccorners[0] = ccorners[2]=0;
    rcorners[2] = rcorners[3] = Io.GetFils()-1;
    ccorners[1] = ccorners[3] = Io.GetCols()-1;
    new_row_min = new_col_min = new_row_max = new_col_max = newimgrows = newimgcols = 0;

    for(int count=0;count<4;++count)
    {
        inter=rcorners[count]*coseno+ccorners[count]*seno;

        if(inter<new_row_min)
            new_row_min=inter;
        if(inter>new_row_max)
            new_row_max=inter;
        inter1=-rcorners[count]*seno+ccorners[count]*coseno;

        if(inter1<new_col_min)
            new_col_min=inter1;
        if(inter1>new_col_max)
            new_col_max=inter1;
    }

    newimgrows=(unsigned)ceil((double)new_row_max-new_row_min);
    newimgcols=(unsigned)ceil((double)new_col_max-new_col_min);

    Imagen Iout(newimgrows,newimgcols);
    for(int rows=0;rows<newimgrows;rows++)
    {
        for(int cols=0;cols<newimgcols;cols++)
        {
            float oldrowcos=((float)rows+new_row_min)*cos(-rads);
            float oldrowsin=((float)rows+new_row_min)*sin(-rads);
            float oldcolcos=((float)cols+new_col_min)*cos(-rads);
            float oldcolsin=((float)cols+new_col_min)*sin(-rads);
            float old_row=oldrowcos+oldcolsin;
            float old_col=-oldrowsin+oldcolcos;
            old_row=ceil((double)old_row);
            old_col=ceil((double)old_col);
            if((old_row>=0)&&(old_row<Io.GetFils())&&
               (old_col>=0)&&(old_col<Io.GetCols()))
            {
                Iout(rows,cols)=Io(old_row,old_col);
                //Iout(rows,cols).transparencia=0;

            }
            else{
                Iout(rows,cols).r=Iout(rows,cols).g=Iout(rows,cols).b=0;
                Iout(rows,cols).transparencia = 0;
            }
        }
    }
    return Iout;

}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        cout << "Los parametros son :" << endl;
        cout << "1.-El fichero de paises" << endl;
        cout << "2.-El mapa" << endl;
        cout << "3.-Directorio donde se almacenan las banderas" << endl;
        cout << "4.-Almacen de rutas" << endl;
        cout << "5.-Imagen de un avión" << endl;
        cout << "6.-Máscara del avión" << endl;
        return 0;
    }

    // Cargar el fichero de paises
    string fichero_paises = argv[1];

    // Cargamos los paises
    Paises paises;
    ifstream is(fichero_paises);
    is >> paises;

    // Cargar el mapa sobre el que pintar
    // Argv[2] es el nombre del fichero del mapa
    Imagen mapa_mundi;
    mapa_mundi.LeerImagen(argv[2]);

    // Cargar el directorio de banderas
    string dir_banderas = argv[3];

    // Cargar el almacen de rutas
    Almacen almacen;
    ifstream is2(argv[4]);
    is2 >> almacen;

    // Cargar la imagen del avión y la máscara
    Imagen avion;
    avion.LeerImagen(argv[5], argv[6]);

    // Pintar las rutas:
    cout << "Introduzca la ruta que desea seguir: " << endl;
    cout << almacen << endl;
    string ruta;
    cin >> ruta;
    Ruta ruta_seleccionada = almacen.GetRuta(ruta);

    int nfil = mapa_mundi.GetFils();
    int ncol = mapa_mundi.GetCols();

    // Pintar los paises

    for (int i = 0; i < ruta_seleccionada.GetSize(); ++i) {
        Pais pais = paises.GetPais(ruta_seleccionada.GetPunto(i));

        double lat = pais.GetPais().GetLat();
        double lon = pais.GetPais().GetLon();

        int r, c;
        r = static_cast<int>((nfil / 180.0) * (90 - lat));
        c = static_cast<int>((ncol / 360.0) * (180 + lon));

        Imagen bandera;
        string dir = dir_banderas + pais.GetBandera();
        const char *dir_char = dir.c_str();
        bandera.LeerImagen(dir_char);
        mapa_mundi.PutImagen(r, c, bandera, OPACO);
    }

    // Pintar los aviones
    for (int i = 0; i < ruta_seleccionada.GetSize() - 1; ++i) {
        Pais pais = paises.GetPais(ruta_seleccionada.GetPunto(i));
        Pais siguiente_pais = paises.GetPais(ruta_seleccionada.GetPunto(i + 1));

        double lat = pais.GetPais().GetLat();
        double lon = pais.GetPais().GetLon();
        double lat_siguiente = siguiente_pais.GetPais().GetLat();
        double lon_siguiente = siguiente_pais.GetPais().GetLon();

        int r, c;
        int r_siguiente, c_siguiente;
        int r_medio, c_medio;

        r = static_cast<int>((nfil / 180.0) * (90 - lat));
        c = static_cast<int>((ncol / 360.0) * (180 + lon));

        r_siguiente = static_cast<int>((nfil / 180.0) * (90 - lat_siguiente));
        c_siguiente = static_cast<int>((ncol / 360.0) * (180 + lon_siguiente));

        r_medio = (r + r_siguiente) / 2;
        c_medio = (c + c_siguiente) / 2;

        double angulo = atan2(r_siguiente-r,c_siguiente-c);

        Imagen avion_rotado = Rota(avion, angulo);

        mapa_mundi.PutImagen(r, c, avion_rotado, OPACO);
        mapa_mundi.PutImagen(r_medio, c_medio, avion_rotado, OPACO);
        mapa_mundi.PutImagen(r_siguiente, c_siguiente, avion_rotado, OPACO);
    }


    mapa_mundi.EscribirImagen("./salida_img/mapa.ppm");

    return 0;
}