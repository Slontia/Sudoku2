#pragma once
#include "stdafx.h"

bool guess_value(Box* box, Subject_sudoku* sudoku, int solution[SIZE * SIZE]);

bool fill_sudoku(Subject_sudoku* sudoku, int solution[SIZE * SIZE]);