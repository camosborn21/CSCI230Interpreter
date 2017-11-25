#pragma once
#include "FlowStackElement.h"
class FlowStackWhileElement :
	public FlowStackElement
{
public:
	vector<FlowStackElement> loopingStatements;
	 void execute(floatVarValueTable &numericVariables, stringVarValueTable &stringVariables) override;
	 void pushStatement(FlowStackElement pushStatement, bool isFinalElement) override;
	~FlowStackWhileElement() = default;
	string Type() override;
};

