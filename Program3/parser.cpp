//============================================================================
// Name        : parser.cpp
// Description : small language parser 
// Student name: Taylor Tu 
// Class	   : CS 280 
//============================================================================

#include "p2lex.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

int errorCount=0;

void usage(char *progname, string msg){
	cerr << "Error: " << msg << endl;
}

class PTree{
protected:
	int line;
	PTree *left;
	PTree *right;

public:
	PTree(int line, PTree *left = 0, *right = 0){
		this -> line = line;
		this -> left = left;
		this -> right = right;
	}

	int nodeCount() {
		//4-5 lines implementation 
	}

	//must be virtual because C++ doesn't automatically do this like JAVA
	virtual void findEmptyStrings() {}
	virtual void  findInvalidOps() {}

	enum Type {T_STRING, T_SEARCHRESULT, T_NONE};

	virtual Type getType() {return T_NONE;}
};

//this is how to create derived class and initialize 
class PTreeStmtList : public PTree {
public: 
	PTreeStmtList(int line, PTree *s1, PTree *s2 = 0) : PTree(line, s1, s2) {}
};

//Program ::= StmtList 
PTree *Program(istream *br){
	return StmtList(br);
}

//StmtList ::= Stmt | Stmt StmtList
PTree *StmtList(istream *br) {
	PTree *stmt;
	stmt = Stmt(br);
	if (stmt)
		return new PTreeStmtList(linenum stmt, StmtList(br));
	return 0; 
}

//Stmt ::= PRINT Expr SC | SET ID Expr SC
PTree *Stmt(istream *br) {
	if getToken(br)	== PRINT{
		PTree *expr;
		expr = Expr(br);
		if (expr){
			if getToken(br) == SC{
				return new PTreeStmtList(linenum expr, Stmt(br));
			}
			else{
				usage(argv[0], "Expecting semi-colon");
				errorCount++;	
				return 1;}
		}
		else {
			usage(argv[0], "Expecting expression");
			errorCount++;
			return 1;
		}
	}
	else if getToken(br) == SET{
		if getToken(br) == ID{
			PTree *expr;
			expr = Expr(br);
			if (expr){
				if getToken(br) == SC{
					return new PTreeStmtList(linenum stmt, Stmt(br));
				}
				else {
					usage(argv[0], "Expecting semi-colon");
					errorCount++;
					return 1;
				}
			} else {
				usage(argv[0], "Expecting expression");
				errorCount++;
				return 1;
			}
		} else {
			usage(argv[0], "Expecting ID");
			errorCount++;
			return 1;
		}
	}
	return 0;	
}

//Expr ::= Term UNION Expr | Term
PTree *Expr(istream *br){
	PTree *term;
	term = Term(br);
	if (term){
		if 	getToken(br) == UNION{
			PTree *term2;
			term2 = Term(br);
			if (term2){
				PTree *expr;
				expr = Expr(br);
				if (expr){
					return new PTreeStmtList(linenum stmt, Expr(br));
				}
				return 1;
			}
			return 1;
		}
		else{
			return new PTreeStmtList(linenum stmt, Expr(br));
		}
	}
	return 0;
}

//Term ::= Primary INTERSECT Term | Primary
PTree *Term(istream *br){
	return 0;
}


//Primary ::= Search_expr | ID | STRING | LPAREN Expr RPAREN
PTree *Primary(istream *br){
	return 0;
}

//Search_expr ::= SEARCH STRING FOR STRING
PTree *Search_expr(istream *br){
	return 0;
}

