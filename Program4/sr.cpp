#include "p3parser.h"
#include "p2lex.h"
#include "p4value.h"
#include "searchResult.h"
#include <string>
#include <list>
#include <iterator>

using namespace std;

int 
main() {
	SearchTool::SearchResult *sea;	
	sea = new SearchTool::SearchResult("underpressure.txt");

	string s = "Pressure";
	string t = "down";

	if (sea->dosearch(s) && sea->dosearch(t)){
		list<SearchTool::SearchResultEntry *> results;
		results = sea->getResults();
		list<SearchTool::SearchResultEntry *>::iterator it;

		for (it=results.begin(); it != results.end(); it++){
			cout << sea->getFile() << ":" << (*it)->getLinenum() << ":" << (*it)->getLine() << endl;
		}

	}
	return 0;

}

