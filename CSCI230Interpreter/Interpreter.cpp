#include "stdafx.h"
#include "Interpreter.h"
#include <iostream>
//#include "ExpressionEvaluator.h"
using namespace std;
//Convert source program lines to execution statements to allow multiline statements or multiple statements per line.

//Template
//	Parse lines to statements
//	Check Syntax
//		Display Syntax Errors
//	Execute statements 1 line at a time
//		read
//		display
//		assignment

string Interpreter::GetErrorQuantityStatement()
{
	string result;
	if (errors.size() == 1)
		result = "(1 error)";
	else
		result = "(" + to_string(errors.size()) + " errors)";
	return result;
}

int Interpreter::GetErrorCount() const
{
	return errors.size();
}

void Interpreter::printErrors()
{
	//[11/26/2017 00:29] Cameron Osborn: If there are no errors, print that the build was successful
	if (BuildStatus)
		cout << endl << endl << "Build Successful" << endl << endl;
	else
	{
		//[11/26/2017 00:29] Cameron Osborn: There are build errors, iterate through each one and display the message.
		cout << endl << endl << "THERE WERE BUILD ERRORS" << endl << "Error Summary" + GetErrorQuantityStatement() +": " << endl;
		for (Error error : errors)
		{
			error.printError();
		}
	}
}

void Interpreter::execute()
{
	//[11/25/2017 21:58] Cameron Osborn: no need to check build status as this routine is only called by the parseSourceCode method which will prevent the call if there are build errors.

	for (Statement statement : statements)
	{
		if(statement.StatementType=="display")
		{
			cout << endl;
			vector<SourceCodeToken>::iterator iter=statement.Tokens.begin() + 1;
			//[11/26/2017 00:49] Cameron Osborn: display all statements except the semicolon at the end
			while (iter < statement.Tokens.end()-1)
			{
				if (iter->Category != COMMA) {
					if (iter->Category == STRING_LITERAL)
					{
						cout << (iter->Token).substr(1,iter->Token.size()-2);
					} else
					{
						//[11/25/2017 23:43] Cameron Osborn: Assume anything that's not a string literal or a comma to be an infix expression which requires evaluation. Even if it's a single value it will return fine from the expression evaluator.
						float resultValue;
						vector<string> tempInfix;

						//[11/25/2017 23:51] Cameron Osborn: for each token between here and the next comma or the end of statement (;), add to the temporary infix vector.
						while(iter->Category!=COMMA && iter->Category != SEMICOLON)
						{
							tempInfix.push_back(iter->Token);
							++iter;
						}
						if(ExpressionEvaluator::infixEvaluator(tempInfix,varTable,resultValue))
						{
							//[11/25/2017 23:51] Cameron Osborn: Valid expression evaluation. Print to output
							cout << resultValue;
						}else
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
			if (statement.StatementType == "read")
			{
				//[11/25/2017 22:12] Cameron Osborn: get Variable name
				string varName = statement.Tokens[1].Token;
				string tempVar;
				cout << endl;
				getline(cin, tempVar);
				if(OriginalScanner::isNUMERICAL_LITERAL(tempVar))
				{

					//[11/25/2017 22:12] Cameron Osborn: insert or assign the value of the variable in the table.
					varTable.insert_or_assign(varName,stof(tempVar));


					/*floatVarValueTable::iterator varTableIterator = varTable.find(varName);
					if(varTableIterator==varTable.end())
					{
						varTable.insert()
					}else
					{
						
					}*/
				} else
				{
					//[11/25/2017 22:15] Cameron Osborn: A non-float value was entered by the user.
					cout << endl << "Runtime Error: Invalid value for variable " + varName + ". Code execution will stop.";
					return;
				}
			}
			else {
				if (statement.StatementType == "assignment")
				{
					string varName = statement.Tokens[0].Token;
					vector<string> infixString;
					float resultValue;
					for(int i=2;i<statement.Tokens.size()-1;i++)
					{
						infixString.push_back(statement.Tokens[i].Token);
					}
					if (ExpressionEvaluator::infixEvaluator(infixString, varTable, resultValue))
					{
						varTable.insert_or_assign(varName, resultValue);
					}else
					{
						//[11/25/2017 22:23] Cameron Osborn: Invalid expression detected by evaluator.
						cout << endl <<  "Runtime error: Expression could not be evaluated.";
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
		if (currentStatement.Tokens.size() > 0)
		{
			statements.push_back(currentStatement);
			currentStatement.Tokens.clear();
		}
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
	}
	checkSyntax();

	if (errors.size() != 0)
		BuildStatus = false;
	else
		BuildStatus = true;

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
	floatVarValueTable::iterator pos;
	//[11/25/2017 20:37] Cameron Osborn: clear the variable table. It will be built by the syntax check to ensure variables are declared and used in the proper order.
	varTable.clear();
	int tokenIndex = 0;
	for (vector<Statement>::iterator iter = statements.begin(); iter < statements.end(); ++iter)
	{
		tokenIndex = 0;
		for (vector<SourceCodeToken>::iterator token = iter->Tokens.begin(); token < iter->Tokens.end(); ++token, tokenIndex++)
		{
			SourceCodeToken nextToken;

			if (tokenIndex + 1 < iter->Tokens.size())
				nextToken = iter->Tokens[tokenIndex + 1];

			//[11/25/2017 14:47] Cameron Osborn: First token must be either 'display', 'read', or ID_NAME
			if (token == iter->Tokens.begin())
			{
				checkTokenValidAtBeginningOfStatement(*token);
				if (token->Category == ID_NAME)
				{
					iter->StatementType = "assignment";
					//[11/25/2017 15:04] Cameron Osborn: this is an assignment operation. Next token must be ASSIGNMENT_OP
					if (nextToken.Category != ASSIGNMENT_OP)
					{
						errors.push_back(Error("Invalid assignment operation: Variable name must be followed by assignment operator", token->LineNumber+1, token->TokenNumber + 1));
					}

					//[11/25/2017 21:18] Cameron Osborn: chcek that variable name is in varTable. If not then add it.
					if (varTable.find(token->Token) == varTable.end())
					{
						varTable.insert(make_pair(token->Token, 0));
					}

				}

				if (token->Category == KEYWORD&&token->Token == "read")
				{
					iter->StatementType = "read";
					//[11/25/2017 15:08] Cameron Osborn: read operation. Next token must be ID_NAME
					if (nextToken.Category != ID_NAME)
					{
						errors.push_back(Error("Invalid read operation: the 'read' keyword must be followed by a variable name.", token->LineNumber + 1, token->TokenNumber + 1));
					}
					else
					{
						//[11/25/2017 21:18] Cameron Osborn: chcek that variable name is in varTable. If not then add it.
						if (varTable.find(nextToken.Token) == varTable.end())
						{
							varTable.insert(make_pair(nextToken.Token, 0));
						}
					}
					if (iter->Tokens.size() != 3)
					{
						errors.push_back(Error("Invalid read operation: the 'read' operation can only contain the read keyword, a variable name, and the statement terminating semi-colon.", token->LineNumber + 1, token->TokenNumber + 1));
					}


				}

				if (token->Category == KEYWORD && token->Token == "display")
				{
					iter->StatementType = "display";
					//[11/25/2017 15:10] Cameron Osborn: display operation. Next token must be string literal, numeric literal, variable name or logical NOT operator
					if (nextToken.Category != ID_NAME && nextToken.Category != STRING_LITERAL && nextToken.Category != NUMERICAL_LITERAL && (nextToken.Category != LOGICAL_OP&&nextToken.Token == "!"))
					{
						errors.push_back(Error("Invalid display operation: the 'display keyword must be followed by a string, number, variable name, or the logical NOT (!) operator.", token->LineNumber + 1, token->TokenNumber + 1));
					}

				}

			}
			else
			{
				//[11/25/2017 14:48] Cameron Osborn: now we're on subsequent tokens

				//[11/25/2017 16:46] Cameron Osborn: ensure final token in statement is semicolon
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
							if (nextToken.Category != COMMA&&nextToken.Category != SEMICOLON)
							{
								errors.push_back(Error("Invalid syntax. In a display statement, a string literal can only be followed by a comma or a semi colon.", token->LineNumber + 1, token->TokenNumber + 1));
							}
						}
						else {

							if (token->Category == NUMERICAL_LITERAL || token->Category == ID_NAME)
							{
								//[11/25/2017 17:11] Cameron Osborn: valid tokens following Numeric literal and ID name: any op except logical NOT operator, right paren, semi colon, comma
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
	if (checkToken.Category == ID_NAME || (checkToken.Category == KEYWORD&&checkToken.Token == "display") || (checkToken.Category == KEYWORD&&checkToken.Token == "read"))
	{

	}
	else
	{
		errors.push_back(Error("Invalid token at the beginning of statement. Statements cannot begin with the " + checkToken.GetTokenCategoryName() + ": " + checkToken.Token + ". Statements must begin with either read, display, or a variable name.", checkToken.LineNumber + 1, checkToken.TokenNumber + 1));
	}
}
