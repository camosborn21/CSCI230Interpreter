#include "stdafx.h"
#include "FlowStackElement.h"

FlowStackElement::FlowStackElement()
{
	isMultilineCompound = false;
}

void FlowStackElement::execute(floatVarValueTable &numericVariables, stringVarValueTable &stringVariables)
{
	//[11/9/2017 12:20] Cameron Osborn: This will execute the basic display, read, and assignment statements? OR subclass those statements as well?

}

string FlowStackElement::Type()
{
	return "basic_element";
}

void FlowStackElement::pushStatement(FlowStackElement pushStatement, bool isFinalElement)
{
}

