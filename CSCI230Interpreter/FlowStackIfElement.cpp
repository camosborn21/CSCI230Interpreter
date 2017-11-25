#include "stdafx.h"
#include "FlowStackIfElement.h"



void FlowStackIfElement::execute(floatVarValueTable & numericVariables, stringVarValueTable & stringVariables)
{
}

void FlowStackIfElement::pushStatement(FlowStackElement pushStatement, bool isFinalElement)
{
	if (statement.size == 0)
	{
		statement = pushStatement.statement;
	}
	else
	{
		if (ifSegmentComplete == false)
		{
			if (pushStatement.statement.size() != 0)
				IfStatements.push_back(pushStatement);
		}
		else
		{
			if (pushStatement.statement.size() != 0)
				ElseStatements.push_back(pushStatement);
		}
	}
	if (isFinalElement)
		ifSegmentComplete = true;
}

//void FlowStackIfElement::pushStatement(vector<SourceCodeToken> statement)
//{
//	//THIS IS NOT GOING TO WORK*****
//	//if (this->statement.size() == 0)
//	//{
//	//	this->statement = statement;
//	//} else
//	//{
//	//	if(this->IfStatements.size()==0)
//	//	{
//	//		
//	//	}
//	//}
//	//*****
//	//IT NEEDS TO HAVE A FLOW STACK ELEMENT PASSED IN
//}

string FlowStackIfElement::Type()
{
	return "if_element";
}
