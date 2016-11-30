#include <iostream>
#include "sparx.h"

using namespace std;

int main(int argc, char* argv[])
{
	string filename = argv[1];

	if(filename == "\0"){
		cout << "File not found!" << endl;
		return 0;
	}

	SPARX SparX;
	SparX.sparx(filename);
	SparX.output("sparx" + filename);

	return 0;
}