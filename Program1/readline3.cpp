//============================================================================
// Name        : readline3.cpp
// Description : read a line using getline, into a string
//============================================================================

#include <iostream>
#include <string>
using namespace std;

int main() {
	string line;

	while( cin.good() ) {
		getline(cin, line);

		cout << line << ":" << line.size() << endl;
	}

	return 0;
}