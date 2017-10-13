#include "stdafx.h"

int solution_count = 0;

bool guess_value(Box* box, Subject_sudoku* sudoku, int solution[SIZE * SIZE], bool unique) {
	int rowno = box->row->number;
	int columnno = box->column->number;
	for (int i = 0; i < SIZE; i++) {
		if (box->posvalue & get_valuebit(i)) { // -- value i+1 is possible
											   //Subject_sudoku* new_sudoku = new Subject_sudoku(*sudoku);
			Box* box = sudoku->getbox(rowno, columnno);
			int members_posvalues[3][9];
			int posvalue = box->make_certain(i + 1, members_posvalues);
			if (fill_sudoku(sudoku, solution, unique)) {
				return true;
			}
			box->cancel_certain(posvalue, members_posvalues);
		}
	}
	return false;
}

bool fill_sudoku(Subject_sudoku* sudoku, int solution[SIZE * SIZE], bool unique){ // -- succeed(true) or failed(false)
	Box* box;
	box = sudoku->get_minpos_box();
	if (box == NULL) {
		sudoku->to_array(solution);
		if (unique == false) {
			return true;
		}
		else {
			display_1d(solution, 81, 9);
			solution_count++;
			return false;
		}
	}
	return guess_value(box, sudoku, solution, unique);
}

bool Core::solve(int puzzle[SIZE * SIZE], int solution[SIZE * SIZE]) {
	Subject_sudoku* sudoku;
	sudoku = new Subject_sudoku(puzzle);
	if (!fill_sudoku(sudoku, solution, false)) {
		return false;
	};
	delete(sudoku);
	return true;
}

int Core::solve(int puzzle[][SIZE * SIZE], int solution[][SIZE * SIZE], int number,
	int insolvable_recorder[]) {
	int solutions_counter = 0;

	int insolvable_counter = 0;
	for (int i = 0; i < number; i++) {
		if (solve(puzzle[i], solution[solutions_counter])) {
			solutions_counter++;
		}
		else {
			insolvable_recorder[insolvable_counter++] = i;
		}
	}
	return solutions_counter;
}