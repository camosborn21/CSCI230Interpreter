// lexScanner.h is a header file exported for the use of scanner module
//The compiler checks whether SCNNER_H is defined already to see
//whether this header file is already included.
//If it is, skip everything all the way to the matching #endif in the end.
#ifndef LEXICAL_ANALYSIS_H

//If LEXICAL_ANALYSIS_H  not defined yet, define it here to avoid inclusion
//of lexScanner.h again later during the compilation of the module.
#define LEXICAL_ANALYSIS_H

#include <vector>
#include <string>
#include "TokenData.h"
using namespace std;

//[9/21/2017 02:25] Cameron Osborn: Might not need this. I enumerate these types in the header for token data
////****************************************************************************
//// define an enumeration type for naming different categories of tokens
////****************************************************************************
//typedef enum
//{
//	KEYWORD,
//	// keywords of BIOLA, like function, return, display, read, if, else, while 
//
//	ID_NAME,
//	// identifiers, i.e. names of variables, labels, and functions
//
//	ASSIGNMENT_OP,
//	// =, the assignment operator		
//
//	NUMERICAL_OP,
//	// numerical operators	 (such as +, -, *, /, and %)	
//
//	LOGICAL_OP,
//	// numerical operators	 (such as !, ||, &&)	
//
//	RELATIONAL_OP,
//	// relational operators	 (such as >, ==, <, >=, <=, !=)
//
//	NUMERICAL_LITERAL,
//	// numerical values (such as 2.45)	
//
//	STRING_LITERAL,
//	// string literals (like "Hi Hi", in a pair of double quotes)
//
//	COLON,
//	// : to signal the end of function name and parameters declaration 
//
//	SEMICOLON,			// ; to signal the end of statement 
//
//	COMMA,				// a comma ,
//
//	LEFT_PARENTHESIS,	// a left parenthesis (
//
//	RIGHT_PARENTHESIS,	// a left parenthesis )
//
//	LEFT_CURLYBRACE,	// a left curly brace {
//
//	RIGHT_CURLYBRACE,	// a right curly brace }
//
//	COMMENT,	// The token // that starts a line of comments
//
//	UNKNOWN,		// Something that we cannot recognize its category
//
//} tokenCategory;

//****************************************************************************
// define a mnemonic name for the type to store tokens of one line of statement
//****************************************************************************
typedef vector<TokenData> perLineTokenDataVector;

//****************************************************************************
// define a mnemonic name for the type to store tokens of lines of statement
//****************************************************************************
typedef vector<perLineTokenDataVector> vectOfTokenVects;

//[9/21/2017 02:27] Cameron Osborn: Vector of tokencategories and its parent vector of per line token vectors has been omitted. That functionality is included within the TokenData class

class Scanner
{
public:
	//****************************************************************************
	// Prototypes of functions to test the category of a given token
	//****************************************************************************
	static	bool isKEYWORD(const string & token);
	static	bool isASSIGNMENT_OP(const string & token);
	static	bool isCOLON(const string & token);
	static	bool isCOMMA(const string & token);
	static	bool isCOMMENT(const string & token);
	static	bool isID_NAME(const string & token);
	static	bool isLEFT_PARENTHESIS(const string & token);
	static	bool isRIGHT_PARENTHESIS(const string & token);
	static	bool isLEFT_CURLYBRACE(const string & token);
	static	bool isRIGHT_CURLYBRACE(const string & token);
	static	bool isNUMERICAL_LITERAL(const string & token);
	static	bool isNUMERICAL_OP(const string & token);
	static	bool isRELATIONAL_OP(const string & token);
	static	bool isSEMICOLON(const string & token);
	static	bool isSTRING_LITERAL(const string & token);
	static	bool isLOGICAL_OP(const string & token);

	//****************************************************************************
	// Prototypes of the getLexicalInfo functions 
	// to get two kinds of lexical information from 
	// all lines of a program, i.e. 
	// (1) the vector of token vectors of all lines and
	// (2) the vector of category vectors of all lines.
	//
	// Implementation:
	// It should be implementated by appropriately calling the functions: 
	//		getPerLineTokenVectFromOneStringObject, [and
	//		getCategoryVectorFromTokenVector | This has been removed because of the type
	//		combination]
	//****************************************************************************
	static void getLexicalInfo(const vector<string> & linesOfStatements,
		vectOfTokenVects & tokenVectors);


	//**********************************************************************
	// getPerLineTokenVectFromOneCharArray and 
	// getPerLineTokenVectFromOneStringObject
	// recognize all the tokens in a single line of statement and
	// then store tokens as a vector of strings.
	//
	// getCategoryVectorFromTokenVector
	// recognizes the categories of the tokens given
	// a vector of the tokens in a single line of statement.
	//****************************************************************************
	static void getPerLineTokenVectFromOneCharArray
	(
		const char* ptrOriginalStatement,
		perLineTokenDataVector & tokenVector
	);

	static void getPerLineTokenVectFromOneStringObject
	(const string statement,
		perLineTokenDataVector & tokenVector
	);

	//[9/21/2017 02:42] Cameron Osborn: omitted because it's covered in the TokenData Class
/*
	static void getCategoryVectorFromTokenVector(
		const perLineTokenVector & tokenVector,
		perLineCategoryVector & categoryVector);*/


		//****************************************************************************
		// Prototype of the function to display lexical information strored in
		// a vector of token vectors of all lines of statements, and 
		// a vector of category vectors of all lines of statements.
		//****************************************************************************
	static void displayLexicalInfo(
		vectOfTokenVects & tokenVectors
		//vectOfCategoryVects & categoryVectors
	);

	//Scanner();
	//~Scanner();
};

#endif
