#include "stdafx.h"
#include "Interpreter.h"

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
	if (lines.size == 0) {

	}
	OriginalScanner::getLexicalInfo(lines, tokenVectorsForAllLines, categoryVectorsForAllLines);
}
