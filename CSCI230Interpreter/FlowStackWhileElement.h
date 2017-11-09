#pragma once
#include "FlowStackElement.h"
class FlowStackWhileElement :
	public FlowStackElement
{
public:
	vector<FlowStackElement> loopingStatements;
	void execute(floatVarValueTable &numericVariables, stringVarValueTable &stringVariables);
};

