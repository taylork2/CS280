//
//  p3eval
//

// these are stubs for assignment 3

#include "p3parser.h"
#include "p4value.h"
#include "searchResult.h"
#include <string>
#include <map>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

map<string, Value*> var;
map<int, list<SearchTool::SearchResultEntry *> > sort;

void
TypeError(string type, int line)
{
    cerr << "Type error performing " << type << " operator at line " << line << endl;
	exit(0);
}

Value *
PTree::eval()
{
	if (left)
		left -> eval();
	if (right)
		right -> eval();
    return 0;
}

Value *
PTreeStmtList::eval()
{
	if (left)
		left -> eval();
	if (right)
		right -> eval();
    return 0;
}

Value *
PTreeSet::eval()
{
	Value *val;
	val = left->eval();
	var[id] = val;	
    return val;
}

Value *
PTreePrint::eval()
{
	if (right || !left)
		TypeError("PRINT", line);

	Value *val;
	val = left -> eval();

	if (val -> getType() == T_STRING )
		cout << val->getStringValue() << endl;
	else if (val -> getType() == T_SEARCHRESULT){
		SearchTool::SearchResult *sea;
		sea = val->getSearchValue();

		list<SearchTool::SearchResultEntry *> results;
		results = sea->getResults();

		map<int, SearchTool::SearchResultEntry *> sort; //map of linenum to SearchResultEntry 

		//iterate through the results list; map linenum to SearchResultEntry
		for (list<SearchTool::SearchResultEntry *>::iterator it=results.begin(); it != results.end(); it++){
			sort[(*it)->getLinenum()] = *it;
		}

		//iterate through map which is sorted; cout the lines in sorted order 
		for (map<int, SearchTool::SearchResultEntry *>::iterator it2 = sort.begin(); it2 != sort.end(); it2++){
			cout << sea->getFile() << ":" << (it2)->first << ":" << (it2)->second -> getLine() << endl;
		}
	}
	else {
		TypeError("PRINT", line);
	}
	
    return 0;
}

Value *
PTreeUnion::eval()
{
	if (!left || !right){
		TypeError("UNION", line);
	}
	Value *val;
	val = left -> eval();

	Value *str;
	str = right -> eval();

	if (val -> getType() != T_SEARCHRESULT || str -> getType() != T_STRING) {
		TypeError("UNION", line);
	}

	SearchTool::SearchResult *sea;
	sea = val->getSearchValue();
	string file = sea->getFile();
	string searchfor = str->getStringValue();

	//do second search, push_back these new SearchResultEntrys to results
	if (!(sea -> dosearch(searchfor))){
		TypeError("UNION", line);
	}

	Value *returnVal;
	returnVal = new ValueSearchResult(sea);
    return returnVal;	
}


Value *
PTreeIntersect::eval()
{
	if (!left || !right) {
		TypeError("INTERSECTION", line);
	}
	Value *val;
	val = left -> eval();
	Value *str;
	str = right -> eval();

	if (val -> getType() != T_SEARCHRESULT || str -> getType() != T_STRING) {
		TypeError("INTERSECTION", line);
	}

	SearchTool::SearchResult *sea;
	SearchTool::SearchResult *sea2;

	sea = val->getSearchValue();
	string file = sea -> getFile();
	string searchfor = str -> getStringValue();

	sea2 = new SearchTool::SearchResult(file);
	sea2 -> dosearch(searchfor);

	list<SearchTool::SearchResultEntry *> result1;
	result1 = sea-> getResults();
	list<SearchTool::SearchResultEntry *> result2;
	result2 = sea2-> getResults();

	//filter these 2 to get the intersection
	map<int, SearchTool::SearchResultEntry *> result1map; //map linenum to searchResultEntry
	for (list<SearchTool::SearchResultEntry *>::iterator it=result1.begin(); it != result1.end(); it++){
		result1map[(*it)->getLinenum()] = *it;
	}

	//New list where result1 and result2 have matching linenum
	list<SearchTool::SearchResultEntry *> filteredList;
	for (list<SearchTool::SearchResultEntry *>::iterator it2=result2.begin(); it2 != result2.end(); it2++){
		try { 
			SearchTool::SearchResultEntry* entry;
			entry = result1map.at((*it2)->getLinenum());
			filteredList.push_back(entry);
		} catch(const std::out_of_range& e) {
			cout << (*it2)->getLinenum() <<endl;
			continue;
		}
	}

	SearchTool::SearchResult *sea3;
	sea3 = new SearchTool::SearchResult(file, filteredList);
	Value *returnVal;
	returnVal = new ValueSearchResult(sea3);

    return returnVal;
}

Value *
PTreeID::eval()
{	
	try { 
		cout << id << endl;
		return var.at(id);
	} catch(const std::out_of_range& e) {
		cout << "Variable " << id << " not set before use at line " << line << endl;
	}  
}

Value *
PTreeSTR::eval()
{
	if ( left || right )
		TypeError("STRING", line);
	Value *str;
	str = new ValueString(val);
    return str;
}

Value *
PTreeSearch::eval()
{
	if (left || right)
		TypeError("SEARCH", line);

	SearchTool::SearchResult *sea;
	sea = new SearchTool::SearchResult(filename);
	
	if(!(sea->dosearch(pattern))){
		TypeError("SEARCH", line);
	}


	Value *val;
	val = new ValueSearchResult(sea);
    return val;
}
