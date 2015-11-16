//============================================================================
// Name        : parser.cpp
// Description : lexical analysis project  
// Student name: Taylor Tu 
// Class	   : CS 280 
//============================================================================

#include "p2.lex"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>


int main(int argc, char *argv[]){
	istream *br; 
	ifstream infile;

	//Opening file 
	if (argc==1){
		br = &cin;
	}
	else if(argc == 2) { //must have at least 2 arguments 
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



}

