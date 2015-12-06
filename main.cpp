//
//  main.cpp
//  p3
//

#include "p2lex.h"
#include "p3parser.h"
#include <fstream>
#include <map>

// it's good practice to have a usage function and tell the user how to run the program
// ... especially if they did something wrong!
void
usage(char *progname, string msg)
{
    cerr << "Error: " << msg << endl;
    cerr << "Usage is: " << progname << " [filename]" << endl;
    cerr << " specifying filename reads from that file; no filename reads standard input" << endl;
}

int
main( int argc, char *argv[] )
{
    istream *br;
    ifstream infile;
    
    if( argc == 1 )
        br = &cin;
    else if( argc == 2 ) {
        infile.open(argv[1]);
        if( infile.is_open() )
            br = &infile;
        else {
            usage(argv[0], "Cannot open " + string(argv[1]));
            return 1;
        }
    }
    else {
        usage(argv[0], "More than one file name was given");
        return 1;
    }

    PTree *program;

    program = Program(br);

    if( !program || errcnt )
    	return 0;
    
    cout << "Node Count Is: " << program->nodeCount() << endl;
    program->findEmptyStrings();
    program->findInvalidOps();
    
    return 0;
}
