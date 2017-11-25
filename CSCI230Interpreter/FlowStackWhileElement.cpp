#include "stdafx.h"
#include "FlowStackWhileElement.h"

void FlowStackWhileElement::execute(floatVarValueTable & numericVariables, stringVarValueTable & stringVariables)
{
}

void FlowStackWhileElement::pushStatement(FlowStackElement pushStatement, bool isFinalElement)
{
	if (statement.size() == 0)
	{
		statement = pushStatement.statement;
		//validate statement evaluates boolean?
	}
	else
	{
		loopingStatements.push_back(pushStatement);
	}
}




string FlowStackWhileElement::Type()
{
	return "while_element";
}
