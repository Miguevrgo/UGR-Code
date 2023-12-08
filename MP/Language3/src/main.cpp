/*
 * Metodología de la Programación: Language3
 * Curso 2022/2023
 */

/* 
 * File:   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 *
 * Created on 7 de febrero de 2023, 14:02
 */

#include "Language.h"


/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(std::ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << std::endl;
    outputStream << "language3 [-t min|max] <file1.bgr> <file2.bgr> [ ... <filen.bgr>]" << std::endl;
}

/**
 * This program reads an undefined number of Language objects from the set of 
 * files passed as parameters to main(). All the Languages object, except the 
 * first one, must be stored in a dynamic array of Language objects. Then, 
 * for each Language in the dynamic array, this program prints to the 
 * standard output the name of the file of that Language and the distance from 
 * the first Language to the current Language. 
 * Finally, the program should print in the standard output, the name of 
 * the file with the Language with the minimum|maximum distance to the Language 
 * of the first file and its language identifier.
 * 
 * At least, two Language files are required to run this program.
 * Running example:
 * > language3 [-t min|max] <file1.bgr> <file2.bgr> [  ... <filen.bgr>] 
 */
int main(int argc, char* argv[]) {

    //Checks that the program has been called with at least 3 parameters
    if (argc < 3 ) {
        showEnglishHelp(std::cerr);
        return 1;
    }

    int begin_arg=1; //If -t max|min is not provided it starts in 1, else 3
    bool max=false; //Default value for min|max is min (max=false)
    
    //Checks if arguments are valid and provided
    if (argv[1][0]=='-'){
        if (strcmp(argv[1],"-t")==0){
            if (std::string(argv[2])=="max"){
                max=true;
                begin_arg=3;
            }
            else if(std::string(argv[2])=="min"){
                begin_arg=3;
            }
            else{
                showEnglishHelp(std::cerr);
                return 1;
            }

        }
        else{
            showEnglishHelp(std::cerr);
            return 1;
        }
        if (argc < 5 ) {
            showEnglishHelp(std::cerr);
            return 1;
        }
    }

    //Creates the language used as a reference
    Language ref_language;
    ref_language.load(argv[begin_arg]);
   
    //Creates dynamic language array
    Language* languages=nullptr;
    languages = new Language[argc-begin_arg-1];
    
    //Loads each language into the array
    for (int i=begin_arg+1;i<argc;i++){
        languages[i-(begin_arg+1)].load(argv[i]);
    }
    
    //String used to distinguish between max|min 
    std::string max_min;
    (max) ? max_min="Farthest" : max_min="Nearest";

    //Prints distance between texts and calculates nearest|farthest distance
    double min_max_dist;
    (max) ? min_max_dist=0 : min_max_dist=100;
    double distance;
    int min_max_index;
    for (int i = 0; i < argc-begin_arg-1; i++) {
        distance = ref_language.getDistance(languages[i]);
        if (max){
            if(distance > min_max_dist){
                min_max_dist=distance;
                min_max_index=i;
            }  
        }
        else{
            if(distance < min_max_dist){
                min_max_dist=distance;
                min_max_index=i;
            }  
        }
        
        std::cout << "Distance to " << argv[i+1+begin_arg] << ": " << distance << std::endl;
    }

    //Prints the nearest|farthest language file
    std::cout << max_min <<" language file: " << argv[min_max_index+1+begin_arg] << std::endl;
    (max) ? max_min="farthest" : max_min="nearest";
    std::cout << "Identifier of the " << max_min << " language: " 
              << languages[min_max_index].getLanguageId() << std::endl;
    
    //Delete dynamic array
    delete[] languages;
    
    return 0;
}