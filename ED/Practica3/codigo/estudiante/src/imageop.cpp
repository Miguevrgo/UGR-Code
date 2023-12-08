/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>

using namespace std;

void Image::Invert() {
    for (int i=0; i<this->size(); i++){
        this->set_pixel(i,255-this->get_pixel(i));
    }
}

void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2) {
    if (!(in1 < in2 && out1 < out2 && in1 >= 0 && in2 <= 255 && out1 >= 0 && out2 <= 255)) {
        throw std::out_of_range(std::string("void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2) ")
                                + " Out of range parameters");
    }

    // Coeficients of the lineal function for the contrast adjustment
    double r_1 = static_cast<double>(out1) / in1;
    double r_2 = static_cast<double>(out2 - out1) / (in2 - in1);
    double r_3 = static_cast<double>(255 - out2) / (255 - in2);

    int elem = this->get_rows()*this->get_cols();

    for (int k=0;k<elem;++k){
        byte value = get_pixel(k);
        if(value < in1){
            this->set_pixel(k,round(r_1*value));
        }
        else if(value <= in2){
            this->set_pixel(k,round(out1 + r_2*(value-in1)));
        }
        else if (value <= 255){
            this->set_pixel(k,round(out2 + r_3*(value-in2)));
        }
    }
}

double Image::Mean(int i, int j, int height, int width) const {
    if(!(i >= 0 && j >= 0 && height > 0 && width > 0 &&
            ((i + width) <= this->size()) && ((j + height) <= this->size()))){

        throw std::out_of_range(std::string("double Image::Mean(int i, int j, int height, int width) const")
                                + " Out of range parameters");
    }

    double mean{};

    for (int k=0;k<height;++k){
        for (int p=0;p<width;++p){
            mean += this->get_pixel(i+k,j+p);
        }
    }

    mean /= (height*width);

    return mean;
}

Image Image::Subsample(int factor) const {
    if(factor <= 0){
        throw std::out_of_range(std::string("Image Image::Subsample(int factor) const ")
                                + " Non permitted negative factor");
    }

    int nrows = this->get_rows()/factor;
    int ncols = this->get_cols()/factor;

    Image subsample(nrows,ncols);

    for (int i = 0; i < nrows;++i) {
        for (int j = 0; j < ncols; ++j) {
            subsample.set_pixel(i, j, round(this->Mean(i*factor, j*factor, factor, factor)));
        }
    }

    return subsample;
}

Image Image::Crop(int nrow, int ncol, int height, int width) const {
    if(!(nrow >= 0 && ncol >= 0 && height > 0 && width > 0 &&
         nrow + width <= this->size() && ncol + height <= this->size())){

        throw std::out_of_range(std::string("Image Image::Crop(int nrow, int ncol, int height, int width) const ")
                                + " Out of range parameters");
    }

    Image cropped(height, width);

    for (unsigned int row=0; row < height; ++row){
        for (unsigned int col=0; col < width; ++col){
            cropped.set_pixel(row,col,this->get_pixel(row+nrow,col+ncol));
        }
    }

    return cropped;
}

Image Image::Zoom2X() const {

    //New size for the Image
    unsigned int nrows = (this->get_rows()*2)-1;
    unsigned int ncols = (this->get_cols()*2)-1;

    Image zoomed(nrows,ncols);

    //Setting original pixels in the zoomed image
    for (int i=0; i< this->rows; ++i){
        for (int j=0; j< this->cols; ++j){
            zoomed.set_pixel(i*2,j*2,this->get_pixel(i,j));
        }
    }

    //Interpolating the new pixels over the columns
    for (int i=0; i< nrows; i+=2){
        for (int j=1; j< ncols; j+=2){
            zoomed.set_pixel(i,j,round((zoomed.get_pixel(i,j-1)+zoomed.get_pixel(i,j+1))/2.0));
        }
    }

    //Interpolating the new pixels over the rows
    for(int i=1;i<nrows;i+=2){
        for(int j=0;j<ncols;j++){
            if(j%2==0){
                zoomed.set_pixel(i,j,round((zoomed.get_pixel(i-1,j)+zoomed.get_pixel(i+1,j))/2.0));
            }
            else{
                zoomed.set_pixel(i,j,round((zoomed.get_pixel(i-1,j-1)+zoomed.get_pixel(i-1,j+1)
                +zoomed.get_pixel(i+1,j-1)+zoomed.get_pixel(i+1,j+1))/4.0));
            }
        }
    }

    return zoomed;
}




void Image::ShuffleRows() {
    // Numero primo mayor que el numero de filas
    const int p = 9973;

    // Array auxiliar para guardar las filas
    byte **aux = new byte * [rows];

    // Se copian las filas en el array auxiliar
    for (int k=0; k<rows; ++k){
        aux[k] = img[k];
    }

    // Se barajan las filas
    for(int k=0; k<rows; ++k){
        int newr = k*p%rows;
        img[k] = aux[newr];
    }

    delete [] aux;
}

bool Image::operator==(const Image &rhs) const {
    if (this->get_rows() != rhs.get_rows() || this->get_cols() != rhs.get_cols()) {
        return false;
    }

    for (int i = 0; i < this->size(); ++i) {
        if (this->get_pixel(i) != rhs.get_pixel(i)) {
            return false;
        }
    }

    return true;
}
