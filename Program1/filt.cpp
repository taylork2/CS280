//============================================================================
// Name        : filt.cpp
// Description : filters out certain things from input file
// Student name: Taylor Tu 
// Class	   : CS 280 
//============================================================================

#include <cctype> //isupper(ch) and islower(ch)
#include <fstream> //to read file 
#include <iostream> //input output 
#include <string> //string shortcut instead of char array 
using namespace std;

//Usage function: Tell user what's wrong 
void  usage(char *progname, string msg) {
	cerr << "Error: " << msg << endl;
	cerr << "Usage is: " << progname << " [filename] [filter1] [filter2] [etc.]" <<endl;
}

int main(int argc, char *argv[]) { //Takes in command line args 
	istream *br; 
	string fullText; 
	ifstream infile;

	//Opening file 
	if(argc >= 3) { //must have at least 3 arguments 
		infile.open(argv[1]);
		if(infile.is_open()){
			br = &infile;
		}
		else{
			usage(argv[0], "Cannot open " + string(argv[1]));
			return 1;
		}
	}
	else {
		usage(argv[0], "Enter a filename and filter.");
		return 1;
	}

	if(!(br->good())){
		usage(argv[0], "I could not read your file :/");
		return 1; 
	}

	//Possible filters 
	bool letterCalled = false;
	bool vowelCalled = false;
	bool consonantCalled = false;
	bool wordCalled = false; 
	bool punctCalled = false;
	bool numberCalled = false;
	bool spaceCalled = false;
	//Upper modifier
	bool upperLetterCalled = false;
	bool upperVowelCalled = false;
	bool upperConsonantCalled = false;
	bool upperWordCalled = false;
	//Lower modifier 
	bool lowerLetterCalled = false;
	bool lowerVowelCalled = false;
	bool lowerConsonantCalled = false;
	bool lowerWordCalled = false;
	bool upperAndLowerWord = false;

	//boolean will be true if filter called  
	for (int it=2; it<argc; it++){
		string arg = argv[it];
		if (arg=="letter"){
			letterCalled = true;
		}
		else if (arg=="vowel"){
			vowelCalled = true;				
		}
		else if (arg=="consonant"){
			consonantCalled = true;
		}
		else if (arg=="upper"){
			if (it+1 >= argc){ //prevent calling out of bounds
				usage(argv[0], "Upper must modify a filter.");
					return 1; 
			}
			else {
				string nextArg = argv[it+1];
				if (nextArg == "letter"){
					upperLetterCalled = true;
				}
				else if (nextArg == "consonant"){
					upperConsonantCalled = true;
				}
				else if (nextArg == "vowel"){
					upperVowelCalled = true;
				}
				else if (nextArg == "word"){
					upperWordCalled = true;
				}
				else {
					usage(argv[0], "Upper cannot modify this filter.");
					return 1; 
				}
				it++;
			}

		}
		else if (arg=="lower"){
			if (it+1 >= argc){ //prevent calling out of bounds
				usage(argv[0], "Upper must modify a filter.");
					return 1; 
			}
			else {
				string nextArg = argv[it+1];  
				if (nextArg == "letter"){
					lowerLetterCalled = true;
				}
				else if (nextArg == "consonant"){
					lowerConsonantCalled = true;
				}
				else if (nextArg == "vowel"){
					lowerVowelCalled = true;
				}
				else if (nextArg == "word"){
					lowerWordCalled = true;
				}
				else{
					usage(argv[0], "Lower cannot modify this filter.");
					return 1; 
				}
				it++;
			}
		}
		else if (arg=="word"){
			wordCalled = true;
		}
		else if (arg=="number"){
			numberCalled = true;
		}
		else if (arg=="space"){
			spaceCalled = true;
		}
		else if (arg=="punct"){
			punctCalled = true;
		}
		else{
			usage(argv[0], "Unrecognized filter: " + arg);
			return 1;
		}
	}

	if (upperWordCalled && lowerWordCalled){
		upperAndLowerWord = true; 
	}

	bool lowerLet = true; //true if entire word is lower letters or numbers
	bool containsLower = false; //true if word contains lower letter 
	bool upperLet = true; //true if entire word is upper letters or numbers
	bool containsUpper = false; //true if word contains upper letter

	string word = "";
	string vowels = "aeiouAEIOU";

	//pulls in character at a time, cout ch if not filtered out
	char ch;
	while(infile.get(ch)) {
		if (letterCalled && isalpha(ch)){ 
			continue;
		}
		else if (upperLetterCalled && isupper(ch)){ 
			continue;
		}
		else if (lowerLetterCalled && islower(ch)){ 
			continue;
		}
		else if (vowelCalled && vowels.find(ch) < vowels.length()){
			continue;
		}
		else if (lowerVowelCalled && islower(ch) && vowels.find(ch) < vowels.length()){
			continue;
		}
		else if (upperVowelCalled && isupper(ch) && vowels.find(ch) < vowels.length()){
			continue;
		}
		else if(consonantCalled && vowels.find(ch) >= vowels.length()){
			continue;
		}
		else if(upperConsonantCalled && isupper(ch) && vowels.find(ch) >= vowels.length()){
			continue;
		}
		else if(lowerConsonantCalled && islower(ch) && vowels.find(ch) >= vowels.length()){
			continue;
		}
		else if(wordCalled && (isalpha(ch) || isdigit(ch))) {
			continue;
		}
		else if (upperAndLowerWord){
			word += ch;
			if ((ispunct(ch) || isspace(ch)) && upperLet && containsUpper){
				containsUpper = false;
				word = "";
				cout << ch;
			}
			else if ((ispunct(ch) || isspace(ch)) && lowerLet && containsLower){
				containsLower=false;
				word = "";
				cout << ch;
			}
			else if (ispunct(ch) || isspace(ch)){
				containsUpper = false;
				upperLet = true;
				containsLower = false;
				lowerLet = true;
				cout << word; 
				word = "";
			}
			else if (!isupper(ch) && !isdigit(ch)){
				upperLet = false;
				containsLower = true;
			}
			else if (isupper(ch)){
				containsUpper = true;
				lowerLet = false;
			}

		}
		else if(upperWordCalled) {
			word += ch; 
			if ((ispunct(ch) || isspace(ch)) && upperLet && containsUpper){
				containsUpper = false;
				word = "";
				cout << ch;
			}
			else if (ispunct(ch) || isspace(ch)){
				containsUpper = false;
				upperLet = true;
				cout << word; 
				word = "";
			}
			else if (!isupper(ch) && !isdigit(ch)){
				upperLet = false;
			}
			else if (isupper(ch)){
				containsUpper = true;
			}

		}
		else if(lowerWordCalled) { 
			word += ch; 
			if ((ispunct(ch) || isspace(ch)) && lowerLet && containsLower){
				containsLower=false;
				word = "";
				cout << ch;
			}
			else if (ispunct(ch) || isspace(ch)){
				containsLower = false;
				lowerLet = true;
				cout << word; 
				word = "";
			}
			else if (!islower(ch) && !isdigit(ch)){
				lowerLet = false;
			}
			else if (islower(ch)){
				containsLower = true;
			}

		}
		else if(numberCalled && isdigit(ch)){
			continue;
		}
		else if(spaceCalled && isspace(ch)){ 
			continue;
		}
		else if(punctCalled && ispunct(ch)){
			continue;
		}
		else {
			cout << ch;
		}
	}

	if (upperWordCalled && upperLet && containsUpper) {
		cout << word;
	}
	if (lowerWordCalled && lowerLet && containsLower) {
		cout << word;
	}

	return 0;
}