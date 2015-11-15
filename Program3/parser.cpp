//============================================================================
// Name        : parser.cpp
// Description : small language parser 
// Student name: Taylor Tu 
// Class	   : CS 280 
//============================================================================

#include "p2lex.h"

using namespace std;

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

	enum Type {T_STRING, T_SEARCHRESULT, T_NONE };

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

PTree *Stmt(istream *br) {
	PTree *
}