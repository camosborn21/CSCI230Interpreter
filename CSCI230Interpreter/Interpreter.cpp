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
			if (categoryVect[j] != COMMENT || categoryVect[j] != COMMENT_TEXT)
				currentStatement.Tokens.push_back(SourceCodeToken(tokenVect[j], categoryVect[j], i, j));
		}
	}
	checkSyntax();

}

void Interpreter::checkSyntax()
{
	
	for(vector<Statement>::iterator iter = statements.begin(); iter<statements.end(); ++iter)
	{
		for(vector<SourceCodeToken>::iterator token = iter->Tokens.begin(); token<iter->Tokens.end(); ++token)
		{
			//[11/25/2017 14:47] Cameron Osborn: First token must be either 'display', 'read', or ID_NAME
			if(token==iter->Tokens.begin())
			{
				
			}
			else
			{
				//[11/25/2017 14:48] Cameron Osborn: now we're on subsequent tokens
			}
		}
	}
}
