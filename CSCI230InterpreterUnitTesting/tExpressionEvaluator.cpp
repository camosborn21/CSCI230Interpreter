#include "stdafx.h"
#include "CppUnitTest.h"
#include <CppUnitTest.h>
#include "../CSCI230Interpreter/ExpressionEvaluator.h"
#include "../CSCI230Interpreter/OriginalScanner.h"
#include "../CSCI230Interpreter/ProgramUI.h"
#include "../CSCI230Interpreter/targetver.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace CSCI230InterpreterUnitTesting
{		
	static  floatVarValueTable varTable;		
	TEST_CLASS(tExpressionEvaluator)
	{

	public:

		TEST_CLASS_INITIALIZE(setUpTests)
		{
			varTable["r"] = 0;
			varTable["s"] = 1;
			varTable["t"] = 2;
			varTable["u"] = 3;
			varTable["v"] = 4;
			varTable["w"] = 5;
			varTable["x"] = 3.5;
			varTable["y"] = 7;
			varTable["z"] = 8;
		}

		//[11/7/2017 13:04] Cameron Osborn: Test that a set of parenthesis with first character operator will result in invalid expression. Test case found by Zach Leonard. Such that: 1(*3)+4 results in invalid expression. Current architecture results in valid evaluation to 7.
		TEST_METHOD(OpenParenWithOperatorResultsInInvalidExpression) {
			//Arrange
			const string rawExpressionString = "1(*3)+4";
			expVector infixExp,expVector;

			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);
			//float returnedValue;

			//Act
			bool result = ExpressionEvaluator::infixToPostfixConversion(infixExp, expVector);

			//Assert
			Assert::IsFalse(result);
		}


		//[10/2/2017 01:22] Cameron Osborn: Test that a valid, complex infix expression with numeric literals and arithmetic operators evaluates correctly with expected result: 5.0+3.0*(7.0-(4.0/(1.0+2.0))) = 22
		TEST_METHOD(ValidExpressionEvaluatesCorrectly)
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
		}
		//[10/2/2017 01:21] Cameron Osborn: Test that mismatched parentheses throws an error with the expected result: 8+4) evaluates to an error/infixToPostfixConversion=false
		TEST_METHOD(RightParenFailsWithoutLeftParen)
		{
			//Arrange
			const string rawExpressionString = "8+4)";
			expVector infixExp, postfixExp;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			bool result = ExpressionEvaluator::infixToPostfixConversion(infixExp, postfixExp);

			//Assert
			Assert::IsFalse(result);

		}

		TEST_METHOD(RightDoubleParenFailsWithSingleLeftParen)
		{
			//Arrange
			const string rawExpressionString = "(8+4))";
			expVector infixExp, postfixExp;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			bool result = ExpressionEvaluator::infixToPostfixConversion(infixExp, postfixExp);

			//Assert
			Assert::IsFalse(result);

		}
		//[10/2/2017 01:21] Cameron Osborn: Test that an equation with correctly paired parentheses evaluates with expected result: ((8+4)) = 12
		TEST_METHOD(EquationWithParenthesesEvaluates)
		{
			//Arrange
			const string rawExpressionString = "((8+4))";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(12), returnedValue);
		}
		//[10/2/2017 01:20] Cameron Osborn: Test addition with numeric literals with expected result: 8+4=12
		TEST_METHOD(PerformsAddition)
		{
			//Arrange
			const string rawExpressionString = "8+4";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(12), returnedValue);
		}
		//[10/2/2017 01:20] Cameron Osborn: Test subtraction with numeric literals with expected result: 8-4=4
		TEST_METHOD(PerformsSubtraction)
		{
			//Arrange
			const string rawExpressionString = "8-4";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(4), returnedValue);
		}
		//[10/2/2017 01:20] Cameron Osborn: Test multiplication with numeric literals with expected result: 8*4=32
		TEST_METHOD(PerformsMultiplication)
		{
			//Arrange
			const string rawExpressionString = "8*4";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(32), returnedValue);
		}
		//[10/2/2017 01:19] Cameron Osborn: Test division with numeric literals with expected result: 8/4=2
		TEST_METHOD(PerformsDivision)
		{
			//Arrange
			const string rawExpressionString = "8/4";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(2), returnedValue);
		}

		//[10/2/2017 01:19] Cameron Osborn: Test modulo with numeric literals with expected result: 8%3=2
		TEST_METHOD(PerformsModulo)
		{
			//Arrange
			const string rawExpressionString = "8%3";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(2), returnedValue);
		}
		//[10/2/2017 01:18] Cameron Osborn: Test addition with variables with expected result: z=8, v=4   z+v=12
		TEST_METHOD(PerformsAdditionWithVariables)
		{
			//Arrange
			const string rawExpressionString = "z+v";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(12), returnedValue);
		}
		//[10/2/2017 01:18] Cameron Osborn: Test subtraction with variables with expected result: z=8, v=4   z-v=4
		TEST_METHOD(PerformsSubtractionWithVariables)
		{
			//Arrange
			const string rawExpressionString = "z-v";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(4), returnedValue);
		}
		//[10/2/2017 01:16] Cameron Osborn: Test multiplication with variables with expected result: z=8, v=4   z*v=32
		TEST_METHOD(PerformsMultiplicationWithVariables)
		{
			//Arrange
			const string rawExpressionString = "z*v";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(32), returnedValue);
		}
		//[10/2/2017 01:15] Cameron Osborn: Test division with variables with expected result: z=8, v=4   z/v=2
		TEST_METHOD(PerformsDivisionWithVariables)
		{
			//Arrange
			const string rawExpressionString = "z/v";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(2), returnedValue);
		}
		//[10/2/2017 01:15] Cameron Osborn: Test modulo with variables with expected result: z=8, u=3  z%u=2
		TEST_METHOD(PerformsModuloWithVariables)
		{
			//Arrange
			const string rawExpressionString = "z%u";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(2), returnedValue);
		}

		//[10/2/2017 01:20] Cameron Osborn: Test addition between numeric literal and variable with expected result: z=8  z+4=12
		//[10/5/2017 23:16] Cameron Osborn: Extrapolated assumption on success--Variables play well with numeric literals and further compatibility testing between the two is not required
		TEST_METHOD(VariablesPlayNiceWithNumericLiterals)
		{
			//Arrange
			const string rawExpressionString = "z+4";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(12), returnedValue);
		}


		//[10/2/2017 01:29] Cameron Osborn: TEST RELATIONAL OPERATORS SECTION

		//[10/2/2017 01:14] Cameron Osborn: Test relational operator < with expected result: pass for 5<6
		TEST_METHOD(EvaluatesLessThanPass)
		{
			//Arrange
			const string rawExpressionString = "5<6";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:13] Cameron Osborn: Test relational operator < with expected result: fail for 6<5
		TEST_METHOD(EvaluatesLessThanFail)
		{
			//Arrange
			const string rawExpressionString = "6<5";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 01:13] Cameron Osborn: Test relational operator > with expected result: pass for 7>5
		TEST_METHOD(EvaluatesGreaterThanPass)
		{
			//Arrange
			const string rawExpressionString = "7>5";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:13] Cameron Osborn: Test relational operator > with expected result: fail for 5>7
		TEST_METHOD(EvaluatesGreaterThanFail)
		{
			//Arrange
			const string rawExpressionString = "5>7";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}

		//[10/2/2017 01:12] Cameron Osborn: Test relational operator <= with expected result: true for 5<=7
		TEST_METHOD(EvaluatesLessThanEqualTo_True_LessThan)
		{
			//Arrange
			const string rawExpressionString = "5<=7";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:12] Cameron Osborn: Test relational operator <= with expected result: true for 5<=5
		TEST_METHOD(EvaluatesLessThanEqualTo_True_Equal)
		{
			//Arrange
			const string rawExpressionString = "5<=5";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:13] Cameron Osborn: Test relational operator <= with expected result: false for 7<=5
		TEST_METHOD(EvaluatesLessThanEqualTo_False)
		{
			//Arrange
			const string rawExpressionString = "7<=5";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}

		//[10/2/2017 01:12] Cameron Osborn: Test relational operator >= with expected result: true for 7>=5
		TEST_METHOD(EvaluatesGreaterThanEqualTo_True_GreaterThan)
		{
			//Arrange
			const string rawExpressionString = "7>=5";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:12] Cameron Osborn: Test relational operator >= with expected result: true for 7>=7
		TEST_METHOD(EvaluatesGreaterThanEqualTo_True_Equal)
		{
			//Arrange
			const string rawExpressionString = "7>=7";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:13] Cameron Osborn: Test relational operator >= with expected result: false for 5>=7
		TEST_METHOD(EvaluatesGreaterThanEqualTo_False)
		{
			//Arrange
			const string rawExpressionString = "5>=7";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 01:27] Cameron Osborn: Test relational operator == with expected result: true for 5==5 
		TEST_METHOD(EvaluatesExactlyEqualPass)
		{
			//Arrange
			const string rawExpressionString = "5==5";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:27] Cameron Osborn: Test relational operator == with expected result: False for 4==5 
		TEST_METHOD(EvaluatesExactlyEqualFail)
		{
			//Arrange
			const string rawExpressionString = "4==5";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}

		//[10/2/2017 01:28] Cameron Osborn: Test relational operator != with expected result: true for 4!=5
		TEST_METHOD(EvaluatesNotEqualPass)
		{
			//Arrange
			const string rawExpressionString = "4!=5";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:27] Cameron Osborn: Test relational operator != with expected result: False for 5!=5 
		TEST_METHOD(EvaluatesNotEqualFail)
		{
			//Arrange
			const string rawExpressionString = "5!=5";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}



		//[10/2/2017 01:30] Cameron Osborn: TEST RELATIONAL OPERATORS WITH VARIABLES
		//[10/2/2017 01:14] Cameron Osborn: Test relational operator < with variables with expected result: v=4, w=5 pass for v<w
		TEST_METHOD(EvaluatesLessThanPassWithVariables)
		{
			//Arrange
			const string rawExpressionString = "v<w";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:13] Cameron Osborn: Test relational operator < with variables with expected result: v=4, w=5 fail for w<v
		TEST_METHOD(EvaluatesLessThanFailWithVariables)
		{
			//Arrange
			const string rawExpressionString = "w<v";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 01:13] Cameron Osborn: Test relational operator > with variables with expected result: y=7, w=5 pass for y>w
		TEST_METHOD(EvaluatesGreaterThanPassWithVariables)
		{
			//Arrange
			const string rawExpressionString = "y>w";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:13] Cameron Osborn: Test relational operator > with variables with expected result: w=5, y=7 fail for w>y
		TEST_METHOD(EvaluatesGreaterThanFailWithVariables)
		{
			//Arrange
			const string rawExpressionString = "w>y";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}

		//[10/2/2017 01:12] Cameron Osborn: Test relational operator <= with variables with expected result: w=5, y=7 true for w<=y
		TEST_METHOD(EvaluatesLessThanEqualTo_True_LessThanWithVariables)
		{
			//Arrange
			const string rawExpressionString = "w<=y";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:12] Cameron Osborn: Test relational operator <= with variables with expected result: w=5true for w<=w
		TEST_METHOD(EvaluatesLessThanEqualTo_True_EqualWithVariables)
		{
			//Arrange
			const string rawExpressionString = "w<=w";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:13] Cameron Osborn: Test relational operator <= with variables with expected result: w=5, y=7 false for y<=w
		TEST_METHOD(EvaluatesLessThanEqualTo_FalseWithVariables)
		{
			//Arrange
			const string rawExpressionString = "y<=w";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}

		//[10/2/2017 01:12] Cameron Osborn: Test relational operator >= with variables with expected result: w=5, y=7 true for y>=w
		TEST_METHOD(EvaluatesGreaterThanEqualTo_True_GreaterThanWithVariables)
		{
			//Arrange
			const string rawExpressionString = "y>=w";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:12] Cameron Osborn: Test relational operator >= with variables with expected result: y=7 true for y>=y
		TEST_METHOD(EvaluatesGreaterThanEqualTo_True_EqualWithVariables)
		{
			//Arrange
			const string rawExpressionString = "y>=y";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:13] Cameron Osborn: Test relational operator >= with variables with expected result: w=5, y=7 false for w>=y
		TEST_METHOD(EvaluatesGreaterThanEqualTo_FalseWithVariables)
		{
			//Arrange
			const string rawExpressionString = "w>=y";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 01:27] Cameron Osborn: Test relational operator == with variables with expected result: w=5, true for w==w 
		TEST_METHOD(EvaluatesExactlyEqualPassWithVariables)
		{
			//Arrange
			const string rawExpressionString = "w==w";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:27] Cameron Osborn: Test relational operator == with variables with expected result: w=5, v=4 False for v==w 
		TEST_METHOD(EvaluatesExactlyEqualFailWithVariables)
		{
			//Arrange
			const string rawExpressionString = "v==w";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}

		//[10/2/2017 01:28] Cameron Osborn: Test relational operator != with expected result: w=5, v=4 true for v!=w
		TEST_METHOD(EvaluatesNotEqualPassWithVariables)
		{
			//Arrange
			const string rawExpressionString = "v!=w";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:27] Cameron Osborn: Test relational operator != with expected result: w=5 False for w!=w
		TEST_METHOD(EvaluatesNotEqualFailWithVariables)
		{
			//Arrange
			const string rawExpressionString = "w!=w";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}

		//[10/2/2017 01:37] Cameron Osborn: TEST LOGICAL OPERATORS
		//[10/2/2017 01:37] Cameron Osborn: Test logical operator && with expected result: true for 1==1 && 2==2
		TEST_METHOD(EvaluatesLogicalANDOperatorPass)
		{
			//Arrange
			const string rawExpressionString = "1==1&&2==2";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:38] Cameron Osborn: Test logical operator && with expected result: false for 1==0 && 2==2
		TEST_METHOD(EvaluatesLogicalANDOperatorFailOnFirst)
		{
			//Arrange
			const string rawExpressionString = "1==0&&2==2";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 01:40] Cameron Osborn: Test logical operator && with expected result: false for 1==1 && 1==2
		TEST_METHOD(EvaluatesLogicalANDOperatorFailOnSecond)
		{
			//Arrange
			const string rawExpressionString = "1==1&&1==2";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 01:40] Cameron Osborn: Test logical operator && with expected result: false for 1==2 && 1==2
		TEST_METHOD(EvaluatesLogicalANDOperatorFailOnBoth)
		{
			//Arrange
			const string rawExpressionString = "1==2&&1==2";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 01:41] Cameron Osborn: Test logical operator || with expected result: false for 1==2 || 2==3
		TEST_METHOD(EvaluatesLogicalOROperatorFail)
		{
			//Arrange
			const string rawExpressionString = "1==2 || 2==3";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 01:42] Cameron Osborn: Test logical operator || with expected result: true for 2==2||2==3
		TEST_METHOD(EvaluatesLogicalOROperatorPassOnFirst)
		{
			//Arrange
			const string rawExpressionString = "2==2 || 2==3";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:43] Cameron Osborn: Test logical operator || with expected result: true for 2==1 || 3==3
		TEST_METHOD(EvaluatesLogicalOROperatorPassOnSecond)
		{
			//Arrange
			const string rawExpressionString = "2==1 || 3==3";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 01:44] Cameron Osborn: Test logical operator || with expected result: true for 2==2 || 3 == 3
		TEST_METHOD(EvaluatesLogicalOROperatorPassOnEither)
		{
			//Arrange
			const string rawExpressionString = "2==2 || 3 == 3";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}

		//[10/2/2017 01:47] Cameron Osborn: Test logical operator ! with expected result: false for !1 (true)
		TEST_METHOD(EvaluatesLogicalNOTOperatorPassOnTrueToFalse)
		{
			//Arrange
			const string rawExpressionString = "!1";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}

		TEST_METHOD(EvaluatesLogicalNOTOperatorPassOnFalseToTrue)
		{
			//Arrange
			const string rawExpressionString = "!0";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}

		//[10/2/2017 22:33] Cameron Osborn: TEST LOGICAL OPERATORS WITH VARIABLES
		//[10/2/2017 22:33] Cameron Osborn: Added 0 value variable to table.
		//[10/2/2017 22:33] Cameron Osborn: Test logical operator && with variables with expected result: s=1, t=2 true for s==s && t==t
		TEST_METHOD(EvaluatesLogicalANDOperatorPassWithVariables)
		{
			//Arrange
			const string rawExpressionString = "s==s&&t==t";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 22:40] Cameron Osborn: Test logical operator && with variables with expected result: r=0, s=1, t=2 false for s==r && t==t
		TEST_METHOD(EvaluatesLogicalANDOperatorFailOnFirstWithVariables)
		{
			//Arrange
			const string rawExpressionString = "s==r&&t==t";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 22:40] Cameron Osborn: Test logical operator && with variables with expected result: s=1, t=2 false for s==s && s==t
		TEST_METHOD(EvaluatesLogicalANDOperatorFailOnSecondWithVariables)
		{
			//Arrange
			const string rawExpressionString = "s==s&&s==t";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 22:40] Cameron Osborn: Test logical operator && with variables with expected result: s=1, t=2 false for s==t && s==t
		TEST_METHOD(EvaluatesLogicalANDOperatorFailOnBothWithVariables)
		{
			//Arrange
			const string rawExpressionString = "s==t&&s==t";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 22:40] Cameron Osborn: Test logical operator || with variables with expected result: s=1, t=2, u=3 false for s==t || t==u
		TEST_METHOD(EvaluatesLogicalOROperatorFailWithVariables)
		{
			//Arrange
			const string rawExpressionString = "s==t || t==u";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}
		//[10/2/2017 22:40] Cameron Osborn: Test logical operator || with variables with expected result: t=2, u=3  true for t==t||t==u
		TEST_METHOD(EvaluatesLogicalOROperatorPassOnFirstWithVariables)
		{
			//Arrange
			const string rawExpressionString = "t==t||t==u";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 22:39] Cameron Osborn: Test logical operator || with variables with expected result: s=1, t=2, u=3 true for t==s || u==u
		TEST_METHOD(EvaluatesLogicalOROperatorPassOnSecondWithVariables)
		{
			//Arrange
			const string rawExpressionString = "t==s || u==u";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
		//[10/2/2017 22:39] Cameron Osborn: Test logical operator || with variables with expected result: t=2, u=3 true for t==t || u == u
		TEST_METHOD(EvaluatesLogicalOROperatorPassOnEitherWithVariables)
		{
			//Arrange
			const string rawExpressionString = "t==t || u == u";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}

		//[10/2/2017 22:39] Cameron Osborn: Test logical operator ! with variables with expected result: s=1 false for !s (true)
		TEST_METHOD(EvaluatesLogicalNOTOperatorPassOnTrueToFalseWithVariables)
		{
			//Arrange
			const string rawExpressionString = "!s";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(0), returnedValue);
		}

		//[10/2/2017 22:38] Cameron Osborn: Test logical operator ! with variables with expected result: r=0 true for !r (false)
		TEST_METHOD(EvaluatesLogicalNOTOperatorPassOnFalseToTrueWithVariables)
		{
			//Arrange
			const string rawExpressionString = "!r";
			expVector infixExp;
			float returnedValue;
			OriginalScanner::getPerLineTokenVectFromOneStringObject(rawExpressionString, infixExp);

			//Act
			ExpressionEvaluator::infixEvaluator(infixExp, varTable, returnedValue);

			//Assert
			Assert::AreEqual(static_cast<float>(1), returnedValue);
		}
	};
}