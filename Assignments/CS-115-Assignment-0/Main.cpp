//Owen Monus – 200482797 ---- CS 115 - 001 ---- Sep 4, 2022
/* In this program, the user enters a word with one or more letters replaced 
by underscores ('_') and the program prints a list of matching words in the 
dictionary. This process repeats until the user enters "q" as a word. */

#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

void checkDictionary(string user_word, string dictionary[], unsigned int dictionary_size);
void checkWord (string user_word, string dictionary_word);
const unsigned int DICTIONARY_SIZE = 58110;
string dictionary[DICTIONARY_SIZE];

int main () { 
    string user_word; //tracks the user inputted word  
    ifstream fin; //creating a new object to read files
    
    //open the dictionary file
    fin.open("dictionary.txt"); 

    //if the file cannot be opened, print an appropriate error message
    if(!fin) { 
        cout << "Error: could not open file" << endl;
    }

    //the following for loop adds words from dictionary.txt to the dictionay array
    for(unsigned int i = 0; i < DICTIONARY_SIZE; i++) {
        fin >> dictionary[i];
    }
    
    //closes the dictionary file
    fin.close(); 

    //takes a user input and assigns it to user_word
    cout << "Welcome to the Word Match Program!" << endl;
    cout << "\nEnter a word with underscores:";
    cin >> user_word; 
    
    //As long as the user does not enter q, this function requests and then reads user input
    while(user_word != "q") { 
        checkDictionary(user_word, dictionary, DICTIONARY_SIZE);
        cout << "\nEnter a new word: "; 
        cin >> user_word;  
    }

    cout << "\nGoodbye!";

    return 0; 
}

//*********FUNCTIONS**********

/*if a word in the dictionary is the same as user_word or, if underscores are present,  a word 
in the dictionary is the same as user_word with the underscores filled in, this function will
print that matching word. This function checks every word in dictionary[] */
void checkDictionary(string user_word, string dictionary[], unsigned int dictionary_size) {
    //converts all characters in user_word to lowercase for comparison to the dictionary.
    for(unsigned int i = 0; i < user_word.length(); i++) { 
        user_word.at(i) = tolower(int(user_word.at(i))); 
    }
    
    /*cheks user_words similarity to all words in dictionary[]. Prints matched words using the
    checkWord function */
    for (unsigned int i = 0; i < dictionary_size; i++) { 
       checkWord(user_word, dictionary[i]); 
    }
}

/*if a word in the dictionary is the same as user_word or, if underscores are present,  a word 
in the dictionary is the same as user_word with the underscores filled in, this function will
print that matching word(s) */
void checkWord(string user_word, string dictionary_word) {
     /* If the user word is longer than 0 characters & there is a word 
    in the dictionary with the same length */
    if(user_word.length() > 0 && user_word.length() == dictionary_word.length()) {    
        //tracks how many characters matched when comparing user_word to a word at dictionary[i]
        unsigned int matched = 0; 
        
       /* checks if a character from user_word is equal to a charcter from 
        the current (at index i) dictionary word at index j. If they are the same, or the character is
        an underscore, this if loop increments matched */
        for(unsigned int j = 0; j < user_word.length(); j++) {
            if(user_word.at(j) == dictionary_word.at(j) || user_word.at(j) == '_') {
                matched ++;
            }
        }

        /* if user_word length and matched are the same length, then they are the same word.
        The following if loop prints out matching words. */
        if(user_word.length() == matched) {
            cout << dictionary_word << endl;
        }
    }
}
