// CSCI230Interpreter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ProgramUI.h"
#include "ExpressionEvaluator.h"

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "OriginalScanner.h"

using namespace std;

void main()
{
	ProgramUI interpreterUi;
	interpreterUi.startInterface();
    
}


void main_ExpressionEvalutorTesting()
{
	//Set up a table to store values of 8 variables
	floatVarValueTable varTable;

	varTable["s"] = 1;
	varTable["t"] = 2;
	varTable["u"] = 3;
	varTable["v"] = 4;
	varTable["w"] = 5;
	varTable["x"] = 3.5;
	varTable["y"] = 7;
	varTable["z"] = 8;

	cout << "******************************************************************" << endl;
	cout << "Based on the following symbol table of variables and their current values, " << endl
		<< "we are going to test the implementation of the arithmetic expression evaluator."
		<< endl;
	cout << "******************************************************************" << endl;
	cout << "You can change the set up of variables and their values manually in the main function source code" << endl;
	cout << "******************************************************************" << endl;
	cout << "The following is the current list of values of the variables" << endl;
	for (floatVarValueTable::iterator i = varTable.begin();
		i != varTable.end();
		++i
		)
	{
		cout << "[" << (*i).first << "," << (*i).second << "]" << endl;
	}


	cout << "******************************************************************" << endl;
	cout << "Test 1: on the implementation of infix-to-postfix conversion and " << endl
		<< "the postfix-expression evaluation." << endl;
	cout << "******************************************************************" << endl;

	string rawExpressionString;
	expVector infixExp, postfixExp;
	rawExpressionString = "";
	infixExp.clear();
	postfixExp.clear();

	while (rawExpressionString != ".")
	{
		rawExpressionString = "";
		infixExp.clear();
		postfixExp.clear();

		float expValue = 0;
		cout << "Give me an infix expression that may have variables s,t,u,v,w,x,y,z in it."
			<< endl << "OR type in an expression of a single period . to quit" << endl << endl;
		getline(cin, rawExpressionString);
		OriginalScanner::getPerLineTokenVectFromOneStringObject
		(rawExpressionString,
			infixExp
		);

		cout << endl
			<< "The infix expression:" << rawExpressionString << endl
			<< "# of tokens in it:" << infixExp.size() << endl
			<< "Token of this infix expression:" << endl;

		for (expVector::iterator pos = infixExp.begin();
			pos != infixExp.end();
			pos++
			)
			cout << '\t' << *pos << endl;

		cout << endl << endl;

		ExpressionEvaluator::infixToPostfixConversion(infixExp, postfixExp);

		cout << "# of tokens in the corresponding postfix expression:"
			<< postfixExp.size() << endl
			<< "Tokens of this postfix expression:" << endl;
		for (expVector::iterator pos = postfixExp.begin();
			pos != postfixExp.end();
			pos++
			)
			cout << '\t' << *pos << endl;

		if (ExpressionEvaluator::postfixEvaluator(postfixExp, varTable, expValue))
			cout << "The value of this expression is " << expValue << endl;
		else
			cout << "This expression is not a valid expression" << endl;
	}


	cout << "******************************************************************" << endl;
	cout << "Test 2: on the implementation of infix-expresion evaluation." << endl;
	cout << "******************************************************************" << endl;

	perLineTokenVector tokenExpression;
	rawExpressionString.clear();
	while (rawExpressionString != ".")
	{
		float expValue;
		cout << "Give me an infix expression that may have variables s,t,u,v,w,x,y,z in it."
			<< endl << "OR type in a . to quit" << endl << endl;
		getline(cin, rawExpressionString);
		OriginalScanner::getPerLineTokenVectFromOneStringObject
		(rawExpressionString,
			tokenExpression
		);

		if (ExpressionEvaluator::infixEvaluator(tokenExpression, varTable, expValue))
			cout << "The value of " << rawExpressionString << " is " << expValue << endl;
		else
			cout << rawExpressionString << " not a valid expression" << endl;
	}

}