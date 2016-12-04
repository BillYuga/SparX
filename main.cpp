#include <iostream>
#include "sparx.h"

using namespace std;

/**
	main function to clean code 
	@param argc --number of command line arguments, maximum of 2 for now
	@param argv[] --argv[0] name of program(SparX) and argv[1] name of sourcefile to clean.
*/

int main(int argc, char* argv[])

{
	if(argv[1] == "-h" || argv[1] == "--help")
		help();
	
	else{
		string filename = argv[1];

		if(filename == "\0"){
			cout << "File not found!" << endl;
			return 0;
		}

		SPARX SparX;
		SparX.sparx(filename);
		SparX.output("sparx_" + filename);

	}

	return 0;
}
