/*
 * Metodología de la Programación: Language2
 * Curso 2022/2023
 */

/**
 * @file   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Miguel Ángel De La Vega Rodríguez <miguevrod@correo.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 **/


#include <iostream>
#include "Language.h"
#include <vector>  
/**
 * Shows help about the use of this program in the given output stream
 * @param ouputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(std::ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << std::endl;
    outputStream << "language2 <file1.bgr> [<file2.bgr> ... <filen.bgr>] <outputFile.bgr> " << std::endl;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally the resulting Language is saved in an output file. The 
 * program must have at least an input file and an output file. 
 * The output Language will have as language identifier, the one of the first
 * file (<file1.bgr>). If an input file <file*.bgr> has a language identifier
 * different from the one of the first file (<file1.bgr>), then it will not
 * be included in the union.
 * Running example:
 * > language2 <file1.bgr> [<file2.bgr> ... <filen.bgr>] <outputFile.bgr> 
 */
int main(int argc, char* argv[]) {
    //Checks that the program has been called with at least 3 parameters
    if (argc < 3) {
        showEnglishHelp(std::cerr);
        return 1;
    }
    const int MAX_LAN=50; //Maximum number of Language objects
    int num_lan=0; //Number of Languages provided
    Language languages[MAX_LAN];
  
    //Reads each input file, creates a Language object from it, and adds it to the array of languages
    for (int i = 1; i < argc - 1; i++) {
        languages[i-1].load(argv[i]);
        num_lan++;
    }
    
    //Creates a new Language object equal to the union of all languages
    Language unionLanguage = languages[0];
    for (int i = 1; i < num_lan; i++) {
        if (unionLanguage.getLanguageId()==languages[i].getLanguageId()){
            unionLanguage.join(languages[i]);
        }
    }
    
    //Sorts the bigrams in unionLanguage
    unionLanguage.sort();
    
    //Saves the resulting Language object to the output file
    unionLanguage.save(argv[argc - 1]);
    
    return 0;
}


