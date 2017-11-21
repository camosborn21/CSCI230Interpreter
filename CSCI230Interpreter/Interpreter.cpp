#include "stdafx.h"
#include "Interpreter.h"
#include <iostream>
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
	//[11/21/2017 01:26] Cameron Osborn: For Each Line
	vector<SourceCodeToken> sourceCodeTokens;
	for (size_t i = 0; i < tokenVectorsForAllLines.size(); i++)
	{
		perLineTokenVector tokenVect = tokenVectorsForAllLines[i];
		perLineCategoryVector categoryVect = categoryVectorsForAllLines[i];
		//[11/21/2017 02:14] Cameron Osborn: for each token: create source code token.
		for (size_t j = 0; j < tokenVect.size(); j++)
		{

			sourceCodeTokens.push_back( new SourceCodeToken(tokenVect[j], categoryVect[j], i, j));
		}





		if (checkSourceCodeContainsFunctions())
		{
			//[11/21/2017 01:56] Cameron Osborn: No need to check token vs category length as it's already confirmed in the SourceCodeContainsFunction check.


		}
		else
		{

		}



	}

}


bool Interpreter::checkTokenVsCategoryLengthParsingError(perLineTokenVector checkTokenVect, perLineCategoryVector checkCategoryVect, int lineNumber)
{

	if (checkTokenVect.size() != checkCategoryVect.size())
	{
		//[11/21/2017 01:35] Cameron Osborn: Scanner Error
		cout << "PARSING ERROR" << endl << "Line " << lineNumber << ": # of tokens inconsisten with # of category labels." << endl;
		return false;
	}
	return true;
}

bool Interpreter::checkSourceCodeContainsFunctions()
{
	for (size_t i = 0; i < tokenVectorsForAllLines.size(); i++)
	{
		perLineTokenVector tokenVect = tokenVectorsForAllLines[i];
		perLineCategoryVector categoryVect = categoryVectorsForAllLines[i];

		//[11/21/2017 01:45] Cameron Osborn: check parsing validity of current line
		if (checkTokenVsCategoryLengthParsingError(tokenVect, categoryVect, i) != true)
			return false;

		for (size_t j = 0; j < tokenVect.size(); j++)
		{
			if (categoryVect[j] == KEYWORD && tokenVect[j] == "function")
				return true;
		}
	}
	return false;
}
