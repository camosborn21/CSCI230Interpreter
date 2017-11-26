#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include<utility>
#include "ExpressionEvaluator.h"
#include "OriginalScanner.h"
using namespace std;

//A variable table recording the names (strings) of variables
//and the current floating point values of these variables.
//typedef map<string, float> floatVarValueTable;


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
	void printError()
	{
		cout << endl << endl << "An error occurred in line " << LineNumber << " token " << TokenNumber << "." << endl << ErrorMessage;
	}
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

	SourceCodeToken()
	{
		LineNumber = 0;
		Category = UNKNOWN;
		TokenNumber = 0;
		Token = "";
	}
	string Token;
	tokenCategory Category;
	int LineNumber;
	int TokenNumber;

	string GetTokenCategoryName() const
	{
		string categoryInfo;
		switch (Category)
		{
		case KEYWORD:
			categoryInfo = "KEYWORD";
			break;
		case ASSIGNMENT_OP:
			categoryInfo = "ASSIGNEMT_OP";
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
			categoryInfo = "COMMENT_TEXT";
			break;
		case ID_NAME:
			categoryInfo = "ID_NAME";
			break;
		case LEFT_CURLYBRACE:
			categoryInfo = "LEFT_CURLYBRACE";
			break;
		case LEFT_PARENTHESIS:
			categoryInfo = "LEFT_PARENTHESIS";
			break;
		case LOGICAL_OP:
			categoryInfo = "LOGICAL_OP";
			break;
		case RIGHT_CURLYBRACE:
			categoryInfo = "RIGHT_CURLYBRACE";
			break;
		case RIGHT_PARENTHESIS:
			categoryInfo = "RIGHT_PARENTHESIS";
			break;
		case NUMERICAL_LITERAL:
			categoryInfo = "NUMERICAL_LITERAL";
			break;
		case NUMERICAL_OP:
			categoryInfo = "NUMERICAL_OP";
			break;
		case RELATIONAL_OP:
			categoryInfo = "RELATIONAL_OP";
			break;
		case SEMICOLON:
			categoryInfo = "SEMICOLON";
			break;
		case STRING_LITERAL:
			categoryInfo = "STRING_LITERAL";
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
	string StatementType;
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
	//[11/26/2017 01:51] Cameron Osborn: returns quantity of errors statement. ie "(1 error)" or "(3 errors)"
	string GetErrorQuantityStatement();

	//[11/26/2017 01:55] Cameron Osborn: Accessor for errors.size value.
	int GetErrorCount() const;

	//[11/2/2017 12:45] Cameron Osborn: Prints out errors found during syntax check.
	void printErrors();

	//[11/2/2017 12:46] Cameron Osborn: Executes all statements of the parsed application
	void execute();

	//[11/2/2017 12:46] Cameron Osborn: Entry point for class. Method exposes options to display errors or run code after all statements have been parsed.
	void parseSourceCode(vector<string> lines, bool displayErrorsAfterParse, bool executeAfterParse);

	//[11/25/2017 14:43] Cameron Osborn: After code parsing, validate that there are no syntax errors in the code.
	void checkSyntax();

	//[11/25/2017 14:56] Cameron Osborn: Verify that the first token in the line is either display, read, or ID_Name
	void checkTokenValidAtBeginningOfStatement(SourceCodeToken checkToken);

	//[11/25/2017 21:39] Cameron Osborn: 
	bool BuildStatus;

};

#endif