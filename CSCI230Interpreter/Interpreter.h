#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <map>
#include <string>
#include <vector>
using namespace std;

//A variable table recording the names (strings) of variables
//and the current floating point values of these variables.
typedef map<string, float> floatVarValueTable;


//[11/1/2017 22:28] Cameron Osborn: A variable table recording the names of variables
// and the current string values of those variables.
typedef map<string, string> stringVarValueTable;

//Ensure that variable names cannot be reused between datatypes.

class Interpreter
{
private:
	vector<string> sourceCode;
	
	vector<string> statements;

public:
	//Interpreter();
	//~Interpreter();
};

#endif