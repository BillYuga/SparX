#include <iostream>
#include <fstream>
#include "sparx.h"

using namespace std;

void help(){
	cout << "**** USAGE *****" << endl;
	cout <<"-> You can enter the file name as a command line arguement" << endl
		 <<"$ SparX filename" << endl
		 <<"-> file should either be *.cpp or *.c" << endl
		 <<"-> To see usage information enter the following command" << endl
		 <<"$ SparX -h or SparX --help\n" << endl;
}//end of help

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

//constructor SPARX::sparx
string SPARX::sparx(string filename){
	_filename = filename;

	//read all_strings into the vector one string at time
	ifstream infile(filename.c_str());

	infile >> temp;
	if(temp.empty()) return "all_strings not found!";

	all_strings.push_back(temp);
	while(infile >> temp) all_strings.push_back(temp);
	while(getline(infile, temp)) all_lines.push_back(temp);

	//loop throught all_strings to break down the code
	for(int i = 0; i < all_strings.size(); i++){
		if(all_strings[i] == "#include"){
			headers.push_back(all_strings[i]);
			headers.push_back(all_strings[i+1]); //name of header
			i++;
			continue;
		}
		//check if string all_strings[i] is a case
		else if(all_strings[i] == "case") _case = true;

		//check is string all_strings[i] is a quote
		else if(all_strings[i][0] == '"') quote = !quote;

		else if(all_strings[i][all_strings[i].size()-1] == '"') quote = !quote;

		//check if string all_strings[i] is the beginning of a for loop
		else if(all_strings[i][0] == 'f' && all_strings[i][1] == 'o' && all_strings[i][2] == 'r' && all_strings[i][3] == '(') loop = true;//when loop is true, newline after ; is disabled
		//check for start blocks of code in order to make proper indentation
		else if(all_strings[i][0] == '{'){
			write = write + "\n" + index(tab) + all_strings[i] + "\n";
			index_flag = true;//tab next item to be written
			tab++; //adds tab
			continue;
		}

		else if(all_strings[i][all_strings[i].size()-1] == '}'){
			tab--;//removes tab
			index_flag = true;//tab next item to be written
			write = write + index(tab) + all_strings[i] + "\n";
			continue;
		}

		else if((all_strings[i][all_strings[i].size()-1] == ';' && !loop) || (all_strings[i][all_strings[i].size()-1] == ':' && _case && !quote))   //test if ; is for and if : is in a quote 
		{
			//writes with space and continues
			if(index_flag) write = write + index(tab) + all_strings[i] + "\n";
			else 
			{
				write = write + all_strings[i] + "\n";
				index_flag = true; //same as above
			}
			_case = false;
			continue;
		}
		else if(loop)  //if a for loop
		{
			if(all_strings[i][all_strings[i].size()-1] == ')') //locates if end of loop
			{
				write = write + all_strings[i];
				loop = false; //no longer a loop
			}
			else if(index_flag) 
			{
				write = write + index(tab) + all_strings[i] + " ";
				index_flag = false; //same as above
			}
			else write = write + all_strings[i] + " ";
			continue;
		}
		
		if(index_flag)  //if tab output
		{
			write = write + index(tab) + all_strings[i] + " ";
			index_flag = false;
		}
		else write = write + all_strings[i] + " ";
	} //loop ends
	
	temp.erase();

}

string SPARX::index(int tabs)
{
	string ret;
	for(int i=0;i<tabs;i++, ret += "\t");
	return ret;
}

string SPARX::output(string output)
{
	string extension;
	string temp;
	if(output != "default") temp = output;
	else for(int i=_filename.size()-1;i>-1;i--)
	{
		if(_filename[i] != '.') extension = _filename[i] + extension;
		else 
		{
			for(int j=0;j<i;j++) temp += _filename[j];
			temp = temp + "_uminified." + extension;
			break;
		}
	}
	
	//finally writing to a file
	ofstream writefile(temp.c_str(), ios::trunc);
	for(unsigned int i=0;i<headers.size();i+=2) writefile << headers[i] << " " << headers[i+1] << endl;
	writefile << write << endl;
	writefile.close();
	
	return "success..\n";
}