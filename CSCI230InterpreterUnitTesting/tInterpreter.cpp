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
		TEST_METHOD(AssignmentOpSecondCharacterIsEqualsBuildsSuccessfully)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 3.14;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		TEST_METHOD(AssignmentOpCannotBeFollowedByInvalidToken)
		{
			//Arrange
			vector<string> testCase1;


			//[11/26/2017 03:41] Cameron Osborn: Check for invalid keywords after the ID_NAME token (14 errors)
			//[11/27/2017 01:37] Cameron Osborn: Errors double up in this section since keywords can't be used outside of the first token in a statement.
			testCase1.push_back("volume read;");
			testCase1.push_back("volume function;");
			testCase1.push_back("volume if;");
			testCase1.push_back("volume else;");
			testCase1.push_back("volume return;");
			testCase1.push_back("volume while;");
			testCase1.push_back("volume display;");

			//[11/26/2017 03:42] Cameron Osborn: Check for invalid logical operators after the ID_NAME token(3 errors). 			
			testCase1.push_back("volume ||8;");
			testCase1.push_back("volume &&8;");
			testCase1.push_back("volume !7;");


			//[11/26/2017 03:51] Cameron Osborn: Check for invalid relational operators after the ID_NAME token(6 errors)
			testCase1.push_back("volume >8;");
			testCase1.push_back("volume ==8;");
			testCase1.push_back("volume <8;");
			testCase1.push_back("volume >=8;");
			testCase1.push_back("volume <=8;");
			testCase1.push_back("volume !=8;");

			//[11/26/2017 03:53] Cameron Osborn: Check for invalid Numeric operators after the ID_NAME token(5 errors)
			testCase1.push_back("volume +8;");
			testCase1.push_back("volume -8;");
			testCase1.push_back("volume *8;");
			testCase1.push_back("volume /8;");
			testCase1.push_back("volume %8;");

			//[11/26/2017 03:58] Cameron Osborn: Check for invalid language reserved characters after the ID_NAME token(12 errors)
			testCase1.push_back("volume (8;");
			testCase1.push_back("volume );");
			testCase1.push_back("volume {;"); //Throws 2 errors
			testCase1.push_back("volume };"); //Throws 2 errors
			testCase1.push_back("volume ;;"); //Throws 2 errors
			testCase1.push_back("volume :;"); //Throws 2 errors
			testCase1.push_back("volume ,;"); //Throws 2 errors

			//[11/27/2017 17:47] Cameron Osborn: Check for invalid string and numeric literal after ID_NAME token(3 errors)
			testCase1.push_back("volume 3.14;");
			testCase1.push_back("volume \"heres some text\""); //Throws 2 errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(43, terp.GetErrorCount());
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
		TEST_METHOD(ReadOpFollowedByVariableNameBuildsSuccessfully)
		{
			//[11/26/2017 04:10] Cameron Osborn: First A3 covered above but rerun here for simplicity of code coverage eval.
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("read height;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		//[11/27/2017 14:12] Cameron Osborn: Read op can only be followed by ID_Name. All other tokens should throw error
		TEST_METHOD(ReadOpCannotBeFollowedByInvalidToken)
		{
			//Arrange
			vector<string> testCase1;


			//[11/26/2017 03:41] Cameron Osborn: Check for invalid keywords after the read token (7 errors)
			//[11/27/2017 01:37] Cameron Osborn: Errors double up in this section since keywords can't be used outside of the first token in a statement.
			testCase1.push_back("read read;");
			testCase1.push_back("read function;");
			testCase1.push_back("read if;");
			testCase1.push_back("read else;");
			testCase1.push_back("read return;");
			testCase1.push_back("read while;");
			testCase1.push_back("read display;");

			//[11/26/2017 03:42] Cameron Osborn: Check for invalid logical operators after the read token(2 errors). Unary operators (logical NOT) can follow the read statement.			
			testCase1.push_back("read ||;");
			testCase1.push_back("read &&;");


			//[11/26/2017 03:51] Cameron Osborn: Check for invalid relational operators after the read token(6 errors)
			testCase1.push_back("read >;");
			testCase1.push_back("read ==;");
			testCase1.push_back("read <;");
			testCase1.push_back("read >=;");
			testCase1.push_back("read <=;");
			testCase1.push_back("read !=;");

			//[11/26/2017 03:53] Cameron Osborn: Check for invalid Numeric operators after the read token(5 errors)
			testCase1.push_back("read +;");
			testCase1.push_back("read -;");
			testCase1.push_back("read *;");
			testCase1.push_back("read /;");
			testCase1.push_back("read %;");

			//[11/26/2017 03:58] Cameron Osborn: Check for invalid language reserved characters after the read token(7 errors)
			testCase1.push_back("read (;");
			testCase1.push_back("read );");
			testCase1.push_back("read {;");
			testCase1.push_back("read };");
			testCase1.push_back("read ;;");
			testCase1.push_back("read :;");
			testCase1.push_back("read ,;");


			//[11/26/2017 03:55] Cameron Osborn: Check for invalid assignment operator (=) after the read token (2 errors)
			//First error from invalid token after read, second error from invalid use of assignment operator.
			testCase1.push_back("read =;");

			//[11/27/2017 14:54] Cameron Osborn: Check for invalid numeric and string literals (2 errors)
			testCase1.push_back("read 3.14;");
			testCase1.push_back("read \"heres some text\";");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(30, terp.GetErrorCount());
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

		//[11/28/2017 04:31] Cameron Osborn: This "Display_SecondToken_{Test}_Fails" series tests ensure that the display token cannot be followed by any disallowed tokens.
		TEST_METHOD(Display_SecondToken_WhileKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display while;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_FunctionKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display function;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}
		TEST_METHOD(Display_SecondToken_IfKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display if;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_ElseKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display else;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_ReturnKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display return;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_DisplayKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display display;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_ReadKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display read;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_LogicalOROp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display || 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_LogicalANDOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display && 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_RelationalGreaterThanOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display > 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_RelationalEqualsOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display == 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_RelationalLessThanOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display < 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_RelationalGreaterThanEqualToOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display >= 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_RelationalLessThanEqualToOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display <= 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_RelationalNotEqualOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display != 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_NumericAddOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display +8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_NumericSubtractOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display -8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_NumericMultiplyOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display *8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_NumericDivisionOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display /8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_NumericModuloOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display %8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_RightParenthesis_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display );"); // expect 1 error

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_LeftCurlybrace_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display {;"); // expect 2 errors: second comes from invalid token in display statement

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_RightCurlybrace_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display };"); // expect 2 errors: second comes from invalid token in display statement

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_SemicolonMidLine_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display ;;"); // expect 2 errors: second comes from invalid token in display statement

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_Colon_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display :;"); // expect 2 errors: second comes from invalid token in display statement

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}
		TEST_METHOD(Display_SecondToken_Comma_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display ,;"); // expect 1 error

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_SecondToken_AssignmentOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display = 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		

		//[11/27/2017 18:48] Cameron Osborn: Check that an error is thrown for each statement type if semi colon does not appear at the end of the statement.
		TEST_METHOD(SemicolonMustAppearAtEndOfStatement)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check variable name after display statement. variable name must be initialized first. Should pass.
			testCase1.push_back("display 3.14");
			testCase1.push_back("read volume"); //Expect two errors because read must be 3 tokens long.
			testCase1.push_back("density = 1/2");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(4, terp.GetErrorCount());
		}

		//[11/27/2017 18:47] Cameron Osborn: Check that the semicolon token can't appear anywhere except at the end of the statement.
		TEST_METHOD(SemiColonCannotApperInMiddleOfStatement)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check variable name after display statement. variable name must be initialized first. Should pass.
			testCase1.push_back("display 3.14;+8;");
			testCase1.push_back("display \"Heres some text\";8+8;");
			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		//[11/28/2017 00:34] Cameron Osborn: Check whether a string literal in a display statement followed by comma or semicolon will successfully build.
		TEST_METHOD(Display_StringLit_FollowedByCommaOrSemiColonSucceeds)
		{
			//Arrange
			vector<string>testCase1;

			testCase1.push_back("display \"Heres some text\";");
			testCase1.push_back("display \"Heres some text\",8;");
			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}


		//[11/28/2017 04:32] Cameron Osborn: The "Display_StringLiteral_{test}_Fails" Series of tests checks that any string literal in a display statement cannot be followed by invalid tokens.
		TEST_METHOD(Display_StringLiteral_WhileKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  while;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_FunctionKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  function;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_IfKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  if;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_ElseKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  else;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_ReturnKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  return;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_DisplayKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  display;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_ReadKeyword_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  read;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_LogicalOROp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  || 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_LogicalANDOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  && 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_LogicalNOTOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  !1;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_RelationalGreaterThanOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  > 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_RelationalEqualsOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  == 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_RelationalLessThanOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  < 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_RelationalGreaterThanEqualToOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  >= 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_RelationalLessThanEqualTo_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  <= 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_RelationalNotEqual_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  != 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_NumericAddOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  +8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_NumericSubtractOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  -8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_NumericMultiplicationOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  *8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_NumericDivisionOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  /8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_NumericModuloOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  %8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_LeftParenthesis_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  (8;"); // expect 1 error

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_RightParenthesis_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  );"); // expect 1 error

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_LeftCurlybrace_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  {;"); // expect 2 errors: second comes from invalid token in display statement

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_RightCurlybrace_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  {;"); // expect 2 errors: second comes from invalid token in display statement

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_StringLiteral_Colon_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  :;"); // expect 2 errors: second comes from invalid token in display statement

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}
		
		TEST_METHOD(Display_StringLiteral_AssignmentOp_Fails)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display \"Heres some text\"  = 8;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		//[11/28/2017 00:34] Cameron Osborn: Check whether a numerical literal or variable evaluation will build. Assumption: Properly constructed equation follows the display statement.
		TEST_METHOD(Display_Evaluation_ValidTokensWillBuild)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check variable name after display statement. variable name must be initialized first. Should pass.
			testCase1.push_back("volume=8;");
			testCase1.push_back("display 8+(volume-3*(2/4))%2>2&&(((1+2)))<4||(4+5)==8&&!1||(0*1&&volume+2<=volume+3)||4>=volume&&2!=3;");
			testCase1.push_back("display 8+(volume-3*(2/4))%2>2&&1+2<4||(4+5)==8&&!1||(0*1&&volume+2<=volume+3)||4>=volume&&(2!=3);");
			testCase1.push_back("display 8+(volume-3*(2/4))%2>2&&(!((1+2)*24))<4||(4+5)==8&&!1||(0*1&&volume+2<=volume+3)||4>=volume&&2!=volume;");
			testCase1.push_back("display 8+(volume-3*(2/4))%2>2&&(((1+2)))<4||(4+5)==8&&!1||(0*1&&volume+2<=volume+3)||4>=volume&&2!=3, \"Thats a lot of numbers\";");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		//[11/28/2017 01:27] Cameron Osborn: Check that undefined variables in the display method are caught by the syntax check.
		TEST_METHOD(Display_Evaluation_UndefinedVariableThrowsError)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check variable name after display statement. variable name must be initialized first. Should pass.
			testCase1.push_back("volume=8;");
			testCase1.push_back("display v;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		//[11/28/2017 04:33] Cameron Osborn: The "Display_Evaluation_{Test}" series checks that numeric literals and variable names in a display statement cannot be followed by invalid characters.
		TEST_METHOD(Display_Evaluation_NumericLiteralLeftParenthesis)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display 8(8+8);");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_NumericLiteralKeyword)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display 8 while;"); // Throws two errors for use of keyword after first token

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_NumericLiteralAssignmentOp)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display 8 = 9;"); //Throws two errors for use of assignment operation in non-second 

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_NumericLiteralNumericLiteral)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display 8 9;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_NumericLiteralStringLiteral)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display 8 \"Thats a lot of numbers\";");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_NumericLiteralRightCurlybrace)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display 8};");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_NumericLiteralLeftCurlybrace)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display 8{;");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_NumericLiteralColon)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("display 8:;");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_VariableLeftParenthesis)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("display volume(8+8);");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_VariableKeyword)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("display volume while;"); // Throws two errors for use of keyword after first token

																							 //Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_VariableAssignmentOp)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("display volume = 9;"); //Throws two errors for use of assignment operation in non-second 

																						 //Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_VariableNumericLiteral)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("display volume 9;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_VariableStringLiteral)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("display volume \"Thats a lot of numbers\";");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_VariableRightCurlybrace)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("display volume};");//Throws two errors

																				 //Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_VariableLeftCurlybrace)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("display volume{;");//Throws two errors

																				 //Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Display_Evaluation_VariableColon)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("display volume:;");//Throws two errors

																				 //Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		//[11/28/2017 02:00] Cameron Osborn: The only category for display that isn't explicitly stated in testing beside string literal and evaluation is the comma character but both of its unit tests are invoked in the above testing for string literals and evaluations.
		TEST_METHOD(Assignment_Evaluation_ValidTokensWillBuild)
		{
			//Arrange
			vector<string>testCase1;

			//[11/26/2017 03:42] Cameron Osborn: Check variable name after display statement. variable name must be initialized first. Should pass.
			testCase1.push_back("volume=8;");
			testCase1.push_back("density = 8+(volume-3*(2/4))%2>2&&(((1+2)))<4||(4+5)==8&&!1||(0*1&&volume+2<=volume+3)||4>=volume&&2!=3;");
			testCase1.push_back("density = 8+(volume-3*(2/4))%2>2&&1+2<4||(4+5)==8&&!1||(0*1&&volume+2<=volume+3)||4>=volume&&(2!=3);");
			testCase1.push_back("density = 8+(volume-3*(2/4))%2>2&&(!((1+2)*24))<4||(4+5)==8&&!1||(0*1&&volume+2<=volume+3)||4>=volume&&2!=volume;");
			testCase1.push_back("density = 8+(volume-3*(2/4))%2>2&&(((1+2)))<4||(4+5)==8&&!1||(0*1&&volume+2<=volume+3)||4>=volume&&2!=3;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsTrue(terp.BuildStatus);
		}

		//[11/28/2017 04:34] Cameron Osborn: The "Assignment_Evaluation_{TestName}" Series of tests ensures that numeric literals and variables on the right hand side of an assignment operator are not followed by an invalid character.
		TEST_METHOD(Assignment_Evaluation_NumericLiteralLeftParen)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = 8(8+8);");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_NumericLiteralKeyword)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = 8 while;"); // Throws two errors for use of keyword after first token

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evalution_NumericLiteralAssignmentOp)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = 8 = 9;"); //Throws two errors for use of assignment operation in non-second 

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}
		TEST_METHOD(Assignment_Evalution_NumericLiteralNumericLiteral)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = 8 9;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_NumericLiteralStringLiteral)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = 8 \"Thats a lot of numbers\";"); //Throws 2

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_NumericLiteralRightCurlybrace)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = 8};");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_NumericLiteralLeftCurlyBrace)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = 8{;");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_NumericLiteralColon)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = 8:;");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_NumericLiteralComma)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = 8,;");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}




		TEST_METHOD(Assignment_Evaluation_VariableLeftParen)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = volume(8+8);");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_VariableKeyword)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = volume while;"); // Throws two errors for use of keyword after first token

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evalution_VariableAssignmentOp)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = volume = 9;"); //Throws two errors for use of assignment operation in non-second 

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}
		TEST_METHOD(Assignment_Evalution_VariableNumericLiteral)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = volume 9;");

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(1, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_VariableStringLiteral)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = volume \"Thats a lot of numbers\";"); //Throws 2

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_VariableRightCurlybrace)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = volume};");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_VariableLeftCurlyBrace)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = volume{;");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_VariableColon)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = volume:;");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}

		TEST_METHOD(Assignment_Evaluation_VariableComma)
		{
			//Arrange
			vector<string>testCase1;
			testCase1.push_back("volume = 8;");
			testCase1.push_back("density = volume,;");//Throws two errors

			//Act
			terp.parseSourceCode(testCase1, false, false);

			//Assert
			Assert::IsFalse(terp.BuildStatus);
			Assert::AreEqual(2, terp.GetErrorCount());
		}
	};
}
