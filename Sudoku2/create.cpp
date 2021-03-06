#include "stdafx.h"

void roll_int(int i_array[], int len) {
	if (i_array == NULL || len == 0) { // if NULL or empty, return
		return;
	}
	int first = i_array[0];
	int i;
	for (i = 0; i < len - 1; i++) {		// go through i_array from the 2nd element
		i_array[i] = i_array[i + 1];	// move char backward
	}
	i_array[i] = first;
}

void fill_line_to_sudoku(int* grid, int line[BLOCK_SIZE]) {
	for (int i = 0; i < BLOCK_SIZE; i++) {
		(*grid) = line[i];
		grid++;
	}
}

void initial_sudoku(int sudoku[SIZE][SIZE]){
	int position_seed[] = POSITION_SEED;
	int base_line[] = BASE_LINE;
	for (int i = 0; i < BLOCK_SIZE; i++) { // each type of base line
		for (int rowno = 0; rowno < SIZE; rowno += BLOCK_SIZE) { // rowno of 0 3 6
			for ( // colno of 0 3 6, j go through position seed
				int colno = 0, j = 0; 
				colno < SIZE; 
				colno += BLOCK_SIZE, j++
			) { 
				fill_line_to_sudoku(
					&(sudoku[rowno + position_seed[j]][colno]), 
					base_line
				); // fill
			}
			roll_int(base_line, BLOCK_SIZE); // roll base_line
		}
		for (int k = 0; k < BLOCK_SIZE; k++) { // each element in base_line +=3
			base_line[k] += BLOCK_SIZE;
		}
		roll_int(position_seed, BLOCK_SIZE); // roll position_seed
	}
}

void initial_exchanger(Exchanger* exchangers[EXCHANGER_COUNT], int sudoku[SIZE][SIZE]) {
	int* perms[EXCHANGER_GROUPS_COUNT][EXCHANGER_GROUPS_SIZE];
	int i = 0;
	/* create */
	for (int j = ORIGIN; j < SIZE; j += BLOCK_SIZE) {
		for (int k = 0; k < BLOCK_SIZE; k++) {
			for (int groupno = 0; groupno < EXCHANGER_GROUPS_COUNT; groupno++) {
				for (int memberno = 0; memberno < EXCHANGER_GROUPS_SIZE; memberno++) {
					perms[groupno][memberno] = &(sudoku[j + memberno][k + groupno * 3]);
				}
			}
			exchangers[i++] = new Exchanger(perms);
		}
	}
	/* link */
	for (int j = 0; j < EXCHANGER_COUNT - 1; j++) {
		exchangers[j]->next = exchangers[j + 1];
	}
}

void output_sudoku(int sudoku[SIZE][SIZE], int result[SIZE*SIZE]) {
	int i = 0;
	for (int j = 0; j < SIZE; j++) {
		for (int k = 0; k < SIZE; k++) {
			result[i++] = sudoku[j][k];
			//cout << sudoku[j][k];
		}
	}
}

void Core::generate(int number, int result[][SIZE*SIZE])
{
	int sudoku[SIZE][SIZE] = { 0 };
	Exchanger* exchangers[EXCHANGER_COUNT];
	/* initial */
	initial_sudoku(sudoku);
	initial_exchanger(exchangers, sudoku);
	/* create */
	Exchanger* head_exchanger = exchangers[0];
	for (int count = 0; count < number; count++)	// (for each result)
	{	
		output_sudoku(sudoku, result[count]);	// -- write to result[][]
		head_exchanger->change2next();			// -- change the sudoku
	}
}