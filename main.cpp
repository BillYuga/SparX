#include <iostream>
#include "sparx.h"

using namespace std;

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