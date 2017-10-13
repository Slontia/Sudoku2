#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Sudoku2Test
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(command_exception0) {
			bool test_result = false;
			int argc = 4;
			char* argv[10] = {
				"sudoku.exe",
				"-c",
				"100",
				"-s"
			};
			try {
				read_command(argc, argv);
			}
			catch (InvalidCommandException*) {
				test_result = true;
			}
			Assert::IsTrue(test_result);
		}

		TEST_METHOD(command_exception1) {
			bool test_result = false;
			int argc = 4;
			char* argv[10] = {
				"sudoku.exe",
				"-s",
				"100",
				"-c"
			};
			try {
				read_command(argc, argv);
			}
			catch (InvalidCommandException*) {
				test_result = true;
			}
			Assert::IsTrue(test_result);
		}

		TEST_METHOD(nr0) {
			bool test_result = true;
			int argc = 6;
			char* argv[10] = {
				"sudoku.exe",
				"-u",
				"-n",
				"1",
				"-r",
				"55~55"
			};
			try {
				read_command(argc, argv);
			}
			catch (InvalidCommandException*) {
				test_result = false;
			}
			Assert::IsTrue(test_result);
		}

		TEST_METHOD(command_exception2) {
			bool test_result = false;
			int argc = 6;
			char* argv[10] = {
				"sudoku.exe",
				"-u",
				"-n",
				"1",
				"-m",
				"1"
			};
			try {
				read_command(argc, argv);
			}
			catch (InvalidCommandException*) {
				test_result = true;
			}
			Assert::IsTrue(test_result);
		}

		TEST_METHOD(command_exception3) {
			bool test_result = false;
			int argc = 6;
			char* argv[10] = {
				"sudoku.exe",
				"-m",
				"100",
				"-n",
				"1",
				"-m",
				"1"
			};
			try {
				read_command(argc, argv);
			}
			catch (InvalidCommandException*) {
				test_result = true;
			}
			Assert::IsTrue(test_result);
		}

	};
}