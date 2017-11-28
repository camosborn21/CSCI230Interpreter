#include "stdafx.h"
#include "Interpreter.h"
#include <iostream>

using namespace std;

string Interpreter::GetErrorQuantityStatement()
{
	string result;
	if (errors.size() == 1)
		result = "(1 error)";
	else
		result = "(" + to_string(errors.size()) + " errors)";
	return result;
}

int Interpreter::GetVariableCount() const
{
	return varTable.size();
}

int Interpreter::GetErrorCount() const
{
	return errors.size();
}

//[11/26/2017 02:23] Cameron Osborn: display only. no testable code.
void Interpreter::printErrors()
{
	//[11/26/2017 00:29] Cameron Osborn: If there are no errors, print that the build was successful
	if (BuildStatus)
		cout << endl << endl << "Build Successful" << endl << endl;
	else
	{
		//[11/26/2017 00:29] Cameron Osborn: There are build errors, iterate through each one and display the message.
		cout << endl << endl << "THERE WERE BUILD ERRORS" << endl << "Error Summary" + GetErrorQuantityStatement() + ": " << endl;
		for (Error error : errors)
		{
			error.printError();
		}
	}
}

//[11/26/2017 02:23] Cameron Osborn: ui interact required. not currently unit testable.
void Interpreter::execute()
{
	//[11/25/2017 21:58] Cameron Osborn: no need to check build status as this routine is only called by the parseSourceCode method which will prevent the call if there are build errors.

	//[11/26/2017 02:25] Cameron Osborn: For each statement in the parsed source code
	for (Statement statement : statements)
	{
		//[11/26/2017 02:25] Cameron Osborn: Determine StatementType: display, read, or assignment.
		if (statement.StatementType == "display")
		{//[11/26/2017 02:25] Cameron Osborn: if display then
			//[11/26/2017 02:26] Cameron Osborn: Insert new line
			cout << endl;

			//[11/26/2017 02:26] Cameron Osborn: for each token following the keyword "display"
			vector<SourceCodeToken>::iterator iter = statement.Tokens.begin() + 1;

			//[11/26/2017 00:49] Cameron Osborn: display all statements except the semicolon at the end
			while (iter < statement.Tokens.end() - 1)
			{

				//[11/26/2017 02:27] Cameron Osborn: Comma is the display concatonator in this language, skip commas outside of string literals
				if (iter->Category != COMMA) {

					//[11/26/2017 02:27] Cameron Osborn: if it's a string literal, print out all but the enclosing double quote marks.
					if (iter->Category == STRING_LITERAL)
					{
						cout << (iter->Token).substr(1, iter->Token.size() - 2);
					}
					else
					{
						//[11/25/2017 23:43] Cameron Osborn: Assume anything that's not a string literal or a comma to be an infix expression which requires evaluation. Even if it's a single value or variable name it will return fine from the expression evaluator.
						float resultValue;
						vector<string> tempInfix;

						//[11/25/2017 23:51] Cameron Osborn: for each token between here and the next comma or the end of statement (;), add to the temporary infix vector.
						while (iter->Category != COMMA && iter->Category != SEMICOLON)
						{
							tempInfix.push_back(iter->Token);
							++iter;
						}

						//[11/26/2017 02:28] Cameron Osborn: Once the tempInfix vector has been built, evaluate it
						if (ExpressionEvaluator::infixEvaluator(tempInfix, varTable, resultValue))
						{
							//[11/25/2017 23:51] Cameron Osborn: Valid expression evaluation. Print to output
							cout << resultValue;
						}
						else
						{
							//[11/25/2017 23:48] Cameron Osborn: invalid expression passed to evaluator.
							cout << endl << "Runtime error: Expression could not be evaluated.";
						}

					}
				}
				++iter;
			}
		}
		else {
			//[11/26/2017 02:29] Cameron Osborn: If the statement type is a 'read' statement.
			if (statement.StatementType == "read")
			{
				//[11/25/2017 22:12] Cameron Osborn: get Variable name
				string varName = statement.Tokens[1].Token;

				//[11/26/2017 02:30] Cameron Osborn: Get the input from user
				string tempVar;
				cout << endl;
				getline(cin, tempVar);

				//[11/26/2017 02:30] Cameron Osborn: validate user input !!!Check for runtime error of non-float value input by user.
				if (OriginalScanner::isNUMERICAL_LITERAL(tempVar))
				{
					//[11/25/2017 22:12] Cameron Osborn: insert or assign the value of the variable in the table.
					varTable.insert_or_assign(varName, stof(tempVar));

				}
				else
				{
					//[11/25/2017 22:15] Cameron Osborn: A non-float value was entered by the user.
					cout << endl << "Runtime Error: Invalid value for variable " + varName + ". Code execution will stop.";
					return;
				}
			}
			else { //[11/26/2017 02:30] Cameron Osborn: If the statement type is an 'assignment' statement.
				if (statement.StatementType == "assignment")
				{
					//[11/26/2017 02:31] Cameron Osborn: get variable name for assinment.
					string varName = statement.Tokens[0].Token;

					//[11/26/2017 02:31] Cameron Osborn: Create the infix vector using all tokens after the assignment operator (=).
					vector<string> infixString;
					for (int i = 2; i < statement.Tokens.size() - 1; i++)
					{
						infixString.push_back(statement.Tokens[i].Token);
					}

					//[11/26/2017 02:32] Cameron Osborn: Evaluate the expression retrieved in the infix vector.
					float resultValue;
					if (ExpressionEvaluator::infixEvaluator(infixString, varTable, resultValue))
					{
						//[11/26/2017 02:32] Cameron Osborn: Valid evaluation of infix vector
						varTable.insert_or_assign(varName, resultValue);
					}
					else
					{
						//[11/25/2017 22:23] Cameron Osborn: Invalid expression detected by evaluator.
						cout << endl << "Runtime error: Expression could not be evaluated.";
					}
				}
				else {
					//[11/25/2017 22:00] Cameron Osborn: unrecognized statement.
					cout << endl << "Runtime error: Unrecognized program code. Code execution will stop.";
					//[11/25/2017 22:01] Cameron Osborn: FWIW this should never happen.
					return;
				}
			}
		}
	}
}


void Interpreter::parseSourceCode(vector<string> lines, bool displayErrorsAfterParse, bool executeAfterParse)
{
	//[11/25/2017 21:42] Cameron Osborn: Clear errors vector to begin parse and syntax check.
	errors.clear();

	//[11/26/2017 01:03] Cameron Osborn: Clear token vectors and category vectors for all lines
	tokenVectorsForAllLines.clear();
	categoryVectorsForAllLines.clear();
	statements.clear();


	//[11/25/2017 14:13] Cameron Osborn: Get lexical analysis of all statements in program
	OriginalScanner::getLexicalInfo(lines, tokenVectorsForAllLines, categoryVectorsForAllLines);

	//[11/21/2017 01:26] Cameron Osborn: For Each Line convert the token vector and category vector data into SourceCodeToken class objects and filter out comments.
	Statement currentStatement;
	for (size_t i = 0; i < tokenVectorsForAllLines.size(); i++)
	{
		//[11/26/2017 02:35] Cameron Osborn: If we're at the beginning of a new line and haven't already pushed the former statement onto the program stack, do so now.
		if (currentStatement.Tokens.size() > 0)
		{
			statements.push_back(currentStatement);
			currentStatement.Tokens.clear();
		}

		//[11/26/2017 02:36] Cameron Osborn: get the current line tokens and categories
		perLineTokenVector tokenVect = tokenVectorsForAllLines[i];
		perLineCategoryVector categoryVect = categoryVectorsForAllLines[i];

		//[11/21/2017 01:45] Cameron Osborn: check parsing validity of current line
		if (tokenVect.size() != categoryVect.size())
		{
			cout << "Line " << i
				<< ": # of tokens inconsistent with # of category labels." << endl;
			return;
		}

		//[11/21/2017 02:14] Cameron Osborn: for each token: create source code token.
		for (size_t j = 0; j < tokenVect.size(); j++)
		{
			//[11/24/2017 19:38] Cameron Osborn: Filter out comments and comment text so it doesn't interfere with parsing.
			if (categoryVect[j] != COMMENT && categoryVect[j] != COMMENT_TEXT)
				currentStatement.Tokens.push_back(SourceCodeToken(tokenVect[j], categoryVect[j], i, j));
		}

		statements.push_back(currentStatement);
		currentStatement.Tokens.clear();
	}

	//[11/26/2017 02:36] Cameron Osborn: Once all lines have been normalized, check for syntax errors.
	checkSyntax();

	//[11/26/2017 02:37] Cameron Osborn: After syntax check, set resultant status.
	if (errors.size() != 0)
		BuildStatus = false; //[11/26/2017 02:37] Cameron Osborn: There are build errors
	else
		BuildStatus = true; //[11/26/2017 02:37] Cameron Osborn: No errors. Build successful

	//[11/26/2017 02:37] Cameron Osborn: parameter option fulfillment to execute code or display errors after code has been parsed.
	if (executeAfterParse)
	{
		if (BuildStatus)
			execute();
		else
			printErrors();
	}
	else
	{
		if (displayErrorsAfterParse)
		{
			printErrors();
		}
	}
}

void Interpreter::checkSyntax()
{

	//[11/25/2017 20:37] Cameron Osborn: clear the variable table. It will be built by the syntax check to ensure variables are declared and used in the proper order.
	varTable.clear();


	//[11/26/2017 02:41] Cameron Osborn: For all statements in the parsed program.
	for (vector<Statement>::iterator iter = statements.begin(); iter < statements.end(); ++iter)
	{
		//[11/26/2017 02:39] Cameron Osborn: keeps track of iterator position by index #. Used to nab next token at the beginning of each subsequent iteration.
		int tokenIndex = 0;

		//[11/26/2017 02:45] Cameron Osborn: For each token within the iter statement.
		for (vector<SourceCodeToken>::iterator token = iter->Tokens.begin(); token < iter->Tokens.end(); ++token, tokenIndex++)
		{
			//[11/26/2017 02:47] Cameron Osborn: if the current token is not the last token of the statement then pick up the next SourceCodeToken to use in evaluation.
			SourceCodeToken nextToken;
			if (tokenIndex + 1 < iter->Tokens.size())
				nextToken = iter->Tokens[tokenIndex + 1];

			//[11/26/2017 02:48] Cameron Osborn: if we're on the first token of the statement.
			if (token == iter->Tokens.begin())
			{
				//[11/25/2017 14:47] Cameron Osborn: First token must be either 'display', 'read', or ID_NAME
				//[11/26/2017 04:08] Cameron Osborn: TestCovered
				checkTokenValidAtBeginningOfStatement(*token);


				if (token->Category == ID_NAME)
				{
					iter->StatementType = "assignment";
					//[11/25/2017 15:04] Cameron Osborn: this is an assignment operation. Next token must be ASSIGNMENT_OP
					//[11/26/2017 04:08] Cameron Osborn: TestCovered
					if (nextToken.Category != ASSIGNMENT_OP)
					{
						errors.push_back(Error("Invalid assignment operation: Variable name must be followed by assignment operator", token->LineNumber + 1, token->TokenNumber + 1));
					}

					//[11/25/2017 21:18] Cameron Osborn: chcek that variable name is in varTable. If not then add it.
					//[11/26/2017 04:08] Cameron Osborn: TestCovered
					if (varTable.find(token->Token) == varTable.end())
					{
						varTable.insert(make_pair(token->Token, 0));
					}

				}


				if (token->Category == KEYWORD&&token->Token == "read")
				{
					iter->StatementType = "read";
					//[11/25/2017 15:08] Cameron Osborn: read operation. Next token must be ID_NAME
					//[11/26/2017 04:12] Cameron Osborn: TestCovered
					if (nextToken.Category != ID_NAME)
					{
						errors.push_back(Error("Invalid read operation: the 'read' keyword must be followed by a variable name.", token->LineNumber + 1, token->TokenNumber + 1));
					}
					else
					{
						//[11/25/2017 21:18] Cameron Osborn: check that variable name is in varTable. If not then add it.
						//[11/26/2017 04:16] Cameron Osborn: TestCovered
						if (varTable.find(nextToken.Token) == varTable.end())
						{
							varTable.insert(make_pair(nextToken.Token, 0));
						}
					}

					//[11/26/2017 04:20] Cameron Osborn: The read operation must be exactly three tokens long. the 'read' keyword token, the IDName variable token, and the semicolon at the end. Any more or less should throw errors.
					//[11/26/2017 04:20] Cameron Osborn: TestCovered
					if (iter->Tokens.size() != 3)
					{
						errors.push_back(Error("Invalid read operation: the 'read' operation can only contain the read keyword, a variable name, and the statement-terminating semicolon.", token->LineNumber + 1, token->TokenNumber + 1));
					}
				}

				if (token->Category == KEYWORD && token->Token == "display")
				{
					iter->StatementType = "display";
					//[11/25/2017 15:10] Cameron Osborn: display operation. Next token must be string literal, numeric literal, left parenthesis, variable name or logical NOT operator
					//[11/27/2017 14:07] Cameron Osborn: TestCovered
					if (nextToken.Category != ID_NAME && nextToken.Category != STRING_LITERAL && nextToken.Category!=LEFT_PARENTHESIS && nextToken.Category != NUMERICAL_LITERAL && !(nextToken.Category == LOGICAL_OP&&nextToken.Token == "!"))
					{
						errors.push_back(Error("Invalid display operation: the 'display keyword must be followed by a string, number, variable name, or the logical NOT (!) operator.", token->LineNumber + 1, token->TokenNumber + 1));
					}

				}

			}
			else //[11/25/2017 14:48] Cameron Osborn: now we're on subsequent tokens
			{
				//[11/25/2017 16:46] Cameron Osborn: ensure final token in statement is semicolon
				//[11/27/2017 18:57] Cameron Osborn: TestCovered
				if (tokenIndex + 1 == iter->Tokens.size())
				{
					if (token->Category != SEMICOLON)
						errors.push_back(Error("Expected end of statement (;). Statements must terminate with a semicolon", token->LineNumber + 1, token->TokenNumber + 1));
				}
				else {
					//[11/25/2017 16:49] Cameron Osborn: for any non final token

					//[11/25/2017 16:47] Cameron Osborn: all read statement validation is conducted based on the first token.

					//[11/25/2017 16:53] Cameron Osborn: validate display statement
					if (iter->StatementType == "display")
					{
						//[11/25/2017 16:54] Cameron Osborn: valid tokens in display operation are: string literal, numeric literal, id name, any operator, comma, left & right paren
						if (token->Category == STRING_LITERAL)
						{
							//[11/25/2017 17:01] Cameron Osborn: string literal can only be followed by a comma or a semicolon
							//[11/27/2017 20:19] Cameron Osborn: TestCovered
							if (nextToken.Category != COMMA&&nextToken.Category != SEMICOLON)
							{
								errors.push_back(Error("Invalid syntax. In a display statement, a string literal can only be followed by a comma or a semi colon.", token->LineNumber + 1, token->TokenNumber + 1));
							}
						}
						else {

							if (token->Category == NUMERICAL_LITERAL || token->Category == ID_NAME)
							{
								//[11/25/2017 17:11] Cameron Osborn: valid tokens following Numeric literal and ID name: any op except logical NOT operator, right paren, semi colon, comma
								//[11/27/2017 20:19] Cameron Osborn: LEFT OFF HERE WITH TEST COVERAGE CHECKS
								if (nextToken.Category != RELATIONAL_OP&& nextToken.Category != SEMICOLON  &&nextToken.Category != NUMERICAL_OP&&nextToken.Category != RIGHT_PARENTHESIS && (nextToken.Category != LOGICAL_OP&&nextToken.Token == "!") && nextToken.Category != COMMA)
								{
									errors.push_back(Error("Invalid syntax. Numeric literal or variable cannot be followed by the " + nextToken.GetTokenCategoryName() + " token: " + nextToken.Token + ".", token->LineNumber + 1, token->TokenNumber + 1));
								}
								if (token->Category == ID_NAME&&varTable.find(token->Token) == varTable.end())
								{
									errors.push_back(Error("Undefined variable. The variable " + token->Token + " is not declared and assigned a value before being used in a display statement.", token->LineNumber + 1, token->TokenNumber + 1));
								}
							}
							else
							{
								//[11/25/2017 18:52] Cameron Osborn: valid tokens following operators
								if (token->Category == RELATIONAL_OP || token->Category == NUMERICAL_OP || token->Category == LOGICAL_OP)
								{
									//[11/25/2017 18:52] Cameron Osborn: valid tokens after an operator: numerical literal, id name, left paren
									if (nextToken.Category != NUMERICAL_LITERAL&&nextToken.Category != ID_NAME&&nextToken.Category != LEFT_PARENTHESIS)
									{
										errors.push_back(Error("Invalid syntax. An operator cannot be followed by the " + nextToken.GetTokenCategoryName() + " token: " + nextToken.Token + ".", token->LineNumber + 1, token->TokenNumber + 1));
									}
								}
								else
								{
									//[11/25/2017 18:57] Cameron Osborn: comma
									if (token->Category == COMMA)
									{
										//[11/25/2017 19:00] Cameron Osborn: Comma can be followed by string literal, numeric literal, left paren, ID_name, logical not op.
										if (nextToken.Category != STRING_LITERAL&&nextToken.Category != NUMERICAL_LITERAL&&nextToken.Category != ID_NAME && nextToken.Category != LEFT_PARENTHESIS && (nextToken.Category != LOGICAL_OP&&nextToken.Token == "!"))
										{
											errors.push_back(Error("Invalid syntax. A comma can't be followed by the " + nextToken.GetTokenCategoryName() + " token: " + nextToken.Token + ".", token->LineNumber + 1, token->TokenNumber + 1));
										}
									}
									else
									{
										//[11/25/2017 18:57] Cameron Osborn: Left Paren
										if (token->Category == LEFT_PARENTHESIS)
										{
											//[11/25/2017 19:05] Cameron Osborn: Left paren can be followed by numeric literal, ID name, left paren, logical NOT operator
											if (nextToken.Category != NUMERICAL_LITERAL&&nextToken.Category != ID_NAME&&nextToken.Category != LEFT_PARENTHESIS && (nextToken.Category != LOGICAL_OP && nextToken.Token == "!"))
											{
												errors.push_back(Error("Invalid syntax. A left parenthesis can't be followed by the " + nextToken.GetTokenCategoryName() + " token: " + nextToken.Token + ".", token->LineNumber + 1, token->TokenNumber + 1));
											}

										}
										else
										{
											//[11/25/2017 19:11] Cameron Osborn: right paren
											if (token->Category == RIGHT_PARENTHESIS)
											{
												//[11/25/2017 19:11] Cameron Osborn: right paren can be followed by any op except logical not op, comma, right paren, semi-colon

												if (nextToken.Category != RELATIONAL_OP&&nextToken.Category != NUMERICAL_OP&&nextToken.Category != COMMA&&nextToken.Category != RIGHT_PARENTHESIS&&nextToken.Category != SEMICOLON && (nextToken.Category != LOGICAL_OP&&nextToken.Token != "!"))
												{
													errors.push_back(Error("Invalid syntax. A right parenthesis can't be followed by the " + nextToken.GetTokenCategoryName() + " token: " + nextToken.Token + ".", token->LineNumber + 1, token->TokenNumber + 1));
												}

											}
											else
											{
												errors.push_back(Error("Invalid token! The " + token->GetTokenCategoryName() + " token: " + token->Token + " cannot be used in a display operation.", token->LineNumber + 1, token->TokenNumber + 1));
											}
										}
									}
								}
							}
						}
					} //end of display syntax check

					//[11/25/2017 19:18] Cameron Osborn: validate assignment statement

					if (iter->StatementType == "assignment")
					{
						// can include: numeric literal, id name, left/right paren, any operator, assignment operator(once in 2nd position) using tokenIndex to check position counting from 0 (i.e. when token index == 1 then assignment op, else fail
						if (token->Category == NUMERICAL_LITERAL || token->Category == ID_NAME)
						{
							//[11/25/2017 19:24] Cameron Osborn: valid tokens following Numeric literal and ID name: any op except logical NOT operator, right paren, semi colon
							if (nextToken.Category != RELATIONAL_OP&& nextToken.Category != SEMICOLON  &&nextToken.Category != NUMERICAL_OP&&nextToken.Category != RIGHT_PARENTHESIS && (nextToken.Category != LOGICAL_OP&&nextToken.Token == "!"))
							{
								errors.push_back(Error("Invalid syntax. Numeric literal or variable cannot be followed by the " + nextToken.GetTokenCategoryName() + " token: " + nextToken.Token + ".", token->LineNumber + 1, token->TokenNumber + 1));
							}
							if (token->Category == ID_NAME&&varTable.find(token->Token) == varTable.end())
							{
								errors.push_back(Error("Undefined variable. The variable " + token->Token + " is not declared and assigned a value before being used in a display statement.", token->LineNumber + 1, token->TokenNumber + 1));
							}

						}
						else
						{
							if (token->Category == LEFT_PARENTHESIS)
							{
								if (nextToken.Category != NUMERICAL_LITERAL&&nextToken.Category != ID_NAME&&nextToken.Category != LEFT_PARENTHESIS && (nextToken.Category != LOGICAL_OP && nextToken.Token == "!"))
								{
									errors.push_back(Error("Invalid syntax. A left parenthesis can't be followed by the " + nextToken.GetTokenCategoryName() + " token: " + nextToken.Token + ".", token->LineNumber + 1, token->TokenNumber + 1));
								}
							}
							else
							{
								if (token->Category == RIGHT_PARENTHESIS)
								{
									//[11/25/2017 19:11] Cameron Osborn: right paren can be followed by any op except logical not op,  right paren, semi-colon

									if (nextToken.Category != RELATIONAL_OP&&nextToken.Category != NUMERICAL_OP&&nextToken.Category != RIGHT_PARENTHESIS&&nextToken.Category != SEMICOLON && (nextToken.Category != LOGICAL_OP&&nextToken.Token != "!"))
									{
										errors.push_back(Error("Invalid syntax. A right parenthesis can't be followed by the " + nextToken.GetTokenCategoryName() + " token: " + nextToken.Token + ".", token->LineNumber + 1, token->TokenNumber + 1));
									}
								}
								else
								{
									if (token->Category == RELATIONAL_OP || token->Category == NUMERICAL_OP || token->Category == LOGICAL_OP)
									{
										//[11/25/2017 18:52] Cameron Osborn: valid tokens after an operator: numerical literal, id name, left paren
										if (nextToken.Category != NUMERICAL_LITERAL&&nextToken.Category != ID_NAME&&nextToken.Category != LEFT_PARENTHESIS)
										{
											errors.push_back(Error("Invalid syntax. An operator cannot be followed by the " + nextToken.GetTokenCategoryName() + " token: " + nextToken.Token + ".", token->LineNumber + 1, token->TokenNumber + 1));
										}
									}
									else
									{
										if (token->Category == ASSIGNMENT_OP)
										{
											if (tokenIndex != 1)
											{

											}
										}
										else
										{
											errors.push_back(Error("Invalid token! The " + token->GetTokenCategoryName() + " token: " + token->Token + " cannot be used in an assignment operation.", token->LineNumber + 1, token->TokenNumber + 1));
										}
									}
								}
							}
						}
					} //End of assignment statement validation
				}
			}
		}
	}
}

void Interpreter::checkTokenValidAtBeginningOfStatement(SourceCodeToken checkToken)
{
	if (checkToken.Category == ID_NAME || (checkToken.Category == KEYWORD && checkToken.Token == "display") || (checkToken.Category == KEYWORD && checkToken.Token == "read"))
	{

	}
	else
	{
		errors.push_back(Error("Invalid token at the beginning of statement. Statements cannot begin with the " + checkToken.GetTokenCategoryName() + ": " + checkToken.Token + ". Statements must begin with either read, display, or a variable name.", checkToken.LineNumber + 1, checkToken.TokenNumber + 1));
	}
	//if(checkToken.Category!=ID_NAME&&(checkToken.Category!=KEYWORD&&checkToken.Token=="display")&&(checkToken.Category!=KEYWORD&&checkToken.Token=="read"))
	//{
	//	errors.push_back(Error("Invalid token at the beginning of statement. Statements cannot begin with the " + checkToken.GetTokenCategoryName() + ": " + checkToken.Token + ". Statements must begin with either read, display, or a variable name.", checkToken.LineNumber + 1, checkToken.TokenNumber + 1));
	//}

}
