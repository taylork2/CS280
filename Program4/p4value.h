//
//  p4value.h
//  parser
//

#ifndef p4value_h
#define p4value_h

// class definition for values in the interpreter

#include <string>
#include "p3parser.h"		// parser definitions
#include "searchResult.h"	// search pieces
using namespace std;

extern int errcnt2;

class Value {
public:
    virtual string getStringValue() {
        return "";
    }
    
    virtual SearchTool::SearchResult *getSearchValue() {
        return 0;
    }
    
    virtual PTree::Type getType() = 0;
};

//String 
class ValueString : public Value {
    string val;
    
public:
    ValueString(string& v) : val(v) {}
    
    string getStringValue() { return val; }
    PTree::Type getType() { return PTree::T_STRING; }
};

//Search Result
class ValueSearchResult : public Value {
    SearchTool::SearchResult    *val;
    
public:
    ValueSearchResult(SearchTool::SearchResult *v) : val(v) {}
    
    SearchTool::SearchResult    *getSearchValue() { return val; }
    PTree::Type getType() { return PTree::T_SEARCHRESULT; }
};

#endif /* p4value_h */