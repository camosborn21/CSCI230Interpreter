#pragma once
#include <string>
#include "Interpreter.h"
class FlowStackElement
{
public:
	vector<SourceCodeToken> statement;
	std::string serial;
	void execute();

};
