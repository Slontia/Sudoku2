#include "stdafx.h"
#include "CppUnitTest.h"


int result[SUDOKU_MAX][SIZE*SIZE];
int puzzle[SUDOKU_MAX][SIZE*SIZE];
int insolvable_recorder[SOLVE_COUNT_MAX];
FILE* fout;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Sudoku2Test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		typedef struct node {
			bool isbottom;
			int depth;
			string* sudoku;
			struct node* ptrs[9];
		}Treenode;

		Treenode* create_treenode(int depth, string* sudoku) {
			Treenode* p = (Treenode*)malloc(sizeof(Treenode));
			p->isbottom = true;
			p->depth = depth;
			p->sudoku = sudoku;
			for (int i = 0; i < 9; i++) {
				p->ptrs[i] = NULL;
			}
			return p;
		}

		void add_sudoku_to_tree(int depth, Treenode** p, string* sudoku) {
			if ((*p) == NULL) {
				(*p) = create_treenode(depth, sudoku);
			}
			else {
				if ((*((*p)->sudoku)).length() > 0) {
					if ((*sudoku).compare(*((*p)->sudoku)) == 0) {
						fclose(fout);
					}
					Assert::AreNotEqual(*sudoku, *((*p)->sudoku));
					add_sudoku_to_tree(depth + 1, &((*p)->ptrs[(*((*p)->sudoku))[depth + 1] - '1']), ((*p)->sudoku));
					(*p)->sudoku = new string("");
				}
				add_sudoku_to_tree(depth + 1, &((*p)->ptrs[(*sudoku)[depth + 1] - '1']), sudoku);
			}
		}

		void repeated_judge(int number, int result[][SIZE * SIZE]) {
			int row_record[9] = { 0 }; // must be 511
			int column_record[9] = { 0 };
			int block_record[9] = { 0 };

			int bit;

			string* sudoku;
			Treenode* root = create_treenode(-1, new string(""));
			int counter = 0;

			for (int i = 0; i < number; i++) {
				sudoku = new string();
				int* sudoku_ptr = result[i];
				for (int j = 0; j < SIZE; j++) {
					for (int k = 0; k < SIZE; k++) {
						int digit;
						digit = sudoku_ptr[GET_POS(j, k)];
						(*sudoku) += digit + '0';
						bit = (1 << (digit - 1));
						row_record[j] |= bit;
						column_record[k] |= bit;
						block_record[(j / 3) * 3 + k / 3] |= bit;
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

				char digit_map[SIZE];
				for (int i = 0; i < SIZE; i++) {
					digit_map[i] = (*sudoku)[i]; // build map
				}
				/* change to equivalence */
				for (int i = 0; i < SIZE * SIZE; i++) {
					(*sudoku)[i] = digit_map[(*sudoku)[i] - '1']; 
				}

				add_sudoku_to_tree(-1, &root, sudoku);
				counter++;
			}
		}

		
		void unique_solution_judge(int number, int puzzle[][SIZE * SIZE]) {
			for (int i = 0; i < number; i++) {
				Assert::IsTrue(generator_solve_sudoku(puzzle[i]));
			}
		}


		void test_c(int number) {
			Core core;
			core.generate(number, result);
			repeated_judge(number, result);
		}

		void test_n(int number, int lower, int upper, bool unique) {
			Core core;
			core.generate(number, lower, upper, unique, result);
			//core.output_file("sudoku.txt", result, number);
			unique_solution_judge(number, result);
			int solved_count = core.solve(result, result, number, insolvable_recorder);
			Assert::AreEqual(number, solved_count);
			repeated_judge(number, result);
			//core.output_file("sudoku2.txt", result, number);
		}


		TEST_METHOD(create){
			test_c(10000);
		}

		TEST_METHOD(puzzle){
			test_n(100, 40, 48, true);
		}

	};
}