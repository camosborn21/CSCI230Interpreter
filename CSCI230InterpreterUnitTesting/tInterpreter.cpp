#include "stdafx.h"
#include "tInterpreter.h"
#include "CppUnitTest.h"
#include"../CSCI230Interpreter/ExpressionEvaluator.h"
#include "../CSCI230Interpreter/OriginalScanner.h"
#include "../CSCI230Interpreter/ProgramUI.h"
#include "../CSCI230Interpreter/Interpreter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace CSCI230InterpreterUnitTesting
{
	Interpreter terp;
	//ProgramUI ui;
	/*vector<string>testCase1;
	vector<string>testCase2;
	vector<string>testCase3;
	vector<string>testCase4;*/
	TEST_CLASS(tInterpreter)
	{
	private:


	public:
		TEST_CLASS_INITIALIZE(tInterpreter_SetUp)
		{
			/*testCase1.push_back("display \"************************************************\";");
			testCase1.push_back("display \"Want to determine the volume of a right circular cylinder!\";");
			testCase1.push_back("display \"\";");
			testCase1.push_back("display \"What is the height of the cylinder ? \";");
			testCase1.push_back("read height;");
			testCase1.push_back("display \"What is the radius of the cylinder ? \";");
			testCase1.push_back("read radius;");
			testCase1.push_back("volume = 3.14* radius * radius * height;");
			testCase1.push_back("display \"\";");
			testCase1.push_back("display \"The volume of the cylinder is \", volume;");
			testCase1.push_back("display \"************************************************\";");*/




		}

		//[11/26/2017 02:56] Cameron Osborn: Validate the parser and syntax checker can successfully build the code from testCylinder1.txt
		TEST_METHOD(BuildSucceedsOnTestCylinder1)
		{
			//Arrange
			vector<string> testCase1;
			testCase1.push_back("display \"************************************************\";");
			testCase1.push_back("display \"Want to determine the volume of a right circular cylinder!\";");
			testCase1.push_back("display \"\";");
			testCase1.push_back("display \"What is the height of the cylinder ? \";");
			testCase1.push_back("read height;");
			testCase1.push_back("display \"What is the radius of the cylinder ? \";");
			testCase1.push_back("read radius;");
			testCase1.push_back("volume = 3.14* radius * radius * height;");
			testCase1.push_back("display \"\";");
			testCase1.push_back("display \"The volume of the cylinder is \", volume;");
			testCase1.push_back("display \"************************************************\";");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		//[11/26/2017 02:56] Cameron Osborn: Validate the parser and syntax checker can successfully build the code from testCylinder2.txt
		TEST_METHOD(BuildSucceedsOnTestCylinder2)
		{
			//Arrange
			vector<string> testCase1;
			testCase1.push_back("display \"************************************************\";");
			testCase1.push_back("display \"Want to determine the volume of a right circular cylinder!\";");
			testCase1.push_back("display \"\";");
			testCase1.push_back("display \"What is the height of the cylinder ? \";");
			testCase1.push_back("read height;");
			testCase1.push_back("display \"What is the radius of the cylinder ? \";");
			testCase1.push_back("read radius;");
			testCase1.push_back("display \"\";");
			testCase1.push_back("display \"The volume of the cylinder is \", 3.14* radius * radius * height;");
			testCase1.push_back("display \"************************************************\";");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		//[11/26/2017 02:57] Cameron Osborn: Validate that the parser can build the code from testCylinder3.txt and that the syntax check fails with 3 errors. Implementation test that these three errors print from line 8 for invalid variable.
		TEST_METHOD(BuildFailsOnTestCylinder3With3Errors)
		{
			//Arrange
			vector<string> testCase1;
			testCase1.push_back("display \"************************************************\";");
			testCase1.push_back("display \"Want to determine the volume of a right circular cylinder!\";");
			testCase1.push_back("display \"\";");
			testCase1.push_back("display \"What is the height of the cylinder ? \";");
			testCase1.push_back("read height;");
			testCase1.push_back("display \"What is the radius of the cylinder ? \";");
			testCase1.push_back("read radius;");
			testCase1.push_back("volume = 3.14* r * r * h;");
			testCase1.push_back("display \"\";");
			testCase1.push_back("display \"The volume of the cylinder is \", volume;");
			testCase1.push_back("display \"************************************************\";");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(3, terp.GetErrorCount());
		}
		//[11/26/2017 02:58] Cameron Osborn: Validate that the parser can build the code from testCylinder4.txt and that the syntax check fails with 2 errors. Implementation test that these two errors print from lines 8 and 10 for invalid first token and invalid variable respectively.
		TEST_METHOD(BuildFailsOnTestCylinder4With2Errors)
		{
			//Arrange
			vector<string> testCase1;
			testCase1.push_back("display \"************************************************\";");
			testCase1.push_back("display \"Want to determine the volume of a right circular cylinder!\";");
			testCase1.push_back("display \"\";");
			testCase1.push_back("display \"What is the height of the cylinder ? \";");
			testCase1.push_back("read height;");
			testCase1.push_back("display \"What is the radius of the cylinder ? \";");
			testCase1.push_back("read radius;");
			testCase1.push_back("3.14* r * r * h = volume;");
			testCase1.push_back("display \"\";");
			testCase1.push_back("display \"The volume of the cylinder is \", volume;");
			testCase1.push_back("display \"************************************************\";");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		//[11/26/2017 02:59] Cameron Osborn: Baseline test ==> ensure that display token can be successfully identified at the beginning of the statement.
		TEST_METHOD(ValidateForBeginningOfStatement_Display_Succeeds)
		{
			//Arrange
			vector<string> testCase1;
			testCase1.push_back("display \"************************************************\";");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		//[11/26/2017 02:59] Cameron Osborn: Baseline test ==> ensure that read token can be successfully identified at the beginning of the statement.
		TEST_METHOD(ValidateForBeginningOfStatement_Read_Succeeds)
		{
			//Arrange
			vector<string> testCase1;
			testCase1.push_back("read height;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		//[11/26/2017 03:00] Cameron Osborn: Baseline test ==> ensure that IDName token can be successfully identified at the beginning of the statement.
		TEST_METHOD(ValidateForBeginningOfStatement_IDName_Succeeds)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 3.14;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
			//Assert::AreEqual(0, terp.GetErrorCount());
		}

		//[11/26/2017 04:12] Cameron Osborn: Validate that all illegal token categories at the beginning of a statement will throw an error. 29 errors expected.
		TEST_METHOD(ValidateForBeginningOfStatement_AllNonValidTokens_Fail)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check numeric literal at start of statement (1 error)
			testCase1.push_back("3.14* r * r * h = volume;");
			//[11/26/2017 03:38] Cameron Osborn: perhaps of note but this will only throw an error for invalid starting token. After that point it doesn't parse the rest of the line because it won't know which rules to follow which means this has no idea that the variable names given there are invalid.

			//[11/26/2017 03:41] Cameron Osborn: Check for invalid keywords at start of statement(5 errors)
			testCase1.push_back("while(1);");
			testCase1.push_back("function main();");
			testCase1.push_back("if(1);");
			testCase1.push_back("else;");
			testCase1.push_back("return;");

			//[11/26/2017 03:42] Cameron Osborn: Check for invalid logical operators at the start of statement(3 errors)
			testCase1.push_back("!1;");
			testCase1.push_back("||8;");
			testCase1.push_back("&&8;");

			//[11/26/2017 03:51] Cameron Osborn: Check for invalid relational operators at the start of statement(6 errors)
			testCase1.push_back(">8;");
			testCase1.push_back("==8;");
			testCase1.push_back("<8;");
			testCase1.push_back(">=8;");
			testCase1.push_back("<=8;");
			testCase1.push_back("!=8;");

			//[11/26/2017 03:53] Cameron Osborn: Check for invalid Numeric operators at the start of statement(5 errors)
			testCase1.push_back("+8;");
			testCase1.push_back("-8;");
			testCase1.push_back("*8;");
			testCase1.push_back("/8;");
			testCase1.push_back("%8;");

			//[11/26/2017 03:55] Cameron Osborn: Check for invalid assignment operator (=) at the start of the statement (1 error)
			testCase1.push_back("=8;");

			//[11/26/2017 03:56] Cameron Osborn: Check for invalid string literal at the start of the statement(1 error)
			testCase1.push_back("\"Here's some text\";");

			//[11/26/2017 03:58] Cameron Osborn: Check for invalid language reserved characters at the start of the statement(7 errors)
			testCase1.push_back("(8;");
			testCase1.push_back(")8;");
			testCase1.push_back("{8;");
			testCase1.push_back("}8;");
			testCase1.push_back(";8;");
			testCase1.push_back(":8;");
			testCase1.push_back(",8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(29, terp.GetErrorCount());
		}

		//[11/26/2017 04:13] Cameron Osborn: Validate that the second character of an assignment operation must be the assignment operator (=). If so, pass. If not, throw 1 error.
		TEST_METHOD(AssignmentOpSecondCharacterIsEquals)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 3.14;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);

			//Arrange
			vector<string>testCase2;
			testCase2.push_back("volume * 3.14;");

			//Act
			terp.parseSourceCode(testCase2, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		//[11/26/2017 04:13] Cameron Osborn: Test that the variable table size is 1 after assignment operation.
		TEST_METHOD(AssignmentOpAddsNewVariableToVariableTable)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 3.14;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetVariableCount());
		}

		//[11/26/2017 04:14] Cameron Osborn: Validate that the read keyword must be followed by an ID_NAME Token. 
		TEST_METHOD(ReadOpFollowedByNonVariableName)
		{
			//[11/26/2017 04:10] Cameron Osborn: First A3 covered above but rerun here for simplicity of code coverage eval.
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("read height;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);

			//Arrange
			vector<string>testCase2;
			testCase2.push_back("read 3.14;");

			//Act
			terp.parseSourceCode(testCase2, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		//[11/26/2017 04:15] Cameron Osborn: Validate that the variable table size is 1 after read operation.
		TEST_METHOD(ReadOpAddsNewVariableToVariableTable)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("read volume;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetVariableCount());
		}
		//[11/26/2017 04:17] Cameron Osborn: Read op must be exactly three tokens long. 'read' keyword, ID_Name, semicolon. Any more or less should throw an error.
		TEST_METHOD(ValidateReadOpIsThreeTokensLong)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("read height;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);

			//Arrange
			vector<string>testCase2;
			testCase2.push_back("read height");

			//Act
			terp.parseSourceCode(testCase2, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			//[11/26/2017 04:18] Cameron Osborn: Must throw 2 errors. Missing semicolon on end of statement and read statement not three tokens long.
			Assert::AreEqual(2, terp.GetErrorCount());

			//Arrange
			vector<string>testCase3;
			testCase3.push_back("read height width;");

			//Act
			terp.parseSourceCode(testCase3, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());

		}

		//[11/26/2017 12:17] Cameron Osborn: Display op must be followed by ID name, string literal, numerical literal,  logical NOT operator, or left parenthesis.
		TEST_METHOD(DisplayCanBeFollowedByNumericLiteral)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check numeric literal after display statement. Should Pass.
			testCase1.push_back("display 3.14;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);

		}
		
		//[11/26/2017 12:17] Cameron Osborn: Display op must be followed by ID name, string literal, numerical literal,  logical NOT operator, or left parenthesis.
		TEST_METHOD(DisplayCanBeFollowedByLeftParenthesis)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check variable name after display statement. variable name must be initialized first. Should pass.
			testCase1.push_back("display (3+2)*5;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		//[11/26/2017 12:17] Cameron Osborn: Display op must be followed by ID name, string literal, numerical literal,  logical NOT operator, or left parenthesis.
		TEST_METHOD(DisplayCanBeFollowedByStringLiteral)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check variable name after display statement. variable name must be initialized first. Should pass.
			testCase1.push_back("display \"Heres some text\";");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		//[11/26/2017 12:17] Cameron Osborn: Display op must be followed by ID name, string literal, numerical literal,  logical NOT operator, or left parenthesis.
		TEST_METHOD(DisplayCanBeFollowedByIdName)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check variable name after display statement. variable name must be initialized first. Should pass.
			testCase1.push_back("radius = 2;");
			testCase1.push_back("display radius;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		//[11/26/2017 12:17] Cameron Osborn: Display op must be followed by ID name, string literal, numerical literal,  logical NOT operator, or left parenthesis.
		TEST_METHOD(DisplayCanBeFollowedByLogicalNotOperator)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check variable name after display statement. variable name must be initialized first. Should pass.
			testCase1.push_back("display !1;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}



		//[11/27/2017 01:57] Cameron Osborn: Verify all invalid tokens following the display statement are caught. Some will throw a double error because the token is outright disallowed in a display statement so when the syntax check gets to that token it will throw a secondary error.
		TEST_METHOD(DisplayCannotBeFollowedByInvalidToken)
		{
			//[11/27/2017 04:01] Cameron Osborn: LEFT OFF HERE. This isn't working.
			//Arrange
			vector<string> testCase1;


			//[11/26/2017 03:41] Cameron Osborn: Check for invalid keywords after the display token (10 errors)
			//[11/27/2017 01:37] Cameron Osborn: Errors double up in this section since keywords can't be used outside of the first token in a statement.
			testCase1.push_back("display while;");
			testCase1.push_back("display function;");
			testCase1.push_back("display if;");
			testCase1.push_back("display else;");
			testCase1.push_back("display return;");

			//[11/26/2017 03:42] Cameron Osborn: Check for invalid logical operators after the display token(2 errors). Unary operators (logical NOT) can follow the display statement.			
			testCase1.push_back("display || 8;");
			testCase1.push_back("display && 8;");


			//[11/26/2017 03:51] Cameron Osborn: Check for invalid relational operators after the display token(6 errors)
			testCase1.push_back("display > 8;");
			testCase1.push_back("display == 8;");
			testCase1.push_back("display < 8;");
			testCase1.push_back("display >= 8;");
			testCase1.push_back("display <= 8;");
			testCase1.push_back("display != 8;");

			//[11/26/2017 03:53] Cameron Osborn: Check for invalid Numeric operators after the display token(5 errors)
			testCase1.push_back("display +8;");
			testCase1.push_back("display -8;");
			testCase1.push_back("display *8;");
			testCase1.push_back("display /8;");
			testCase1.push_back("display %8;");

			//[11/26/2017 03:58] Cameron Osborn: Check for invalid language reserved characters after the display token(10 errors)
			
			testCase1.push_back("display );"); // expect 1 error
			testCase1.push_back("display {;"); // expect 2 errors: second comes from invalid token in display statement
			testCase1.push_back("display };"); // expect 2 errors: second comes from invalid token in display statement
			testCase1.push_back("display ;;"); // expect 2 errors: second comes from invalid token in display statement
			testCase1.push_back("display :;"); // expect 2 errors: second comes from invalid token in display statement
			testCase1.push_back("display ,;"); // expect 1 error


			//[11/26/2017 03:55] Cameron Osborn: Check for invalid assignment operator (=) at the start of the statement (2 errors)
			//First error from invalid token after display, second error from invalid use of assignment operator.
			testCase1.push_back("display = 8;");



			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(35, terp.GetErrorCount());
		}
	};
}
