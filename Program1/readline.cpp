//============================================================================
// Name        : readline.cpp
// Description : Reading a line by using get and specifying a delimiter
//============================================================================

#include <iostream>
#include <cstring>
using namespace std;

int main() {
	char line[1000];

	while( cin.good() ) {
		cin.get(line, 1000, '\n');

		cout << line << ":" << strlen(line) << endl;
	}

	return 0;
}