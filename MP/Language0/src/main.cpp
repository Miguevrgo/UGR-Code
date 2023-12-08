/*
 * Metodología de la Programación: Language0
 * Curso 2022/2023
 */

/* 
 * File:   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * @author Miguel Angel De la Vega Rodríguez <miguevrod@correo.ugr.es>
 * Created on 2 de febrero de 2023, 12:23
 */


#include <string>
#include "Bigram.h" //For bigram class

using  namespace std;
/**
 * This program reads a text (without spaces) with a undefined number of 
 * characters and a text with two characters (bigram). It finds the bigrams 
 * contained in the first text, storing them in an array of Bigram. 
 * After that, the bigrams of the array are shown in the standard output. 
 * Then it converts to uppercase the bigrams in the array that are equals to the 
 * bigram of the second text. Finally the bigrams of the array are shown again 
 * in the standard output. 
 * Running example:
 * > language0 < data/SimpleText.txt
 */
int main(int argc, char* argv[]) {
    // This string contains the list of characters that are considered as
    // valid within a word. The rest of characters are considered as
    // separators
    const string validCharacters = "abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

    // Read a text
    string cadena1;
    cin >> cadena1;
    for(int i=0;i<cadena1.length();i++){
        cadena1.at(i)=tolower(cadena1.at(i));
    }

    // Read a bigram (text with two characters)
    string cadena2;
    cin >> cadena2;
    Bigram bigram_to_find(cadena2);
    
    // Find the bigrams in text and put them in an array of Bigrams
    int n=0; //counter for bigrams
    const int MAX_BIGRAMS = cadena1.length();
    Bigram bigrams[MAX_BIGRAMS];
    for (int i=0,j=1;j<cadena1.length();i++,j++){
        if(isValidCharacter(cadena1.at(i),validCharacters) && isValidCharacter(cadena1.at(j),validCharacters)){
            bigrams[n] = Bigram(cadena1[i],cadena1[j]);
            n++;
        }
    }

    // Show the bigrams stored in the array
    cout << n << "\n"; //number of bigrams in the vector
    for (int i=0;i<n;i++){
        cout << bigrams[i].toString() << "\n";
    }
    cout << "\n";

    // Convert to uppercase the bigrams in the array that are equals to input bigram
    for (int i=0;i<n;i++){
        if(bigrams[i].getText() == bigram_to_find.getText()){
            toUpper(bigrams[i]);
        }
    }

    // Show again the bigrams stored in the array
    cout << n << "\n"; //number of bigrams in the vector
    for (int i=0;i<n;i++){
        cout << bigrams[i].toString() << "\n";
    }
}
