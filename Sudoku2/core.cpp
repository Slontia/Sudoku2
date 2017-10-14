#include "stdafx.h"
#include <time.h>

Core::Core() {
	//srand(time(0));
	srand((int)time(0));
	srand(0);
}

int Core::input_file(char* filename, int output[][SIZE * SIZE]) {
	int sudoku_counter = 0;
	int digit_counter = 0;
	FILE* fin = fopen(filename, "r");

	if (fin == NULL) {
		throw new CannotOpenFileException(FILE_ERROR);
	}

	char buffer[BUFFER_SIZE + 10];

	while (fgets(buffer, BUFFER_SIZE, fin) != NULL) {
		for (int i = 0; i < BUFFER_SIZE; i++) {
			char c = buffer[i];
			if (c == '\0') {
				break;
			}
			else if (c >= '0' && c <= '9') {
				if (digit_counter == SIZE * SIZE) {
					digit_counter = 0;
					sudoku_counter++;
				}
				output[sudoku_counter][digit_counter++] = c - '0';
			}
			else if (c != '\n' && c != '\r' && c != ' ' && c != '\t') {
				throw new BadFileException((string)"Unexpected character: '" + c + "'");
			}
		}
	}
	if (digit_counter != SIZE * SIZE) {
		throw new BadFileException("Incomplete sudoku!");
	}
	fclose(fin);
	return sudoku_counter + 1;
}


void Core::output_file(char* filename, int input[][SIZE * SIZE], int sudoku_number) {
	FILE* fout = fopen(filename, "w");

	if (fout == NULL) {
		throw new CannotOpenFileException(FILE_ERROR);
	}

	char buffer[BUFFER_SIZE];

	int buffer_index = 0;
	for (int sudoku_index = 0; sudoku_index < sudoku_number; sudoku_index++) {
		for (int digit_index = 0; digit_index < SIZE * SIZE; digit_index++) {
			buffer[buffer_index++] = input[sudoku_index][digit_index] + '0';
			if (digit_index % SIZE == SIZE - 1) {
				buffer[buffer_index++] = '\n';
			}
			else {
				buffer[buffer_index++] = ' ';
			}
		}
		buffer[buffer_index++] = '\n';
		if (buffer_index >= BUFFER_SIZE - 300) {
			buffer[buffer_index++] = '\0';
			fputs(buffer, fout);
			buffer_index = 0;
		}
	}
	fputs(buffer, fout);
	fclose(fout);
}