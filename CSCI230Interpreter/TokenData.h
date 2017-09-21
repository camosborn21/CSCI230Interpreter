#pragma once
#include <string>


using namespace std;
typedef enum
{
	KEYWORD,
	// keywords of BIOLA, like function, return, display, read, if, else, while 

	ID_NAME,
	// identifiers, i.e. names of variables, labels, and functions

	ASSIGNMENT_OP,
	// =, the assignment operator		

	NUMERICAL_OP,
	// numerical operators	 (such as +, -, *, /, and %)	

	LOGICAL_OP,
	// numerical operators	 (such as !, ||, &&)	

	RELATIONAL_OP,
	// relational operators	 (such as >, ==, <, >=, <=, !=)

	NUMERICAL_LITERAL,
	// numerical values (such as 2.45)	

	STRING_LITERAL,
	// string literals (like "Hi Hi", in a pair of double quotes)

	COLON,
	// : to signal the end of function name and parameters declaration 

	SEMICOLON,			// ; to signal the end of statement 

	COMMA,				// a comma ,

	LEFT_PARENTHESIS,	// a left parenthesis (

	RIGHT_PARENTHESIS,	// a left parenthesis )

	LEFT_CURLYBRACE,	// a left curly brace {

	RIGHT_CURLYBRACE,	// a right curly brace }

	COMMENT,	// The token // that starts a line of comments

	UNKNOWN,		// Something that we cannot recognize its category

} tokenCategory;
class TokenData
{
private:
	tokenCategory _category;
	string _tokenValue;

public:
	TokenData(string value, tokenCategory category);

};

