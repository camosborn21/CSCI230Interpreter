#include "stdafx.h"
#include "Scanner.h"
#include <iostream>
#include <cctype>
using namespace std;
const char DOUBLE_QUOTE = '\"';




//
//Scanner::Scanner()
//{
//}
//
//
//Scanner::~Scanner()
//{
//}

//***************************************************************************
//*  Section 1. two functions: 
//*  getPerLineTokenVectFromOneCharArray and 
//*	 getPerLineTokenVectFromOneStringObject
//*
//***************************************************************************
//*  They analyze one C-style character array or a string object and 
//*  collect the tokens there as a vetor of token strings.
//***************************************************************************
void Scanner::getPerLineTokenVectFromOneCharArray(const char * ptrOriginalStatement, perLineTokenVector & tokenVector)
// 1. One line of code is stored in a C-style character array: statement, 
//    with a terminating '\0' NULL character to end the string stored there.
// 2. In the end, we'll store all the tokens, each as an object of the string class,
//    in tokenVector, which is a vector of strings.
{
	string statement;
	while ((*ptrOriginalStatement) != NULL) {
		if (isspace(*ptrOriginalStatement))
			//Convert every white space characters into a space ' '
			//	and append it to the end of statement;
			statement = statement + ' ';

		else
			//Append a character as it is to the end of statement;
			statement = statement + (*ptrOriginalStatement);

		++ptrOriginalStatement;
	}

	string tokenBuffer;
	//reserve an initial storage of 200 characters
	tokenBuffer.reserve(200);

	size_t iBuffIndex = 0; // index into the statement string


	//A while loop that normalizes the statement string
	//into an equaivalent string with one space between two adjacent tokens.
	while (iBuffIndex < statement.size())
		//While it is not the end of the character string stored in the statement array
	{
		//[9/21/2017 12:26] Cameron Osborn: set up the current character examination and detect what the next character is
		char c, nextChar;
		c = statement[iBuffIndex];
		if (iBuffIndex + 1 < statement.size())
			nextChar = statement[iBuffIndex + 1];
		else
			nextChar = ' ';

		if (c == DOUBLE_QUOTE)
			//if a double quote is encountered, search for the matching double quote 
			//and skip the entire string literal like "Hello" enclosed in 
			//the pair of double quotes.
		{
			tokenBuffer += DOUBLE_QUOTE;
			//Copy the starting double quote into token buffer

			iBuffIndex++;
			c = statement[iBuffIndex];
			while (c != NULL && c != DOUBLE_QUOTE)
				//Search for a matching double quote or a terminating NULL character.
				//Append all achracters in between into tokenBuffer
			{
				tokenBuffer += c;
				iBuffIndex++;
				c = statement[iBuffIndex];

			}
			tokenBuffer += DOUBLE_QUOTE;
			//Copy the endinging double quote into token buffer

		}
		else  //The character examined is not a double quote.
	// In the following id statement,
	// we try to detect the end (last character) of a token in the statement array.
	// We insert a space appropriately into the components string to make sure 
	// in the components string there is at least one space between two tokens. 
		{
			if (
				((isalnum(c) || c == '.') &&
					!(isalnum(nextChar) || nextChar == '.'))
				// If the current character c is alphnumerical character or a dot
				// (i.e. a letter ot a digit), but the next character is not.
				||
				((c == '=') && (nextChar != '='))
				// equal sign, but not followed by another equal sign 
				||
				c == ',' || c == ':' || c == ';'
				// comma, colon, semicolon 
				||
				c == '+' || c == '-' || c == '*' || c == '%'
				// numerical operators: +,-, *, %
				||
				((c == '/') && (nextChar != '/'))
				// numerical operator: / but not followed by /
				||
				((c == '>') && (nextChar != '='))
				// relational operator: > but not followed by =
				||
				((c == '<') && (nextChar != '='))
				// relational operator: < but not followed by =
				||
				((c == '&') && (nextChar != '&'))
				// end of logical operator: && 
				||
				((c == '|') && (nextChar != '|'))
				// end of logical operator: ||
				||
				((c == '!'))
				// end of logical operator: !
				||
				(c == '(' || c == ')')
				// parenthesis
				||
				(c == '{' || c == '}')
				// curly braces
				)
				//We detect c as the end of a token.
			{
				// Copy the character c from statement array i
				// and append it into the end of of the token components string.
				tokenBuffer += c;

				// If the next character is not a space,
				// append a space to the end of components to make sure
				// in components there is at least one space between two tokens.
				if (nextChar != ' ')
					tokenBuffer += ' ';
			}
			else
				// c is not the end of a token
			{
				if (c != ' ')
					// c is not a space, but a part of a token while not the end of the token.
					// So just copy the character c from statement array i
					// and append it into the end of of the token components string.
					tokenBuffer += c;
				else
				{
					if (c == ' ' && nextChar != ' ')
						// c is a space, but the next character is not a space.
						// append a space to the end of components to make sure
						// in components there is at least one space between two tokens.
						tokenBuffer += ' ';
				}
			}

			if (c != NULL)
				//If the character we just finish examining is not the terminating NULL,
				//prepare to examine the next character on the next iteration.
				iBuffIndex++;
			//else we have reached a NULL character signaling the end of the statement.

			//Prepare to check the next character in the statement array.
		}

	}
	//end of while loop that normalizes the statement in the character array
	//into an equaivalent string with one space between two adjacent tokens.

	size_t startIndex; // The index of the beginning of a token
	size_t endIndex;   // The index of the end of a token

	bool keepChecking;
	//Detect the first NON-SPACE character in the string.
	//Set startIndex as the index this character or
	//set it as the length of the string if the entire string is composed of spaces.
	for (startIndex = 0, keepChecking = true; startIndex < tokenBuffer.size() && keepChecking;)
		if (tokenBuffer[startIndex] != ' ')
			keepChecking = false;
		else
			startIndex++;

	tokenVector.clear();

	while (startIndex < tokenBuffer.size()) {
		if (tokenBuffer[startIndex] == DOUBLE_QUOTE) 
			//If the token is a string LITERAL like "YES" started with a double quote,
			//search for the matching double quote after the index startIndex.
			//Set endIndex as the index after that of the matching double quote.
		{
			for (endIndex = startIndex + 1, keepChecking = true; endIndex < tokenBuffer.size() && keepChecking; endIndex++)
				if (tokenBuffer[endIndex] == DOUBLE_QUOTE)
					keepChecking = false;
		}
		else
			//If the token is not started with a double quote,
			//Detect the first SPACE character after the index startIndex.
			//Set endIndex as the index this space character or
			//set it as the length of the string 
			//if none such space exists after the index startIndex.
		{
			for (endIndex = startIndex + 1, keepChecking = true; endIndex < tokenBuffer.size() && keepChecking;)
				if (tokenBuffer[endIndex] == ' ')
					keepChecking = false;
				else
					endIndex++;
		}
		//tokenBuffer.substr(startIndex, endIndex - startIndex) is a token.
		//Append such a token in the token vector to tokenVector
		//[9/21/2017 13:10] Cameron Osborn: this needs to change because at this point tokenVector isn't taking a string any more, it's taking a token data object
		tokenVector.push_back(tokenBuffer.substr(startIndex, endIndex - startIndex));
		

		//Detect the next non-space character with an index after current endIndex.
		//Set startIndex as the index this character or
		//set it as the length of the string if the reaminder of the string 
		//is entirely composed of spaces.
		for (startIndex = endIndex, keepChecking = true; startIndex < tokenBuffer.size() && keepChecking;)
			if (tokenBuffer[startIndex] != ' ')
				keepChecking = false;
			else
				startIndex++;
	}

}
