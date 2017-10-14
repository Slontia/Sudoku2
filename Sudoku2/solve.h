#pragma once
#include "stdafx.h"

bool guess_value(Box* box, Subject_sudoku* sudoku, int solution[SIZE * SIZE], bool unique = false);

bool fill_sudoku(Subject_sudoku* sudoku, int solution[SIZE * SIZE], bool unique = false);

void validity_judge(int puzzle[SIZE * SIZE]);

int solve(int puzzle[][SIZE * SIZE], int solution[][SIZE * SIZE], int number,
	int insolvable_recorder[]);