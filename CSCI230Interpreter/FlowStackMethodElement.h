#pragma once
#include "FlowStackElement.h"
class FlowStackMethodElement :
	public FlowStackElement
{
public:
	string name;
	vector<FlowStackElement> methodStatements;
	string returnValue;
	void execute(floatVarValueTable &numericVariables, stringVarValueTable &stringVariables);
	
};

