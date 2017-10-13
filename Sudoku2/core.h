#pragma once

class __declspec(dllexport) Core {

public:
	Core();

	/* -c */
	void generate(int number, int result[][SIZE * SIZE]);

	/* -s */
	bool solve(int puzzle[SIZE * SIZE], int solution[SIZE * SIZE]);
	int solve(int puzzle[][SIZE * SIZE], int solution[][SIZE * SIZE], int number);

	/* -n -r -u */
	void generate(int number, int lower, int upper, bool unique, int result[][SIZE * SIZE]);

	/* -n -m */
	void generate(int number, int mode, int result[][SIZE * SIZE]);

	/* file */
	int input_file(char* filename, int output[][SIZE * SIZE]);
	void output_file(char* filename, int input[][SIZE * SIZE], int sudoku_number);
};


