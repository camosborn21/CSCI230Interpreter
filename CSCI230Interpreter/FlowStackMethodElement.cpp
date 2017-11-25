#include "stdafx.h"
#include "FlowStackMethodElement.h"

FlowStackMethodElement::FlowStackMethodElement()
{
	UUID* uniqueSerial = new UUID;
	UuidCreate(uniqueSerial);
	UuidToString(uniqueSerial, serial);
}

void FlowStackMethodElement::execute(floatVarValueTable & numericVariables, stringVarValueTable & stringVariables)
{
	//blockFloatVariables.insert(make_pair("string", 123));
}

void FlowStackMethodElement::pushStatement(FlowStackElement pushStatement, bool isFinalElement)
{
}


string FlowStackMethodElement::Type()
{
	return "method_element";
}
