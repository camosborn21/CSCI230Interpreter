#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <map>
#include <string>
#include <vector>
#include "ExpressionEvaluator.h"
#include "OriginalScanner.h"
#include "FlowStackMethodElement.h"
#include "Rpc.h"
using namespace std;

//A variable table recording the names (strings) of variables
//and the current floating point values of these variables.
typedef map<string, float> floatVarValueTable;


//[11/1/2017 22:28] Cameron Osborn: A variable table recording the names of variables
// and the current string values of those variables.
typedef map<string, string> stringVarValueTable;

//Ensure that variable names cannot be reused between datatypes.

//[11/24/2017 17:19] Cameron Osborn: A method table holding the names and flowstack elements of each method
typedef map<string, FlowStackMethodElement> programMethods;

class Error {
public:
	string ErrorMessage;
	int LineNumber;
	int TokenNumber;
	Error(string errorMessage, int lineNumber, int tokenNumber)
	{
		ErrorMessage = errorMessage;
		LineNumber = lineNumber;
		TokenNumber = tokenNumber;
	}
};

class SourceCodeToken {
public:
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
	string GetCategoryName()
	{
		string categoryInfo;
		switch (Category)
		{
		case KEYWORD:
			categoryInfo = "KEYWORD";
			break;
		case ASSIGNMENT_OP:
			categoryInfo = "ASSIGNEMT OPERATION";
			break;
		case COLON:
			categoryInfo = "COLON";
			break;
		case COMMA:
			categoryInfo = "COMMA";
			break;
		case COMMENT:
			categoryInfo = "COMMENT";
			break;
		case COMMENT_TEXT:
			categoryInfo = "COMMENT TEXT";
			break;
		case ID_NAME:
			categoryInfo = "ID NAME";
			break;
		case LEFT_CURLYBRACE:
			categoryInfo = "LEFT CURLYBRACE";
			break;
		case LEFT_PARENTHESIS:
			categoryInfo = "LEFT PARENTHESIS";
			break;
		case LOGICAL_OP:
			categoryInfo = "LOGICAL OPERATOR";
			break;
		case RIGHT_CURLYBRACE:
			categoryInfo = "RIGHT CURLYBRACE";
			break;
		case RIGHT_PARENTHESIS:
			categoryInfo = "RIGHT PARENTHESIS";
			break;
		case NUMERICAL_LITERAL:
			categoryInfo = "NUMERICAL LITERAL";
			break;
		case NUMERICAL_OP:
			categoryInfo = "NUMERICAL OP";
			break;
		case RELATIONAL_OP:
			categoryInfo = "RELATIONAL OP";
			break;
		case SEMICOLON:
			categoryInfo = "SEMICOLON";
			break;
		case STRING_LITERAL:
			categoryInfo = "STRING LITERAL";
			break;
		default:
			categoryInfo = "UNKNOWN";
		}

		return categoryInfo;
	}
};

class Statement {
public:
	vector<SourceCodeToken> Tokens;
};

class Interpreter
{
private:
	//[11/22/2017 20:52] Cameron Osborn: create possibility for global variables with global variables table
	floatVarValueTable globalFloatVariables;
	stringVarValueTable globalStringVariables;

	programMethods declaredMethods;

	vector<string> sourceCode;
	//vector<Statement> statements;
	//This may need to be replaced by a vector of Error pointers IOT use errors.push_back((Error*) new Error({Constructor}))
	vector<Error> errors;
	vectOfCategoryVects categoryVectorsForAllLines;
	vectOfTokenVects tokenVectorsForAllLines;
	vector<SourceCodeToken> sourceCodeTokens;
	FlowStackMethodElement main;
public:
	//[11/2/2017 12:45] Cameron Osborn: Prints out errors found during syntax check.
	void printErrors();

	//[11/2/2017 12:46] Cameron Osborn: Executes all statements of the parsed application
	void execute();

	//[11/2/2017 12:46] Cameron Osborn: Entry point for class. Method exposes options to display errors or run code after all statements have been parsed.
	void parseSourceCode(vector<string> lines, bool displayErrorsAfterParse, bool executeAfterParse);



	//[11/22/2017 21:11] Cameron Osborn: Check if token can only occur at the beginning of a statement
	bool checkTokenOnlyValidAtBeginningOfStatement(SourceCodeToken checkToken);

	//[11/22/2017 21:27] Cameron Osborn: Check if token is invalid at the beginning of a statement
	bool checkTokenInvalidAtBeginningOfStatement(SourceCodeToken checkToken);

	//[11/21/2017 01:46] Cameron Osborn: This procedure verifies that the number of tokens in a perLineTokenVector match the total number of categories in a perLineCategoryVector. On fail it will print a parsing error to the output.
	bool checkTokenVsCategoryLengthParsingError(perLineTokenVector checkTokenVect, perLineCategoryVector checkCategoryVect, int lineNumber);

	//[11/21/2017 01:49] Cameron Osborn: Check whether the source code has seperate functions or all statements are part of a nameless main function.
	bool checkSourceCodeContainsFunctions();
};

#endif