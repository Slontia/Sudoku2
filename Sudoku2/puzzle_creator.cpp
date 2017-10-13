#include "stdafx.h"
#include <iostream>
#include <time.h>
#include "puzzle_creator.h"
//#include "solve.cpp"

#define FREE_GRIDS_COUNT 55
#define GET_GRID_WITH_BLOCKNO(blockno, position) (((blockno / 3) * 3 + position / 3) * 9 + ((blockno % 3) * 3 + position % 3))

#define DIFFICULTY_COUNT 3
#define LOWERS {30, 40, 48}
#define UPPERS {39, 47, 55}

using namespace std;

void Core::generate(int number, int mode, int result[][SIZE * SIZE]) {
	int lowers[DIFFICULTY_COUNT] = LOWERS;
	int uppers[DIFFICULTY_COUNT] = UPPERS;
	int lower = lowers[mode - 1];
	int upper = uppers[mode - 1];

	for (int i = 0; i < number; i++) {
		get_unique_solution_puzzle(result[i], lower, upper);
	}
}

void Core::generate(int number, int lower, int upper, bool unique, int result[][SIZE * SIZE]) {
	if (unique) {
		for (int i = 0; i < number; i++) {
			get_unique_solution_puzzle(result[i], lower, upper);
		}
	}
	else {
		for (int i = 0; i < number; i++) {
			get_puzzle(result[i], lower, upper);
		}
	}
}

int get_unique_solution_puzzle(int puzzle[SIZE * SIZE],
	int lower, int upper, int sudoku[SIZE * SIZE]) {
	bool unique;
	int all_freebox_num;
	do {
		if (sudoku == NULL) {
			all_freebox_num = get_puzzle(puzzle, lower, upper);
		}else {
			all_freebox_num = get_puzzle(sudoku, puzzle, lower, upper);
		}
		Subject_sudoku* sub_sudoku = new Subject_sudoku(puzzle);
		int solution_counter = 0;
		unique = generator_fill_sudoku(sub_sudoku, solution_counter);
		delete sub_sudoku;
	} while (!unique);
	return all_freebox_num;
}


int get_puzzle(int sudoku[SIZE * SIZE], int puzzle[SIZE * SIZE], 
	int lower, int upper) {
	do {
		for (int i = 0; i < SIZE*SIZE; i++) { // initialize
			sudoku[i] = 0;
		}
		set_number_randomly(sudoku); // set numbers
	} while (!create_final_sudoku(sudoku)); // create final sudoku
	/*for (int i = 0; i < SIZE* SIZE; i++) { // copy to puzzle
		puzzle[i] = sudoku[i];
	}
	return create_puzzle(puzzle, lower, upper); // clean grids*/
	return create_puzzle(sudoku, puzzle, lower, upper);
}


int get_puzzle(int puzzle[SIZE * SIZE], int lower, int upper) {
	do {
		for (int i = 0; i < SIZE*SIZE; i++) { // initialize
			puzzle[i] = 0;
		}
		set_number_randomly(puzzle); // set numbers
	} while (!create_final_sudoku(puzzle)); // create final sudoku
	return create_puzzle(puzzle, lower, upper); // clean grids
}


void set_number_randomly(int sudoku[SIZE * SIZE]) {
	int position;
	for (int i = 1; i <= SIZE; i++) { // randomly fill 1~9
		position = rand() % (SIZE * SIZE);
		sudoku[position] = i;
	}
}


bool create_final_sudoku(int sudoku[SIZE * SIZE]) {
	Subject_sudoku* unsolving_sudoku = new Subject_sudoku(sudoku);
	bool result = fill_sudoku(unsolving_sudoku, sudoku);
	delete unsolving_sudoku;
	return result;
}

int create_puzzle(int sudoku[SIZE * SIZE], int puzzle[SIZE * SIZE],
	int lower, int upper) {
	if (lower > upper || lower < 0 || upper > SIZE * SIZE) {
		return 0;
	}
	int all_freebox_num = (rand() % (upper - lower + 1)) + upper;
	int freebox_num = all_freebox_num - dig(sudoku, puzzle, all_freebox_num);

	if (freebox_num == 0) {
		return all_freebox_num;
	}

	int cleaned_recorder_int[SIZE] = { 0 }; // for blocks
	int cleaned_counter[SIZE] = { 0 }; // for blocks
	for (int blockno = 0; blockno < SIZE; blockno++) { // each block
		for (int pos = 0; pos < SIZE; pos++) { // each grid in the block
			int digit = puzzle[GET_GRID_WITH_BLOCKNO(blockno, pos)];
			if (digit == 0) {
				cleaned_recorder_int[blockno] |= (1 << pos);
				cleaned_counter[blockno]++;
			}
		}
	}

	for (int i = 0; i < freebox_num; i++) {
		int min_cleaned_blockno = -1;
		int min_cleaned_count = SIZE + 1;
		for (int j = 0; i < SIZE; j++) {
			int count = cleaned_counter[j];
			if (count <= min_cleaned_count) {
				min_cleaned_blockno = j;
				min_cleaned_count = count;
			}
		}
		int free_position = rand() % (SIZE - min_cleaned_count);
		int free_digit_index = 0;
		int digit_index;
		for (digit_index = 0; digit_index < SIZE; digit_index++) { // find uncleaned grid
			if ((!(cleaned_recorder_int[min_cleaned_blockno] & (1 << digit_index))) && // uncleaned?
				(free_position == free_digit_index++) // the right position?
				) {
				break;
			}
		}
		puzzle[GET_GRID_WITH_BLOCKNO(i, digit_index)] = 0;
		cleaned_recorder_int[min_cleaned_blockno] |= (1 << digit_index);
		cleaned_counter[min_cleaned_blockno]++;
	}

}



void clean_each_block_grids(int clean_count, int puzzle[SIZE * SIZE]) {
	int cleaned_recorder_int;
	for (int i = 0; i < SIZE; i++) { // each block
		cleaned_recorder_int = 0;
		for (int j = 0; j < clean_count; j++) { // each grid to clean
			int free_position = rand() % (SIZE - j);
			int free_digit_index = 0;
			int digit_index;
			for (digit_index = 0; digit_index < SIZE; digit_index++) { // find uncleaned grid
				if ((!(cleaned_recorder_int & (1 << digit_index))) &&
					(free_position == free_digit_index++)
				) {
					break;
				}
			}
			puzzle[GET_GRID_WITH_BLOCKNO(i, digit_index)] = 0;
			cleaned_recorder_int |= (1 << digit_index);
		}
	}
}





int create_puzzle(int puzzle[SIZE * SIZE], int lower, int upper) {
	if (lower > upper || lower < 0 || upper > SIZE * SIZE) {
		return 0;
	}
	int all_freebox_num = (rand() % (upper - lower + 1)) + upper;
	int clean_block_grids_count = all_freebox_num / SIZE;
	int freebox_num = all_freebox_num - SIZE * clean_block_grids_count;

	clean_each_block_grids(clean_block_grids_count, puzzle);

	int randpos;
	for (int i = 0; i < freebox_num; i++) {
		do {
			randpos = rand() % (SIZE * SIZE);
		} while (puzzle[randpos] == 0);
		puzzle[randpos] = 0;
	}
	return all_freebox_num;
}