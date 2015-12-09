//
//  searchResult.h
//  parser
//

#ifndef searchResult_h
#define searchResult_h

#include <string>
#include <istream>
#include <vector>
#include <list>
using namespace std;

namespace SearchTool {
    
    class SearchResultEntry {
        long              linenum;    // line number where match was found
        string            line;       // the lines that were matched
        vector<string>    patterns;   // strings that are found in "match"
        
    public:
        SearchResultEntry(long ln, vector<string> s, string l) {
            linenum = ln;
            line = l;
            patterns = s;
        }
        long getLinenum() { return linenum; }
        string getLine() { return line; }
        vector<string>& getPatterns() { return patterns; }
    };
    
    class SearchResult {
        string				file_to_search;
        list<SearchResultEntry *>  results;
        bool                            didSearch;
        
    public:
        SearchResult(string filename) : file_to_search(filename), didSearch(false) {}
        SearchResult(string filename, list<SearchResultEntry *>  r) : file_to_search(filename), results(r), didSearch(false) {}
        
        ~SearchResult();
        
        string getFile() { return file_to_search; }
        
        bool searched();
        bool dosearch(string& searchfor);
        
        list<SearchResultEntry *>& getResults() { return results; }

	SearchResult *operator+(string str);
	SearchResult *operator^(string str);
    };
    
}
#endif /* searchResult_h */