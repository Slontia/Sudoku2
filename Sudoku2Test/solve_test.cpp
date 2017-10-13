#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
int solution[SIZE * SIZE] = { 0 };
int result_solve[SUDOKU_MAX][SIZE * SIZE] = { 0 };
int row_record[9] = { 0 }; // must be 511
int column_record[9] = { 0 };
int block_record[9] = { 0 };

namespace Sudoku2Test
{
	TEST_CLASS(UnitTest2)
	{
	public:

		void test_s(int puzzle[], bool resolvable) {
			int bit;

			int counter = 0;

			Core core;

			bool success = core.solve(puzzle, solution);
			Assert::AreEqual(resolvable, success);
			if (!success) {
				return;
			}
			for (int rowno = 0; rowno < SIZE; rowno++) {
				for (int columnno = 0; columnno < SIZE; columnno++) {
					bit = (1 << (solution[GET_POS(rowno, columnno)] - 1));
					row_record[rowno] |= bit;
					column_record[columnno] |= bit;
					block_record[GET_BLOCKNO(rowno, columnno)] |= bit;
				}
			}

			// judge & initial
			for (int i = 0; i < 9; i++) {
				Assert::AreEqual(511, row_record[i]);
				Assert::AreEqual(511, column_record[i]);
				Assert::AreEqual(511, block_record[i]);
				row_record[i] = 0;
				column_record[i] = 0;
				block_record[i] = 0;
			}
			counter++;
		}

		TEST_METHOD(solve)
		{
			// TODO: 在此输入测试代码
			int mat_input[SIZE*SIZE] =
			{
				1, 2, 3, 0, 0, 0, 0, 0, 0,
				4, 5, 6, 0, 0, 0, 0, 0, 0,
				7, 8, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0
			};
			test_s(mat_input, true);
		}

		TEST_METHOD(solve2)
		{
			// TODO: 在此输入测试代码
			int mat_input[SIZE*SIZE] =
			{
				1, 0, 0, 0, 0, 0, 0, 0, 0,
				2, 0, 0, 0, 0, 0, 0, 0, 0,
				3, 0, 0, 0, 0, 0, 0, 0, 0,
				4, 0, 0, 0, 0, 0, 0, 0, 0,
				5, 0, 0, 0, 0, 0, 0, 0, 0,
				6, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 1, 2, 3, 4, 5, 6
			};
			test_s(mat_input, false);
		}

		TEST_METHOD(good_file) {
			FILE* ftest = fopen("puzzle.txt", "w");
			Core core;
			fputs(
				"4 1 7 2 3 8 6 5 9\n\
				3 2 6 4 9 5 8 1 7\n\
				9 5 8 7 1 6 3 2 4\n\
				6 9 1 8 5 2 7 4 3\n\
				8 4 2 9 7 3 1 6 5\n\
				7 3 5 6 4 1 9 8 2\n\
				1 8 3 5 2 7 4 9 6\n\
				2 7 9 1 6 4 5 3 8\n\
				5 6 4 3 8 9 2 7 1"
				, ftest);
			fclose(ftest);
			bool test_result = false;
			try {
				core.input_file("puzzle.txt", result_solve);
				test_result = true;
			}
			catch(Exception* e){
				
			}
			Assert::IsTrue(test_result);
		}
	
		TEST_METHOD(incompleted_sudoku) {
			FILE* ftest = fopen("puzzle.txt", "w");
			Core core;
			fputs(
				"4 1 7 2 3 8 6 5 9\n\
				3 2 6 4 9 5 8 1 7\n\
				9 5 8 7 1 6 3 2 4\n\
				6 9 1 8 5 2 7 4 3\n\
				8 4 2 9 7 3 1 6 5\n\
				7 3 5 6 4 1 9 8 2\n\
				1 8 3 5 2 7 4 9 6\n\
				2 7 9 1 6 4 5 3 8\n\
				5 6 4 3 8 9 2 7 b"
				, ftest);
			fclose(ftest);
			bool test_result = false;
			try {
				core.input_file("puzzle.txt", result_solve);
			}
			catch (BadFileException* e) {
				test_result = true;
			}
			Assert::IsTrue(test_result);
		}

		TEST_METHOD(unexpected_character) {
			FILE* ftest = fopen("puzzle.txt", "w");
			Core core;
			fputs(
				"4 1 7 2 3 8 6 5 9\n\
				3 2 6 4 9 5 8 1 7\n\
				9 5 8 7 1 6 3 2 4\n\
				6 9 1 8 5 2 7 4 3\n\
				8 4 2 9 7 3 1 6 5\n\
				7 3 5 6 4 1 9 8 2\n\
				1 8 3 5 2 7 4 9 6\n\
				2 7 9 1 6 4 5 3 8\n\
				5 6 4 3 8 9 2 7 "
				, ftest);
			fclose(ftest);
			bool test_result = false;
			try {
				core.input_file("puzzle.txt", result_solve);
			}
			
			catch (BadFileException* e) {
				test_result = true;
			}
			Assert::IsTrue(test_result);
		}

		TEST_METHOD(cannot_open) {
			bool test_result = false;
			Core core;
			try {
				core.input_file("puz.txt", result_solve);
			}
			catch (CannotOpenFileException* e) {
				test_result = true;
			}
			Assert::IsTrue(test_result);
		}
	};
}