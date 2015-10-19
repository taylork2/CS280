#include "p2lex.h"
#include "token.cpp"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

map<Token, int> counters;
map< int, vector<Token> > bycount;

void usage(char *progname, string msg){
	cerr << "Error: " << msg << endl;
}
int main(int argc, char *argv[]){
	istream *br; 
	ifstream infile;

	//Opening file 
	if (argc==1){
		br = &cin;
	}
	else if(argc == 2) { //must have at least 3 arguments 
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
		usage(argv[0], "Too many command line arguments.");
		return 1;
	}

	if(!(br->good())){
		usage(argv[0], "I could not read your file :/");
		return 1; 
	}

	Token token;
	string lex;
	vector<string> identifiers;
	while (true){
		token = getToken(br, lex);
		counters[token]++;

		if (token == ID){
			if (identifiers.count(lex)){
				identifiers.push_back(lex);	
			}
		} else if (token == DONE){
			break;
		} else if (token == ERR){
			cout << "Error on line " << linenum;
			return 1;
		}
	}
	
	
	return 0;

}