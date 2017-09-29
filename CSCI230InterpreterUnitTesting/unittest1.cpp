#include "stdafx.h"
#include "CppUnitTest.h"
#include <CppUnitTest.h>
#include "..\CSCI230Interpreter\ExpressionEvaluator.h"
#include "..\CSCI230Interpreter\OriginalScanner.h"
#include "..\CSCI230Interpreter\ProgramUI.h"
#include "..\CSCI230Interpreter\targetver.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace CSCI230InterpreterUnitTesting
{		
	TEST_CLASS(UnitTest1)
	{
	private:
		
	public:
		floatVarValueTable varTable;
		TEST_CLASS_INITIALIZE(setUpTests)
		{
			
	/*		varTable["s"] = 1;
			varTable["t"] = 2;
			varTable["u"] = 3;
			varTable["v"] = 4;
			varTable["w"] = 5;
			varTable["x"] = 3.5;
			varTable["y"] = 7;
			varTable["z"] = 8;*/
		}
		TEST_METHOD(TestMethod1)
		{
			//Arrange
			const string rawExpressionString = "5.0+3.0*(7.0-(4.0/(1.0 + 2.0)))";
			expVector infixExp;
			
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);
			float returnedValue;
			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(22), returnedValue);

			//Assert::AreEqual(1, 1);
		}

	};
}