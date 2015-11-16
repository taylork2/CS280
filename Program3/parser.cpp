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

void usage(string msg){
	cerr << "Error: " << msg << endl;
}

class PTree{
protected:
	int line;
	PTree *left;
	PTree *right;

public:
	PTree(int line, PTree *left = 0, PTree *right = 0){
		this -> line = line;
		this -> left = left;
		this -> right = right;
	}

	int nodeCount(PTree *node) {
		if (node == NULL){
			return 0;
		}
		else {
			int count = 1;
			count += nodeCount(node -> left);
			count += nodeCount(node -> right);
			return count; 
		}
	}

	//must be virtual because C++ doesn't automatically do this like JAVA
	virtual void findEmptyStrings() {}
	virtual void  findInvalidOps() {}

	enum Type {T_STRING, T_SEARCHRESULT, T_NONE};

	virtual Type getType() {return T_NONE;}
};

//Class inheritance hierarchy ====================================================
class PTreeStmtList : public PTree {
public: 
	PTreeStmtList(int line, PTree *s1, PTree *s2 = 0) : PTree(line, s1, s2) {}
};

class PTreeStmt : public PTree{
public:
	PTreeStmt(int line, PTree *s1, PTree *s2 = 0) : PTree(line, s1, s2) {}
};

class PTreeExpr : public PTree{
public:
	PTreeExpr(int line, PTree *s1, PTree *s2 = 0) : PTree(line, s1, s2) {}
};

//===============================================================================

string lexeme;

//Search_expr ::= SEARCH STRING FOR STRING
PTree *Search_expr(istream *br){
	if (getToken(br, lexeme) == SEARCH){

	}
	return 0;
}

//Primary ::= Search_expr | ID | STRING | LPAREN Expr RPAREN
PTree *Primary(istream *br){
	return 0;
}

//Term ::= Primary INTERSECT Term | Primary
PTree *Term(istream *br){
	return 0;
}

//Expr ::= Term UNION Expr | Term
PTree *Expr(istream *br){
	PTree *term;
	term = Term(br);
	if (term){
		if 	(getToken(br, lexeme) == UNION){
			PTree *term2;
			term2 = Term(br);
			if (term2){
				PTree *expr;
				expr = Expr(br);
				if (expr){
					return new PTreeStmtList(linenum, expr, Expr(br));
				}
				return 0;
			}
			return 0;
		}
		else{
			return new PTreeStmtList(linenum, term, Expr(br));
		}
	}
	return 0;
}


//Stmt ::= PRINT Expr SC | SET ID Expr SC
PTree *Stmt(istream *br) {
	
	if (getToken(br, lexeme) == PRINT){
		PTree *expr;
		expr = Expr(br);
		if (expr){
			if (getToken(br, lexeme) == SC){
				return new PTreeStmt(linenum, expr, Stmt(br));
			}
			else{
				usage("Expecting semi-colon");
				errorCount++;	
				return 0;}
		}
		else {
			usage("Expecting expression");
			errorCount++;
			return 0;
		}
	}
	else if (getToken(br, lexeme) == SET){
		if (getToken(br, lexeme) == ID){
			PTree *expr;
			expr = Expr(br);
			if (expr){
				if (getToken(br, lexeme) == SC){
					return new PTreeStmt(linenum, expr, Stmt(br));
				}
				else {
					usage("Expecting semi-colon");
					errorCount++;
					return 0;
				}
			} else {
				usage("Expecting expression");
				errorCount++;
				return 0;
			}
		} else {
			usage("Expecting ID");
			errorCount++;
			return 0;
		}
	}
	return 0;	
}

//StmtList ::= Stmt | Stmt StmtList
PTree *StmtList(istream *br) {
	PTree *stmt;
	stmt = Stmt(br);
	if (stmt)
		return new PTreeStmtList(linenum, stmt, StmtList(br));
	return 0; 
}

//Program ::= StmtList 
PTree *Program(istream *br){
	return StmtList(br);
}