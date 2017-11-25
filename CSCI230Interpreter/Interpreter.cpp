#include "stdafx.h"
#include "Interpreter.h"
#include <iostream>
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

void Interpreter::printErrors()
{
}

void Interpreter::execute()
{
}

void Interpreter::parseSourceCode(vector<string> lines, bool displayErrorsAfterParse, bool executeAfterParse)
{
	//[11/25/2017 14:13] Cameron Osborn: Get lexical analysis of all statements in program
	if (lines.size > 0) {
		OriginalScanner::getLexicalInfo(lines, tokenVectorsForAllLines, categoryVectorsForAllLines);
	}

	//[11/25/2017 14:14] Cameron Osborn: Convert statements to source code tokens for ease of use and filter out comments
	Statement currentStatement;
	for (size_t i=0; i<tokenVectorsForAllLines.size();i++)
	{
		if (currentStatement.Tokens.size() > 0)
		{
			statements.push_back(currentStatement);
			currentStatement.Tokens.clear();
		}
		if (tokenVectorsForAllLines[i].size() != categoryVectorsForAllLines[i].size())
		{
			cout << "Line " << i << ": # of tokens inconsisten with # of category labels." << endl;
			return;
		}

		for (size_t j=0; j<tokenVectorsForAllLines[i].size(); j++)
		{
			
		}

	}
}
