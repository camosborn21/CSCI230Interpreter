#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <map>
#include <string>
#include <vector>
#include "ExpressionEvaluator.h"
#include "OriginalScanner.h"
using namespace std;

//A variable table recording the names (strings) of variables
//and the current floating point values of these variables.
typedef map<string, float> floatVarValueTable;


//[11/1/2017 22:28] Cameron Osborn: A variable table recording the names of variables
// and the current string values of those variables.
//typedef map<string, string> stringVarValueTable;

//Ensure that variable names cannot be reused between datatypes.

class Error {
public:
	Error(const string& error_message, int line_number, int token_number)
		: ErrorMessage(error_message),
		  LineNumber(line_number),
		  TokenNumber(token_number)
	{
	}
	string ErrorMessage;
	int LineNumber;
	int TokenNumber;
};

class SourceCodeToken {
public:
	SourceCodeToken(const string& token, tokenCategory category, int line_number, int token_number)
		: Token(token),
		  Category(category),
		  LineNumber(line_number),
		  TokenNumber(token_number)
	{
	}


	string Token;
	tokenCategory Category;
	int LineNumber;
	int TokenNumber;
};

class Statement {
public:
	vector<SourceCodeToken> Tokens;
};

class Interpreter
{
private:
	vector<string> sourceCode;
	vector<Statement> statements;
	vector<Error> errors;
	vectOfCategoryVects categoryVectorsForAllLines;
	vectOfTokenVects tokenVectorsForAllLines;
	floatVarValueTable varTable;

public:
	//[11/2/2017 12:45] Cameron Osborn: Prints out errors found during syntax check.
	void printErrors();

	//[11/2/2017 12:46] Cameron Osborn: Executes all statements of the parsed application
	void execute();

	//[11/2/2017 12:46] Cameron Osborn: Entry point for class. Method exposes options to display errors or run code after all statements have been parsed.
	void parseSourceCode(vector<string> lines, bool displayErrorsAfterParse, bool executeAfterParse);

	//[11/25/2017 14:43] Cameron Osborn: After code parsing, validate that there are no syntax errors in the code.
	void checkSyntax();

};

#endif