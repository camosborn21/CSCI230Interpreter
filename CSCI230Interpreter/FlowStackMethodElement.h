#pragma once
#include "FlowStackElement.h"
#include "Interpreter.h"
#include "Rpcdce.h"
class FlowStackMethodElement :
	public FlowStackElement
{
	//add var tables for float and string and vector<id_name> for parameters?
	
public:
	FlowStackMethodElement();
	string name;
	vector<FlowStackElement> methodStatements;
	string returnValue;
	void execute(floatVarValueTable &numericVariables, stringVarValueTable &stringVariables) override;
	void pushStatement(FlowStackElement pushStatement, bool isFinalElement) override;
	~FlowStackMethodElement()=default;
	string Type() override;
};

