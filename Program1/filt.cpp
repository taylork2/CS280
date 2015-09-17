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

string letter(string text){
	//remove letters 
	for (int index = 0; index < text.length(); index++){
		char ch = text[index];
		if (isalpha(ch)){
			//cout << ch << endl;
			text.erase(text.begin() + index);
			index--;
		}
	}
	return text;
}	

string vowel(string text){
	//remove vowels 
	string vowels = "aeiouAEIOU";
	for (int index = 0; index < text.length(); index++){
		char ch = text[index];
		if (vowels.find(ch)<vowels.length()){
			//cout << ch << endl;
			text.erase(text.begin() + index);
			index--;
		}
	}
	return text;
}

string punct(string text){
	//remove punctuation
	for (int index = 0; index < text.length(); index++){
		char ch = text[index];
		if (ispunct(ch)){
			//cout << ch << endl;
			text.erase(text.begin() + index);
			index--;
		}
	}
	return text;
}

string consonant(string text){
	//remove consonants
	string vowels = "aeiouAEIOU";
	for (int index = 0; index < text.length(); index++){
		char ch = text[index];
		if (vowels.find(ch)>=vowels.length()&&isalpha(ch)){
			//cout << ch << endl;
			text.erase(text.begin() + index);
			index--;
		}
	}
	return text;
}

string upper(string text){
	//remove Uppercase letters 
	for (int index = 0; index < text.length(); index++){
		char ch = text[index];
		if (isupper(ch)){
			//cout << ch << endl;
			text.erase(text.begin() + index);
			index--;
		}
	}
	return text;
}

string lower(string text){
	//remove lowercase letters 
	for (int index = 0; index < text.length(); index++){
		char ch = text[index];
		if (islower(ch)){
			//cout << ch << endl;
			text.erase(text.begin() + index);
			index--;
		}
	}
	return text;
}

string number(string text){
	//remove numbers
	for (int index = 0; index < text.length(); index++){
		char ch = text[index];
		if (isdigit(ch)){
			//cout << ch << endl;
			text.erase(text.begin() + index);
			index--;
		}
	}
	return text;
}

int main(int argc, char *argv[]) { //Takes in command line args 
	istream *br;
	string text;
	string fullText;
	ifstream infile;
	//string filters[9] = {"letter", "vowel", "consonant", "word", "number", "space", "punct", "upper", "lower"};

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
	while(getline(*br, text)){
		fullText += text;
		fullText.push_back('\n');
		//cout << fullText << endl;
	}

	//while(file.good()){
	//{
	//	char ch = file.get();
}
}
	cout << fullText << endl;

	cout << "There were " << argc << " arguments on the command line" << endl;

	bool letterCalled = false;
	//check if all arguments are filters 
	for (int it=2; it<argc; it++){
		string arg = argv[it];
		if (arg=="letter"){ //== instead of .compare
			cout << "letter" << endl;
			fullText = letter(fullText);
			letterCalled = true;
			cout << fullText << endl;
		}
		else if (arg.compare("vowel")==0){
			cout << "vowel" << endl;
			fullText = vowel(fullText);
			cout << fullText << endl;
		}
		else if (arg.compare("consonant")==0){
			cout << "consonant" << endl;
			fullText = consonant(fullText);
			cout << fullText << endl;
		}
		else if (arg.compare("upper")==0){
			cout << "upper" << endl;
			fullText = upper(fullText);
			cout << fullText<<endl;
		}
		else if (arg.compare("lower")==0){
			cout << "lower" << endl;
			fullText = lower(fullText);
			cout << fullText<<endl;
		}
		else if (arg.compare("word")==0){
			cout << "word" << endl;
		}
		else if (arg.compare("number")==0){
			cout << "number" << endl;
			fullText = number(fullText);
			cout << fullText<<endl;
		}
		else if (arg.compare("space")==0){
			cout << "space" << endl;
		}
		else if (arg.compare("punct")==0){
			cout << "punct" << endl;
		}
		else{
			usage(argv[0], "Unrecognized filter: " + arg);
			return 1;
		}
	}

	return 0;
}