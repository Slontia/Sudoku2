#pragma once

#include <iostream>
#define SIZE 9

using namespace std;

int get_unique_solution_puzzle(int puzzle[SIZE * SIZE],
	int lower, int upper, int sudoku[SIZE * SIZE] = NULL);
void clean_each_block_grids(int clean_count, int puzzle[SIZE * SIZE]);
int get_puzzle(int sudoku[SIZE * SIZE], int puzzle[SIZE * SIZE], 
	int lower, int upper);
int get_puzzle(int puzzle[SIZE * SIZE], int lower, int upper);
void set_number_randomly(int sudoku[SIZE * SIZE]);
bool create_final_sudoku(int sudoku[SIZE * SIZE]);
int create_puzzle(int puzzle[SIZE * SIZE],
	int lower, int upper);
int create_puzzle(int sudoku[SIZE * SIZE], int puzzle[SIZE * SIZE],
	int lower, int upper);