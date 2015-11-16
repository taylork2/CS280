//
//  main.cpp
//  filt
//
//  Created by Gerard Ryan on 9/5/15.
//  Copyright (c) 2015 Gerard Ryan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

void
usage(const string msg, const char *progname) {
    if (msg.length() > 0) {
        cout << msg << endl;
    }
    cout << "Usage is: " << progname << " inputfile list_of_filters" << endl;
    cout << "where list_of_filters contains:" << endl;
    cout << "letter: all letters" << endl;
    cout << "vowel: all vowels" << endl;
    cout << "consonant: all consonants" << endl;
    cout << "word: all words" << endl;
    cout << "number: all numbers" << endl;
    cout << "space: all whitespace" << endl;
    cout << "punct: all punctuation" << endl;
    cout << endl;
    cout << "upper or lower before letter, vowel, consonant or word will restrict the filter to uppercase or lowercase" <<endl;
    
    exit(0);
}

bool
isvowel(char ch)
{
    char uch = toupper(ch);
    
    return uch == 'A' || uch == 'E' || uch == 'I' || uch == 'O' || uch == 'U';
}

int main(int argc, const char * argv[]) {
    bool foundUpper;
    bool foundLower;
    
    bool doLetter = false;
    bool doUpperLetter = false;
    bool doLowerLetter = false;
    
    bool doVowel = false;
    bool doUpperVowel = false;
    bool doLowerVowel = false;
    
    bool doConsonant = false;
    bool doUpperConsonant = false;
    bool doLowerConsonant = false;
    
    bool doWord = false;
    bool doUpperWord = false;
    bool doLowerWord = false;
    
    bool doNumber = false;
    bool doSpace = false;
    bool doPunct = false;
    
    const char *progname = argv[0];
    if (argc < 3) {
        usage("Argument count is wrong", progname);
    }
    
    const char *filename = argv[1];
    ifstream infile;
    
    infile.open(filename);
    if (!infile.is_open()) {
        usage("Cannot open file " + string(filename), progname);
    }
    
    // this code goes through all of the arguments to see what the filters are...
    
    // there is a chance that the user will preface a filter with upper or lower
    // i remember of they did with these variables
    // i use them to make sure they don't say upper lower or lower upper,
    // or end the list of filters with lower or upper
    foundUpper = foundLower = false;
    
    for (int i = 2; i < argc; i++) {
        string filt = argv[i]; // put it in a c++ string so that == works; the code is more readable!
        
        if (filt == "upper") {
            if (foundUpper) {
                usage("You said upper twice", progname);
            }
            if (foundLower) {
                usage("You said lower upper", progname);
            }
            
            foundUpper = true;
        } else if (filt == "lower") {
            if (foundLower) {
                usage("You said lower twice", progname);
            }
            if (foundUpper) {
                usage("You said upper lower", progname);
            }
            
            foundLower = true;
        } else if (filt == "letter") {
            doLetter = true;
            
            if (foundUpper) {
                doUpperLetter = true;
            }
            
            if (foundLower) {
                doLowerLetter = true;
            }
            
            foundUpper = foundLower = false;
        } else if (filt == "vowel") {
            doVowel = true;
            
            if (foundUpper) {
                doUpperVowel = true;
            }
            
            if (foundLower) {
                doLowerVowel = true;
            }
            
            foundUpper = foundLower = false;
        } else if (filt == "consonant") {
            doConsonant = true;
            
            if (foundUpper) {
                doUpperConsonant = true;
            }
            
            if (foundLower) {
                doLowerConsonant = true;
            }
            
            foundUpper = foundLower = false;
        } else if (filt == "word") {
            doWord = true;
            
            if (foundUpper) {
                doUpperWord = true;
            }
            
            if (foundLower) {
                doLowerWord = true;
            }
            
            foundUpper = foundLower = false;
        } else if (filt == "number") {
            if (foundUpper || foundLower) {
                usage("No such thing as an upper or lower number!", progname);
            }
            doNumber = true;
        } else if (filt == "space") {
            if (foundUpper || foundLower) {
                usage("No such thing as an upper or lower space!", progname);
            }
            doSpace = true;
        } else if (filt == "punct") {
            if (foundUpper || foundLower) {
                usage("No such thing as an upper or lower punct!", progname);
            }
            doPunct = true;
        } else {
            usage("Used unrecognized filter " + filt, progname);
        }
    }
    
    if (foundUpper || foundLower) {
        usage("You cannot end the list of filters with upper or lower", progname);
    }
    
    // ok, now it's time to read input a character at a time and apply the filters
    // i loop through reading characters and, if i decide they ought to be filtered,
    // i just "continue" to the next thing in the loop
    
    // i keep a simple state machine to know if i am in a word or not
    
    // doing things with "word" will supersede other smaller things...
    // ... so I do word things first when word things have been selected
    
    bool inWord = false;
    string theWord;
    
    while (true) {
        char    ch = infile.get();
        
        if (!infile.good()) {
            break;
        }
        
        if (doWord) {
            // if I am supposed to do something about words... and I am not in a word...
            // then remember that i am in a word and gather letters into a string
            if (!inWord && isalnum(ch)) {
                inWord = true;
                theWord = ch;
                continue;
            } else if (inWord && isalnum(ch)) {
                theWord += ch;
                continue;
            } else if (inWord && !isalnum(ch)) {
                // i am done with gathering a word, so I have to
                // decide to print it or skip it
                
                // for the letter that made me detect that I was at the "end of word",
                // put it back so I process it next time through
                infile.putback(ch);
                
                inWord = false;
                
                // decide if the word is all uppercase or all lowercase
                bool isAllUpper = true;
                bool isAllLower = true;
		bool hasLetters = false;
                
                for (int l=0; l < theWord.length(); l++) {
		    if (!hasLetters && isalpha(theWord[l]) )
		    	hasLetters = true;

                    if (isAllLower && isupper(theWord[l])) {
                        isAllLower = false;
                    }
                    else if (isAllUpper && islower(theWord.at(l))) {
                        isAllUpper = false;
                    }
                    
                    if (!isAllUpper && !isAllLower) {
                        break;
                    }
                }
                
                // decide what to do with it
                if (doUpperWord && hasLetters && isAllUpper) {
                    continue;
                }
                if (doLowerWord && hasLetters && isAllLower) {
                    continue;
                }
                if (!doUpperWord && !doLowerWord) { // then it's just a word... and we have to filter it
                    continue;
                }
                
                cout << theWord;
                continue;
            }
        }
        
        if (doSpace && isspace(ch)) {
            continue; // skip it
        }
        if (doPunct && ispunct(ch)) {
            continue;
        }
        if (doNumber && isdigit(ch)) {
            continue;
        }
        
        if (doLetter && isalpha(ch)) {
            if (doUpperLetter) {
                if (isupper(ch)) {
                    continue;
                }
            }
            if (doLowerLetter) {
                if (islower(ch)) {
                    continue;
                }
            }
            
            if (!doUpperLetter && !doLowerLetter) {
                continue;
            }
        }
        
        if (doVowel && isalpha(ch) && isvowel(ch)) {
            if (doUpperVowel) {
                if (isupper(ch)) {
                    continue;
                }
            }
            if (doLowerVowel) {
                if (islower(ch)) {
                    continue;
                }
            }
            
            if (!doUpperVowel && !doLowerVowel) {
                continue;
            }
        }
        
        if (doConsonant && isalpha(ch) && !isvowel(ch)) {
            if (doUpperConsonant) {
                if (isupper(ch)) {
                    continue;
                }
            }
            if (doLowerConsonant) {
                if (islower(ch)) {
                    continue;
                }
            }
            
            if (!doUpperConsonant && !doLowerConsonant) {
                continue;
            }
        }
        
        cout << ch;
    }
    
    return 0;
}
