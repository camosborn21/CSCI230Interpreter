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

tokenCategory TokenData::Category()
{
	return _category;
}

string TokenData::Token()
{
	return _tokenValue;
}

void TokenData::ParseToken()
{

}

void TokenData::TokenIsCommentText()
{
	_category = COMMENT_TEXT;
}
