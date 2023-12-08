/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file JOIN.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */

#include "BigramCounter.h"
/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(std::ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << std::endl;
    outputStream << "JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>] " << std::endl;
    outputStream << "       join the Language files <file1.bgr> <file2.bgr> ... into <outputFile.bgr>" << std::endl;
    outputStream << std::endl;
    outputStream << "Parameters:" << std::endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << std::endl;
    outputStream << "-o <outputFile.bgr>: name of the output file (output.bgr by default)" << std::endl;
    outputStream << "<file*.bgr>: each one of the files to be joined" << std::endl;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally, the resulting Language is saved in an output file. The 
 * program must have at least an input file. 
 * Running example:
 * >  JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char* argv[]) { 
    
    if (argc < 2){
        showEnglishHelp(std::cerr);
        return 1;
    }
    
    // Default values
    char mode = 't';    // Binary mode.
    std::string output = "output.bgr";

    bool valid_param = true; // If the parameters are valid
    bool reused_option = false; // If an option has been already used


    bool tb_option = false; // Binary or text mode
    bool out_option = false; // Output file name

    unsigned int num_param(1); // Number of parameters to be checked

    while(valid_param && !reused_option && argv[num_param][0] == '-'){
        
        // Once there is an optional option we need at least a file (+1)
        valid_param = argc >= num_param+1;

        /*_______________________Check tb_option___________________________*/
        if (strcmp(argv[num_param], "-t") == 0 || strcmp(argv[num_param], "-b") == 0){
            if (!tb_option){
                tb_option = true; // Used
                mode = argv[num_param][1];
                num_param++;
            }
            else{
                reused_option = true;
            }
        }
        /*_______________________Check out_option___________________________*/
        else if(strcmp(argv[num_param], "-o") == 0){
            if(!out_option){
                out_option = true; // Used
                valid_param = argc >= ++num_param;
                output = argv[num_param];
                num_param++;
            }
            else{
                reused_option = true;
            }
        }
        else{
            valid_param = false; // No valid option after -
        }

    } // End While

    if (!valid_param || reused_option){
        showEnglishHelp(std::cerr);
        return 1;
    }

    Language lang, aux;
    lang.load(argv[num_param++]);
    
    // Loading and joining languages
    for(unsigned int i=num_param;i<argc;i++){
        aux.load(argv[i]);
        lang += aux;
    }
    
    lang.sort();
    lang.save(output.c_str(),mode);

}

