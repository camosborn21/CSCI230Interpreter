#include "stdafx.h"
#include "CppUnitTest.h"
#include <CppUnitTest.h>
#include "../CSCI230Interpreter/OriginalScanner.h"
#include "../CSCI230Interpreter/ProgramUI.h"
#include "../CSCI230Interpreter/targetver.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace CSCI230InterpreterUnitTesting
{		
	TEST_CLASS(tOriginalScanner)
	{

	public:

		TEST_CLASS_INITIALIZE(setUpTests)
		{
			
		}
		//[10/2/2017 03:16] Cameron Osborn: Test the functionality of the token parser against a pre-loaded vector to ensure successful delineation of tokens.
		TEST_METHOD(PerLineTokenVectorCorrectlyParsedForAllPossibleCategories)
		{
			//Arrange
			const string originalStatment = "function return display read if else while main(){ x=2+3*radius-n/3%8} ! || && > == < >= <= != , ; : \"Here's some literal text\" 12asdf234xkcd // Comment text ";
			perLineTokenVector tokenVector;
			perLineTokenVector expectedVector;
			expectedVector.push_back("function");
			expectedVector.push_back("return");
			expectedVector.push_back("display");
			expectedVector.push_back("read");
			expectedVector.push_back("if");
			expectedVector.push_back("else");
			expectedVector.push_back("while");
			expectedVector.push_back("main");
			expectedVector.push_back("(");
			expectedVector.push_back(")");
			expectedVector.push_back("{");
			expectedVector.push_back("x");
			expectedVector.push_back("=");
			expectedVector.push_back("2");
			expectedVector.push_back("+");
			expectedVector.push_back("3");
			expectedVector.push_back("*");
			expectedVector.push_back("radius");
			expectedVector.push_back("-");
			expectedVector.push_back("n");
			expectedVector.push_back("/");
			expectedVector.push_back("3");
			expectedVector.push_back("%");
			expectedVector.push_back("8");
			expectedVector.push_back("}");
			expectedVector.push_back("!");
			expectedVector.push_back("||");
			expectedVector.push_back("&&");
			expectedVector.push_back(">");
			expectedVector.push_back("==");
			expectedVector.push_back("<");
			expectedVector.push_back(">=");
			expectedVector.push_back("<=");
			expectedVector.push_back("!=");
			expectedVector.push_back(",");
			expectedVector.push_back(";");
			expectedVector.push_back(":");
			expectedVector.push_back("\"Here's some literal text\"");
			expectedVector.push_back("12asdf234xkcd");
			expectedVector.push_back("//");
			expectedVector.push_back("Comment");
			expectedVector.push_back("text");

			//Act
			OriginalScanner::getPerLineTokenVectFromOneStringObject(originalStatment, tokenVector);

			//Assert
			Assert::IsTrue(expectedVector == tokenVector);
		}

		//[10/2/2017 03:17] Cameron Osborn: Test the functionality of the category parser against a pre-loaded vector to ensure successful interpretation of tokens.
		TEST_METHOD(GetCategoryVectorFromTokenVectorParsesAllCategories)
		{
			//Arrange
			const string originalStatment = "function return display read if else while main(){ x=2+3*radius-n/3%8} ! || && > == < >= <= != , ; : \"Here's some literal text\" 12asdf234xkcd // Comment text ";
			perLineTokenVector tokenVector;
			perLineCategoryVector expectedVector;
			perLineCategoryVector categoryVector;
			expectedVector.push_back(KEYWORD);
			expectedVector.push_back(KEYWORD);
			expectedVector.push_back(KEYWORD);
			expectedVector.push_back(KEYWORD);
			expectedVector.push_back(KEYWORD);
			expectedVector.push_back(KEYWORD);
			expectedVector.push_back(KEYWORD);
			expectedVector.push_back(ID_NAME);
			expectedVector.push_back(LEFT_PARENTHESIS);
			expectedVector.push_back(RIGHT_PARENTHESIS);
			expectedVector.push_back(LEFT_CURLYBRACE);
			expectedVector.push_back(ID_NAME);
			expectedVector.push_back(ASSIGNMENT_OP);
			expectedVector.push_back(NUMERICAL_LITERAL);
			expectedVector.push_back(NUMERICAL_OP);
			expectedVector.push_back(NUMERICAL_LITERAL);
			expectedVector.push_back(NUMERICAL_OP);
			expectedVector.push_back(ID_NAME);
			expectedVector.push_back(NUMERICAL_OP);
			expectedVector.push_back(ID_NAME);
			expectedVector.push_back(NUMERICAL_OP);
			expectedVector.push_back(NUMERICAL_LITERAL);
			expectedVector.push_back(NUMERICAL_OP);
			expectedVector.push_back(NUMERICAL_LITERAL);
			expectedVector.push_back(RIGHT_CURLYBRACE);
			expectedVector.push_back(LOGICAL_OP);
			expectedVector.push_back(LOGICAL_OP);
			expectedVector.push_back(LOGICAL_OP);
			expectedVector.push_back(RELATIONAL_OP);
			expectedVector.push_back(RELATIONAL_OP);
			expectedVector.push_back(RELATIONAL_OP);
			expectedVector.push_back(RELATIONAL_OP);
			expectedVector.push_back(RELATIONAL_OP);
			expectedVector.push_back(RELATIONAL_OP);
			expectedVector.push_back(COMMA);
			expectedVector.push_back(SEMICOLON);
			expectedVector.push_back(COLON);
			expectedVector.push_back(STRING_LITERAL);
			expectedVector.push_back(UNKNOWN);
			expectedVector.push_back(COMMENT);
			expectedVector.push_back(COMMENT_TEXT);
			expectedVector.push_back(COMMENT_TEXT);

			//Test one must pass for test two to be valid because of functionality reuse.
			OriginalScanner::getPerLineTokenVectFromOneStringObject(originalStatment, tokenVector);

			//Act
			OriginalScanner::getCategoryVectorFromTokenVector(tokenVector, categoryVector);

			//Assert
			Assert::IsTrue(expectedVector == categoryVector);
		}
	};
}