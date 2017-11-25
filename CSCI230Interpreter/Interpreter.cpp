#include "stdafx.h"
#include "Interpreter.h"
#include <iostream>
#include "FlowStackElement.h"
#include "FlowStackIfElement.h"
#include "FlowStackWhileElement.h"
//Convert source program lines to execution statements to allow multiline statements or multiple statements per line.

//Template
//	Parse lines to statements
//	Check Syntax
//		Display Syntax Errors
//	Execute statements 1 line at a time
//		read
//		display
//		assignment
using namespace std;
void Interpreter::printErrors()
{
}

void Interpreter::execute()
{
}

void Interpreter::parseSourceCode(vector<string> lines, bool displayErrorsAfterParse, bool executeAfterParse)
{
	if (lines.size == 0) {
		//[11/14/2017 12:28] Cameron Osborn: Program has no statements
		return;
	}
	OriginalScanner::getLexicalInfo(lines, tokenVectorsForAllLines, categoryVectorsForAllLines);


	//[11/21/2017 01:26] Cameron Osborn: For Each Line convert the token vector and category vector data into SourceCodeToken class objects.
	for (size_t i = 0; i < tokenVectorsForAllLines.size(); i++)
	{
		perLineTokenVector tokenVect = tokenVectorsForAllLines[i];
		perLineCategoryVector categoryVect = categoryVectorsForAllLines[i];

		//[11/21/2017 01:45] Cameron Osborn: check parsing validity of current line
		if (checkTokenVsCategoryLengthParsingError(tokenVect, categoryVect, i) != true)
			return;

		//[11/21/2017 02:14] Cameron Osborn: for each token: create source code token.
		for (size_t j = 0; j < tokenVect.size(); j++)
		{
			//[11/24/2017 19:38] Cameron Osborn: Filter out comments and comment text so it doesn't interfere with parsing.
			if (categoryVect[j] != COMMENT || categoryVect[j] != COMMENT_TEXT)
				sourceCodeTokens.push_back(SourceCodeToken(tokenVect[j], categoryVect[j], i, j));
		}

	}

	//[11/24/2017 17:21] Cameron Osborn: The current statement being built in the buffer
	vector<SourceCodeToken> currentStatement;


	//[11/24/2017 17:21] Cameron Osborn: The stack of compound statements on the buffer.
	vector<FlowStackElement> compoundStatementStack;


	int tokenIndex = 0;
	if (checkSourceCodeContainsFunctions())
	{
		//[11/23/2017 20:27] Cameron Osborn: global variable declaration by assignment is permissible before the first function.
		bool firstFunctionFound = false;
		//Find all functions
		//Find all variables
		//function and compound statement stack
		//	functions can't be declared while anything is on the stack
		//	statements can only exist outside the stack before the stack is first loaded.
		//  statement ending tokens: ;  }  )
		//  valid statment beginning tokens: any keyword or ID Name
		//	push these statements to?
		//		statments vector
		for (vector<SourceCodeToken>::iterator iter = sourceCodeTokens.begin(); iter < sourceCodeTokens.end(); ++iter, tokenIndex++)
		{

			SourceCodeToken nextToken = sourceCodeTokens[tokenIndex + 1];

			//check if token is first character of current statment
			if (currentStatement.size() == 0)
			{
				//[11/22/2017 21:33] Cameron Osborn: if we are looking at the first token in a statement, ensure it's valid in that position.
				checkTokenInvalidAtBeginningOfStatement(*iter);

				//If next token is assignment op then current token must by ID_Name of Variable
			}
			else
			{
				//[11/22/2017 21:01] Cameron Osborn: we're not on the first token of a statement, ensure no first token exclusive tokens are being used further on in the statement =>results in error: expected end of statement.
				checkTokenOnlyValidAtBeginningOfStatement(*iter);
			}


			//LEFT OFF HERE
			currentStatement.clear();
		}


	}
	else
		//[11/23/2017 20:24] Cameron Osborn: Source code doesn't contain funtions
	{
		//compoundStatementStack.push_back(FlowStackMethodElement());
		FlowStackMethodElement main;
		main.name = "main";
		//main.isMultilineCompound = true;
		compoundStatementStack.push_back(main);

		for (vector<SourceCodeToken>::iterator iter = sourceCodeTokens.begin(); iter < sourceCodeTokens.end(); ++iter, tokenIndex++)
		{
			SourceCodeToken nextToken = sourceCodeTokens[tokenIndex + 1];

			//check if token is first character of current statment
			if (currentStatement.size() == 0)
			{
				//[11/22/2017 21:33] Cameron Osborn: if we are looking at the first token in a statement, ensure it's valid in that position. First token must be Keyword, ID Name, Left-Paren, Left curlybrace, or Comment indicator.
				checkTokenInvalidAtBeginningOfStatement(*iter);


				//IF TOKEN IS KEYWORD: function, return, read, display, while, if, else

				//If current token begins a compound conditional (if or while) then the next token must be left parentheses.
				if (iter->Category == KEYWORD && (iter->Token == "if" || iter->Token == "while"))
				{
					if (nextToken.Category != LEFT_PARENTHESIS)
					{
						errors.push_back(Error("'(' expected. The keyword " + iter->Token + " must be followed by a condition enclosed in parentheses.", iter->LineNumber, iter->TokenNumber));
					}
					else
					{
						//[11/23/2017 22:31] Cameron Osborn: Add appropriate container (if or while) to the compound statement stack
						if (iter->Token == "if")
							compoundStatementStack.push_back(FlowStackIfElement());
						if (iter->Token == "while")
							compoundStatementStack.push_back(FlowStackWhileElement());

						currentStatement.clear();
					}

				}

				//[11/24/2017 14:24] Cameron Osborn: else keyword
				if (iter->Category == KEYWORD && iter->Token == "else")
				{
					if (compoundStatementStack.back().Type() != "if_element")
					{
						//[11/24/2017 14:04] Cameron Osborn: Else token found but the top compound statement in the stack isn't an if element.
						errors.push_back(Error("'else' statement requires preceding 'if' statement.", iter->LineNumber, iter->TokenNumber));
					}
					else
					{
						//[11/24/2017 18:41] Cameron Osborn: else token found, If there was formerly an element, push it to the top compound statement and move on.
						FlowStackElement addElement;
						addElement.statement = currentStatement;
						compoundStatementStack.back().pushStatement(addElement, true);
						currentStatement.clear();
					}
				}

				//[11/24/2017 14:24] Cameron Osborn: return keyword
				if (iter->Category == KEYWORD && iter->Token == "return")
				{
					//[11/24/2017 14:22] Cameron Osborn: This is a functionless program, it can't have return statements.
					errors.push_back(Error("Function-less program can't use 'return'", iter->LineNumber, iter->TokenNumber));
				}

				//[11/24/2017 14:42] Cameron Osborn: display keyword
				if (iter->Category == KEYWORD && iter->Token == "display") {
					currentStatement.push_back(*iter);
				}

				//[11/24/2017 14:42] Cameron Osborn: read keyword
				if (iter->Category == KEYWORD && iter->Token == "read") {
					if (nextToken.Category != ID_NAME)
					{
						errors.push_back(Error("'read' keyword must be followed by a variable name.", iter->LineNumber, iter->TokenNumber));
					}
					currentStatement.push_back(*iter);
				}
				//[11/24/2017 14:26] Cameron Osborn: no handler required for 'function' keyword because we've already determined we're executing functionless code.

				//IF TOKEN IS ID_NAME
				if (iter->Category == ID_NAME)
					currentStatement.push_back(*iter);

				//IF TOKEN IS LEFT PAREN
				if (iter->Category == LEFT_PARENTHESIS)
					currentStatement.push_back(*iter);

				//IF TOKEN IS LEFT CURLYBRACE
				if (compoundStatementStack.size() == 0 || compoundStatementStack.back().isMultilineCompound == true)
				{
					errors.push_back(Error("Expected compound statement. A left curly brace must follow a compound statement declaration", iter->LineNumber, iter->TokenNumber));
				}
				else
				{
					compoundStatementStack.back().isMultilineCompound = true;
				}

				//IF TOKEN IS RIGHT CURLYBRACE??????
				stop;

			}
			else
			{
				//[11/22/2017 21:01] Cameron Osborn: we're not on the first token of a statement, ensure no first token exclusive tokens (in this language thats KEYWORD tokens) are being used further on in the statement =>results in error: expected end of statement.
				checkTokenOnlyValidAtBeginningOfStatement(*iter);


				//Numerical Op
				if (iter->Category == NUMERICAL_OP)
				{
					if (nextToken.Category != NUMERICAL_LITERAL || nextToken.Category != ID_NAME || nextToken.Category != LEFT_PARENTHESIS || (nextToken.Category != RELATIONAL_OP&&nextToken.Token == "!"))
					{
						errors.push_back(Error("Numeric literal or variable name expected. A numeric operator was used and followed by a " + nextToken.GetCategoryName() + ". This is not allowed.", iter->LineNumber, iter->TokenNumber));
					}
					currentStatement.push_back(*iter);
				}

				//Relational Op
				if (iter->Category == RELATIONAL_OP)
				{
					if (nextToken.Category != NUMERICAL_LITERAL || nextToken.Category != ID_NAME || nextToken.Category != LEFT_PARENTHESIS || (nextToken.Category != RELATIONAL_OP&&nextToken.Token == "!"))
					{
						errors.push_back(Error("Numeric literal or variable name expected. A relational operator was used and followed by a " + nextToken.GetCategoryName() + ". This is not allowed.", iter->LineNumber, iter->TokenNumber));
					}
					currentStatement.push_back(*iter);
				}
				//Logical Op
				if (iter->Category == LOGICAL_OP)
				{
					if (nextToken.Category != NUMERICAL_LITERAL || nextToken.Category != ID_NAME || nextToken.Category != LEFT_PARENTHESIS || (nextToken.Category != RELATIONAL_OP&&nextToken.Token == "!"))
					{
						errors.push_back(Error("Numeric literal or variable name expected. A logical operator was used and followed by a " + nextToken.GetCategoryName() + ". This is not allowed.", iter->LineNumber, iter->TokenNumber));
					}
					currentStatement.push_back(*iter);
				}

				//Assignment Op
				if (iter->Category == ASSIGNMENT_OP)
				{

					if (nextToken.Category != NUMERICAL_LITERAL || nextToken.Category != LEFT_PARENTHESIS || nextToken.Category != ID_NAME || (nextToken.Category != RELATIONAL_OP&&nextToken.Token == "!") || currentStatement.size() != 1)
					{
						errors.push_back(Error("Invalid assignmet operation.", iter->LineNumber, iter->TokenNumber));
					}
					currentStatement.push_back(*iter);
				}

				//Numerical_Literal
				//[11/24/2017 19:35] Cameron Osborn: Can be followed by Numeric, Relational, and Logical operators, Comma, Right Parentheses, SemiColon, 
				if (iter->Category == NUMERICAL_LITERAL)
				{
					if (nextToken.Category != NUMERICAL_OP || nextToken.Category != RELATIONAL_OP || nextToken.Category != LOGICAL_OP || nextToken.Category != COMMA || nextToken.Category != RIGHT_PARENTHESIS || nextToken.Category != SEMICOLON)
					{
						errors.push_back(Error(nextToken.GetCategoryName() + " can't follow a numeric literal.", iter->LineNumber, iter->TokenNumber));
					}
					currentStatement.push_back(*iter);
				}

				//String Literal
				if (iter->Category == STRING_LITERAL)
				{
					//[11/24/2017 20:47] Cameron Osborn: can be followed by comma, semicolon, and ???
					if (nextToken.Category != COMMA || nextToken.Category != SEMICOLON)
					{
						errors.push_back(Error("Expected ',' or ';'. A string literal can't be followed by the" + nextToken.GetCategoryName() + " token.", iter->LineNumber, iter->TokenNumber));
					}
					currentStatement.push_back(*iter);
				}

				//Left Paren
				if (iter->Category == LEFT_PARENTHESIS)
				{
					//[11/24/2017 21:16] Cameron Osborn: Can only be followed by numeric literal, ID_Name,Left_paren, or logical NOT (!)
					if (nextToken.Category != NUMERICAL_LITERAL || nextToken.Category != ID_NAME || nextToken.Category != LEFT_PARENTHESIS || (nextToken.Category != RELATIONAL_OP&&nextToken.Token == "!"))
					{
						errors.push_back(Error("A left parenthesis cannot be followed by the " + nextToken.GetCategoryName() + " token: " + nextToken.Token + ".", iter->LineNumber, iter->TokenNumber));
					}
					currentStatement.push_back(*iter);
				}


				//Right Paren
				if (iter->Category == RIGHT_PARENTHESIS)
				{
					//[11/24/2017 21:36] Cameron Osborn: Can be followed by semicolon, right parenthesis, all operators except logical NOT operator, Left curlybrace. Also: ID_Name, Keyword 
					//[11/24/2017 22:03] Cameron Osborn: If the next token is an ID name or a keyword and the current top of the compound statement stack is an 'if' or 'while' statement AND the top of the compound statement stack does not yet contain a conditional than the next statement is a stand-alone executable for that compound statement.
					if (
							(
								(nextToken.Category == ID_NAME&&nextToken.LineNumber == iter->LineNumber + 1)
								||
								(nextToken.Category == KEYWORD&&nextToken.LineNumber == iter->LineNumber + 1)
							)
						&&
							(
								compoundStatementStack.back().Type() != "if_element"
								||
								compoundStatementStack.back().Type() != "while_element"
							)
						&&
							compoundStatementStack.back().statement.size() == 0)
					{
						currentStatement.push_back(*iter);
						FlowStackElement addElement;
						addElement.statement = currentStatement;
						compoundStatementStack.back().pushStatement(addElement, false);
						compoundStatementStack.back().isMultilineCompound = false;
						currentStatement.clear();
					}
					else
					{
						if (nextToken.Category != SEMICOLON || nextToken.Category != RIGHT_PARENTHESIS || nextToken.Category != NUMERICAL_OP || nextToken.Category != RELATIONAL_OP || (nextToken.Category != LOGICAL_OP&&nextToken.Token != "!") || nextToken.Category != LEFT_CURLYBRACE)
						{
							errors.push_back(Error("A right parenthesis cannot be followed by the " + nextToken.GetCategoryName() + " token: " + nextToken.Token + ".", iter->LineNumber, iter->TokenNumber));
						}
						currentStatement.push_back(*iter);
					}
				}

				//Left Curlybrace
				if(iter->Category==LEFT_CURLYBRACE)
				{
					if(compoundStatementStack.size()==0 || compoundStatementStack.back().isMultilineCompound==true|| ((compoundStatementStack.back().Type()=="if_element"||compoundStatementStack.back().Type()=="while_element")&&compoundStatementStack.back().statement.size()!=0))
					{
						errors.push_back(Error("Mismatched {", iter->LineNumber, iter->TokenNumber));
					}else
					{

						FlowStackElement addElement;
						addElement.statement = currentStatement;

					}
				}


				//Right Curlybrace

				//Semicolon

				//Colon

				//Comma

				//Comment

				//Comment Text



			}




		}
	}





}



bool Interpreter::checkTokenOnlyValidAtBeginningOfStatement(SourceCodeToken checkToken)
{
	if (checkToken.Category == KEYWORD)
	{
		errors.push_back(Error("Invalid Token. End of statement (';' or ')') expected. A " + checkToken.GetCategoryName() + " token cannot appear in the middle of a statement.", checkToken.LineNumber, checkToken.TokenNumber));
		return false;
	}
	return true;
}

bool Interpreter::checkTokenInvalidAtBeginningOfStatement(SourceCodeToken checkToken)
{
	if (checkToken.Category != KEYWORD || checkToken.Category != ID_NAME || checkToken.Category != LEFT_PARENTHESIS || checkToken.Category != LEFT_CURLYBRACE || checkToken.Category != RIGHT_CURLYBRACE)
	{
		errors.push_back(Error("Invalid token at the beginning of the statment. The " + checkToken.GetCategoryName() + " token cannot appear as the first token in a statement.", checkToken.LineNumber, checkToken.TokenNumber));
		return false;
	}
	return true;
}

bool Interpreter::checkTokenVsCategoryLengthParsingError(perLineTokenVector checkTokenVect, perLineCategoryVector checkCategoryVect, int lineNumber)
{

	if (checkTokenVect.size() != checkCategoryVect.size())
	{

		errors.push_back(Error("PARSING ERROR \nLine: " + to_string(lineNumber) + " # of tokens inconstistent with # of category labels.", lineNumber, 0));
		//[11/21/2017 01:35] Cameron Osborn: Scanner Error
		//cout << "PARSING ERROR" << endl << "Line " << lineNumber << ": # of tokens inconsisten with # of category labels." << endl;
		return false;
	}
	return true;
}

bool Interpreter::checkSourceCodeContainsFunctions()
{
	for (vector<SourceCodeToken>::iterator iter = sourceCodeTokens.begin(); iter < sourceCodeTokens.end(); ++iter)
	{
		if (iter->Category == KEYWORD && iter->Token == "function")
			return true;
	}
	return false;
}
