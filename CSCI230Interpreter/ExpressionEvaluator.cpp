#include "stdafx.h"
#include "ExpressionEvaluator.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include "OriginalScanner.h"

using namespace std;

int ExpressionEvaluator::precedenceLevel(const string & opToken)
//return the precedence level of an operator token
{

	if (opToken == "||")
		return 0;
	if (opToken == "&&")
		return 1;
	if (opToken == "!=")
		return 2;
	if (opToken == "<")
		return 2;
	if (opToken == "==")
		return 2;
	if (opToken == ">")
		return 2;
	if (opToken == ">=")
		return 2;
	if (opToken == "<=")
		return 2;

	if (opToken == "+")
		return 3;
	if (opToken == "-")
		return 3;

	if (opToken == "*")
		return 4;
	if (opToken == "/")
		return 4;
	if (opToken == "%")
		return 4;

	if (opToken == "!")
		return 5;

	//Otherwise
	cout << "unkown op:" << opToken << ". precedence level?? " << endl;
	return -1;
}

bool ExpressionEvaluator::postfixEvaluator(const expVector & postfixExp, floatVarValueTable & varTable, float & expValue)
//Evaluate the value of a postfix expression postfixExp
//with respect to the variables and their current values  in varTable.
//finally store the value of the expresson in expValue.
//If postfixExp is not a valid postfix expression, return false; otherwsie return true.
{
	vector<float> stack;
	for (expVector::const_iterator pos = postfixExp.begin(); pos != postfixExp.end(); ++pos)
	{
		string token;

		token = *pos;
		if (token.size() < 1)
		{
			expValue = 0;
			cout << "Empty Token, not valid." << endl;
			return false;
		}

		if (OriginalScanner::isNUMERICAL_LITERAL(token))
			//A numerical constant, convert it into a float value, and
			//store push it onto the stack
			stack.push_back(atof(token.c_str()));
		else if (OriginalScanner::isID_NAME(token))
			//An ID_NAME, try to look up its current value from the table.
			//If succeeds, push the value onto the stack.
		{
			if (varTable.find(token) == varTable.end())
				return false; //Invalid name
			stack.push_back(varTable[token]);
		}
		else if (OriginalScanner::isNUMERICAL_OP(token) ||
			OriginalScanner::isRELATIONAL_OP(token) ||
			OriginalScanner::isLOGICAL_OP(token)
			)
			//A numerical or relational operator
			//Try to pop two operands from the stack apply the operator.
			//If succeeds, push te result back to the stack.
		{
			float op1, op2;
			//Try to pop op2 first
			if (!stack.empty()) {
				op2 = stack.back();
				stack.pop_back();
			}
			else {
				cout << "No matching op2 for the op: " << token << endl;
				return false; //op2 not available, Not a valid expression
			}

			//Determine whether this is a binary operator or a unary operator
			bool isUnaryOp, isBinaryOp;
			if (token == "!") //unary logical negation operator
			{
				isUnaryOp = true;
				isBinaryOp = false;
			}
			else {
				isUnaryOp = false;
				isBinaryOp = true;
			}

			if (isUnaryOp) // when the operator is a unary operator
			{//the only case at this moment: the logical negation operator ! 
				if (token == "!")
					stack.push_back(!op2);
				else
				{
					cout << "Unknown unary op: " << token << endl;
					return false;
				}
			}//end the processing of a unary operator

			if (isBinaryOp) //When the operator is a binary operator
			{
				if (stack.empty())
					return false; //op1 not available, not a valid expression

				op1 = stack.back();
				stack.pop_back();

				//apply the binary operator and push back the result to the stack
				if (token == "+")
					stack.push_back(op1 + op2);
				else if (token == "-")
					stack.push_back(op1 - op2);
				else if (token == "*")
					stack.push_back(op1*op2);
				else if (token == "/")
					stack.push_back(op1 / op2);
				else if (token == "%")
					stack.push_back((int)op1 % (int)op2);
				else if (token == "<")
					stack.push_back(op1 < op2);
				else if (token == "==")
					stack.push_back(op1 == op2);
				else if (token == ">")
					stack.push_back(op1 > op2);
				else if (token == ">=")
					stack.push_back(op1 >= op2);
				else if (token == "<=")
					stack.push_back(op1 <= op2);
				else if (token == "!=")
					stack.push_back(op1 != op2);
				else if (token == "&&")
					stack.push_back(op1&&op2);
				else if (token == "||")
					stack.push_back(op1 || op2);
				else
				{
					cout << "Unkown binary op: " << token << endl;
					return false;
				}
			}//end the processing of a binary operator
		}//end the processing of the case that the token is an operator
		else
		{
			cout << "Unknown token type (Not an operator or an operand): " << token << endl;
			return false;
		}
		// Every token in the expression must be either be a numerical constant, 
		// an ID_NAME or an operator; Otherwise it is NOT a valid expression.
	}// end for
	if (stack.size() == 1)
		//The evaluated value of the expression should be the only value left on the stack
	{
		expValue = stack.back();
		return true;
	}
	else
		//It was not a valid expression
		return false;

	//return false;
}
bool OperatorPostfixCheck(expVector &stack, string operatorToken)
{
	//[9/28/2017 22:15] Cameron Osborn: when the infix to postfix conversion encounters an operator it loops through the stack until one of three rules returns true
	if (
		//[9/28/2017 22:19] Cameron Osborn: Stack is empty
		stack.size() == 0
		)
		return false;

	if (//[9/28/2017 22:19] Cameron Osborn: Top of stack is not some sort of operator
		!(OriginalScanner::isRELATIONAL_OP(stack.back()) ||
			OriginalScanner::isLOGICAL_OP(stack.back()) ||
			OriginalScanner::isNUMERICAL_OP(stack.back())))
		return false;

	if (//[9/28/2017 22:21] Cameron Osborn: The operator on the top of the stack is of lower precedence than the operatorToken in question from the postfix conversion
		ExpressionEvaluator::precedenceLevel(stack.back()) < ExpressionEvaluator::precedenceLevel(operatorToken))
		return false;



	return true;
}

bool ExpressionEvaluator::infixToPostfixConversion(const expVector & infixExp, expVector & postfixExp)
//Convert the infix expression in infixExp into a corresponding postfix expression.
//Store the corresponding postfix expression in postfixExp.
//If infixExp is not a valid infix expression, return false; otherwsie return true.
{
	expVector stackVect;
	for (expVector::const_iterator pos = infixExp.begin(); pos != infixExp.end(); ++pos) {
		if (OriginalScanner::isNUMERICAL_LITERAL((*pos)) || OriginalScanner::isID_NAME(*pos)) {
			//[9/28/2017 13:12] Cameron Osborn: check if the token is an operand; valid options are numerical literal and variable
			postfixExp.push_back(*pos);
		}

		//[9/28/2017 21:34] Cameron Osborn: Push the left parenthesis to the top of the stack.
		if (OriginalScanner::isLEFT_PARENTHESIS(*pos))
			stackVect.push_back(*pos);

		if (OriginalScanner::isRIGHT_PARENTHESIS(*pos))
		{
			//[9/28/2017 21:35] Cameron Osborn: If we encounter a right parenthesis then in a valid expression it's been preceded by a left paren.
			// scan backward through the stack looking for that open paren. Each non left paren should be pushed to the post fix vector.
			while (stackVect.back() != "(")
			{
				if (stackVect.size() == 0)
					//[9/28/2017 21:31] Cameron Osborn: No elements in vector. Invalid expression.
					return false;
				//[9/28/2017 21:33] Cameron Osborn: Pass each non left parenthesis token to the postfix expression then pop it from the stack
				postfixExp.push_back(stackVect.back());
				stackVect.pop_back();
			}

			//[9/28/2017 21:33] Cameron Osborn: Now pop the left parenthesis from the stack.
			stackVect.pop_back();
		}

		if (OriginalScanner::isNUMERICAL_OP(*pos) ||
			OriginalScanner::isRELATIONAL_OP(*pos) ||
			OriginalScanner::isLOGICAL_OP(*pos)
			)
		{
			while (OperatorPostfixCheck(stackVect,*pos))
			{
				postfixExp.push_back(stackVect.back());
				stackVect.pop_back();
			}
			stackVect.push_back(*pos);
		}


	}
	while(stackVect.size()!= 0)
	{
		postfixExp.push_back(stackVect.back());
		stackVect.pop_back();
	}

	return true;
}


bool ExpressionEvaluator::infixEvaluator(const expVector & infixExp, floatVarValueTable & varTable, float & expValue)
//Evaluate the value of the infix expression in postfixExp
//with respect to the variables and their current values in varTable.
//finally store the value of the expresson in expValue.
//If postfixExp is not a valid postfix expression, return false; otherwsie return true.
{
	expVector postfixExp;
	infixToPostfixConversion(infixExp, postfixExp);
	return postfixEvaluator(postfixExp, varTable, expValue);
}

bool ExpressionEvaluator::infixEvaluator(expVector::iterator begin, expVector::iterator end, floatVarValueTable & varTable, float & expValue)
{
	expVector infixExp(begin, end);

	return infixEvaluator(infixExp, varTable, expValue);
}


