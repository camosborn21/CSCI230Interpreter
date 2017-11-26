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
		//string tc1 = "display \"************************************************\";\ndisplay \"Want to determine the volume of a right circular cylinder!\";\ndisplay \"\";\ndisplay \"What is the height of the cylinder? \";\nread height;\ndisplay \"What is the radius of the cylinder? \";\nread radius;\nvolume = 3.14* radius * radius * height;\ndisplay \"\";\ndisplay \"The volume of the cylinder is \", volume;\ndisplay \"************************************************\";";
		

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

	};
}
