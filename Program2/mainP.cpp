/* 
 * File:   main.cpp
 * Author: Phoebe Yu
 *
 * Created on October 11, 2015, 10:41 PM
 */

#include <iostream>
#include <fstream>
#include "p2lex.h"
#include <string.h>
#include <map>
#include <vector>

using namespace std;


map<Token, int> counter;
map<string, int> IDMap;

string getTextForEnum( Token enumVal )
{
  switch( enumVal )
  {
    case ID:
      return "Identifier";
    case STRING:
      return "String constant";
    case UNION:
      return "Union operator" ;
    case INTERSECT:
      return "Intersect operator" ;
    case SET:
      return "SET keyword" ;
    case PRINT:
      return "PRINT keyword" ;
    case SEARCH:
      return "SEARCH keyword" ;
    case FOR:
      return "FOR keyword" ;
    case LPAREN:
      return "Left paren" ;
    case RPAREN:
      return "Right paren" ;
    case SC:
      return "Semicolon" ;
    case ERR:
      return "ERR" ;
    case DONE:
      return "DONE" ;

    default:
      return "Not recognized..";
  }
}


int main(int argc, char** argv) {
    istream *br;
    ifstream infile;
    
    string tokens="";
    Token typeOfToken;
    string idList="";
    
    if( argc == 1 )
        br = &cin;
    else if( argc != 2 ) {
        cout<<"Wrong amount of passing parameters."<<endl; 
        return 1; // print an error msg
    } else {
        infile.open(argv[1]);
        if( infile.is_open() )
            br = &infile;
        else {
            cout << argv[1] << " can't be opened" << endl;
            return 1;

        }
    }
   

    while(true){
        typeOfToken=getToken(br,tokens);
    
        if (counter.count(typeOfToken))
            counter[typeOfToken]+=1;
        else
            counter[typeOfToken]=1;
        
        if (typeOfToken == ID) {
            if (IDMap.count(tokens))
                IDMap[tokens]+=1;
            else
                IDMap[tokens]=1;
        }

        if(typeOfToken==DONE || typeOfToken==ERR)
            break;
    }
    //cout<<"total token count: "<<endl;
    if(typeOfToken==ERR)
        return 0;
    
    map<int, vector<Token> > bycount;
    map<Token,int>::iterator it;
    for(it=counter.begin(); it != counter.end(); it++)
        bycount[it->second].push_back(it->first);
    // adds to vector
    map<int, vector<Token> >::reverse_iterator sit;
    
    int total=0;
    for(sit= bycount.rbegin(); sit != bycount.rend(); sit++) {
        int siz = sit->second.size(); // read through the vector
        for(int i=0; i<siz; i++) {
            if(sit->second[i] == DONE)
                continue;
            
            cout << getTextForEnum(sit->second[i])
                  << ": "
                  << sit->first   // string's value 
                  << endl ;
            total++;
        }
        if(total>2)
            break;
    }
    
    cout << endl;
    for (map<string,int>::iterator it=IDMap.begin(); it!=IDMap.end(); ++it) {
        
        if(idList == "")
            idList = it->first;
        else
            idList = idList + ", " + it->first;  
    }
    if(idList != "")
        idList = "List of identifiers: " + idList;
    cout << idList << endl ;

    return 0;
}

