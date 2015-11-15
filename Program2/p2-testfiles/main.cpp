//============================================================================
// Name        : main.cpp
// Description : Outputs number of top 3 most-used tokens
// Student name: Taylor Tu 
// Class	   : CS 280 
//============================================================================

#include "p2lex.h"
#include "token.cpp"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

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
	//Calling getToken()
	while (true){
		token = getToken(br, lex);
		counters[token]++;

		if (token == ID){
			if (identifiers.empty() || find(identifiers.begin(), identifiers.end(), lex) == identifiers.end()){
				identifiers.push_back(lex);	
			}
		} else if (token == DONE){
			break;
		} else if (token == ERR){
			cout << "Error on line " << linenum <<endl;
			return 1;
		}
	}

	//iterate through counters, append Tokens to list at int of Tokens key 
	map<Token, int>::iterator it;
	for(it=counters.begin(); it != counters.end(); it++){
		bycount[it->second].push_back(it->first);		
	}

	//iterate backward through bycount, output top 3 Tokens
	map< int, vector<Token> >::reverse_iterator it2;
	int limit=0;
	for (it2=bycount.rbegin(); it2 != bycount.rend(); it2++){
		limit ++; 
		for (int x=0; x< it2-> second.size(); x++){
			Token token = it2->second[x];
			if (token == ID){
				cout << "Identifier: ";
			} else if (token == STRING){
				cout << "String constant: ";
			} else if (token == UNION){
				cout << "Union operator: ";
			} else if (token == INTERSECT){
				cout << "Intersect operator: ";
			} else if (token == SET){
				cout << "SET keyword: ";
			} else if (token == PRINT){
				cout << "PRINT keyword: ";
			} else if (token == SEARCH){
				cout << "SEARCH keyword: ";
			} else if (token == FOR){
				cout << "FOR keyword: ";
			} else if (token == LPAREN){
				cout << "Left paren: ";
			} else if (token == RPAREN){
				cout << "Right paren: ";
			} else if (token == SC){
				cout << "Semicolon: ";
			}

			if (token != DONE){
				cout << it2->first <<endl;	
			}			
		}
		//Print only top 3 
		if (limit > 2){
			break;
		}
	}

	//output identifiers if there are any
	if (identifiers.size() != 0){
<<<<<<< Updated upstream
		cout << "List of identifiers: ";
		for (int x = 0; x < identifiers.size(); x++){
			if (x==identifiers.size()-1){
				cout << identifiers[x];
=======
		cout << endl; 
		int index=0;
		cout << "List of identifiers: ";
		map<string, int>::iterator it3;
		for (it3 = identifiers.begin(); it3 != identifiers.end(); it3++){
			index++;
			if (index == identifiers.size()){
				cout << it3-> first << endl;
>>>>>>> Stashed changes
			} else {
				cout << identifiers[x] << ", ";
			}
		}
	}
	 
	return 0;
}