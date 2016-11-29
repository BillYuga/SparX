#include <iostream>
#include <fstream>
#include "sparx.h"

using namespace std;

vector<string> seperate(string input, bool show = false){
	string temp;
	vector<string> ret;//this vector will hold strings to be returned by the function.

	for(int i=0; i < input.size(); i++){
		if(input[i] == ' '){
			ret.push_back(temp);
			temp.erase();
		}
		else temp += input[i];
	}

	if(show) cout << "Seperating " << input + "..." << endl;

	return ret;
}//end of seperate

//the constructor SPARX::sparx


string SPARX::sparx(string filename){
	_filename = filename;

	//read file into the vector one string at time
	ifstream infile(filename.c_str());

	infile >> temp;
	if(temp.empty()) return "File not found!";

	all_strings.push_back(temp);
	while(infile >> temp) all_strings.push_back(temp);
	while(getline(infile, temp)) all_lines.push_back(temp);

	//loop throught all_strings to break down the code
	for(int i = 0; i < all_strings.size(); i++){
		if(all_strings[i] == "#include"){
			headers.pushback(all_strings[i]);
			headers.pushback(all_strings[i+1]); //name of header
			i++;
			continue;
		}
		//check if string all_strings[i] is a case
		else if(file[i] == "case" _case = true);

		//check is string all_strings[i] is a quote
		else if(file[i][0] == '"') quote = !quote;

		else if(file[i][file[i].size()-1] == '"') quote = !quote;

		//check if string all_strings[i] is the beginning of a for loop
		else if(); 

	} 

}