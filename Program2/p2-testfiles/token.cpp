#include "p2lex.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int linenum=0;

Token getToken(istream *br, string& lexeme){
	string lex = "";
	char ch;
	bool comment = false;

	while (br->get(ch)){
		lex += ch;
		if (ch==';'){
			lexeme = lex;
			return SC;
		} else if (ch=='+'){
			lexeme = lex;
			return UNION;
		} else if (ch=='^'){
			lexeme = lex;
			return INTERSECT;
		} else if (ch=='('){
			lexeme = lex;
			return LPAREN;
		} else if (ch==')'){
			lexeme = lex;
			return RPAREN;
		} 

		else if (isalpha(ch)){
			char ch2;
			while (br->get(ch2)){
				if (!isalpha(ch2)){
					br->unget();
					break;
				} else{
					lex += ch2;
				}
			}

			if (lex == "set"){
				lexeme = lex;
				return SET;
			} else if (lex == "print"){
				lexeme = lex;
				return PRINT;
			} else if (lex == "search"){
				lexeme = lex;
				return SEARCH;
			} else if (lex == "for"){
				lexeme = lex;
				return FOR;
			} else {
				lexeme = lex;
				return ID;
			}
		}

		else if (ch=='\"'){
			lex = "";
			char ch2;
			while (br->get(ch2)){
				if (ch2 == '\"'){
					lexeme = lex;
					return STRING;
				} else if (ch2=='\n'){
					linenum++;
					return ERR;
				} else{
					lex += ch2;
				}
			}
		}

		else if (ch == '/' && comment){
			char ch2;
			while (br->get(ch2)){
				if (ch2=='\n'){
					linenum ++;
					comment = false;
					break;
				}
			}
		} else if (ch=='/'){
			comment = true; 
		}

		else if (isspace(ch)){
			if(ch=='\n'){
				linenum++;
			}
			lex = "";
			continue;
		}

		else {
			lexeme = "";
			return ERR;
		}
	}
	lexeme = lex;
	return DONE;
};
