/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file LEARN.cpp
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
    outputStream << "LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> .... ]" << std::endl;
    outputStream << "           learn the model for the language languageId from the text files <text1.txt> <text2.txt> <text3.txt> ..." << std::endl;
    outputStream << std::endl;
    outputStream << "Parameters:" << std::endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << std::endl;
    outputStream << "-l languageId: language identifier (unknown by default)" << std::endl;
    outputStream << "-o outputFilename: name of the output file (output.bgr by default)" << std::endl;
    outputStream << "<text1.txt> <text2.txt> <text3.txt> ....: names of the input files (at least one is mandatory)" << std::endl;
}

/**
 * This program learns a Language model from a set of input tex files (tex1.txt,
 * tex2.txt, ...
 * Running example:
 * > LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> ....]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

int main(int argc, char *argv[]) { 
    
    if (argc < 2){
        showEnglishHelp(std::cerr);
        return 1;
    }
    
    // Default values
    char mode = 't';    // Binary mode.
    std::string language = "unknown";
    std::string output = "output.bgr";

    bool valid_param = true;
    bool reused_option = false; // If an option has been already used


    bool tb_option = false; // Binary or text mode
    bool id_option = false; // Language ID
    bool out_option = false; // Output file name

    unsigned int num_param(1); // Number of parametre to be cheked

    while(!reused_option && valid_param && argv[num_param][0] == '-'){

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
        /*_______________________Check id_option___________________________*/
        else if(strcmp(argv[num_param], "-l") == 0){
            if(!id_option){
                id_option = true; // Used
                valid_param = argc >= ++num_param;
                language = argv[num_param];
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

    BigramCounter builder;

    Language lang;
    lang.setLanguageId(language);

    for(unsigned int i=num_param;i<argc;i++){
        builder.calculateFrequencies(argv[i]);
        lang += builder.toLanguage();
    }
    
    lang.sort();
    lang.save(output.c_str(),mode);

    return 0;
}