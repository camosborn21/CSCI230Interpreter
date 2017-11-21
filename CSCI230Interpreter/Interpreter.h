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
typedef map<string, string> stringVarValueTable;

//Ensure that variable names cannot be reused between datatypes.

struct Error {
	string ErrorMessage;
	int LineNumber;
	int TokenNumber;
};

struct SourceCodeToken {
	string Token;
	tokenCategory Category;
	int LineNumber;
	int TokenNumber;

	SourceCodeToken(string token, tokenCategory category, int lineNumber, int tokenNumber)
	{
		Token = token;
		Category = category;
		LineNumber = lineNumber;
		TokenNumber = tokenNumber;
	}
};

struct Statement {
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


public:
	//[11/2/2017 12:45] Cameron Osborn: Prints out errors found during syntax check.
	void printErrors();

	//[11/2/2017 12:46] Cameron Osborn: Executes all statements of the parsed application
	void execute();

	//[11/2/2017 12:46] Cameron Osborn: Entry point for class. Method exposes options to display errors or run code after all statements have been parsed.
	void parseSourceCode(vector<string> lines, bool displayErrorsAfterParse, bool executeAfterParse);
	


	//[11/21/2017 01:46] Cameron Osborn: This procedure verifies that the number of tokens in a perLineTokenVector match the total number of categories in a perLineCategoryVector. On fail it will print a parsing error to the output.
	bool checkTokenVsCategoryLengthParsingError(perLineTokenVector checkTokenVect, perLineCategoryVector checkCategoryVect, int lineNumber);

	//[11/21/2017 01:49] Cameron Osborn: Check whether the source code has seperate functions or all statements are part of a nameless main function.
	bool checkSourceCodeContainsFunctions();
};

#endif