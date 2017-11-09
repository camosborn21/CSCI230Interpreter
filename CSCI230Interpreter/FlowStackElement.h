#pragma once
#include <string>
#include "Interpreter.h"

using namespace std;
class FlowStackElement
{
public:
	vector<SourceCodeToken> statement;
	string serial;
	void execute(floatVarValueTable &numericVariables, stringVarValueTable &stringVariables);

};
