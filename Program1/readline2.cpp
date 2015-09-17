//============================================================================
// Name        : readline2.cpp
// Description : read a line using getline, into an array
//============================================================================

#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

int main() {
	char line[BUFSIZ];

	while( cin.good() ) {
		cin.getline(line, sizeof(line));
		cout << line << ":" << strlen(line) << endl;
	}

	return 0;
}