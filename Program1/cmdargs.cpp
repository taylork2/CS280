//============================================================================
// Name        : cmdargs.cpp
// Description : Look at and print the command line arguments that are passed
//============================================================================

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
	cout << "There were " << argc << " arguments on the command line" << endl;

	for( int i=0; i<argc; i++ ) {
		cout << i << ":" << argv[i] << ":" << endl;
	}
	return 0;
}
