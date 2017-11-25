#pragma once
#include <string>
#include "Interpreter.h"

using namespace std;
class FlowStackElement
{
private:
	
public:
	FlowStackElement();
	virtual ~FlowStackElement() = default;
	vector<SourceCodeToken> statement;
	unsigned short** serial;
	virtual void execute(floatVarValueTable &numericVariables, stringVarValueTable &stringVariables);
	virtual string Type();
	virtual void pushStatement(FlowStackElement pushStatement, bool isFinalElement) ;
	floatVarValueTable blockFloatVariables;
	stringVarValueTable blockStringVariables;
	bool isMultilineCompound;
};
