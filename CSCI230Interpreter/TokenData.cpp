#include "stdafx.h"
#include "TokenData.h"

TokenData::TokenData(string value)
{
	_tokenValue = value;
}
TokenData::TokenData(string value, tokenCategory category)
{
	_tokenValue = value;
	_category = category;
}
