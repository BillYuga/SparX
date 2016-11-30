#ifndef SPARX_H
#define SPARX_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> seperate(string input, bool show);

class SPARX{
protected:
	string _filename;
private:
	string temp, write;\

	/**
		This function keeps track of the number of tabs to print
		@param tab --number of tabs to print
	*/
	string index(int tab);
	vector<string> all_strings; //contains all strings in the source file
	vector<string> headers;//contains all the headers in the source file
	vector<string>  all_lines;//contains all the lines in the sourcefile
	bool _case = false, loop = false, quote = false;
	bool _comment = false;
	int tab = 0;

public:
	/**
		This function will do the main work of cleaning the code
		@param filename --the name of the source file to clean
	*/
	string sparx(string filename);

	/**
		This function shrinks the code to one line
		@param filename --name of the source file to clean
	*/
	string oneLineTool(string filename);

	string output(string _output = "default");
	string _function();

};

#endif