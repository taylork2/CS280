//============================================================================
// Name        : parser.cpp
// Description : small language parser 
// Student name: Taylor Tu 
// Class	   : CS 280 
//============================================================================

#ifndef PARSER
#define PARSER_H

#include "p2lex.h"
#include <string>	
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int errorCount=0;

void usage(string msg){
	errorCount++;
	cerr << linenum << ": " << msg << endl;
}

void invalid(string op, int line) {
	cerr << "Invalid " << op << " operator for given types at line " << line << endl;
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

	int nodeCount() {
		if (left == NULL && right == NULL){
			return 1;
		} else if (left == NULL){
			return 1 + right -> nodeCount();
		} else if (right == NULL){
			return 1 + left -> nodeCount();
		} else {
			return 1+right->nodeCount() + left->nodeCount();
		}
	}

	//must be virtual because C++ doesn't automatically do this like JAVA
	virtual void findEmptyStrings() {
		if (left!=NULL){
			left -> findEmptyStrings();
		}
		if (right!=NULL){
			right -> findEmptyStrings();
		}
	}

	virtual void  findInvalidOps() {
		if (left!=NULL){
			left -> findInvalidOps();
		}
		if (right!=NULL){
			right -> findInvalidOps();
		}
	}

	enum Type {T_STRING, T_SEARCHRESULT, T_NONE};

	virtual Type getType() {return T_NONE;}
};


PTree *Search_expr(istream *br);
PTree *Primary(istream *br);
PTree *Term(istream *br);
PTree *Expr(istream *br);
PTree *Stmt(istream *br);
PTree *StmtList(istream *br);
PTree *Program(istream *br);

//Class inheritance hierarchy ====================================================
class PTreeStmtList : public PTree {
public: 
	PTreeStmtList(int line, PTree *s1, PTree *s2 = 0) : PTree(line, s1, s2) {}
};

class PTreePrint : public PTree{
public:
	PTreePrint(int line, PTree *s1, PTree *s2 = 0) : PTree(line, s1, s2) {}
};

class PTreeSet : public PTree{
public:
	PTreeSet(int line, PTree *s1=0, PTree *s2 = 0) : PTree(line, s1, s2) {}
};

class PTreeID : public PTree{ 
public:
	PTreeID(int line, PTree *s1=0, PTree *s2 = 0) : PTree(line, s1, s2) {}
};

class PTreeUnion : public PTree{
protected:
	PTree *s1;
	PTree *s2;
public:
	PTreeUnion(int line, PTree *s1=0, PTree *s2 = 0) : PTree(line, s1, s2) {
		this -> s1 = s1;
		this -> s2 = s2;
	}

	void findInvalidOps(){
		if (s1){
			if (s1->getType() == T_STRING){
				if ((s2 && s2->getType() != T_SEARCHRESULT) || s2==NULL){
					invalid("union", line);
				}
			}
			else if(s1->getType() == T_SEARCHRESULT){
				if ((s2 && s2->getType() != T_STRING) || s2==NULL){
					invalid("union", line);
				}
			}
			else {
				invalid("union", line);
			}
		}
		else{
			invalid("union", line);
		}
		s1->findInvalidOps();	
		s2->findInvalidOps();
	}

	Type getType(){ return T_SEARCHRESULT; }
};

class PTreeIntersect : public PTree{
protected:
	PTree *s1;
	PTree *s2;
public:
	PTreeIntersect(int line, PTree *s1=0, PTree *s2 = 0) : PTree(line, s1, s2) {
		this -> s1 = s1;
		this -> s2 = s2;
	}
	void findInvalidOps(){
		if (s1){
			if (s1->getType() == T_STRING){
				if ((s2 && s2->getType() != T_SEARCHRESULT) || s2==NULL){
					invalid("intersect", line);
				}
			}
			else if(s1->getType() == T_SEARCHRESULT){
				if ((s2 && s2->getType() != T_STRING) || s2==NULL){
					invalid("intersect", line);
				}
			}
			else {
				invalid("intersect", line);
			}
		}
		else{
			invalid("intersect", line);
		}
		s1->findInvalidOps();	
		s2->findInvalidOps();
	}

	Type getType(){ return T_SEARCHRESULT; }
};

class PTreeString : public PTree{
private: 
	string lex;
	PTree *s1;
	PTree *s2;
public:
	PTreeString(int line, string lex, PTree *s1=0, PTree *s2 = 0) : PTree(line, s1, s2) {
		this -> lex = lex;
		this -> s1 = s1;
		this -> s2 = s2;
	}	
	void findEmptyStrings(){
		if (lex == "\"\""){
			cout << "Empty string at line " << line << endl;
		}
		if (s1 != NULL){s1 -> findEmptyStrings();}
		if (s2 != NULL){s2 -> findEmptyStrings();}
		
	}

	Type getType(){	return T_STRING; }
};

class PTreeSearch : public PTree{
public:
	PTreeSearch(int line, PTree *s1=0, PTree *s2 = 0) : PTree(line, s1, s2) {}
	Type getType(){	return T_SEARCHRESULT; }
};

//===============================================================================

string lexeme;

//Search_expr ::= SEARCH STRING FOR STRING
PTree *Search_expr(istream *br){
	Token tok = getToken(br, lexeme);
	if (tok == SEARCH){
		if (getToken(br, lexeme) == STRING){
			if (getToken(br, lexeme) == FOR){
				if (getToken(br, lexeme)== STRING){
					return new PTreeSearch(linenum);
				} else {
					usage("Expecting STRING");}
			} else {
				usage("expecting FOR");}
		} else {
			usage("Expecting STRING");}
	}
	else {
		pushbackToken(tok, lexeme);
		usage("Missing primary");
	}
	return 0;
}

//Primary ::= Search_expr | ID | STRING | LPAREN Expr RPAREN
PTree *Primary(istream *br){
	Token tok = getToken(br, lexeme);
	if (tok == STRING){return new PTreeString(linenum, lexeme);}
	else if (tok == ID) {return new PTreeID(linenum);}
	else if (tok == LPAREN) {
		PTree *expr;
		expr = Expr(br);
		if (expr){
			if (getToken(br, lexeme)==RPAREN){
				return expr;
			} else {
				usage("Expecting RParen");
			}	
		} else {
			usage("Expected a expression");
		}
	}
	else {	
		pushbackToken(tok, lexeme);
		PTree *search;
		search = Search_expr(br);
		if (search){return search;}
		else{
			usage("Expected an expression");
		}
	}
	return 0;
}

//Term ::= Primary INTERSECT Term | Primary
PTree *Term(istream *br){
	PTree *primary;
	primary = Primary(br);
	if (primary){
		Token tok = getToken(br, lexeme);
		if (tok ==INTERSECT){
			PTree *term;
			term = Term(br);
			if (term){
				return new PTreeIntersect(linenum, primary, term);
			}
			else{
				usage("Expected an expression");
			}
		}
		else {
			pushbackToken(tok, lexeme);
			return primary;}
	}
	return 0;
}

//Expr ::= Term UNION Expr | Term
PTree *Expr(istream *br){
	PTree *term;
	term = Term(br);
	if (term){
		Token tok = getToken(br, lexeme);
		if 	( tok == UNION ){
			PTree *expr;
			expr = Expr(br);
			if (expr){
				return new PTreeUnion(linenum, term, expr);
			}
			else {
				usage("Expected an expression");}
		}
		else{
			pushbackToken(tok, lexeme);
			return term;}
	}
	return 0;
}


//Stmt ::= PRINT Expr SC | SET ID Expr SC
PTree *Stmt(istream *br) {
	Token tok = getToken(br, lexeme);
	if ( tok == PRINT){
		PTree *expr;
		expr = Expr(br);
		if (expr){
			Token tok2 = getToken(br, lexeme);
			if (tok2  == SC){
				return new PTreePrint(linenum, expr);
			}
			else{
				pushbackToken(tok, lexeme);
				usage("Expecting semi-colon");
			}
		}
	}
	else if (tok == SET){
		if (getToken(br, lexeme) == ID){
			PTree *expr;
			expr = Expr(br);
			if (expr){
				if (getToken(br, lexeme) == SC){
					PTree *pSet;
					pSet = new PTreeSet(linenum, 0);
					return new PTreeID(linenum, pSet, expr);
				}
				else {
					usage("Expecting semi-colon");
				}
			} else {
				usage("Expected an expression");
				// return 0;
			}
		} else {
			usage("Expecting ID");
			// return 0;
		}
	}
	return 0;	
}

//StmtList ::= Stmt | Stmt StmtList
PTree *StmtList(istream *br) {
	PTree *stmt;
	stmt = Stmt(br);
	if (stmt){
		return new PTreeStmtList(linenum, stmt, StmtList(br));
	}
	return 0; 
}

//Program ::= StmtList 
PTree *Program(istream *br){
	return StmtList(br);
}

#endif
