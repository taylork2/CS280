//============================================================================
// Name        : filt.cpp
// Description : filters out certain things from input file
// Student name: Taylor Tu 
// Class: CS 280 
//============================================================================

#include <cctype> //isupper(ch) and islower(ch)
#include <fstream> //to read file 
#include <iostream> //input output 
#include <string> //string shortcut instead of char array 
#include <vector> //vector short cut (list)
using namespace std;

//Usage function: Tell user what's wrong 
void  usage(char *progname, string msg) {
	cerr << "Error: " << msg << endl;
	cerr << "Usage is: " << progname << " [filename] [arg1] [arg2] [etc.]" <<endl;
}

int main(int argc, char *argv[]) { //Takes in command line args 
	istream *br;
	string text;
	string fullText;
	ifstream infile;
	string filters[9] = {"letter", "vowel", "consonant", "word", "number", "space", "punct", "upper", "lower"};

	//Opening file 
	if (argc == 1){
		usage(argv[0], "Enter a filename.");
	}
	else if(argc >= 3) { //must have 3 arguments
		infile.open(argv[1]);
		if(infile.is_open()){
			br = &infile;
		}
		else{
			usage(argv[0], "Cannot open " + string(argv[1]));
			return 1;
		}
	}

	if( br->good() )
		cout << "GOOD"<<endl;
	else{
		usage(argv[0], "I could not read your file :/");
		return 1; 
	}
	//Done opening file 

	//Go through text line by line, put each line into fullText  
	// while(getline(*br, text)){
	// 	fullText += text;
	// 	fullText.push_back('\n');
	// 	//cout << fullText << endl;
	// }

	//while(file.good()){
	//{
	//	char ch = file.get();
	//}
	//cout << fullText << endl;

	cout << "There were " << argc << " arguments on the command line" << endl;

	bool letterCalled = false;
	bool vowelCalled = false;
	bool consonantCalled = false;
	bool upperCalled = false;
	bool lowerCalled = false;
	bool wordCalled = false; 
	bool punctCalled = false;
	bool numberCalled = false;
	bool spaceCalled = false;

	//check if all arguments are filters 
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
			upperCalled = true;
		}
		else if (arg=="lower"){
			lowerCalled = true;
		}
		else if (arg=="word"){ //what do????? 
			wordCalled = true;
		}
		else if (arg=="number"){
			numberCalled = true;
		}
		else if (arg=="space"){ //what do?????
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

	string vowels = "aeiouAEIOU";
	while(infile.good()) {
		char ch = infile.get();
		if (isalpha(ch) && letterCalled){ 
			cout << ch << endl;
			continue;
		}
		else if (vowelCalled && vowels.find(ch) < vowels.length()){
			cout << ch << endl;
			continue;
		}
		else if(consonantCalled && isalpha(ch) && vowels.find(ch) >= vowels.length()){
			cout << ch << endl;
			continue;
		}
		else if(upperCalled && isupper(ch)){
			cout << ch << endl;
			continue;
		}
		else if(lowerCalled && islower(ch)){
			cout << ch << endl;
			continue;
		}
		else if(wordCalled){ //what do????? 
			cout << ch << endl;
		}
		else if(numberCalled && isdigit(ch)){
			cout << ch << endl;
			continue;
		}
		else if(spaceCalled && isdigit(ch)){ //what do???? 
			cout << ch << endl;
		}
		else if(punctCalled && ispunct(ch)){
			cout << ch << endl;
			continue;
		}
		else {
			fullText += ch;
		}
	}
	cout << fullText;
	return 0;
}