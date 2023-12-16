/**
 * @file imagen.cpp
 * @author Miguel Angel De la Vega Rodriguez
 * @author Joaquín Aviles De la Fuente
 * @brief Fichero de implementación de los métodos de la clase Imagen
 * 
 */


#include "imagen.h"

Imagen::Imagen(const Imagen &rhs){
    nfil = rhs.nfil;
    ncol = rhs.ncol;
    AllocateMemory(nfil,ncol);
    for(int i = 0; i < nfil; ++i){
        for(int j = 0; j < ncol; ++j){
            datos[i][j] = rhs.datos[i][j];
        }
    }
}

Imagen::Imagen(int filas, int columnas){
    nfil = filas;
    ncol = columnas;
    AllocateMemory(filas,columnas);
}

Imagen::~Imagen(){
    DeallocateMemory();
}

Imagen &Imagen::operator=(const Imagen &rhs){
    if (this != &rhs){
        DeallocateMemory();
        nfil = rhs.nfil;
        ncol = rhs.ncol;
        AllocateMemory(nfil,ncol);
        for(int i = 0; i < nfil; ++i){
            for(int j = 0; j < ncol; ++j){
                datos[i][j] = rhs.datos[i][j];
            }
        }
    }
    return *this;
}

Pixel &Imagen::operator()(int fil, int col){
    return datos[fil][col];
}

const Pixel &Imagen::operator()(int fil, int col) const{
    return datos[fil][col];
}

void Imagen::EscribirImagen(const char *nombre){
    std::string extension = std::string(nombre).substr(std::string(nombre).find_last_of(".") + 1);
    TipoImagen tipo = (extension == "ppm") ? IMG_PPM : IMG_PGM;
    
    if (tipo == IMG_PGM){
        unsigned char *buffer = new unsigned char[nfil*ncol];
        for(int i = 0; i < nfil; ++i){
            for(int j = 0; j < ncol; ++j){
                buffer[i*ncol+j] = datos[i][j].r;
            }
        }
        EscribirImagenPGM(nombre,buffer,nfil,ncol);
        delete[] buffer;
    }
    else{
        unsigned char *buffer = new unsigned char[nfil*ncol*3];
        for(int i = 0; i < nfil; ++i){
            for(int j = 0; j < ncol; ++j){
                buffer[(i*ncol+j)*3] = datos[i][j].r;
                buffer[(i*ncol+j)*3+1] = datos[i][j].g;
                buffer[(i*ncol+j)*3+2] = datos[i][j].b;
            }
        }
        EscribirImagenPPM(nombre,buffer,nfil,ncol);
        delete[] buffer;
    }
}

void Imagen::LeerImagen(const char *nimagen, std::string mascara){
    TipoImagen tipo = LeerTipoImagen(nimagen,nfil,ncol);
    
    if (tipo == IMG_PGM){
        unsigned char *buffer = new unsigned char[nfil*ncol];
        LeerImagenPGM(nimagen,nfil,ncol,buffer);
        AllocateMemory(nfil,ncol);
        for(int i = 0; i < nfil; ++i){
            for(int j = 0; j < ncol; ++j){
                datos[i][j].r = buffer[i*ncol+j];
                datos[i][j].g = buffer[i*ncol+j];
                datos[i][j].b = buffer[i*ncol+j];
            }
        }
        delete[] buffer;
    }
    else if (tipo == IMG_PPM){
        unsigned char *buffer = new unsigned char[nfil*ncol*3];
        LeerImagenPPM(nimagen,nfil,ncol,buffer);
        AllocateMemory(nfil,ncol);
        for(int i = 0; i < nfil; ++i){
            for(int j = 0; j < ncol; ++j){
                datos[i][j].r = buffer[(i*ncol+j)*3];
                datos[i][j].g = buffer[(i*ncol+j)*3+1];
                datos[i][j].b = buffer[(i*ncol+j)*3+2];
            }
        }
        delete[] buffer;
    }
    else{
        std::cerr << "Error: Formato de imagen no soportado" << std::endl;
    }
    
    if (mascara != ""){
        Imagen mask;
        mask.LeerImagen(mascara.c_str());
        for(int i = 0; i < nfil; ++i){
            for(int j = 0; j < ncol; ++j){
                if (mask(i,j).r == 0){
                    datos[i][j].r = 0;
                    datos[i][j].g = 0;
                    datos[i][j].b = 0;
                }
            }
        }
    }
}

void Imagen::PutImagen(int i, int j, const Imagen &Ip, TipoPegado tipo){
    for (int k = 0; k < Ip.nfil; ++k){
        for (int l = 0; l < Ip.ncol; ++l){
            if (i+k < nfil && j+l < ncol){
                if (tipo == OPACO){
                    if (Ip(i+k,l+j).r != 0){
                        datos[i+k][j+l] = Ip.datos[k][l];
                    }
                }
                else if (tipo == BLENDING){
                    // La sobrecarga del operador suma calcula la media de los dos píxeles
                    // Que tiene mas sentido que simplemente sumar los valores de los canales
                    if (Ip(i+k,l+j).r != 0) {
                        datos[i+k][j+l] = (Ip.datos[k][l] + datos[i+k][j+l]);
                    }
                }
            }
        }
    }
}

void Imagen::PutImagen(int i, int j, const Imagen &Ip, char blend){
    for (int k = 0; k < Ip.nfil; ++k){
        for (int l = 0; l < Ip.ncol; ++l){
            if (i+k < nfil && j+l < ncol){
                if (Ip(i+k,l+j).r != 0){
                    datos[i+k][j+l].r = (Ip.datos[k][l].r*(blend/100) + datos[i+k][j+l].r*((100-blend)/100))/2;
                    datos[i+k][j+l].g = (Ip.datos[k][l].g*(blend/100) + datos[i+k][j+l].g*((100-blend)/100))/2;
                    datos[i+k][j+l].b = (Ip.datos[k][l].b*(blend/100) + datos[i+k][j+l].b*((100-blend)/100))/2;
                }
            }
        }
    }
}

void Imagen::AllocateMemory(int filas, int columnas){
    datos = new Pixel*[filas];
    datos[0] = new Pixel[filas*columnas];
    
    for (int i = 1; i < filas; ++i){
        datos[i] = datos[i-1] + columnas;
    }
}

void Imagen::DeallocateMemory(){
    delete[] datos[0];
    delete[] datos;
    datos = nullptr;
    nfil = 0;
    ncol = 0;
}
