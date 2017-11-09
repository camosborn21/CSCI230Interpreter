#pragma once
#include "FlowStackElement.h"
class FlowStackIfElement :
	public FlowStackElement
{
public:
	vector<FlowStackElement> IfStatements;
	vector<FlowStackElement> ElseStatements;
	void execute(floatVarValueTable &numericVariables, stringVarValueTable &stringVariables);
};

